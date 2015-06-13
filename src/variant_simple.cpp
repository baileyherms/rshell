#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost;
using boost::variant;

int main()
{
	variant<char, string> var;
	var = 'V';
	cout << var << endl;
	var = "hello world";
	cout << var << endl;
	return 0;
}
