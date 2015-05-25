#include <iostream>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <ostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
unsigned int slash = 0;
unsigned int c = 0;
unsigned int z = 0;
void ctrl(int signal)
{
	const char *signal_name;
	sigset_t pending;

	switch(signal)
	{
		case SIGINT:
			cout << 'C';
			c++;
			break;
		case SIGQUIT:
			cout << '\\';
			slash++;
			break;
		case SIGTSTP:
			cout << 'S';
			z++;
			raise(SIGSTOP);
			break;
		default:
			cerr << "Incorrect signal" << endl;
			return;
	}

}

int main(int argc, char** argv)
{
	//print x, flush, wait 1 second, no endl, same line

	struct sigaction act;
	act.sa_handler = ctrl;
	if(sigaction(SIGINT, &act, NULL) <= -1)
	{
		perror("sigaction");
	}
	else if(sigaction(SIGQUIT, &act, NULL) <= -1)
	{
		perror("sigaction");
	}
	else if(sigaction(SIGTSTP, &act, NULL) <= -1)
	{
		perror("sigaction");
	}
	while(1)
	{
		printf("X");
		fflush(stdout);
		sleep(1);
		
		if(z==3)
		{
			cout << endl;
			cout << "Ctrl-\\ = " << slash << endl;
			cout << "Ctrl-C = " << c << endl;
			cout << "Ctrl-Z = " << z << endl;
			break;
		}
	}
		//if ctrl-c (interrupt) -> print C
	//if ctrl-\ (quit) -> print \
	//if ctrl-z (stop) -> print S and stop (fg)
	//if ctrl-z is pressed for the third time, print a summary of how many times ctrl-c, ctrl-\, and ctrl-z were pressed then exit the program (use exit())
	//
	//Handle signals: SIGINT, SIGQUIT, SIGTSTP
	return 0;
}
