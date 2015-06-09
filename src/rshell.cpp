#include <iostream>
#include <string>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <stdio.h>

#include <vector>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

using namespace std;
//using namespace boost;
#define MAXSIZE 10000
void get_input(string& usr_input)
{
	char arr[MAXSIZE];//tokenize
	char* argv[MAXSIZE];
	//char* con_arr[MAXSIZE];//stores connectors
	char* cmdargv[MAXSIZE];
	for(unsigned i = 0; i < MAXSIZE; i++)
	{	
		arr[i] = 0;
		argv[i] = 0;
		cmdargv[i]=0;
		//con_arr[i] = 0;
	}
	int index=0;	//cmd argv index
	int start=0;	//current cmd starts in arr[]
	int j_index=0;	//argv index 
	int n_index=0;	//arr index
	//int k=0;		//arr char ptr;
	int c_cnt=0;	//current word size
	char tmp;
	//cout<<"In getinput="<<usr_input.size()<<endl;
	for(unsigned i = 0; i < usr_input.size(); i++)
	{
		tmp=usr_input.at(i);
		if(tmp==' '||tmp==';'||tmp=='&'||tmp=='|'||tmp=='#')
		{
			if(c_cnt>0)
			{
			argv[j_index]=(char*)&arr[start];
			j_index++;
			c_cnt=0;
			arr[n_index]='\0';
			n_index++;
			}
			start=n_index;
			if (tmp!=' ')
			{
				switch(tmp)
				{
					case '#':
						start=n_index;
						arr[n_index++]=';';
												
						
						
						argv[j_index]=(char*)&arr[start];
						c_cnt=0;
						i=usr_input.size();
						j_index++;
						break;
					case ';':
						arr[n_index++]=';';
						arr[n_index++]='\0';
						argv[j_index]=(char*)&arr[start];
						start=n_index;
						j_index++;
						c_cnt=0;
						break;
					case '&':
						if(usr_input.at(i+1)=='&')
						{
							arr[n_index++]='&';
							arr[n_index++]='&';
							arr[n_index++]='\0';
							argv[j_index]=(char*)&arr[start];
							j_index++;
							start=n_index;
							c_cnt=0;
							i++;
						}
						break;
					case '|':
						if(usr_input.at(i+1)=='|')
						{
							arr[n_index++]='|';
							arr[n_index++]='|';
							arr[n_index++]='\0';
							argv[j_index]=(char*)&arr[start];
							j_index++;
							start=n_index;
							c_cnt=0;
							i++;
						}
						break;
						
				}
			}
		}else
		{
			//arr[i] = usr_input[i];
			arr[n_index]=usr_input.at(i);
			c_cnt++;
			n_index++;
			if(i==usr_input.size()-1)
			{
				argv[j_index]=(char*)&arr[start];
				n_index++;
				j_index++;
			}
		}
	}
	if(strcmp(argv[j_index-1],";")!=0)
	{
		n_index++;
		start=n_index;
		arr[n_index++]=';';
		argv[j_index]=(char*)&arr[start];
		j_index++;
	}
	argv[j_index]=(char*)NULL;
	
	//debug INPUT to arguments display
	/*
	cout<<"J="<<j_index<<endl;
	for(int i=0;i<j_index;i++)
	{
		cout<<"Arg="<<i<<":"<<argv[i]<<endl;
	}
	//return;
	*/
	
	//char* tok = strtok(arr, " \t");
	//vector<int> cmd_arg_amt;
	//int x = 0;
	//while(tok != NULL)
	//{
	//	argv[x] = tok;
	//	x++;
	//	tok = strtok(NULL, " \t");
	//}
	//argv[x] = '\0';
	
	//int con_amount = 0;
	//int hold_amt = 0;
	
	
	
	//char* con_arr[MAXSIZE];//stores connectors
	;
	int status;
	for(int i = 0; i < j_index; i++)
	{
		if(strcmp(argv[i], "&&")==0 || strcmp(argv[i], "||")==0 || strcmp(argv[i], ";")==0)
		{
			//cout<<"CMD="<<argv[i]<<endl;
			int pid;
			pid=fork();
			if(pid<0)
			{
				//Big prolem
				cout<<"Fork problem"<<endl;
				//exit(1);
			}
			else if(pid==0) //starting child process
			{
				//int status;
				cmdargv[index]=NULL;
				status=execvp(cmdargv[0],cmdargv);
				if(status==-1)
				{
					perror("Error CMD\n");
					int x;
					int nxt=-1;
					if(strcmp(argv[i],"&&")==0)
					{
						for(x=i+1;x<j_index;x++)
						{
							if( strcmp(argv[x], "||")==0 || strcmp(argv[x], ";")==0)
							{
								nxt=x;
								break;
								
							}
						}
						if(nxt>0)i=nxt;
					}
				}
				index=0;
				exit(status);
			}
			else
			{
			}
			//Normal program ends here
			waitpid(-1, &status, 0);
			if(strcmp(argv[i], "&&")==0 && (status > 0))	//failed on prameter 
					{
						int x;
						int nxt = -1;
						x = i+1;
						for(;x<j_index; x++)
						{
							
							if( strcmp(argv[x], "&&")==0||strcmp(argv[x], "||")==0 || strcmp(argv[x], ";")==0)
							{
								nxt = x;
								break;
							}
						}
						if(nxt>0)
						{
							i = nxt;
							nxt = -1;
						}
					}
			if(strcmp(argv[i], "||")==0 && (status == 0))
			{
				//break;
				int x;
						int nxt = -1;
						x = i+1;
						for(;x<j_index; x++)
						{
							
							if( strcmp(argv[x], "&&")==0||strcmp(argv[x], "||")==0 || strcmp(argv[x], ";")==0)
							{
								nxt = x;
								break;
							}
						}
						if(nxt>0)
						{
							i = nxt;
							nxt = -1;
						}
			}
			index=0;
			
		}
		else
		{
			if(index==0 && (strcmp(argv[i],"exit"))==0)exit(1);
			cmdargv[index]=argv[i];
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
	//cout<<"In output:"<<usr_input<<endl;
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

