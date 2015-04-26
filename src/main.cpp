#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

#define MAXSIZE 10000

void printNoArguments()
{
	cout << "ls with no arguments" << endl; //REMOVE
}
void printAll()
{
	cout << "printAll" << endl; //REMOVE
}
void printLong()
{
	cout << "printLong" << endl; //REMOVE

}
void printRecursive()
{
	cout << "printRecursive" << endl; //REMOVE

}
void printAllLong()
{
	cout << "printAllLong" << endl; //REMOVE

}
void printAllRecursive()
{
	cout << "printAllRecursive" << endl; //REMOVE

}
void printLongRecursive()
{
	cout << "printLongRecursive" << endl; //REMOVE

}
void printAllLongRecursive()
{
	cout << "printAllLongRecursive" << endl; //REMOVE

}

void fileSpecs(int argc/*argc needs to be the number of entries passed into argv*/, char* argv[]/*argv needs to be the directory pointer*/ )//insert parameters and return value
{
	//May delete this functions and just put the directory stuff into the print functions to make coding easier
	if(argc <= 1)
	{
		perror("argc");//Nothing passed in to argc
		exit(1);
	}
	DIR *dirp;
	if(NULL == (dirp = opendir(argv[1])))
	{
		perror("opendir()");
		exit(1);
	}
	struct dirent *filespecs;
	errno = 0;
	while(NULL != (filespecs = readdir(dirp)))
	{
		//change to put files in certain order
		cout << filespecs->d_name << " ";
	}
	if(errno != 0)
	{
		perror("readdir()");
		exit(1);
	}
	cout << endl;
	if(-1 == closedir(dirp))
	{
		perror("closedir");
		exit(1);
	}

	//return *filespecs; if used, return value is struct dirent
}

void ls_define(int argc, char* argv[])//insert parameters
{
	//ls functionality

	cout << "ls" << endl;//REMOVE
	
	//fileSpecs(argc, directory_name);

	vector<string> destination;
	int arguments = 0; //000
	int a = 0;
	while(a < argc)
	{
		if(a != 0 && argv[a][0] != '-')
		{
			cout << "destination: " << argv[a] << endl;
			destination.push_back(argv[a]);
		}
		else if(argv[a][0] == '-')
		{
			int b = 0;
			while(argv[a][b] != '\0')
			{
				if(argv[a][b] == 'a')
				{
					arguments = arguments | 1;
				}
				else if(argv[a][b] == 'l')
				{
					arguments = arguments | 2;
				}
				else if(argv[a][b] == 'R')
				{
					arguments = arguments | 4;
				}
				b++;
			}
		}
		a++;
	}
	if(destination.size() == 0)
	{
		destination.push_back(".");//Current destination
	}
	switch(arguments)
	{
		case 0:
			printNoArguments();
			break;
		case 1:
			printAll();
			break;
		case 2:
			printLong();
			break;
		case 3:
			printAllLong();
			break;
		case 4:
			printRecursive();
			break;
		case 5:
			printAllRecursive();
			break;
		case 6:
			printLongRecursive();
			break;
		case 7:
			printAllLongRecursive();
			break;
		default:
			cout << "Something went wrong" << endl; //REMOVE
			break;
	}

	/*
	//Need to figure out how to print -a -l as if it is -al for all arguments

	//create flags (-a, -l, -R)
	map<string, void(*)()> flag_functions;
	flag_functions["--all"] = printAll;
	flag_functions["-a"] = printAll;
	flag_functions["--long"] = printLong;
	flag_functions["-l"] = printLong;
	flag_functions["--recursive"] = printRecursive;
	flag_functions["-R"] = printRecursive;
	flag_functions["-al"] = printAllLong;
	flag_functions["-la"] = printAllLong;
	flag_functions["-aR"] = printAllRecursive;
	flag_functions["-Ra"] = printAllRecursive;
	flag_functions["-lR"] = printLongRecursive;
	flag_functions["-Rl"] = printLongRecursive;
	flag_functions["-alR"] = printAllLongRecursive;
	flag_functions["-aRl"] = printAllLongRecursive;
	flag_functions["-lRa"] = printAllLongRecursive;
	flag_functions["-laR"] = printAllLongRecursive;
	flag_functions["-Ral"] = printAllLongRecursive;
	flag_functions["-Rla"] = printAllLongRecursive;

	for(int i = 1; i < argc; i++)
	{
		void(*fp)() = flag_functions[string(argv[i])];
		if(fp != NULL)
		{
			fp();
		}
		else
		{
			cout << "Invalid Flag: " << argv[i] << endl;
		}
	}
	*/
}

