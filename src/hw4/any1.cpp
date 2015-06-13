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

void type(any a)
{
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
}
int main()
{
	any a = 1;
	type(a);
	a = 3.65;
	type(a);
	return 0;
}
