//main file for rshell
#include <iostream>
#include <string>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
//#include <stdio>

using namespace std;
using namespace boost;

//make functions



void get_input(string usr_input)
{
	char arr[10000];//tokenize
	for(unsigned i = 0; i < usr_input.size(); i++)
	{
		arr[i] = usr_input[i];
	}
	char* argv[10000];
	char* tok = strtok(arr, " \t");
	//char* argu[10000];// = {0};
	vector<int> cmd_arg_amt;
	//char* conn[10000];
	int x = 0;
	while(tok != NULL)
	{
		argv[x] = tok;
		x++;
		tok = strtok(NULL, " \t");
	}
	argv[x] = '\0';
	int con_amount = 0;
	int hold_amt = 0;
	for(int i = 0; i < x; i++)
	{
	//	cout << "argv " << argv[i] << endl;
		if(strcmp(argv[i], "&&") || strcmp(argv[i], "||") || strcmp(argv[i], ";"))
		{
			cmd_arg_amt.push_back(hold_amt);//push back the number of arguments for a certain command
		//	cout << "cmd " << argv[i] << endl;
			hold_amt = 0;
			//conn[con_amount] = argv[i];
			con_amount++;
		}
		else if(strcmp(argv[i], "#"))
		{
			cmd_arg_amt.push_back(hold_amt);
			hold_amt = 0;
			//conn[con_amount] = argv[i];
			con_amount++;
			break;
		}
		
	
	}
	if(hold_amt > 0)
	{
		cmd_arg_amt.push_back(hold_amt);
		hold_amt = 0;
	}
	bool com_end = false;
	int a = 0;
	int place = 0;
	int executive;
	//bool working = true;
	char* con_arr[1000];//stores connectors
	int con_place = 0;
	while(argv[place] != NULL)
	{
		if(!strcmp(argv[place] , ";") || !strcmp(argv[place] , "&&") || !strcmp(argv[place] , "||") || !strcmp(argv[place] , "#"))
		{
			con_arr[con_place] = argv[place];
			con_place++;
			place++;
		}
		else
		{
			place++;
		}
	}
	con_arr[con_place] = NULL;
	place = 0;
	bool exec_works = true;
	while(a <= con_place && !com_end)
	{
		char* run[1000];
		int b = 0;
		b = 0;
		bool stop = false;
		while(!stop && argv[place] != NULL)
		{
			if(!strcmp(argv[place] , ";") || !strcmp(argv[place] , "&&") || !strcmp(argv[place] , "||") || !strcmp(argv[place] , "#") )
			{
				place++;
				break;
				stop = true;
			}
			else
			{
				run[b] = argv[place];
				b++;
				place++;
			}
		}
		for(int i = 0; i < b; i++)
		{
			if(!strcmp(run[i], ";") || !strcmp(run[i], "&&") || !strcmp(run[i], "||") || !strcmp(run[i], "#") )
			{
				run[i] = NULL;
			}
		
		}
		
		run[b] = NULL;

		int pid = fork();
		for(int i = 0; i < b; i++)
		{
			if(!strcmp(run[i], "exit"))
			{
			//	cout << "Exiting" << endl;
				exit(0);
			}
		}
		if(pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if(pid == 0)
		{
			executive = execvp(run[0], run);
			exec_works = executive;
			if(executive == -1)
			{
				//cout << "EXEC FAILED!!!!" << endl;
				exec_works = false;
				//cout << "exec in exec: " << exec_works << endl;
				perror("execvp");
				//exit(1);
			}
			else
			{
				exec_works = true;
			}
		}
		else if(pid > 0)
		{
			if(-1 == wait(0))
			{
				perror("wait");
			}
		}
		/*
		if(executive == -1)
		{
			exec_works = false;
		}
		*/
		//when exec is true, && and || work fine, but when exec is false and runs and or doesn't
		//FIX
		//&& never goes into false
		//|| always goes into false
		//FIX
		if(con_arr[a] == NULL)
		{
			com_end = true;
			break;
		}
		else if(!strcmp(con_arr[a], "||"))
		{
			//cout << "||" << endl;
			if(exec_works)
			{
				//cout << "exec for || " << exec_works << endl;
				//cout << "|| false" << endl;
				com_end = true;
				break;
			}
		}
		else if(!strcmp(con_arr[a], "&&"))
		{
			//cout << "exec for && " << exec_works << endl;
			//cout << "&&" << endl;
			if(!exec_works)
			{
				//cout << "&& false" << endl;
				com_end = true;
				break;
			}
		}
		else if(!strcmp(con_arr[a], ";"))
		{
			//cout << ";" << endl;
		}
		else if(!strcmp(con_arr[a], "#"))
		{
			//cout << "#" << endl;
			//working = false;
			com_end = true;
			break;
		}
		//cout << "con_arr " << con_arr[a] << endl;


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
	}
	return 0;
}
