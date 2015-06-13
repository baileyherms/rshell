#include <boost/optional.hpp>
#include <iostream>

using namespace std;
using boost::optional;

double deg;
boost::optional<double> degrees()
{
	if(deg)
	{
		return deg;
	}
	else
	{
		return optional<double>{};
	}
}
int main()
{
	degrees();
	if(deg)
		cout << "The temperature is " << deg << " degrees." << endl;
	else
		cout << "There is no temperature reported." << endl;
	deg = 43;
	degrees();
	if(deg)
		cout << "The temperature is " << deg << " degrees." << endl;
	else
		cout << "There is no temperature reported." << endl;
	return 0;
}
