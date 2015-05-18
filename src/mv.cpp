#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
	char srcf[1000];
	strcpy(srcf, argv[1]); 
	//if file1 DNE, print error
	struct stat s;
	if (-1 == stat(srcf, &s))
	{
		cout << "ERROR: " << srcf << " does not exist." << endl;
		exit(1);
	}

	char dstf[1000];
	strcpy(dstf, argv[2]); 
	//if file2 DNE, rename file1 to file2
	if (-1 == stat (dstf, &s))
	{
		if (-1 == link(srcf, dstf))
		{
			perror("link failed");
			exit(1);
		}
		if (-1 == unlink(srcf))
		{
			perror("unlink failed");
			exit(1);
		}
	}

	//if file2 exists
	else
	{
	//if file2 is direc, move file1 into file2
		if (S_IFDIR & s.st_mode)
		{
			char nf[1000];
			strcpy(nf, ".");
			strcat(nf, "/");
			strcat(nf, dstf);
			strcat(nf, "/");
			strcat(nf, srcf);

			if (-1 == link(srcf, nf))
			{
				perror("link failed");
				exit(1);
			}
			if (-1 == unlink(srcf))
			{
				perror("unlink failed");
				exit(1);
			}
		}
	//if file2 is not direc, print error
		else 
		{
			cout << "ERROR: " << dstf << " is not a directory." << endl;
		}
	}

	return 0;
}
