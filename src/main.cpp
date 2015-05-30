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
#include <pwd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace boost;

bool unblock = false;
char* prev;
char* curr;
//char* other;
vector<char*> env;

void output();
void ctrl(int signal1);
void ground_signal_bg()
{
	cout << "BG" << endl;
	
}
void ground_signal_fg()
{
	cout << "FG" << endl;
	
}
void cd_command(char *argv[])
{
	//char* prev;
	//char* curr;
	//Need to getenv and setenv to have cd - working
	//cd - is not currently working
	unsigned number;
	//char* prev;
	//cout << "argv: ";
	for(number = 0; argv[number] != NULL; number++)
	{
		//cout << argv[number] << " ";//DELETE
		
	}
	if(number == 1 || (number == 2 && !strcmp(argv[1], "~")))
	{
		if((curr = getenv("HOME")) == NULL)
		{
			perror("getenv");
		}
		if((prev = getenv("PWD")) == NULL)
		{
			perror("getenv");
		}
		if(chdir(curr) == -1)
		{
			perror("chdir");
		}
		//cout << "curr: " << curr << endl;
		if(setenv("OPENPWD", prev, 1) == -1)
		{
			perror("setenv");
		}
		if(setenv("PWD", curr, 1) == -1)
		{
			perror("setenv");
		}
		//prev = getcwd(prev, 0);
		//holder = holder + prev;
	}
	//if cd -
	//change directory to previous (need to store previous maybe in global)
	//automatically goes to /rshell every time for some reason
	else if(number == 2 && !strcmp(argv[1], "-"))
	{
		//cout << "prev: " << prev << endl;
		//cout << "curr: " << curr << endl;
		if((prev = getenv("PWD")) == NULL)
		{
			perror("getenv");
			exit(1);
		}
		//cout << "prev: " << prev << endl;
		//char* fix;
		if((curr = getenv("OLDPWD")) == NULL)//(getcwd(prev, (size_t)sizeof(prev)) == NULL))
		{
			perror("getenv");
			exit(1);
		}
		//holder += curr;
		//cout << holder << endl;
		//cout << getenv("OLDPWD") << endl;
		//cout << getenv("PWD") << endl;
		cout << curr << endl;
		if(chdir(curr) == -1)
		{
			perror("chdir");
			exit(1);
		}
		if((setenv("OLDPWD", prev, 1)) == -1)
		{
			perror("setenv");
		}
		if((setenv("PWD", curr, 1)) == -1)
		{
			perror("setenv");
		}
		
		//cout << prev << endl;
		//free(prev);
	}
	//if cd <PATH>
	//change directory to PATH
	else
	{
		//char* other;
		if((curr = getenv("PWD")) == NULL)
		{
			perror("getenv");
		}
		if((prev = getenv("OLDPWD")) == NULL)
		{
			perror("getenv");
		}
		if(chdir(argv[1]) == -1)
		{
			perror("chdir");
		}
		getcwd(prev, 2000);
		if(setenv("PWD", prev, 1) == -1)
		{
			perror("setenv");
		}
		//cout << getenv("PWD") << endl;
		if(setenv("OLDPWD", curr, 1) == -1)
		{
			perror("setenv");
		}
		//cout << getenv("OLDPWD") << endl;
		//prev = getcwd(prev, 0);
	}
	//change directories
}
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
	
	
	//int con_amount = 0;
	int hold_amt = 0;
	
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
		//char* run_pior[10000];
		for(unsigned i = 0; i < 10000; i++)
		{
			run[i] = 0;
			//run_pior[i] = 0;
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
				//run_pior[b] = argv[place];
				b++;
				place++;
			}
		}
		bool stop1 = false;
		for(int i = 0; i < b; i++)
		{
			if(!strcmp(run[i], ";") || !strcmp(run[i], "&&") || !strcmp(run[i], "||") || !strcmp(run[i], "#") )
			{
				run[i] = NULL;
			}
			else if(!strcmp(run[i], "bg"))
			{
				//run[i] = NULL;
				ground_signal_bg();
				stop1 = true;
				break;
			}
			else if(!strcmp(run[i], "fg"))
			{
				//run[i] = NULL;
				ground_signal_fg();
				stop1 = true;
				break;
			}
		}
		if(stop1)
			break;
		run[b] = NULL;
		bool cd = false;
		for(int i = 0; i < b; i++)
		{
			if(!strcmp(run[i], "cd"))
			{
				//cout << "CD" << endl;
				cd_command(run);
				cd = true;
			}
		}
		if(cd)
			break;
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
			sigignore(SIGINT);
			if(-1 == wait(0))
			{
				perror("wait");
				exit(1);
			}
			struct sigaction sa;
			sa.sa_handler = ctrl;
			sigemptyset(&sa.sa_mask);
			sigaction(SIGINT, &sa, 0);
			if(errno <= -1)
				perror("sigaction");
			/*
			do
			{
				wpid = wait(&status);
			}
			while(wpid == -1 && errno == EINTR);
			if(wpid == -1)
			{
				perror("wait");
				return -1;
			}
			*/
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
void ctrl(int signal1)
{
	//const char *signal_name;
	//sigset_t pending;
	//unblock = true;
	if(signal1 == SIGINT)
	{
		//cout << "Ctrl-C" << endl;
		//cin.clear();
		//cin.ignore(10000, '\n');
		//signal(SIGINT, SIG_IGN);
		/*
		if(errno <= -1)
		{
			perror("SIGINT");
		}
		*/
		//sigaction(SIGINT, &sa, 0);
		cout << endl;
		output();
	}
	
}
void ctrl2(int signal2)
{
	if(signal2 == SIGTSTP)
	{
		cout << endl;
		//break;
	}
}
void output()
{
	//cin.clear();
	bool log = false;
	struct sigaction sa, as;
	sa.sa_handler = ctrl;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, 0);
	if(errno <= -1)
		perror("sigaction");
	//struct sigaction2 as;
	as.sa_handler = ctrl2;
	sigemptyset(&as.sa_mask);
	sigaction(SIGTSTP, &as, 0);
	if(errno <= -1)
		perror("sigaction");
	char host[255];
	char direc[1200];
	string new_direc;
	string out_direc;
	string home;
	size_t minus = -1;
	//cin.clear();
	//cout << "info" << endl;
	string login = getlogin();
	if(log)
		perror("getlogin");
	gethostname(host, 255);
	
	if(host == NULL)
		perror("gethostname");

	if(getcwd(direc, 1200) == NULL)
	{
		perror("getcwd");
	}
	else
	{
		home = getenv("HOME");
		//cout << "home: " << home << endl;
		new_direc = direc;
		if(new_direc.find(home, 0) != minus)
		{
			new_direc.erase(0, home.size());
			//cout << new_direc << endl;
			out_direc = "~" + new_direc;
			//cout << out_direc << endl;
		}
	}
	
	cout << login << "@" << host << ":";
	cout << out_direc << " ";
	string usr_input;
	size_t poso = usr_input.find("exit");
	if(poso > 0 && poso < 1000)
	{
		exit(0);
	}
	cout << "$";
	cout << " ";
	cin.clear();
	getline(cin, usr_input);
	//if(usr_input != SIGINT)
	get_input(usr_input);
}

int main(int argc, char *argv[])
{
	//get path
	while(1)
	{
		output();
	}


	return 0;
}
