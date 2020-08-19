#include "person.hpp"
#include <fstream>
#include <iomanip>

using namespace std;

person::person()
{
    name="";
    tel="";
    DoB=date(1900,1,1);
    age=DoB.age(false);
}
person::~person()
{
    name.clear();
    tel.clear();
}

bool is_number(const string& s)
{
    for(auto x:s)
    {
        if(x<'0'||x>'9')
        {
            return false;
        }
    }
    return !s.empty();
}

void person::input()
{
    cout<<"Input name: ";cin>>name;
    while(true)
    {
    cout<<"Input telephone: ";cin>>tel;
    if(is_number(tel))
    {
        break;
    }
    else
    {
        cout<<"Invalid input! Please input again!\n\n";
    }
    }
    cout<<"Input day of birth: \n";
    cin>>DoB;
}
void person::output(bool real_age=true)
{
    cout<<"Name : "<<name<<endl;
    cout<<"Telephone:   "<<tel<<endl;
    cout<<"Day of birth: "<<DoB<<endl;
    if(real_age)
        cout<<"Age: "<<age<<endl;
    else
    {
        cout<<"Age: "<<ceil(age)<<endl;
    }
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

tuple<date,string,string> person::get()
{
    return make_tuple(DoB,name,tel);
}
void  person::set(date Date,string Name,string Tel)
{
    DoB=Date;
    name=Name;
    tel=Tel;
    age=DoB.age(false);
}