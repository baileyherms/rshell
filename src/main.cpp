//main file for rshell
#include <iostream>
#include <string>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;
using namespace boost;

//make functions



void get_input(string usr_input)
{
	char arr[10000];//tokenize
	for(int i = 0; i < usr_input.size(); i++)
	{
		arr[i] = usr_input[i];
	}
	char* argv[10000];
	char* tok = strtok(arr, " \t");
	char* argu[10000];// = {0};
	char* conn[10000];
	vector<int> cmd_arg_amt;
	int x = 0;
	while(tok != NULL)
	{
		argv[x] = tok;
		x++;
		tok = strtok(NULL, " ");
	}
	argv[x] = '\0';
	int con_amount = 0;
	int hold_amt = 0;
	int store = 0;
	for(int i = 0; i < x; i++)
	{
	//	cout << "argv " << argv[i] << endl;
		if(strcmp(argv[i], "&&") || strcmp(argv[i], "||") || strcmp(argv[i], ";"))
		{
			cmd_arg_amt.push_back(hold_amt);//push back the number of arguments for a certain command
		//	cout << "cmd " << argv[i] << endl;
			hold_amt = 0;
			conn[con_amount] = argv[i];
			con_amount++;
		}
		else if(argv[i] == "#")
		{
			cmd_arg_amt.push_back(hold_amt);
			hold_amt = 0;
			conn[con_amount] = argv[i];
			con_amount++;
			break;
		}
		else
		{
			/*cout << "Here " << endl;
			cout << i << endl;
			argu[store] = argv[i];
			store++;
			hold_amt++;*/
		}
	
	}
	if(hold_amt > 0)
	{
		cmd_arg_amt.push_back(hold_amt);
		hold_amt = 0;
	}
	int argu_amt = 0;
	bool working = true; //check if command is working
	bool in_command = false;
	bool com_end = false;
	int a = 0;
	int place = 0;
	int executive;
	while(a <= cmd_arg_amt.size() && !com_end)
	{
		char* run[1000];
		int b = 0;
		bool broken = false;
		/*
		while(!broken && argv[place] != NULL)
		{
		//	cout << "place " << place << endl;
		//	cout << "argu " << argv[place] << endl;	
			if(argv[place] == '\0')
			{
				broken = true;
				break;
			}
			else if(!strcmp(argv[place], "&&") && !strcmp(argv[place], "||") && !strcmp(argv[place], ";") && !strcmp(argv[place], "#"))
			{
				run[b] = argv[place];
				cout << "Now " << endl;
				b++;
			}
			else
			{
				broken = true;
				break;
			}
			place++;
		}
		run[b] = '\0';
		*/
		
		//int b = 0;
		while(argv[place] != NULL && argv[place] != ";" && argv[place] != "||" && argv[place] != "&&" && argv[place] != "#")
		{
			run[b] = argv[place];
			b++;
			place++;
			//cout << run[b] << endl;
		}

		run[b] = NULL;
		int pid = fork();
		if(pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if(pid == 0)
		{
			executive = execvp(run[0], run);
			if(executive == -1)
			{
				perror("execvp");
				exit(1);
			}
		}
		else if(pid > 0)
		{
			if(-1 == wait(0))
			{
				perror("wait");
			}
		}
		if(a >= con_amount)
		{
			//cout << "Here" << endl;
			break;
		}
		else if(conn[a] == "&&")
		{
			if(executive == -1)
			{
				com_end = true;
				break;
			}
		}
		else if(conn[a] == "||")
		{
			if(executive != -1)
			{
				com_end = true;
				break;
			}
		}
		else if(conn[a] == ";")
		{
		}
		else if(conn[a] == "#")
		{
			working = false;
			com_end = true;
			break;
		}

		a++;
	}
		
}

void output()
{
	char host[255];
	string login = getlogin();
	gethostname(host, 255);
	cout << login << "@" << host << " ";
	string usr_input;
	cout << "$";
	cout << " ";
	getline(cin, usr_input);
	get_input(usr_input);
}

int main(int argc, char *argv[])
{
	while(1)
	{
		output();
		//get_input();
	}
	return 0;
}