void get_input(string& usr_input)
{
	char arr[MAXSIZE];
	char* argv[MAXSIZE];
	char* argvcmd[MAXSIZE];

	for(unsigned i = 0; i < MAXSIZE; i++)
	{
		arr[i] = 0;
		argv[i] = 0;
		argvcmd[i] = 0;
	}
	
	int index = 0;
	int start = 0;
	int j = 0;
	int n = 0;
	int c_cnt = 0;
	int tmp;

	for(unsigned i = 0; i < usr_input.size(); i++)
	{
		tmp = usr_input.at(i);
		if(tmp == ' ' || tmp == ';' || tmp == '&' || tmp == '|' || tmp == '#')
		{
			if(c_cnt > 0)
			{
				argv[j] = (char*)&arr[start];
				j++;
				c_cnt = 0;
				arr[n] = '\0';
				n++;		
			}
			start = n;
			if(tmp != ' ')
			{
				if(tmp == '#')
				{
					start = n;
					arr[n++] = ';';
					argv[j] = (char*)&arr[start];
					c_cnt = 0;
					i = usr_input.size();
					j++;
				}
				else if(tmp == ';')
				{
					arr[n++] = ';';
					arr[n++] = '\0';
					argv[j] = (char*)&arr[start];
					start = n;
					j++;
					c_cnt = 0;
				}
				else if(tmp == '&')
				{
					if(usr_input.at(i+1) == '&')
					{
						arr[n++] = '&';
						arr[n++] = '&';
						arr[n++] = '\0';
						argv[j] = (char*)&arr[start];
						j++;
						start = n;
						c_cnt = 0;
						i++;
					}
				}
				else if(tmp == '|')
				{
					if(usr_input.at(i+1) == '|')
					{
						arr[n++] = '|';
						arr[n++] = '|';
						arr[n++] = '\0';
						argv[j] = (char*)&arr[start];
						j++;
						start = n;
						c_cnt = 0;
						i++;
					}
				}
			}
		}
		else
		{
			arr[n] = usr_input.at(i);
			c_cnt++;
			n++;
			if(i == usr_input.size() - 1)
			{
				argv[j] = (char*)&arr[start];
				n++;
				j++;
			}
		}
	}	
	if(strcmp(argv[j-1], ";") != 0)
	{
		n++;
		start = n;
		arr[n++] = ';';
		argv[j] = (char*)&arr[start];
		j++;
	}
	argv[j] = (char*)NULL;
	int status;
	for(int i = 0; i < j; i++)
	{
		if(strcmp(argv[i], "&&") == 0 || strcmp(argv[i], "||") == 0 || strcmp(argv[i], ";") == 0)
		{
			int pid;
			pid = fork();
			if(pid < 0)
			{
				perror("fork");
			}
			else if(pid == 0)
			{
				argvcmd[index] = NULL;
				
				if(!(strcmp(argvcmd[0], "ls")))
				{
					ls_define(index, argvcmd);
				}
				else
				{
					status = execvp(argvcmd[0], argvcmd);
				}
		
				if(status == -1)
				{
					perror("execvp");
					int x;
					int next = -1;
					if(strcmp(argv[i], "&&") == 0)
					{
						for(x = i + 1; x < j; x++)
						{
							if(strcmp(argv[x], "||") == 0 || strcmp(argv[x], ";") == 0)
							{
								next = x;
								break;
							}
						}
						if(next > 0)
						{
							i = next;
						}
					}
				}
				index = 0;
				exit(status);
			}
			else
			{
			}
			waitpid(-1, &status, 0);
			if(strcmp(argv[i], "&&") == 0 && (status > 0))
			{
				int x;
				int next = -1;
				x = i + 1;
				while(x < j)
				{
					if(strcmp(argv[x], "&&") == 0 || strcmp(argv[x], "||") == 0 || strcmp(argv[x], ";") == 0)
					{
						next = x;
						break;
					}
					x++;
				}
				if(next > 0)
				{
					i = next;
					next = -1;
				}
			}
			if(strcmp(argv[i], "||") == 0 && (status == 0))
			{
				int x;
				int next = -1;
				x = i + 1;
				while(x < j)
				{
					if(strcmp(argv[x], "&&") == 0 || strcmp(argv[x], "||") == 0 || strcmp(argv[x], ";") == 0)
					{
						next = x;
						break;
					}
					x++;
				}
				if(next > 0)
				{
					i = next;
					next = -1;
				}
			}
			index = 0;
		}
		else
		{
			if(index == 0 && (strcmp(argv[i], "exit")) == 0)
			{
				exit(1);
			}
			argvcmd[index] = argv[i];
			index++;
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
