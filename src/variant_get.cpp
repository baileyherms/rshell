#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost;
using boost::variant;

int main()
{
	variant<int, string> var, var2;
	var = 4;
	cout << get<int>(var) + get<int>(var) << endl;
	var = "hello";
	var2 = " world";
	cout << get<string>(var) + get<string>(var2) << endl;
	return 0;
}
