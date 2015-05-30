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
#include <sys/stat.h>
#include <cstdio>
#include <stdio.h>

using namespace std;

bool piping(char* arr[]);
void loop_pipe(char*** cmd)
{
	int p[2];
	pid_t pid;
	int fd_in = 0;
	//int iterate = 0;
	while(*cmd != NULL)
	{
		pipe(p);
		if((pid = fork()) == -1)
		{
			perror("loop_pipe");
			perror("fork");
			exit(1);
		}
		else if(pid == 0)
		{
			dup2(fd_in, 0);
			if(*(cmd + 1) != NULL)
			{
				dup2(p[1], 1);
			}
			else
				perror("dup2");
			if(close(p[0]) == -1)
				perror("closee");
			//cout << "execute" << endl;
			if(execvp((*cmd)[0], *cmd) == -1)
			{
				perror("execvp");
			}
			exit(1);
			
		}
		else
		{
			if(wait(NULL) == 0)
				perror("wait(NULL)");
			//close(p[0]);
			if (close(p[1]) == -1)
				perror("close");
			fd_in = p[0];
			cmd++;
			//pior_order++;
		}
	}
}
void loop_pipe(char** argv, char*** cmd, bool input, bool output, bool appending, bool number)
{
	//do output redirection and send execvp stuff to file
	
	unsigned place = 0;
	unsigned place2 = 0;
	char* in_arg[1000];
	//char* out_arg[1000];
	//char* in2_arg[1000];
	char* out2_arg[1000];
	bool stop = false;
	if(input)
	{
		while(argv[place] != NULL && !stop)
		{
			//cout << "there" << endl;
			//out_arg[place] = argv[place];
			//cout << "out_arg: " << out_arg[place] << endl;
			place++;
			if(!strcmp(argv[place], "<"))
			{
				//out_arg[place] = '\0';
				place++;
				if(argv[place] != NULL && (strcmp(argv[place], ">")) != 0 && (strcmp(argv[place], "|")) != 0 && (strcmp(argv[place], "<")) != 0 && (strcmp(argv[place], ">>")) != 0 )
				{
					if(strcmp(argv[place], ">") != 0)
					{

						in_arg[place2] = argv[place];
						//cout << "in_arg: " << in_arg[place2] << endl;
						place++;
						place2++;
						stop = true;
						if(!strcmp(argv[place], "<"))
						{
							perror("Too many '<' arguments");
							exit(1);
						}
					}
				}
				in_arg[place2] = '\0';
			}
		}
	}
	place = 0;
	place2 = 0;

	if(output || appending)
	{
		while((strcmp(argv[place], ">")))
		{
			place++;
		}
		place--;

		stop = false;
		//cout << "argv: " << argv[place] << endl;
		//cout << "place: " << place << endl;
		while(argv[place] != NULL && !stop)
		{
			//cout << "there" << endl;
			//in2_arg[place2] = argv[place];
			place++;
			place2++;
			if(!strcmp(argv[place], ">") || !strcmp(argv[place], ">>"))
			{
				//in2_arg[place2] = '\0';
				place++;
				place2 = 0;
				//if(argv[place] != NULL && (strcmp(argv[place], ">")) && (strcmp(argv[place], "|")) != 0 && (strcmp(argv[place], "<")) != 0 && (strcmp(argv[place], ">>")) != 0 )
				{
					//cout << "here" << endl;
					out2_arg[place2] = argv[place];
					//cout << "out2_arg: " << out2_arg[place2] << endl;
					place++;
					place2++;
					stop = true;
					
				}
				//cout << "out2_arg[0] " << out2_arg[0] << endl;
				out2_arg[place2] = '\0';
			}
		}
	}
	
	//start of pipe
	int p[2];
	pid_t pid;
	int fd_in = 0;
	//int iterate = 0;
	//cout << "out2_arg[0] " << out2_arg[0] << endl;
	//cout << "in_arg[0] " << in_arg[0] << endl;
	while(*cmd != NULL)
	{
		if(pipe(p) == -1)
			perror("pipe(p)");
		if((pid = fork()) == -1)
			perror("fork");
		if(input)
		{
			if(close(0) == -1)
				perror("close");
			int in = open(in_arg[0], O_RDONLY);
			if(in == -1)
			{
				perror("open in");
				exit(1);
			}
			if(dup2(in, 1) == -1)
			{
				perror("dup2");
				exit(1);
			}
		}
		if(output || appending)
		{
			if(close(1) == -1)
				perror("close");
			//cout << "out2_arg[0] " << out2_arg[0] << endl;
			int out;
			if(!appending)
			{
				out = open(out2_arg[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				if(out == -1)
				{
					perror("open");
					exit(1);
				}
			}
			else
			{
				out = open(out2_arg[0], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				if(out == -1)
				{
					perror("open");
					exit(1);
				}
			}
			/*
			if(out == -1)
			{
				perror("open out");
				exit(1);
			}
			*/
			if(dup2(out, 1) == -1)
			{
				perror("dup2");
				exit(1);
			}
		}
		if(pid == -1)
		{
			perror("loop_pipe fork error");
			exit(1);
		}	
		else if(pid == 0)
		{
			if(dup2(fd_in, 0) == -1)
				perror("dup2");
			if(*(cmd + 1) != NULL)
			{
				dup2(p[1], 1);
			}
			if(close(p[0]) == -1)
				perror("close");
			//cout << "execute" << endl;
			if(execvp((*cmd)[0], *cmd) == -1)
			{
				perror("execvp");
			}
			exit(1);
			
		}
		else
		{
			if(wait(NULL) == 0)
				perror("wait");
			//close(p[0]);
			if(close(p[1]) == -1)
				perror("close");
			fd_in = p[0];
			cmd++;
			//pior_order++;
		}
	}
}
void input_func(char **argv, bool output, bool appending, bool number)
{
	//input redirection
	//figure out what input and output would be
	unsigned place = 0;
	unsigned place2 = 0;
	char* in_arg[1000];
	char* out_arg[1000];
	bool stop = false;
	while(argv[place] != NULL && !stop)
	{
		//cout << "there" << endl;
		out_arg[place] = argv[place];
		//cout << "out_arg: " << out_arg[place] << endl;
		place++;
		if(!strcmp(argv[place], "<"))
		{
			out_arg[place] = '\0';
			place++;
			if(argv[place] != NULL && (strcmp(argv[place], ">")) != 0 && (strcmp(argv[place], "|")) != 0 && (strcmp(argv[place], "<")) != 0 && (strcmp(argv[place], ">>")) != 0 )
			{
				if(strcmp(argv[place], ">") != 0)
				{

					in_arg[place2] = argv[place];
					//cout << "in_arg: " << in_arg[place2] << endl;
					place++;
					place2++;
					stop = true;
					/*
					if(!strcmp(argv[place], "<"))
					{
						perror("Too many '<' arguments");
						exit(1);
					}
					*/
				}
			}
			in_arg[place2] = '\0';
		}
	}
	place = 0;
	//cout << "output: " << output << endl;	
	if(!output)
	{
		//cout << "not output" << endl;
		pid_t pid;
		pid = fork();
		if(pid < 0)
		{
			perror("input fork error");
			exit(1);
		}
		else if(pid == 0)
		{
			if(close(0) == -1)
				perror("close");
			int fd = open(in_arg[0], O_RDONLY);
			if(fd)
			{
				perror("open");
				exit(1);
			}
			if(dup2(fd, 0) == -1)
				perror("dup2");
			//close(fd);
			execvp(out_arg[0], out_arg);
			perror("execvp");
			exit(1);
		}
		else
		{
			if(wait(NULL) == -1)
				perror("wait");
		}
	}
	else
	{
		place = 0;
		place2 = 0;
		char* in2_arg[1000];
		char* out2_arg[1000];
		while((strcmp(argv[place], ">")))
		{
			place++;
		}
		place--;

		stop = false;
		//cout << "argv: " << argv[place] << endl;
		//cout << "place: " << place << endl;
		while(argv[place] != NULL && !stop)
		{
			//cout << "there" << endl;
			in2_arg[place2] = argv[place];
			place++;
			place2++;
			if(!strcmp(argv[place], ">") || !strcmp(argv[place], ">>"))
			{
				in2_arg[place2] = '\0';
				place++;
				place2 = 0;
				if(argv[place] != NULL && (strcmp(argv[place], ">")) && (strcmp(argv[place], "|")) != 0 && (strcmp(argv[place], "<")) != 0 && (strcmp(argv[place], ">>")) != 0 )
				{
					//cout << "here" << endl;
					out2_arg[place2] = argv[place];
					//cout << out_arg[place2] << endl;
					place++;
					place2++;
					stop = true;
					
				}
				in2_arg[place2] = '\0';
			}
		}
		if(-1 == close(0))
		{
			perror("close");
		}
		int fd = open(in2_arg[0], O_RDONLY, 0);
		if(fd == -1)
		{
			perror("open: input");
			exit(1);
		}
		
		if(dup2(fd, 0) == -1)
		{
			perror("dup2");
			exit(1);
		}
		int out;
		if(appending)
		{
			//cout << appending << endl;
			out = open(out2_arg[0], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if(out == -1)
			{
				perror("open: output");
				exit(1);

			}
		}
		else
		{
			out = open(out2_arg[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if(out == -1)
			{
				perror("open: output");
				exit(1);

			}
		}
		
		if(dup2(out, 1) == -1)
		{
			perror("dup2");
			exit(1);
		}
		if(close(fd) == -1)
		{
			perror("close");
			exit(1);
		}
		if(close(out) == -1)
		{
			perror("close");
			exit(1);
		}
		execvp(out_arg[0], out_arg);
		perror("execvp");
		exit(1);

	}
	
}

void output_func(char **argv, bool appending, bool number)
{
	//cout << "output redirection" << endl;
	unsigned place = 0;
	unsigned place2 = 0;
	char* in_arg[1000];
	char* out_arg[1000];
	bool end = false;
	/*
	while((strcmp(argv[place], ">")) != 0 && strcmp(argv[place], ">>") != 0)
	{
		place++;
	}
	place--;
	*/
	//cout << "place: " << place << endl;
	//cout << argv[place] << endl;
	unsigned port = 1;
	//cout << number << endl;
	if(number)
	{
		unsigned placement = 0;
		while(argv[place] != NULL && !end)
		{
			//cout << "there" << endl;
			in_arg[place] = argv[place];
			place++;
			if(!strcmp(argv[place], "0>") || (!strcmp(argv[place], "0>>")) || !strcmp(argv[place], "1>") || (!strcmp(argv[place], "1>>")) || !strcmp(argv[place], "2>") || (!strcmp(argv[place], "2>>")) || !strcmp(argv[place], "3>") || (!strcmp(argv[place], "3>>")))
			{
				placement = place;
				in_arg[place] = '\0';
				//cout << "in " << in_arg[place] << endl;
				place++;
				if(argv[place] != NULL && (strcmp(argv[place], ">")) && (strcmp(argv[place], "|")) != 0 && (strcmp(argv[place], "<")) != 0 && (strcmp(argv[place], ">>")) != 0 )
				{
					out_arg[place2] = argv[place];
					//cout << out_arg[place2] << endl;
					place++;
					place2++;
					end = true;
				}
				in_arg[place2] = '\0';
			}
		}
		if(!strcmp(argv[placement], "0>") || (!strcmp(argv[placement], "0>>")))
			port = 0;
		else if(!strcmp(argv[placement], "1>") || (!strcmp(argv[placement], "1>>")))
			port = 1;
		else if(!strcmp(argv[placement], "2>") || (!strcmp(argv[placement], "2>>")))
			port = 2;
		else if(!strcmp(argv[placement], "3>") || (!strcmp(argv[placement], "3>>")))
			port = 3;

	}
	else
	{
		//cout << "else" << endl;
		end = false;
		place = 0;
		while(argv[place] != NULL && !end)
		{
			//cout << "there" << endl;
			in_arg[place] = argv[place];
			//cout << "in_arg " << in_arg[place] << endl;
			place++;
			if(!strcmp(argv[place], ">") || (!strcmp(argv[place], ">>")))
			{
				in_arg[place] = '\0';
				//cout << "in " << in_arg[place] << endl;
				place++;
				if(argv[place] != NULL && (strcmp(argv[place], ">")) && (strcmp(argv[place], "|")) != 0 && (strcmp(argv[place], "<")) != 0 && (strcmp(argv[place], ">>")) != 0 )
				{
					out_arg[place2] = argv[place];
					//cout << out_arg[place2] << endl;
					place++;
					place2++;
					end = true;
				}
				out_arg[place2] = '\0';
			}
		}

	}
	place = 0;
	while(out_arg[place] != NULL)
	{
		place++;
	}
	place = 0;
	//cout << "    ";
	while(in_arg[place] != NULL)
	{
		//cout << in_arg[place] << endl;
		place++;
	}
	/*
	if(number && number != 1)
	{
		if(-1 == close(port))
		{
			perror("close");
		}
	}
	*/
	int fd;
	//cout << "here" << endl;
	if(appending)
	{
		//cout << appending << endl;
		fd = open(out_arg[0], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(fd == -1)
		{
			perror("open: output");
			exit(1);

		}
	}
	else
	{
		fd = open(out_arg[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(fd == -1)
		{
			perror("open: output");
			exit(1);

		}
	}
	/*
	if(fd == -1)
	{
		perror("open: output");
		exit(1);

	}
	*/
	if(dup2(fd, port) == -1)
	{
		perror("dup2");
		exit(1);
	}
	/*
	if(close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
	*/
	if(close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
	//cout << in_arg[0] << " " << in_arg[1] << endl;
	execvp(in_arg[0], in_arg);
	perror("execvp");
	exit(1);

}
void translator(char** argv)//, char* new_arr[])
{
	//cout << "translator" << endl;
	unsigned place = 0;
	unsigned place2 = 0;
	char* in_arg[1000];
	char* out_arg[1000];
	bool end = false;
	while(argv[place] != NULL && !end)
	{
		//cout << "there" << endl;
		in_arg[place] = argv[place];
		//cout << "in " << in_arg[place] << endl;
		place++;
		if(!strcmp(argv[place], "<<<"))
		{
			in_arg[place] = '\0';
			place++;
			while(argv[place] != NULL)
			{
				out_arg[place2] = argv[place];
				//cout << out_arg[place2] << endl;
				place++;
				place2++;
				end = true;
			}
			out_arg[place2] = '\0';
		}
	}
	//cout << "zero" << endl;
	place = 1;
	while(out_arg[0][place] != '\0')
	{
		//cout << place << endl;
		//removes quotation mark from first character in array
		out_arg[0][place-1] = out_arg[0][place];
		place++;
	}
	out_arg[0][place-1] = '\0';
	place = 0;
	//cout << "first" << endl;
	while(out_arg[place2 - 1][place] != '\0')
	{
		//removes quotation mark from last character in array
		place++;
	}
	//cout << "here" << endl;
	out_arg[place2 - 1][place - 1] = '\0';
	place = 0;
	while(out_arg[place] != '\0')
	{
		//cout << out_arg[place] << endl;
		place++;
	}
	place = 0;
	//char** new_arr = (char *) malloc(sizeof(char) * 100);
	char arr[5] = "echo";
	char* new_arr[10000];
	new_arr[0] = arr;
	place = 0;
	unsigned new_place = 1;
	
	//cout << "new_arr: " << new_arr[0] << endl;
	place = 0;
	while(out_arg[place] != '\0')
	{
		new_arr[new_place] = out_arg[place]; 
		//cout << "new: " << new_arr[new_place] << endl;
		place++;
		new_place++;
	}
	char arr2[2] = "|";
	new_arr[new_place] = arr2;
	new_place++;
	while(in_arg[place] != '\0')
	{
		new_arr[new_place] = in_arg[place];
		//cout << "new: " << new_arr[new_place] << endl;
		place++;
		new_place++;
	}
	char arr3[4] = "cat";
	new_arr[new_place] = arr3;
	new_place++;
	new_arr[new_place] = '\0';
	place = 0;
	while(new_arr[place] != '\0')
	{
		//cout << new_arr[place] << " ";
		place++;
	}
	//cout << endl;
	piping(new_arr);
	//return new_arr;
}
bool piping(char* arr[])
{
	//input first
	//then pipe
	//then output
	char* pior_order[100];//holds each of the pior in order
	vector<int> pior_place_vect;//holds where in arr each pior is
	
	//char* argv[1000];
	unsigned x = 0;
	//unsigned argv_count = 0;
	unsigned count = 0;
	bool input = false;
	bool output = false;
	//bool output_erase = false;
	bool appending = false;
	bool number = false;
	bool translate = false;
	bool pipes = false;
	vector<int> seperate_argv;
	for(unsigned i = 0; arr[i] != '\0'; i++)
	{
		//cout << arr[i] << endl;
		if(!strcmp(arr[i], "<<<") || !strcmp(arr[i], "0>") || (!strcmp(arr[i], "0>>")) || !strcmp(arr[i], "1>") || (!strcmp(arr[i], "1>>")) || !strcmp(arr[i], "2>") || (!strcmp(arr[i], "2>>")) || !strcmp(arr[i], "3>") || (!strcmp(arr[i], "3>>")) || !strcmp(arr[i], ">") ||  !strcmp(arr[i], "|") || !strcmp(arr[i], "<") || !strcmp(arr[i], ">>"))
		{
			if(!strcmp(arr[i], "<"))
			{
				input = true;
				//cout << "INPUT" << endl;
			}
			if(!strcmp(arr[i], "|"))
			{
				pipes = true;
				//cout << "PIPING" << endl;
			}
			else if(!strcmp(arr[i], ">"))
			{
				output = true;
				//cout << "OUTPUT" << endl;
			}
			else if(!strcmp(arr[i], ">>"))
			{
				appending = true;
			}
			else if(!strcmp(arr[i], "0>"))
			{
				output = true;
				number = true;
			}
			else if(!strcmp(arr[i], "1>"))
			{
				output = true;
				number = true;
			}
			else if(!strcmp(arr[i], "2>"))
			{
				output = true;
				number = true;
			}
			else if(!strcmp(arr[i], "3>"))
			{
				output = true;
				number = true;
			}
			else if(!strcmp(arr[i], "0>>"))
			{
				number = true;
				appending = true;
			}
			else if(!strcmp(arr[i], "1>>"))
			{
				number = true;
				appending = true;
			}
			else if(!strcmp(arr[i], "2>>"))
			{
				number = true;
				appending = true;
			}
			else if(!strcmp(arr[i], "3>>"))
			{
				number = true;
				appending = true;
			}
			else if(!strcmp(arr[i], "<<<"))
			{
				translate = true;
			}
			pior_order[x] = arr[i];
			x++;
			pior_place_vect.push_back(count);
		}
		else
		{
			//argv[argv_count] = arr[i];
			//cout << argv[argv_count] << endl;
			//argv_count++;
		}
		count++;
	}
	//argv[argv_count] = '\0';
	x = 0;
	//char* new_arr[10000];
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
			pipes = true;
		}
	}
	//char* name = new char[pipe_amount];
	if(translate)
	{
		translator(arr);//, new_arr);
	}
	if(input && !pipes)
	{
		//do input redirection
		//cout << "----------------------------------" << endl;
		input_func(arr, output, appending, number);
	}
	if((appending || output) && !input && !pipes)
	{
		//cout << "----------------------------------" << endl;
		//cout << "here " << appending << endl;
		output_func(arr, appending, number);
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
			/*
			while((strcmp(arr[travel], "|") != 0))
			{
				travel++;
			}
			travel--;
			*/
			while(strcmp(arr[travel], "|") != 0 && strcmp(arr[travel], ">") != 0 && strcmp(arr[travel], "<") != 0 && strcmp(arr[travel], ">>") != 0 && arr[travel] != '\0')
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
			if(input | output | appending)
				loop_pipe(arr, cmd, input, output, appending, number);
			else
				loop_pipe(cmd);
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
	
		x++;
	}
	
	return true;

}

#endif
