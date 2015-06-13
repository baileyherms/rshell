#include <boost/optional.hpp>
#include <iostream>

using namespace std;
using boost::optional;

double deg;
boost::optional<double> degrees()
{
	if(deg)
	{
		cout << "There is a temperature reported." << endl;
		cout << deg << " degrees" << endl;
		return optional<double>{};
	}
	else
	{
		cout << "There is no temperature reported." << endl;
		return optional<double>{};
	}
}
int main()
{
	degrees();
	deg = 43;
	degrees();
	return 0;
}
