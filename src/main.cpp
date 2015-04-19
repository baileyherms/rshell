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
		//put input into array
		for(int i = 0; i < usr_input.size(); i++)
		{
			arr[i] = usr_input[i];
		}

		char* argv[10000];
		char* tok = strtok(arr, " ");
		char* argu[10000];
		char* conn[10000];
		int x = 0;
		while(tok != NULL)
		{
			argv[x] = tok;
			x++;
			tok = strtok(NULL, " ");
		}
		argv[x] = '\0';
		int con_amount = 0;
		for(int i = 0; i < x; i++)
		{
			if(argv[i] == "&&" || argv[i] == "||" || argv[i] == ";")
			{
				conn[con_amount] = argv[i];
				con_amount++;
			}
			else if(argv[i] == "#")
			{
				break;
			}
			else
			{
				argu[i] = argv[i];
			}
		}

		int argu_amt = 0;
		bool working = true; //check if command is working
		bool com_end = false;
		for(int i = 0; i < x; i++)
		{
			
			//cout << argu[i] << endl;
			if(argu[i] == "&&" || argu[i] == "||" || argu[i] == ";")
			{
				if(argu[i] == "&&")
				{
					if(!working)
					{
						com_end = true;
						break;
					}
				}
				else if(argu[i] == "||")
				{
					if(working)
					{
						com_end = true;
						break;
					}
				}
				else if(argu[i] == ";")
				{

				}

			}
			else if(argu[i] == "#")
			{
				working = false;
				com_end = true;
				break;
			}
			else if(!com_end)
			{
				//cout << "Here" << endl;
				char* run[10000];
				int y = 0;
				int w = 0;//separate commands
				while(argu[w] != "&&" || argu[w] != "||" || argu[w] != "#" || argu[w] != ";" || argu[w] != NULL) 
				{
					if(w > x)
					{
						break;
					}
					run[y] = argu[y];
					y++;
					w++;
				//	cout << "stuck" << endl;
				}
				int pid = fork();
				//cout << "now" << endl;
				if(pid == -1)
				{
					perror("fork");
					exit(1);
				}
				else if(pid == 0)
				{
					//cout << run[0] << endl;
					//cout << endl;
					if(execvp(run[0], run) == -1)
					{
						perror("execvp");
						exit(1);
					}
					/*
					working = true;
					char host[255];
					string login = getlogin();
					gethostname(host, 255);
					cout << login << "@" << host << " ";
					string usr_input;
					cout << "$";
					getline(cin, usr_input);
					*/
				}
				else if(pid > 0)
				{
					if(-1 == wait(0))
					{
						perror("wait");
						working = false;
					}
				}
			}
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
