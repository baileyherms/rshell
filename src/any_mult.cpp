#include <boost/any.hpp>
#include <iostream>

using boost::any;
using boost::any_cast;
using namespace std;
using namespace boost;

int main()
{
	any var = 4;
	cout << any_cast<int>(var) << endl;
	var = false;
	cout << any_cast<bool>(var) << endl;
	var = 3.25678;
	cout << any_cast<double>(var) << endl;
	var = string("hello world");
	cout << any_cast<string>(var) << endl;
	return 0;
}
