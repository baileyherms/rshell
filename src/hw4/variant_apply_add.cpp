#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost;
using boost::variant;

struct func : public static_visitor<>
{
    void operator()(int i) const { cout << "integer " << i + i << endl;}
    void operator()(string s) const { cout << "string " << s + s << endl;}
};
int main()
{
    variant<int, string> var;
    var = 4;
    apply_visitor(func{}, var);
    var = "hello";
    apply_visitor(func{}, var);
    return 0;
}
