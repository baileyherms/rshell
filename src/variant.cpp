#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using boost::variant;
using namespace boost;

vector<char> connectors;
vector<string> commands;
struct output : public boost::static_visitor<>
{
	void operator()(char c) const
	{
		connectors.push_back(c);
	}
	void operator()(string s) const
	{
		commands.push_back(s);
	}
};

int main()
{
	vector<variant<string, char>> vect;
	vect = {"cat", '<', "in.txt", '|', "tr", "A-Z", "a-z", '>', "out.txt"};
	cout << "Original: ";
	for(unsigned i = 0; i < vect.size(); ++i)
	{
		boost::apply_visitor(output{}, vect.at(i));
		cout << vect.at(i) << " ";
	}
	//Put into an example file, only put the relevent parts (ex: above stuff) in the writeup, reference the other stuff and say "if we output the commands vector and the connectors vector we get the following: then put the compiled and run code in the writeup"
	cout << endl;
	cout << "Commands: ";
	for(unsigned i = 0; i < commands.size(); ++i)
	{
		cout << commands.at(i) << " ";
	}
	cout << endl;
	cout << "Connectors: ";
	for(unsigned i = 0; i < connectors.size(); ++i)
	{
		cout << connectors.at(i) << " ";
	}
	cout << endl;
}
