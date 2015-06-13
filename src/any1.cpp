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
	any a = 1;
	if(!a.empty())
	{
		const type_info &ti = a.type();
		cout << "type: " << ti.name() << endl;
		if(a.type() == typeid(int))
			cout << any_cast<int>(a) << endl;
		else if(a.type() == typeid(double))
			cout << any_cast<double>(a) << endl;
		else
			cout << "The type of a is not an int or a double" << endl;
	}
	a = 3.65;
	if(!a.empty())
	{
		const type_info &ti = a.type();
		cout << "type: " << ti.name() << endl;
		if(a.type() == typeid(int))
			cout << any_cast<int>(a) << endl;
		else if(a.type() == typeid(double))
			cout << any_cast<double>(a) << endl;
		else
			cout << "The type of a is not an int or a double" << endl;
	}
	return 0;
}
