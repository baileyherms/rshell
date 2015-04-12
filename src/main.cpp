//main file for rshell
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <vector>

using namespace std;
using namespace boost;

//make functions

int main(int argc, char *argv[])
{
	while(1)
	{
		int max_input = 1000; //change later
		string usr_input;

		int hold = 0;
		
		cout << "$";
		getline(cin, usr_input);


		while(hold < usr_input.size())
		{
			//check the command line argument
			hold++;
		}

		vector<char> cmd_arg;//user arguments after token separation
		char_separator<char> cmd_tok(" ", "; #");//add other tokens
		tokenizer<char_separator<char>> mytok(usr_input, cmd_tok);
		
		for(auto it = mytok.begin(); it != mytok.end(); ++it)
		{
			if(*it == "&&")
			{
				cout << "&&";//REMOVE
				cout << endl;
				//do something
			}
			else if(*it == "||")
			{
				cout << "||";//REMOVE
				cout << endl;
				//do something
			}
			else if(*it == ";")
			{
				cout << ";";//REMOVE
				cout << endl;
				//do something
			}
			else if(*it == "#")
			{
				cout << "#";//REMOVE
				cout << endl;
				//ignore/exit?
			}
			else
			{
				cout << "else";//REMOVE
				cout << endl;
				//add to cmd_arg vector
			}
		}
	}
	return 0;
}
