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
	cout << "Ex 1:" << endl;
	any a = 1;
	if(!a.empty())
	{
		const type_info &ti = a.type();
		cout << "type: " << ti.name() << endl;
		if(a.type() == typeid(int))
			cout << any_cast<int>(a) << endl;
		else if(a.type() == typeid(double))
			cout << any_cast<double>(a) << endl;
		else
			cout << "The type of a is not an int or a double" << endl;
	}
	a = 3.65;
	if(!a.empty())
	{
		const type_info &ti = a.type();
		cout << "type: " << ti.name() << endl;
		if(a.type() == typeid(int))
			cout << any_cast<int>(a) << endl;
		else if(a.type() == typeid(double))
			cout << any_cast<double>(a) << endl;
		else
			cout << "The type of a is not an int or a double" << endl;
	}
	//Put in different files when submitting
	cout << "--------" << endl << "Ex 2:" << endl;
	vector<any> vect;
	for(unsigned i = 0; i < 2; i++)
	{
		int in;
		double d;
		char c;
		cout << "Insert an integer: ";
		cin >> in;
		vect.push_back(in);
		cout << "Insert a double: ";
		cin >> d;
		vect.push_back(d);
		cout << "Insert a char: ";
		cin >> c;
		vect.push_back(c);
	}
	for(unsigned i = 0; i < vect.size(); i++)
	{
		if(vect.at(i).type() == typeid(int))
			cout << any_cast<int>(vect.at(i)) << endl;
		else if(vect.at(i).type() == typeid(double))
			cout << any_cast<double>(vect.at(i)) << endl;
		else if(vect.at(i).type() == typeid(char))
			cout << any_cast<char>(vect.at(i)) << endl;
	}
	//Put in different files when submitting
	cout << "--------" << endl << "Ex 3:" << endl;
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
		v.push_back(name);//string(name));
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
	//possibly add "accessing values through a pointer" section
}
