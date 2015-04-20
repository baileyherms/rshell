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

char glb_arr[10000];

/*
char* spaces(char* arry)
{
	//Fixes spacing issues
	int trav = 0;
	int glb_trav = 0;
	while(arry[trav] != NULL)
	{
		if(strcmp(arry[trav], "&&"))
		{
			glb_arr[glb_trav] = ' ';
			glb_arr[glb_trav + 1] = '&';
			glb_arr[glb_trav + 1] = '&';
			glb_arr[glb_trav + 1] = ' ';
			glb_trav++;
		}
		else if(strcmp(arry[trav], "||"))
		{
			glb_arr[glb_trav] = ' ';
			glb_arr[glb_trav + 1] = '|';
			glb_arr[glb_trav + 1] = '|';
			glb_arr[glb_trav + 1] = ' ';
			glb_trav++;
		}
		else if(strcmp(arry[trav], ";"))
		{
			glb_arr[glb_trav] = ' ';
			glb_arr[glb_trav + 1] = ';';
			glb_arr[glb_trav + 1] = ' ';
			glb_trav++;	
		}
		else if(strcmp(arry[trav], "#"))
		{
			glb_arr[glb_trav] = NULL;
		}
		else
		{
			glb_arr[glb_trav] = arry[trav];
		}


		trav++;
	}
	glb_arr[glb_trav] = NULL;
	return glb_arr;
}

int findChar(char[] sub, char[] array)
{
	return array.ToString().IndexOf(sub.ToString());
}
*/

void get_input(string usr_input)
{
	char arr[10000];//tokenize
	char* argv[10000];
	char* con_arr[10000];//stores connectors
	//char* hold_arr[10000];
	for(unsigned i = 0; i < 10000; i++)
	{	
		arr[i] = 0;
		argv[i] = 0;
		con_arr[i] = 0;
	//	hold_arr[i] = 0;
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

	
	//char* other_char = strtok(argv, " ");
	/*
	int m = 0;
	while(other_char != NULL)
	{
		hold_arr[m] = other_char;
		m++;
		other_char = strtok(NULL, ";#&|");
	}
	*/
	
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
		/*
		else if(strcmp(argv[i], "&") || strcmp(argv[i], "|") || strcmp(argv[i], "&&&") || strcmp(argv[i], "|||"))
		{
			perror("connector");
		}
		*/
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
	int con_place = 0;
	//char *inp;
	while(argv[place] != NULL)
	{
		//cout << "argv " << argv[place] << endl;
		//char *sc = strstr(argv[place], ";");//semicolon
		//char *as = strstr(argv[place], "&&");//ampersands
		//char *pi = strstr(argv[place], "||");//pipes
		if(!strcmp(argv[place] , ";") || !strcmp(argv[place] , "&&") || !strcmp(argv[place] , "||") || !strcmp(argv[place] , "#"))
		{
			con_arr[con_place] = argv[place];
			//cout << "con_arr " << con_arr[con_place] << endl;
			con_place++;
			place++;
		}
		/*
		else if(sc != NULL)
		{
			cout << "sc " << sc << endl;
			cout << "find " << argv[place] << endl;
			//Do ; stuff
			con_arr[con_place] = sc;
			//inp =
			int len_arry = 0;
			while(argv[len_arry] != ";")
			{
				len_arry++;
				cout << "length of array: " << len_arry << endl;
			}
			strcpy(argv[place], argv[place], len_arry - 1);

			con_place++;
			place++;
		
		}
		else if(as != NULL)
		{
			cout << "find " << argv[place] << endl;
			//Do ; stuff
		}
		else if(pi != NULL)
		{
			cout << "find " << argv[place] << endl;
			//Do ; stuff
		}
		*/
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
		exec_works = true;
		char* run[10000];
		for(unsigned i = 0; i < 10000; i++)
		{
			run[i] = 0;
		}
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
