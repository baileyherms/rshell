#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <fcntl.h>

using namespace std;

void rm(const char* file)
{
    struct stat filespec;
    if(stat(file, &filespec) < 0)
	{
        perror("stat");
    }
    bool dict = (S_ISDIR(filespec.st_mode));
    if(dict)
	{
		//cout << "here" << endl;
		//Similar to homework #1
        DIR *dirp;
        if(NULL == (dirp = opendir(const_cast<char*>(file))))
		{
            perror("opendir");
        }
        struct dirent *d_file;
        while(NULL != (d_file = readdir(dirp)))
		{
            if(strcmp(d_file->d_name, ".") && strcmp(d_file->d_name, ".."))
            {
				string holdFile = file;
				holdFile.append("/");
				holdFile.append(d_file->d_name);
				rm(holdFile.c_str());
			}
        }
		closedir(dirp);
        //DIR *dirr = closedir(const_cast<char*>(file));
		//{
			//perror("closedir");
		//}
        rmdir(file);
        if(rmdir(file))
		{
			//perror("rmdir");
		}
		
		//Add error checking, will remove directory and give 1 else give 0
    }
    else
    {    
		unlink(file);
	}
}
int main(int argc, char* argv[])
{
	bool rflag;
    int hold;
	rflag = false;
    hold = 1;
	if(strcmp(argv[hold], "-r") == 0)
	{
        hold++;
        rflag = true;
    }
    for(int i = hold; i < argc; i++)
    {
		string temp = argv[i];
        struct stat filespec;
        if(stat(argv[i], &filespec) < 0)
        {
			//cannot find the status of the file
		    perror("stat");
		}
        bool dict = (S_ISDIR(filespec.st_mode));
        if(dict && !rflag)
		{
			//If directory but not -r flag
            cout << "You fucked up" << endl;
			exit(0);
        }
        else if(dict && rflag)
		{
			//if directory and -r flag
            if(temp.at(temp.size()-1) == '/')
			{
                temp.pop_back();
            }
            //rm function with directory
			rm(temp.c_str());
        }
        else
		{
			//rm file
            rm(argv[i]);
    	}
	}
    return 0;
}
