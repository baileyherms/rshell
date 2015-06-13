#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost;
using boost::variant;

struct func : public static_visitor<>
{
    void operator()(int i) const { cout << "integer " <<  i << endl;}
    void operator()(double d) const { cout << "double " <<  d << endl;}
    void operator()(char c) const { cout << "character " <<  c << endl;}
    void operator()(string s) const { cout << "string " << s << endl;}
};
int main()
{
    variant<int, double, char, string> var;
    var = 4;
    apply_visitor(func{}, var);
    var = 3.98;
    apply_visitor(func{}, var);
    var = 'V';
    apply_visitor(func{}, var);
    var = "hello world";
    apply_visitor(func{}, var);
    return 0;
}
