#include <iostream>
#include <iomanip>
#include <algorithm>
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
#define TABLE_SIZE 30
void printNoArguments(vector<string> &output)
{
	//cout << "ls with no arguments" << endl; //REMOVE
	for(int unsigned i = 0; i < output.size(); i++)
	{
		if(output[i][0] == '.')
		{
			//file is hidden
		}
		else
		{
			//cout << setw(4);
			cout << output[i] << "  ";
		}
	}
	cout << endl;
}
void printAll(vector<string> &output)
{
	//cout << "printAll" << endl; //REMOVE
	for(unsigned i = 0; i < output.size(); i++)
	{
		//cout << setw(4);
		cout << output[i] << "  ";
	}
	cout << endl;
}
void printLong(vector<string> &output)
{
	cout << "printLong" << endl; //REMOVE

}
void printRecursive(vector<string> &output)
{
	cout << "printRecursive" << endl; //REMOVE

}
void printAllLong(vector<string> &output)
{
	cout << "printAllLong" << endl; //REMOVE

}
void printAllRecursive(vector<string> &output)
{
	cout << "printAllRecursive" << endl; //REMOVE

}
void printLongRecursive(vector<string> &output)
{
	cout << "printLongRecursive" << endl; //REMOVE

}
void printAllLongRecursive(vector<string> &output)
{
	cout << "printAllLongRecursive" << endl; //REMOVE

}
void permissions()
{

}
void fileSpecs(string &args, vector<string> &output)
{
	//cout << "filespecs" << endl;
	DIR *dirp;
	dirp = opendir(args.c_str());
	if(NULL == dirp)
	{
		perror("opendir()");
		//cout << "opendir" << endl;
		exit(1);
	}
	struct dirent *filespecs;
	while(NULL != (filespecs = readdir(dirp)))
	{
		//cout << "out" << endl;
		output.push_back(filespecs->d_name);
	}
	if(-1 == closedir(dirp))
	{
		//cout << "closedir" << endl;
		perror("closedir");
		exit(1);
	}
	//sort(output.begin(), output.end());
}

bool changeCaseCompare(string c1, string c2)
{
	for(int i = 0; i < c1.size(); i++)
	{
		c1.at(i) = tolower(c1.at(i));
	}
	for(int i = 0; i < c2.size(); i++)
	{
		c2.at(i) = tolower(c2.at(i));
	}
	return c1.compare(c2) < 0;
}

void ls_define(int argc, char* argv[])//insert parameters
{
	//ls functionality

	//cout << "ls" << endl;//REMOVE
	
	//fileSpecs(argc, directory_name);

	//char* arguments_v[10000];
	string hold_args;
	vector<string> destination;
	int arguments = 0; //000
	int a = 0;
	int args_so_far = 0;
	while(a < argc)
	{
		if(a != 0 && argv[a][0] != '-')
		{
			hold_args = argv[a];
			//arguments_v[args_so_far] = argv[a];
			args_so_far++;
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
	//cout << args_so_far << endl;
	
	vector<string> output;
	
	//arguments_v[args_so_far] = NULL;
	if(hold_args == "")
	{
		hold_args = ".";
	}
	if(args_so_far > 0)
	{
		for(int i = 0; i < args_so_far; i++)
		{
			//cout << arguments_v[i] << endl;
		}
		//fileSpecs(hold_args, output);
	}
	fileSpecs(hold_args, output);
	for(unsigned i = 0; i < output.size(); i++)
	{
		//cout << output[i] << endl;
	}
	//cout << "here" << endl;
	sort(output.begin(), output.end(), changeCaseCompare);
	switch(arguments)
	{
		case 0:
			printNoArguments(output);
			break;
		case 1:
			printAll(output);
			break;
		case 2:
			printLong(output);
			break;
		case 3:
			printAllLong(output);
			break;
		case 4:
			printRecursive(output);
			break;
		case 5:
			printAllRecursive(output);
			break;
		case 6:
			printLongRecursive(output);
			break;
		case 7:
			printAllLongRecursive(output);
			break;
		default:
			cout << "Something went wrong" << endl; //REMOVE
			break;
	}

	
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
