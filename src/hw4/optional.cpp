#include <boost/optional.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace boost;
using boost::optional;

optional<int> get_random_number()
{
	int i = rand();
	return (i % 2 == 0) ? i : optional<int>{};
}
int main()
{
	srand(static_cast<unsigned int>(time(0)));
	for(unsigned i = 0; i < 10; i++)
	{
		optional<int> temp = get_random_number();
		if(temp)
			cout << sqrt(static_cast<float>(*temp)) << endl;
	}
}
