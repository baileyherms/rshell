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
#include <sys/ioctl.h>
#include <grp.h>
#include <pwd.h>
#include <ctime>
#include <cmath>
using namespace std;

#define MAXSIZE 10000
#define TABLE_SIZE 30

bool stuf = false;

void fileSpecs(int &max_length, string &args, vector<string> &output);
bool changeCaseCompare(string c1, string c2);
unsigned max_length(vector<string> output);
void printAll(unsigned max_length, vector<string> &output, string &args);
void colors(string item, struct stat perms)
{
	if(S_ISDIR(perms.st_mode))
	{
		//cout << perms.st_mode << endl;
		//color directory
		if(item[0] != '.')
		{
			//directory
			//cout << "here" << endl;
			//Everything in ls -a and ls -aR is going here
			cout << "\x1b[1;34m" << item << "\033[0m" << "/";//"\x1b[0m";
		}
		else
		{
			//directory hidden
			cout << "\x1b[0;34m\x1b[11;47m" << item << "\033[0m";//"\x1b[0m\x1b[0m";
		}
		
	}
	else if((perms.st_mode & S_IEXEC) && S_ISREG(perms.st_mode))
	{
			//color executable
			if(item[0] != '.')
			{
				//executable
				cout << "\x1b[0;32m" << item << "\033[0m" << "/";//"\x1b[0m";
			}
			else
			{
				//executable hidden
				cout << "\x1b[0;32m\x1b[11;47m" << item << "\033[0m";//"\x1b[0m\x1b[0m";
			}
	}
	else if(item[0] == '.')
	{
		//hidden
		//DELETE
		cout << "\x1b[11;47m" << item << "\033[0m";//"\x1b[0m";
	}
	else
	{
		cout /*<< "HERE" */<< "\033[0m" <<  item;
	}
}
void printNoArguments(unsigned max, vector<string> &output, string &args)
{	
	vector<string> no_hide;
	for(unsigned i = 0; i < output.size(); i++)
	{
		if(output[i][0] != '.')
		{
			//cout << output.at(i) << endl;
			no_hide.push_back(output.at(i));
		}
	}
	unsigned max_l = max_length(no_hide) + 1;
	//printAll(max_l, no_hide);
	
	struct winsize win;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == -1)
		perror("ioctl");
	int width = no_hide.size()*max_l;
	double row_coun = ceil((double)width/(double)win.ws_col);
	unsigned row_count = (unsigned)row_coun;
	for(unsigned i = 0; i < row_count; i++)
	{
		string file= "";
		for(unsigned j = i; j < no_hide.size(); j += row_count)
		{
			struct stat perms;
			file = args + "/" + no_hide.at(j);
			if(stat(file.c_str(), &perms) == -1)//no_hide was file
			{
				if(stuf) perror("stat");
			}
			//cout << no_hide.at(j);
			colors(no_hide.at(j), perms);//file was no_hide
			unsigned k;// = strlen(output.at(j).c_str();
			for(k = strlen(no_hide.at(j).c_str()); k < max_l; k++)
			{	
				cout << " ";
			}
		}
		cout << endl;
	}
	
}

