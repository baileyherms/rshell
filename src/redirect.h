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

void loop_pipe(char*** cmd)//, char** pior_order)
{
	//cout << "command: " <<  **cmd << endl;//first command
	//cout << "pior_order: " << *pior_order << endl;//first | < > >>
	int p[2];
	pid_t pid;
	int fd_in = 0;
	int iterate = 0;
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
			//cout << "execute" << endl;
			execvp((*cmd)[0], *cmd);
			exit(1);
			
		}
		else
		{
			wait(NULL);
			//close(p[0]);
			close(p[1]);
			fd_in = p[0];
			cmd++;
			//pior_order++;
		}
	}
}
void loop_pipe_out(char*** cmd)
{
	//do output redirection and send execvp stuff to file
}
void input()
{
	//input redirection
}
/*
void output()
{
	//output redirection
}
*/
void output_erase()
{
	//output_erase redirection
}
bool piping(char* arr[])
{
	//input first
	//then pipe
	//then output
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
	bool input = false;
	bool output = false;
	bool output_erase = false;
	vector<int> seperate_argv;
	for(unsigned i = 0; arr[i] != '\0'; i++)
	{
		if((!strcmp(arr[i], "|")) || (!strcmp(arr[i], "<")) || (!strcmp(arr[i], ">")) || (!strcmp(arr[i], ">>")))
		{
			if(!strcmp(arr[i], "<"))
			{
				input = true;
			}
			else if(!strcmp(arr[i], ">"))
			{
				output = true;
			}
			else if(!strcmp(arr[i], ">>"))
			{
				output_erase = true;
			}
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
			pipe_amount++;
		}
	}
	if(input)
	{
		//do input redirection
	}
	while(x < pior_place_vect.size())
	{
		//do different pipes depending on if output
		if(!strcmp(pior_order[x], "|"))
		{
			unsigned parts = 1;//parts of the command (ex: ls | wc -l is 2 parts)
			parts += pipe_amount;
			//cout << "parts " << parts << endl;
			unsigned start1 = 0;
			unsigned start2 = 0;
			unsigned travel = 0;
			while(strcmp(arr[travel], "|") != 0 && /* strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 && */arr[travel] != '\0')
			{
				one[start1] = arr[travel];
				//cout << "one: " << one[start1] << " ";
				//cout << pior_order[0] << endl;
				start1++;
				start2++;
				travel++;
			}
			travel++;
			one[start1] = '\0';
			start1 = 0;
			if(parts >= 2)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					two[start1] = arr[travel];
					//cout << "two: " << two[start1] << " ";
					//cout << pior_order[1] << endl;
					start1++;
					start2++;
					travel++;
				}
				travel++;
				two[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 3)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
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
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					four[start1] = arr[travel];
					//cout << "four: " << four[start1] << endl;
					start1++;
					start2++;
					travel++;
				}
				travel++;
				four[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 5)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					five[start1] = arr[travel];
					start1++;
					start2++;
					travel++;
				}
				travel++;
				five[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 6)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					six[start1] = arr[travel];
					start1++;
					start2++;
					travel++;
				}
				travel++;
				six[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 7)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					seven[start1] = arr[travel];
					start1++;
					start2++;
					travel++;
				}
				travel++;
				seven[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 8)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					eight[start1] = arr[travel++];
					start1++;
					start2++;
					travel++;
				}
				travel++;
				eight[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 9)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					nine[start1] = arr[travel++];
					start1++;
					start2++;
					travel++;
				}
				travel++;
				nine[start1] = '\0';
				start1 = 0;
				x++;
			}
			if(parts >= 10)
			{
				while(travel < count && strcmp(arr[travel], "|") != 0)// && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], ">>") != 0 )
				{
					ten[start1] = arr[travel];
					start1++;
					start2++;
					travel++;
				}
				travel++;
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

			loop_pipe(cmd);//, pior_order);

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
			//break;
		}
		else if(!strcmp(pior_order[x], "<"))
		{
			//ignore, done at beginning
		}
		else if(!strcmp(pior_order[x], ">"))
		{
			//do output
		}
		else if(!strcmp(pior_order[x], ">>"))
		{
			//do output erase
		}
		
		
		
		
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
		
		x++;
	}
	
	return true;

}

#endif
