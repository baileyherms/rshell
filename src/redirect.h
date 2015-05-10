#ifndef __PIPING_H__
#define __PIPING_H__
#include <iostream>
#include <string>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>

using namespace std;

bool piping(char* arr[])
{
	int x = 0;
	vector<string> pior_vect;
	unsigned pior_place = 0;
	vector<unsigned> pior_place_vect;
	char *argv[10000];
	unsigned argv_place = 0;
	bool is_pipe = false;
	////find the |, <, >, >>
	while(arr[x] != '\0')
	{
		//cout << arr[x] << " ";
		if(!strcmp(arr[x], "|") || !strcmp(arr[x], "<") || !strcmp(arr[x], ">") || !strcmp(arr[x], ">>"))
		{
			if(!strcmp(arr[x], "|"))
			{
				is_pipe = true;
			}
			//cout << arr[x] << " ";//DELETE
			pior_vect.push_back(arr[x]);	
			pior_place_vect.push_back(pior_place);
			pior_place = 0;
		}
		else
		{
			argv[argv_place] = arr[x];
			cout << argv[argv_place] << " ";
			argv_place++;
		}
		pior_place++;
		x++;
	}
	cout << endl;
	for(int i = 0; i < pior_place_vect.size(); i++)
	{
		//cout << pior_place_vect.at(i) << endl;//DELETE
	}
	
	//Need to send the left side of the pipe to the right side of the pipe

	//dup
	int pid = fork();
	if(pid == -1)
	{
		perror("There was an error with fork().");
		return false;
		//exit(1);
	}
	else if(pid == 0)
	{
		cout << "This is the child process." ;
		if(-1 == execvp(argv[0], argv))
		{
			perror("There was an error in execvp.");
			return false;
			//exit(1);
		}
	}
	else if(pid > 0)
	{
		if(-1 == wait(0))
		{
			perror("There was an error with wait().");
		}
	}
	int savestdin;
	if(-1 == (savestdin == dup(0)))
	{
		perror("There is an error with dup.");
	}
	//Needs to be restored after pipe, not before
	if(-1 == dup2(savestdin, 0))
	{
		perror("There is an error with dup2.");
	}

	//pipe
	if(is_pipe)
	{
		const int PIPE_READ = 0;
		const int PIPE_WRITE = 1;
		int fd[2];
		if(pipe(fd) == -1)//call to pipe, it puts the read end and write end file descriptors in fd
		   perror("There was an error with pipe(). ");

		pid = fork();
		if(pid == -1)//fork’s return value for an error is -1
		{
		   perror("There was an error with fork(). ");
		   exit(1);//there was an error with fork so exit the program and go back and fix it
		}
		else if(pid == 0)//when pid is 0 you are in the first child process
		{
		   cout<<"This is the first child process ";

		   //write to the pipe
		   if(-1 == dup2(fd[PIPE_WRITE],1))//make stdout the write end of the pipe
			  perror("There was an error with dup2. ");
		   if(-1 == close(fd[PIPE_READ]))//close the read end of the pipe because we're not doing anything with it right now
			  perror("There was an error with close. ");

		   if(-1 == execvp(argv[0], argv))
			  perror("There was an error in execvp. ");


		   exit(1);  //prevents zombie process
		}
		//if pid is not 0 then we’re in the first parent
		else if(pid > 0) //first parent function
		{
		   //read end of the pipe
		   int savestdin;
		   if(-1 == (savestdin = dup(0)))//need to restore later or infinite loop
			  perror("There is an error with dup. ");
		   if( -1 == wait(0)) //wait for the child process to finish executing
			  perror("There was an error with wait().");

		   int pid2 = fork();
		   if(pid2 == -1)//fork's return value for an error is -1
		   {
			  perror("There was an error with fork(). ");
			  exit(1);//there was an error with fork so exit the program and go back and fix it
		   }
		   else if(pid2 == 0)//when pid2 is 0 you are in the second child process
		   {
			  cout << "This is the second child process ";

			  if(-1 == dup2(fd[PIPE_READ],0))//make stdin the read end of the pipe
				 perror("There was an error with dup2.");
			  if(-1 == close(fd[PIPE_WRITE]))//close the write end of the pipe because we're not doing anything with it right now
				 perror("There was an error with close.");

			  if(-1 == execvp(argv[0], argv))
				 perror("There was an error in excecvp. ");

			  exit(1); //prevents zombie process
		   }
		   else if(pid2 > 0) //second parent function
		   {
			  if(-1 == wait(0)) //wait for the child process to finish executing
				 perror("There was an error with wait(). ");
		   }

		   if(-1 == dup2(savestdin,0))//restore stdin
			  perror("There is an error with dup2. ");
		}	
	}
	return true;
}

#endif