void printAll(unsigned max_length, vector<string> &output1, string &args)
{
	vector<string> output;
	for(unsigned i = 0; i < output1.size(); i++)
	{
		//cout << output.at(i) << endl;
		output.push_back(output1.at(i));
	}
	//cout << "max length: " << max_length << endl;
	struct winsize win;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == -1)
		perror("ioctl");
	int width = output.size()*max_length;
	double row_coun = ceil((double)width/(double)win.ws_col);
	unsigned row_count = (unsigned)row_coun;
	//int arguments = 0;
	for(unsigned i = 0; i < row_count; i++)
	{
		string file = "";
		for(unsigned j = i; j < output.size(); j += row_count)
		{
			//cout << output.at(i) << endl;
			struct stat perms;
			file = args + "/" + output.at(j);
			if(stat(file.c_str(), &perms) == -1)//file was output.at(j)
			{
				if(stuf) perror("stat");
			}
			//if(S_ISDIR(perms.st_mode))
				//cout << "DIR" << endl;
			colors(output.at(j), perms);
			unsigned k;// = strlen(output.at(j).c_str();
			for(k = strlen(output.at(j).c_str()); k < max_length; k++)
			{	
				cout << " ";
			}
		}
		cout << endl;
	}
}
void printLong(unsigned max_length, vector<string> &output, string args)
{
	struct stat perms;//holds the directory files
	unsigned entire_size = 0;
	unsigned max = 0;
	string file = "";
	for(unsigned j = 0; j < output.size(); j++)
	{
		if(output[j][0] != '.')
		{
			unsigned temp_max = 0;
			string fake = args;
			fake += "/";
			fake += output[j];
			if(stat(fake.c_str(), &perms) == -1)
			{
				perror("stat");
				exit(1);
			}
			//single_blocks.push_back(perms.st_blocks);
			int hold_size = perms.st_size;
			entire_size += perms.st_blocks;
			//cout << single_blocks.at(j) << endl;
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
	}
	cout << "total " << entire_size/2; //Add number here	
	cout << endl;
	for(unsigned i = 0; i < output.size(); i++)
	{
		if(output[i][0] == '.')
		{
			//file is hidden
		}
		else
		{
			file = args;
			file += "/";
			file += output[i];
			if(stat(file.c_str(), &perms) == -1)
			{
				if(stuf)
				{
					perror("stat");
					exit(1);
				}
			}


			
			
			struct tm *dt = localtime(&perms.st_mtime);
			if(!dt)
			{
				//perror("Error gettting date");
				exit(1);
			}
			if(S_ISDIR(perms.st_mode))
			{
				cout << "d";
				//if(stuf)
					//perror("S_ISDIR");
			}
			else if(S_ISLNK(perms.st_mode))
			{
				cout << "l";
				//if(stuf)
					//perror("S_ISLNK");
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
			cout << setw(3) << perms.st_nlink;
			cout << " "  << pw->pw_name << " " << gr->gr_name;
			cout << setw(max + 1) << perms.st_size;
			cout << " " <<  (months[dt->tm_mon]);
			if(dt->tm_mday < 10)
			{
				cout << "  " << dt->tm_mday;
			}
			else
			{
				cout << " " << dt->tm_mday;
			}
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

			cout << " ";
			colors(output.at(i), perms);
			cout << endl;
			//cout << " " << output[i] << endl;
		}
	}
	
}
void printRecursive(unsigned max_length, vector<string> &output, string args)
{
	//cout << "printRecursive" << endl; //REMOVE
	cout << args << ":" << endl;
	printNoArguments(max_length, output, args);
	max_length = 0;
	cout << endl;
	vector<string> rec_output;
	for(unsigned i = 0; i < output.size(); i++)
	{
		vector<string> rec_output;
		struct stat perms;
		DIR *dirp;
		bool stuff = false;
		string rec_args = args + "/" + output.at(i);
		dirp = opendir(rec_args.c_str());
		if(0)
		{
			perror("opendir");
			//cout << "opendir" << endl;
			exit(1);
		}
		if(NULL != dirp && output[i][0] != '.' && !(stat(rec_args.c_str(), &perms) == -1))
		{
			if(stuf)
				perror("stat");
			if(S_ISDIR(perms.st_mode))
			{
				//cout << rec_args  << ":";
				//cout << endl;
				struct dirent *filespecs;
				max_length = 0;
				while(NULL != (filespecs = readdir(dirp)))
				{
					if(stuff)
						perror("readdir");
					rec_output.push_back(filespecs->d_name);
					if(strlen(filespecs->d_name) > max_length)
					{
						max_length = strlen(filespecs->d_name);
					}
				}
				sort(rec_output.begin(), rec_output.end(), changeCaseCompare);
				printRecursive(max_length + 1, rec_output, rec_args);
			}
			
			if(-1 == closedir(dirp))
			{
				perror("closedir");
				exit(1);
			}
		}
		else//if(dirp == NULL)
			free(dirp);
	}
}
void printAllLong(unsigned max_length, vector<string> &output, string &args)
{
	string file = "";
	struct stat perms;//holds the directory files
	unsigned entire_size = 0;
	unsigned max = 0;
	//vector<unsigned> single_blocks;
	for(unsigned j = 0; j < output.size(); j++)
	{
		if(1)//output[j][0] != '.')
		{
			unsigned temp_max = 0;
			string fake = args;
			fake += "/";
			fake += output[j];
			if(stat(fake.c_str(), &perms) == -1)
			{
				perror("stat");
				exit(1);
			}
			//single_blocks.push_back(perms.st_blocks);
			int hold_size = perms.st_size;
			entire_size += perms.st_blocks;
			//cout << single_blocks.at(j) << endl;
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
	}
	//cout << "printAllLong" << endl; //REMOVE
	cout << "total " << entire_size/2 << endl;//Add number here
	//string stuff = "~";
	// = stuff;
	/*
	for(unsigned j = 0; j < output.size(); j++)
	{
		unsigned temp_max = 0;
		stat(output.at(i).c_str(), &perms);
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
	*/
	for(unsigned i = 0; i < output.size(); i++)
	{
		
		if(0)
		{
			//file is hidden (removed for -al)
		}
		else
		{
			file = args;
			file += "/";
			file += output[i];
			if(stat(file.c_str(), &perms) == -1)
			{
				//cout << "Here" << endl;
				perror("stat");
				exit(1);
			}
			
			if(stat(file.c_str(), &perms) == -1)
			{
				perror("stat");
				exit(1);
			}
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
				//perror("Error gettting date");
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
			cout << setw(3) << perms.st_nlink;
			cout << " "  << pw->pw_name << " " << gr->gr_name;
			cout << right <<  setw(max + 1) << perms.st_size;
			cout << " " <<  (months[dt->tm_mon]);
			if(dt->tm_mday < 10)
			{
				cout << "  " << dt->tm_mday;
			}
			else
			{
				cout << " " << dt->tm_mday;
			}
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
			cout << " ";
			colors(output.at(i), perms);
			cout << endl;
			//cout << " " << output[i] << endl;
		}
	}
}
void printAllRecursive(unsigned max_length, vector<string> &output, string args)
{
	//cout << "printAllRecursive" << endl; //REMOVE
	cout << args << ":" << endl;
	printAll(max_length, output, args);
	max_length = 0;
	cout << endl;
	vector<string> rec_output;
	for(unsigned i = 0; i < output.size(); i++)
	{
		vector<string> rec_output;
		struct stat perms;
		DIR *dirp;
		string rec_args = args + "/" + output.at(i);
		dirp = opendir(rec_args.c_str());
		if(0)
		{
			perror("opendir()");
			//cout << "opendir" << endl;
			exit(1);
		}
		if(NULL != dirp && output[i] != "." && output[i] != ".." &&  !(stat(rec_args.c_str(), &perms) == -1))
		{
			if(stuf)
				perror("stat");
			if(S_ISDIR(perms.st_mode))
			{
				//cout << rec_args  << ":";
				//cout << endl;
				struct dirent *filespecs;
				max_length = 0;
				while(NULL != (filespecs = readdir(dirp)))
				{
					if(stuf)
						perror("readdir");
					rec_output.push_back(filespecs->d_name);
					if(strlen(filespecs->d_name) > max_length)
					{
						max_length = strlen(filespecs->d_name);
						//cout << max_length << endl;
					}
				}
				//max_length++;
				sort(rec_output.begin(), rec_output.end(), changeCaseCompare);
				//cout << max_length << endl;
				printAllRecursive(max_length + 1, rec_output, rec_args);
			}
			
			if(-1 == closedir(dirp))
			{
				perror("closedir");
				exit(1);
			}
		}
		else//if(dirp == NULL)
			free(dirp);
	}
}
void printLongRecursive(unsigned max_length, vector<string> &output, string args)
{
	//cout << "printLongRecursive" << endl; //REMOVE
	cout << args << ":" << endl;
	printLong(max_length, output, args);
	cout << endl;
	vector<string> rec_output;
	for(unsigned i = 0; i < output.size(); i++)
	{
		vector<string> rec_output;
		struct stat perms;
		DIR *dirp;
		string rec_args = args + "/" + output.at(i);
		dirp = opendir(rec_args.c_str());
		int stuff = false;
		if(stuff)
		{
			perror("opendir()");
			//cout << "opendir" << endl;
			exit(1);
		}
		if(NULL != dirp && output[i][0] != '.' && !(stat(rec_args.c_str(), &perms) == -1))
		{
			if(stuf)
				perror("stat");
			if(S_ISDIR(perms.st_mode))
			{
				//cout << rec_args  << ":";
				//cout << endl;
				struct dirent *filespecs;
				max_length = 0;
				while(NULL != (filespecs = readdir(dirp)))
				{
					if(0)
						perror("readdir");
					rec_output.push_back(filespecs->d_name);
					if(strlen(filespecs->d_name) > max_length)
					{
						max_length = strlen(filespecs->d_name);
						//cout << max_length << endl;
					}
				}
				max_length++;
				sort(rec_output.begin(), rec_output.end(), changeCaseCompare);
				//cout << max_length << endl;
				printLongRecursive(max_length, rec_output, rec_args);
			}
			
			if(-1 == closedir(dirp))
			{
				perror("closedir");
				exit(1);
			}
		}
		else//if(dirp == NULL)
			free(dirp);
	}
}
void printAllLongRecursive(unsigned max_length, vector<string> &output, string args)
{
	//cout << "printAllLongRecursive" << endl; //REMOVE
	cout << args << ":" << endl;
	printAllLong(max_length, output, args);
	cout << endl;
	vector<string> rec_output;
	for(unsigned i = 0; i < output.size(); i++)
	{
		vector<string> rec_output;
		struct stat perms;
		DIR *dirp;
		string rec_args = args + "/" + output.at(i);
		dirp = opendir(rec_args.c_str());
		if(0)
		{
			perror("opendir()");
			//cout << "opendir" << endl;
			exit(1);
		}
		if(NULL != dirp && output[i] != "." && output[i] != ".." && !(stat(rec_args.c_str(), &perms) == -1))
		{
			if(stuf)
				perror("stat");
			if(S_ISDIR(perms.st_mode))
			{
				//cout << rec_args  << ":";
				//cout << endl;
				struct dirent *filespecs;
				max_length = 0;
				while(NULL != (filespecs = readdir(dirp)))
				{
					if(0)
						perror("readdir");
					rec_output.push_back(filespecs->d_name);
					if(strlen(filespecs->d_name) > max_length)
					{
						max_length = strlen(filespecs->d_name);
						//cout << max_length << endl;
					}
				}
				max_length++;
				sort(rec_output.begin(), rec_output.end(), changeCaseCompare);
				//cout << max_length << endl;
				printAllLongRecursive(max_length, rec_output, rec_args);
			}
			
			if(-1 == closedir(dirp))
			{
				perror("closedir");
				exit(1);
			}
		}
		else//if(dirp == NULL)
			free(dirp);
	}
}
void fileSpecs(unsigned &max_length, string &args, vector<string> &output)
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
		//cout << "filespecs: " << filespecs->d_name << endl;
		//cout << "out" << endl;
		if(0)
			perror("readdir");
		output.push_back(filespecs->d_name);
		if(strlen(filespecs->d_name) > max_length)
		{
			max_length = strlen(filespecs->d_name); 
		}
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
	string hold_args;// = "~/";
	vector<string> destination;
	int arguments = 0; //000
	int a = 0;
	//string argv_hold;
	int args_so_far = 0;
	while(a < argc)
	{
		//cout << argv[a] << endl;
		if(a != 0 && argv[a][0] != '-')
		{
			hold_args += argv[a];
			//arguments_v[args_so_far] = argv[a];
			//argv_hold[args_so_far] = argv[a];
	
			//cout << hold_args << endl;
			//cout << endl;
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
				else if(argv[a][b] != ' ' && argv[a][b] != '-')
				{
					//cout << argv[a][b] << endl;
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
	unsigned max_length = 0;
	fileSpecs(max_length, hold_args, output);
	max_length += 1;
	//cout << "Max Length: " << max_length << endl;
	//unsigned max_size = max_length(output);
	for(unsigned i = 0; i < output.size(); i++)
	{
		//cout << output[i] << endl;
	}
	//cout << "here" << endl;
	sort(output.begin(), output.end(), changeCaseCompare);
	//cout << "args: " << hold_args << endl;
	
	switch(arguments)
	{
		case 0:
			printNoArguments(max_length, output, hold_args);
			break;
		case 1:
			printAll(max_length, output, hold_args);
			break;
		case 2:
			printLong(max_length, output, hold_args);
			break;
		case 3:
			printAllLong(max_length, output, hold_args);
			break;
		case 4:
			printRecursive(max_length, output, hold_args);
			break;
		case 5:
			printAllRecursive(max_length, output, hold_args);
			break;
		case 6:
			printLongRecursive(max_length, output, hold_args);
			break;
		case 7:
			printAllLongRecursive(max_length, output, hold_args);
			break;
		default:
			cout << "Something went wrong" << endl; //REMOVE
			break;
	}

	
}
