//main file for rshell
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{

	while(1)
	{
		int max_input = 1000; //change later
		char usr_input[max_input];
	
		int hold = 0;
		
		cout << "$";
		cin.getline(usr_input, max_input);


		while(hold < max_input)
		{
			//check the command line argument
			hold++;
		}
	}
	
	return 0;//will return false
}
