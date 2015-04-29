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
#include <grp.h>
#include <pwd.h>
#include <ctime>
#include <cmath>
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
			cout << left << setw(output.at(i).size() + 2) << output[i];
			
		}
	}
	cout << endl;
}
void printAll(vector<string> &output)
{
	//cout << "printAll" << endl; //REMOVE
	for(unsigned i = 0; i < output.size(); i++)
	{
		//cout << setw(6);
		cout << left << setw(output.at(i).size() + 2) << output[i];
	
	}
	cout << endl;
}

void printLong(vector<string> &output)
{
	//cout << "printLong" << endl; //REMOVE
	//cout << "args " << args << endl;
	/*
	for(unsigned i = 0; i < output.size(); i++)
	{
		cout << "output at " << i << " " << output.at(i) << endl;
	}
	*/
	cout << "total " << "#"; //Add number here	
	cout << endl;
	struct stat perms;//holds the directory files
	unsigned max = 0;
	for(unsigned i = 0; i < output.size(); i++)
	{
		if(output[i][0] == '.')
		{
			//file is hidden
		}
		else
		{
			if((stat(output.at(i).c_str(), &perms)) != 0)
			{
				perror(output.at(i).c_str());
				exit(1);
			}
			for(unsigned j = 0; j < output.size(); j++)
			{
				unsigned temp_max = 0;
				stat(output.at(j).c_str(), &perms);
				int hold_size = perms.st_size;
				while(hold_size > 0)
				{
					hold_size = hold_size/10;
					temp_max++;
				}
				if(temp_max > max)
				{
					max = temp_max;
				}
			}
			stat(output.at(i).c_str(), &perms);

			struct passwd *pw = getpwuid(perms.st_uid);
			struct group *gr = getgrgid(perms.st_gid);
			if(!pw)
			{
				perror("Error with getting owner name");
				exit(1);
			}
			if(!gr)
			{
				perror("Error with getting group name");
				exit(1);
			}
			struct tm *dt = localtime(&perms.st_mtime);
			if(!dt)
			{
				perror("Error gettting date");
				exit(1);
			}
			if(S_ISDIR(perms.st_mode))
			{
				cout << "d";
			}
			else if(S_ISLNK(perms.st_mode))
			{
				cout << "l";
			}
			else
			{
				cout << "-";
			}
			cout << ((perms.st_mode & S_IRUSR) ? "r" : "-")
				<< ((perms.st_mode & S_IWUSR) ? "w" : "-")
				<< ((perms.st_mode & S_IXUSR) ? "x" : "-");
				
			cout << ((perms.st_mode & S_IRGRP) ? "r" : "-")	
				<< ((perms.st_mode & S_IWGRP) ? "w" : "-")
				<< ((perms.st_mode & S_IXGRP) ? "x" : "-");
			
			cout << ((perms.st_mode & S_IROTH) ? "r" : "-")
				<< ((perms.st_mode & S_IWOTH) ? "w" : "-")
				<< ((perms.st_mode & S_IXOTH) ? "x" : "-");

			char months[12][4] = {"Jan", "Feb", "Mar",
								"Apr", "May", "Jun",
								"Jul", "Aug", "Sep",
								"Oct", "Nov", "Dec"};
			cout << " " << "#";
			cout << " "  << pw->pw_name << " " << gr->gr_name;
			cout << setw(max + 1) <<  perms.st_size;
			cout << " " <<  (months[dt->tm_mon])
				<< " " << dt->tm_mday;

			if(dt->tm_hour < 10)
			{
				cout << " " << "0" << dt->tm_hour;
			}
			else
			{
				cout << " " << dt->tm_hour;
			}
			cout << ":";
			if(dt->tm_min < 10)
			{
				cout << "0" << dt->tm_min;
			}
			else
			{
				cout << dt->tm_min;
			}

			cout << " " << output.at(i).c_str() << endl;
		}
	}
	
}
void printRecursive(vector<string> &output)
{
	cout << "printRecursive" << endl; //REMOVE

}
void printAllLong(vector<string> &output)
{
	//cout << "printAllLong" << endl; //REMOVE
	cout << "total " << "#";//Add number here
	cout << endl;
	struct stat perms;//holds the directory files
	unsigned max = 0;
	for(unsigned i = 0; i < output.size(); i++)
	{
		if(0)
		{
			//file is hidden (removed for -al)
		}
		else
		{
			if((stat(output.at(i).c_str(), &perms)) != 0)
			{
				perror(output.at(i).c_str());
				exit(1);
			}
			
			for(unsigned j = 0; j < output.size(); j++)
			{
				unsigned temp_max = 0;
				stat(output.at(j).c_str(), &perms);
				int hold_size = perms.st_size;
				while(hold_size > 0)
				{
					hold_size = hold_size/10;
					temp_max++;
				}
				if(temp_max > max)
				{
					max = temp_max;
				}
			}
			stat(output.at(i).c_str(), &perms);
			struct passwd *pw = getpwuid(perms.st_uid);
			struct group *gr = getgrgid(perms.st_gid);
			if(!pw)
			{
				perror("Error with getting owner name");
				exit(1);
			}
			if(!gr)
			{
				perror("Error with getting group name");
				exit(1);
			}
			struct tm *dt = localtime(&perms.st_mtime);
			if(!dt)
			{
				perror("Error gettting date");
				exit(1);
			}
			
			if(S_ISDIR(perms.st_mode))
			{
				cout << "d";
			}
			else if(S_ISLNK(perms.st_mode))
			{
				cout << "l";
			}
			else
			{
				cout << "-";
			}
			cout << ((perms.st_mode & S_IRUSR) ? "r" : "-")
				<< ((perms.st_mode & S_IWUSR) ? "w" : "-")
				<< ((perms.st_mode & S_IXUSR) ? "x" : "-");
				
			cout << ((perms.st_mode & S_IRGRP) ? "r" : "-")	
				<< ((perms.st_mode & S_IWGRP) ? "w" : "-")
				<< ((perms.st_mode & S_IXGRP) ? "x" : "-");
			
			cout << ((perms.st_mode & S_IROTH) ? "r" : "-")
				<< ((perms.st_mode & S_IWOTH) ? "w" : "-")
				<< ((perms.st_mode & S_IXOTH) ? "x" : "-");

			char months[12][4] = {"Jan", "Feb", "Mar",
								"Apr", "May", "Jun",
								"Jul", "Aug", "Sep",
								"Oct", "Nov", "Dec"};
			cout << " " << "#";
			cout << " "  << pw->pw_name << " " << gr->gr_name;
			cout << right <<  setw(max + 1) << perms.st_size;
			cout << " " <<  (months[dt->tm_mon])
				<< " " << dt->tm_mday;

			if(dt->tm_hour < 10)
			{
				cout << " " << "0" << dt->tm_hour;
			}
			else
			{
				cout << " " << dt->tm_hour;
			}
			cout << ":";
			if(dt->tm_min < 10)
			{
				cout << "0" << dt->tm_min;
			}
			else
			{
				cout << dt->tm_min;
			}

			cout << " " << output.at(i).c_str() << endl;
		}
	}
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
unsigned max_length(vector<string> output)
{
	unsigned max = 0;
	for(unsigned i = 0; i < output.size(); i++)
	{
		if(output.at(i).size() > max)
		{
			max = output.at(i).size();
		}
	}
	return max;
}
bool changeCaseCompare(string c1, string c2)
{
	for(unsigned i = 0; i < c1.size(); i++)
	{
		c1.at(i) = tolower(c1.at(i));
	}
	for(unsigned i = 0; i < c2.size(); i++)
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
	//unsigned max_size = max_length(output);
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
