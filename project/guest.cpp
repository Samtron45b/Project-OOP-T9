#include "guest.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include "myLib.hpp"

using namespace std;

const string url="./project/data/";

void guest::input()
{
    person::input();
}

void guest::output()
{
    person::output(false);
    for(auto x:cart)
    {
        cout<<left<<setfill(' ')<<setw(25)<<x.first.name<<setw(4)<<'|'<<setw(4)<<x.second<<setw(4)<<'|'<<setw(4)<<x.first.price<<'|'<<right<<setw(9)<<x.first.price*x.second<<"   |"<<endl;
        cout<<setfill('-')<<setw(50)<<"-\n";
    }
    cout<<"\n";
    // ! Sẽ được viết ở main sau output cout<<"Total: "<<payment()<<endl;
}

void guest::export()
{
    date today;
    string link = url+"/export/"+to_string(today.day)+'_'+to_string(today.month)+'_'+to_string(today.year)+'/';
    int count;
    fstream file1(link+"count.dat",ios::in);
    if(file1.is_open())
    {
        file1>>count;
        file1.close();
    }
    else
    {
        throw "File not found";
    }
    string fileName="#"+string(4-(int)(log10(count)),'0')+to_string(count);
    ofstream file2(link+fileName+".exe");
    if(file2.is_open())
    {
        file2<<setfill('*')<<setw(29)<<fileName<<setw(23)<<"*\n";
        auto [DoB1,name1,tel1]=person::get();
        auto [hour,min,sec]=currentTime();
        int age=DoB1.age(true);
        file2<<"Name        : "<<name1<<endl;
        file2<<"Telephone   : "<<tel1<<endl;
        file2<<"Day of birth: "<<DoB1<<endl;
        file2<<"Age         : "<<age<<endl;
        file2<<setfill('*')<<setw(52)<<"*\n";
        for(auto x:cart)
        {
        file2<<left<<setfill(' ')<<setw(25)<<x.first.name<<setw(4)<<'|'<<setw(4)<<x.second<<setw(4)<<'|'<<setw(4)<<x.first.price<<'|'<<right<<setw(11)<<x.first.price*x.second<<"   |"<<endl;
        file2<<setfill('-')<<setw(52)<<"-\n";
        }
        file2<<"\n";
        file2<<setfill('*')<<setw(52)<<"*\n\n";
        file2<<"Total       : "<<setfill(' ')<<setw(38)<<setprecision(3)<<payment()<<endl;
        file2.close();
    }

}

double guest::payment()
{
    double money=0;
    for(auto x: cart)
    {
        money+= x.first.price*x.second;
    }
    return money;
}

