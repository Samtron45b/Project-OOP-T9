#include "guest.hpp"
#include <fstream>
#include <iomanip>

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

