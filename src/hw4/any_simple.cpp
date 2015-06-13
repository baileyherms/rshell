#include <boost/any.hpp>
#include <iostream>

using boost::any;
using boost::any_cast;
using namespace std;
using namespace boost;

int main()
{
	any var = 4;
	var = false;
	var = 3.25678;
	var = string("hello world");
	cout << any_cast<string>(var) << endl;
	return 0;
}
