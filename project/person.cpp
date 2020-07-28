#include "person.hpp"
#include <fstream>
#include <iomanip>
using namespace std;

person::person()
{
    age=DoB.age(false);
}
person::~person()
{
    name.clear();
    tel.clear();
}

bool is_number(const string& s)
{
    return !s.empty() && find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void person::input()
{
    cout<<"Input name: ";cin>>name;
    while(true)
    {
    cout<<"Input telephone: ";cin>>tel;
    if(is_number(tel))
    {
        break;;
    }
    else
    {
        cout<<"Invalid input! Please input again!\n\n";
    }
    }
    cout<<"Input day of birth: ";
    cin>>DoB;
}
void person::output()
{
    cout<<"Name : "<<name<<endl;
    cout<<"Telephone:   "<<tel<<endl;
    cout<<"Day of birth: "<<DoB<<endl;
    cout<<"Age: "<<ceil(age)<<endl;
}
void person::print(ostream& out) const
{
    out<<name<<";"<<tel<<";"<<DoB;

}
void person::load(istream& in)
{
    string temp;
    getline(in,temp,';');
    name=temp;
    temp.clear();
    getline(in,temp,';');
    tel=temp;
    in>>DoB;
    in.ignore(1);
}
istream& operator>>(istream& in,person& a)
{
    a.load(in);
    return in;
}
ostream& operator<<(ostream& out,const person& a)
{
    a.print(out);
    return out;
}