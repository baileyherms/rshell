#ifndef __PIPING_H__
#define __PIPING_H__
#include <iostream>
#include <string>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>

using namespace std;

void piping(char* arr[])
{
	int x = 0;
	//DELETE OUTPUT LATER
	while(arr[x] != '\0')
	{
		cout << arr[x];
		x++;
	}
	cout << endl;
	//traverse the array, stop when && or || or ; or # or NULL is found
	////find the |, <, >, >>
	
}

#endif
