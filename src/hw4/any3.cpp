#include <boost/any.hpp>
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using boost::any;
using boost::any_cast;
using namespace std;
using namespace boost;
int main()
{
	vector<any> v;
	vector<string> l;
	int num;
	cout << "How many students do you have? ";
	cin >> num;
	for(unsigned i = 0; i < num; i++)
	{
		int sid;
		double gpa;
		string name;
		cout << "Student " << i+1 << "'s username: ";
		cin.ignore();
		getline(cin, name);
		v.push_back(name);
		cout << "Student " << i+1 << "'s SID: ";
		cin >> sid;
		v.push_back(sid);
		cout << "Student " << i+1 << "'s GPA: ";
		cin >> gpa;
		v.push_back(gpa);
	}
	cout << "List of students:" << endl;
	for(unsigned i = 0; i < v.size(); i++)
	{
		cout << "Username: " << any_cast<string>(v.at(i)) << " ";
		i++;
		cout << "SID: " << any_cast<int>(v.at(i)) << " ";
		i++;
		cout << "GPA: " << any_cast<double>(v.at(i)) << endl;
	}
	return 0;
}
