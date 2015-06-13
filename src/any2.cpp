#include <boost/any.hpp>
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using boost::any;
using boost::any_cast;
using namespace std;
using namespace boost;
int main()
{
	vector<any> vect;
	int in;
	double d;
	char c;
	cout << "Insert an integer: ";
	cin >> in;
	vect.push_back(in);
	cout << "Insert a double: ";
	cin >> d;
	vect.push_back(d);
	cout << "Insert a char: ";
	cin >> c;
	vect.push_back(c);
	for(unsigned i = 0; i < vect.size(); i++)
	{
		if(vect.at(i).type() == typeid(int))
			cout << any_cast<int>(vect.at(i)) << endl;
		else if(vect.at(i).type() == typeid(double))
			cout << any_cast<double>(vect.at(i)) << endl;
		else if(vect.at(i).type() == typeid(char))
			cout << any_cast<char>(vect.at(i)) << endl;
	}
	return 0;
}
