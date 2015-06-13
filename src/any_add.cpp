#include <boost/any.hpp>
#include <iostream>
#include <string>

using boost::any;
using boost::any_cast;
using namespace std;
using namespace boost;

int main()
{
	any var = 4;
	cout << any_cast<int>(var) + any_cast<int>(var) << endl;
	var = string("ho");
	cout << any_cast<string>(var) + any_cast<string>(var) + any_cast<string>(var) << endl;
	return 0;
}
