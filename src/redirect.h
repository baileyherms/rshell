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

void loop_pipe(char ***cmd)
{
	int p[2];
	pid_t pid;
	int fd_in = 0;
	while(*cmd != NULL)
	{
		pipe(p);
		if((pid = fork()) == -1)
		{
			perror("loop_pipe fork error");
			exit(1);
		}
		else if(pid == 0)
		{
			dup2(fd_in, 0);
			if(*(cmd + 1) != NULL)
			{
				dup2(p[1], 1);
			}
			close(p[0]);
			execvp((*cmd)[0], *cmd);
			exit(1);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0];
			cmd++;
		}
	}
}

bool piping(char* arr[])
{
	char* pior_order[100];//holds each of the pior in order
	vector<int> pior_place_vect;//holds where in arr each pior is
	/*
	int x = 0;
	//DELETE OUTPUT LATER
	
	while(arr[x] != '\0')
	{
		cout << arr[x];
		x++;
	}
	
	cout << endl;
	*/
	char* argv[1000];
	unsigned x = 0;
	unsigned argv_count = 0;
	unsigned count = 0;
	vector<int> seperate_argv;
	for(unsigned i = 0; arr[i] != '\0'; i++)
	{
		if((!strcmp(arr[i], "|")) || (!strcmp(arr[i], "<")) || (!strcmp(arr[i], ">")) || (!strcmp(arr[i], ">>")))
		{
			pior_order[x] = arr[i];
			x++;
			pior_place_vect.push_back(count);
		}
		else
		{
			argv[argv_count] = arr[i];
			argv_count++;
		}
		count++;
	}
	argv[argv_count] = '\0';
	x = 0;
	char* one[20];
	char* two[20];
	char* three[20];
	char* four[20];
	char* five[20];
	char* six[20];
	char* seven[20];
	char* eight[20];
	char* nine[20];
	char* ten[20];
	char** cmd[11];
	unsigned pipe_amount = 0;

	for(unsigned i = 0; i < pior_place_vect.size(); i++)
	{
		if(!strcmp(pior_order[x], "|"))
		{
			//cout << pipe_amount << endl;
			pipe_amount++;
		}
	}
	while(x < pior_place_vect.size())
	{
		if(!strcmp(pior_order[x], "|"))
		{
			unsigned parts = 1;//parts of the command (ex: ls | wc -l is 2 parts)
			parts += pipe_amount;
			//cout << parts << endl;
			unsigned start1 = 0;
			unsigned start2 = 0;
			unsigned travel = 0;
			while(strcmp(arr[travel], "|") != 0 && arr[travel] != '\0')
			{
				//cout << argv[start1] << endl;
				one[start1] = arr[travel];
				//cout << "one: " << one[start1] << endl;
				start1++;
				start2++;
				travel++;
			}
			travel++;
			one[start1] = '\0';
			start1 = 0;
			if(parts >= 2)
			{
				//cout << "arr " << arr[travel] << endl;
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					//cout << "parts == 2" << argv[start2] << endl;
					two[start1] = arr[travel];
					//cout << "two: " << two[start1] << endl;
					start1++;
					start2++;
					travel++;
				}
				//cout << "here" << endl;
				travel++;
				two[start1] = '\0';
				start1 = 0;
				x++;
				//cout << "here" << endl;
			}
			//cout << "here" << endl;
			if(parts >= 3)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					three[start1] = arr[travel];
					//cout << "three: " << three[start1] << endl;
					start1++;
					start2++;
					travel++;
				}
				travel++;
				three[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 4)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					//cout << argv[start2] << endl;
					four[start1] = argv[start2];
					//cout << "two: " << two[start1] << endl;
					start1++;
					start2++;
					travel;
				}
				travel++;
				four[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 5)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					five[start1] = argv[start2];
					//cout << "three: " << three[start1] << endl;
					start1++;
					start2++;
				}
				five[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 6)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					//cout << argv[start2] << endl;
					six[start1] = argv[start2];
					//cout << "two: " << two[start1] << endl;
					start1++;
					start2++;
				}
				six[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 7)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					seven[start1] = argv[start2];
					//cout << "three: " << three[start1] << endl;
					start1++;
					start2++;
				}
				seven[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 8)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					//cout << argv[start2] << endl;
					eight[start1] = argv[start2];
					//cout << "two: " << two[start1] << endl;
					start1++;
					start2++;
				}
				eight[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 9)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					nine[start1] = argv[start2];
					//cout << "three: " << three[start1] << endl;
					start1++;
					start2++;
				}
				nine[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 10)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)
				{
					ten[start1] = argv[start2];
					//cout << "three: " << three[start1] << endl;
					start1++;
					start2++;
				}
				ten[start1] = '\0';
				start1 = 0;
				x++;
			}
			
			if(parts >= 1)
				cmd[0] = one;
			if(parts >= 2)
				cmd[1] = two;
			if(parts >= 3)
				cmd[2] = three;
			if(parts >= 4)
				cmd[3] = four;
			if(parts >= 5)
				cmd[4] = five;
			if(parts >= 6)
				cmd[5] = six;
			if(parts >= 7)
				cmd[6] = seven;
			if(parts >= 8)
				cmd[7] = eight;
			if(parts >= 9)
				cmd[8] = nine;
			if(parts >= 10)
				cmd[9] = ten;
			cmd[parts] = '\0';
			//cout << "here" << endl;
			//cout << cmd[0][0] << endl;
			//cout << cmd[1][1] << endl;

			loop_pipe(cmd);

			/*
			while(!strcmp(pior_order[x], "|"))
			{
				//Need to find out how many pipes and how many times each set (ex: ls -a or wc -l) 					is put into a pipe
				

				if(x == 0)
				{
					unsigned trav = pior_place_vect.at(x) + 1;
					unsigned go = 0;
					while(go < pior_place_vect.at(x))
					{
						beg[go] = arr[go];
						cout << "begin: " << beg[go] << endl;
						go++;	
					}
					beg[go] = '\0';
					go = 0;
					while(arr[trav] != '\0' && !((!strcmp(arr[trav], "|")) || (!strcmp(arr[trav], "<")) || (!strcmp(arr[trav], ">")) || (!strcmp(arr[trav], ">>"))))
					{
						end[go] = arr[trav];
						cout << "end: " << end[go] << endl;
						go++;
						trav++;
					}
					end[go] = '\0';
				}
				else
				{
					unsigned trav = pior_place_vect.at(x) + 1;
					unsigned go = 0;
					go = pior_place_vect.at(x-1) + 1;
					while(go < pior_place_vect.at(x))
					{
						beg[go] = arr[go];
						cout << "begin: " << beg[go] << endl;
						go++;
					}
					beg[go] = '\0';
					go = 0;
					while(arr[trav] != '\0' && !((!strcmp(arr[trav], "|")) || (!strcmp(arr[trav], "<")) || (!strcmp(arr[trav], ">")) || (!strcmp(arr[trav], ">>"))))
					{
						end[go] = arr[trav];
						cout << "end: " << end[go] << endl;
						go++;
						trav++;
					}
					end[go] = '\0';
				}
				x++:
			}
			*/
			break;
		}
		
		
		char* beg[20];
		char* end[20];
		if(x == 0)
		{
			unsigned trav = pior_place_vect.at(x) + 1;
			unsigned go = 0;
			while(go < pior_place_vect.at(x))
			{
				beg[go] = arr[go];
				cout << "begin: " << beg[go] << endl;
				go++;	
			}
			beg[go] = '\0';
			go = 0;
			while(arr[trav] != '\0' && !((!strcmp(arr[trav], "|")) || (!strcmp(arr[trav], "<")) || (!strcmp(arr[trav], ">")) || (!strcmp(arr[trav], ">>"))))
			{
				end[go] = arr[trav];
				cout << "end: " << end[go] << endl;
				go++;
				trav++;
			}
			end[go] = '\0';
		}
		else
		{
			unsigned trav = pior_place_vect.at(x) + 1;
			unsigned go = 0;
			go = pior_place_vect.at(x-1) + 1;
			while(go < pior_place_vect.at(x))
			{
				beg[go] = arr[go];
				cout << "begin: " << beg[go] << endl;
				go++;
			}
			beg[go] = '\0';
			go = 0;
			while(arr[trav] != '\0' && !((!strcmp(arr[trav], "|")) || (!strcmp(arr[trav], "<")) || (!strcmp(arr[trav], ">")) || (!strcmp(arr[trav], ">>"))))
			{
				end[go] = arr[trav];
				cout << "end: " << end[go] << endl;
				go++;
				trav++;
			}
			end[go] = '\0';
		}
		cout << "pior_order: " << pior_order[x] << endl;
		
		/*
		if(!strcmp(pior_order[x], "|"))
		{
			cout << "HERE" << endl;
			int des_p[2];
			if(pipe(des_p) == -1)
			{
				perror("Pipe failed");
				exit(1);
			}
			if(fork() == 0)
			{
				close(1);
				dup(des_p[1]);
				close(des_p[0]);
				close(des_p[1]);
				
				if(-1 == execvp(beg[0], beg))
				{
					perror("execvp of first parameter");
					exit(1);
				}
			}
			if(fork() == 0)
			{
				close(0);
				dup(des_p[0]);
				close(des_p[1]);
				close(des_p[0]);
				
				if(-1 == execvp(end[0], end))
				{
					perror("execvp of second parameter");
					exit(1);
				}
			}
			close(des_p[0]);
			close(des_p[1]);
			wait(0);
			wait(0);
		}
		*/
		if(!strcmp(pior_order[x], "<"))
		{

		}
		else if(!strcmp(pior_order[x], ">"))
		{

		}
		else if(!strcmp(pior_order[x], ">>"))
		{

		}
		else
		{
			//error, should never go here
		}
		x++;
	}

	/*
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
	
	int fd[2];
	
	if(-1 == pipe(fd))
	{
		perror("pipe");
	}
	cerr << "fd[0] = " << fd[0] << endl;
	cerr << "fd[1] = " << fd[1] << endl;
	
	if(-1 == write(fd[1], execvp(argv[0], argv), 10000))
	{
		perror("write");
	}
	char buf[BUFSIZ];
	read(fd[0], buf, 11);
	cerr << "buf = " << buf << endl;
	return 0;
	
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
	*/
	return true;

}

#endif
