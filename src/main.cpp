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
		//int max_input = 10000; //change later
		string usr_input;
		vector<string> cmd_arg;//user arguments after token separation
		int hold = 0;
		
		cout << "$";
		getline(cin, usr_input);
		unsigned int input_size = usr_input.size() * 2;//just in case


		while(hold < usr_input.size())
		{
			//check the command line argument
			hold++;
		}

		char_separator<char> cmd_tok(" ", "; #");//add other tokens
		tokenizer<char_separator<char>> mytok(usr_input, cmd_tok);
		
		for(auto it = mytok.begin(); it != mytok.end(); ++it)
		{
			if(*it == "&&")
			{
			}
			else if(*it == "||")
			{
			}
			else if(*it == ";")
			{
			}
			else if(*it == "#")
			{
				break;
			}
			else
			{
				cmd_arg.push_back(*it);
			}
		}
		for(int i = 0; i < cmd_arg.size(); i++)
		{
			cout << cmd_arg[i] << endl;
			//Get 1st, 2nd, 3rd argument
		}
	}
	return 0;
}
