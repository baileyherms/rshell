#include <iostream>
#include <string>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include "redirect.h"

using namespace std;
using namespace boost;

void exiting(char *in)
{
	if(!strcmp(in, "exit"))
	{
		exit(0);
	}
}
void get_input(string usr_input)
{
	bool exit_now = false;
	size_t pos = usr_input.find("exit");
	//cout << "pos" << pos << endl;
	if(pos > 0 && pos < 1000)
	{
		exit(0);
	}
	char arr[10000];//tokenize
	char* argv[10000];
	char* con_arr[10000];//stores connectors
	for(unsigned i = 0; i < 10000; i++)
	{	
		arr[i] = 0;
		argv[i] = 0;
		con_arr[i] = 0;
	}
	for(unsigned i = 0; i < usr_input.size(); i++)
	{
		arr[i] = usr_input[i];
	}
	char* tok = strtok(arr, " \t");
	vector<int> cmd_arg_amt;
	int x = 0;
	while(tok != NULL)
	{
		argv[x] = tok;
		x++;
		tok = strtok(NULL, " \t");
	}
	argv[x] = '\0';
	x = 0;
	
	
	int con_amount = 0;
	int hold_amt = 0;
	/*
	for(int i = 0; i < x; i++)
	{
		if(strcmp(argv[i], "&&") || strcmp(argv[i], "||") || strcmp(argv[i], ";"))
		{
			cmd_arg_amt.push_back(hold_amt);//push back the number of arguments for a certain command
			hold_amt = 0;
			con_amount++;
		}
		else if(strcmp(argv[i], "#"))
		{
			cmd_arg_amt.push_back(hold_amt);
			hold_amt = 0;
			con_amount++;
			break;
		}
		else if(strcmp(argv[i], "exit"))
		{
			exit(0);
		}
	}
	*/
	if(hold_amt > 0)
	{
		cmd_arg_amt.push_back(hold_amt);
		hold_amt = 0;
	}
	bool com_end = false;
	int a = 0;
	int place = 0;
	int executive;
	int con_place = 0;
	vector<int> places_con;//where connectors are
	while(argv[place] != NULL)
	{
		char *sc = strstr(argv[place], ";");//semicolon
		char *as = strstr(argv[place], "&&");//ampersands
		char *pi = strstr(argv[place], "||");//pipes
		char *hs = strstr(argv[place], "#");//hash
		if(!strcmp(argv[place] , ";") || !strcmp(argv[place] , "&&") || !strcmp(argv[place] , "||") || !strcmp(argv[place] , "#"))
		{
			con_arr[con_place] = argv[place];
			con_place++;
			place++;
		}
		else if(sc != NULL)
		{
			con_arr[con_place] = sc;
			con_place++;
			places_con.push_back(place);
			place++;
		}
		else if(as != NULL)
		{
			con_arr[con_place] = as;
			con_place++;
			place++;
			places_con.push_back(place);
		}
		else if(pi != NULL)
		{
			con_arr[con_place] = pi;
			con_place++;
			place++;
			places_con.push_back(place);	
		}
		else if(hs != NULL)
		{
			con_arr[con_place] = hs;
			con_place++;
			place++;
			places_con.push_back(place);
		}
		else
		{
			place++;
		}
	}
	char* aargv = strtok(arr, "#;|& ");
	int l = 0;
	while(aargv != NULL)
	{
		argv[l] = aargv;
		l++;
		aargv = strtok(NULL, "#;|& ");
	}
	l = 0;
	con_arr[con_place] = NULL;
	place = 0;
	bool exec_works = true;
	while(a <= con_place && !com_end)
	{
		exec_works = true;
		char* run[10000];
		char* run_pior[10000];
		for(unsigned i = 0; i < 10000; i++)
		{
			run[i] = 0;
			run_pior[i] = 0;
		}
		int b = 0;
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
				run_pior[b] = argv[place];
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
			bool pipe = false;
			exit_now = true;
			int value = 0;
			while(run[value] != NULL)
			{
				if(!strcmp(run[value], "<<<") || !strcmp(run[value], "|") || !strcmp(run[value], "<") || !strcmp(run[value], ">") || !strcmp(run[value], ">>")  || !strcmp(run[value], "0>") || !strcmp(run[value], "0>>")  || !strcmp(run[value], "1>") || !strcmp(run[value], "1>>")  || !strcmp(run[value], "2>") || !strcmp(run[value], "2>>")  || !strcmp(run[value], "3>") || !strcmp(run[value], "3>>") )
				{
					pipe = true;
				}
				value++;
			}
			if(pipe)
			{
				executive = piping(run);
				exec_works = executive;
			}
			else
			{
				executive = execvp(run[0], run);
				exec_works = executive;
			}
			if(executive == -1)
			{
				exec_works = false;
				perror("execvp");
			}
			else
			{
				exec_works = true;
			}
		}
		else if(pid > 0)
		{
			//exiting(run[0]);

			if(-1 == wait(0))
				perror("wait");
		}	
		//exiting(run[0]);
		if(con_arr[a] == NULL)
		{
			com_end = true;
			break;
		//	exit(0);
		}
		else if(!strcmp(con_arr[a], "||"))
		{
			if(exec_works)
			{
				com_end = true;
				break;
				//exit(0);
			}
		}
		else if(!strcmp(con_arr[a], "&&"))
		{
			if(!exec_works)
			{
				com_end = true;
				break;
			//	exit(0);
			}
		}
		else if(!strcmp(con_arr[a], ";"))
		{
		}
		else if(!strcmp(con_arr[a], "#"))
		{
			com_end = true;
			break;
			//exit(0);
		}
		/*
		if(exec_works == false && com_end == true)
		{
			exit(1);
		}
		*/
		a++;
	}	
	if(exit_now)
	{
		exit(1);
	}
}

void output()
{
	char host[255];
	string login = getlogin();
	gethostname(host, 255);
	cout << login << "@" << host << " ";
	string usr_input;
	size_t poso = usr_input.find("exit");
	if(poso > 0 && poso < 1000)
	{
		exit(0);
	}
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
