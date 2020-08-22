#include "item.hpp"
#include "myLib.hpp"
#include <fstream>
#include <set>
#include <algorithm>
using namespace std;

const string url="./data/";

item::item()
{   
    id=0;
    storage=0;
    name="";
    price=0;
}
item::item(int ID ,string Name,int Store,double Price)
{
    id=ID;
    name=Name;
    storage=Store;
    price=Price;
}
bool item::get(int ID)
{
    item a;
    fstream myFile(url+"item/info.dat",ios::in);
    set<item> list;
    bool found=false;
    if(myFile.is_open())
    {
        item temp;
        while(myFile>>temp)
        {
            list.insert(temp);
        }
        myFile.close();
    }
    else
    {
        cout<<"Item info not found!\n";
        return found;
    }

    for(auto x: list)
    {
        if(x.id==ID)
        {
            a=x;
            found=true;
            break;
        }
    }
    if(found)
    {
    name=a.name;
    id=a.id;
    storage=a.storage;
    price=a.price;
    }
    return found;
}

void item::update()
{
    int choice=-1;
    bool change=true;
    while(true)
    {
    cout<<"Input (0): Exit\n";
    cout<<"Input (1): Change storage\n";
    cout<<"Input (2): Change price\n";
    cout<<"Input your choice: ";
    if(cinIg(cin,choice))
    {
        if(choice<0||choice>2)
        {
            cout<<"Invalid input!Please input again!\n";
            getchar();
            clearConsole();
        }
        else
        {
            break;
        }
    }
    else
    {
        choice=0;
        break;
    }
    }
    clearConsole();
    switch (choice)
    {
    case 1:
    {
        int Storage;
        cout<<"Input your new storage: ";
        if(cinIg(cin,Storage))
        {
            storage=Storage;
        }
        else
        {
            change=false;
        }
    }
        break;
    case 2:
    {
        float tmp;
        cout<<"Input your new price: ";
        if(cinIg(cin,tmp))
        {
            price=tmp;
        }
        else
        {
            change=false;
        }
    }
        break;

    default:
        change=false;
        break;
    }

    if(!change)
    {
        return;
    }
    string link=url+"member/";
    fstream myFile;
    myFile.open(link+"ID_List.txt");
    int *arr,n;
    if(myFile.is_open())
    {
        myFile>>n;
        arr=new int[n+1];
        for(int i=0;i<n;++i)
        {
            myFile>>arr[i];
        }
        myFile.close();
    }
    else
    {
        cout<<"ID_list not found!\n";
        return;
    }
    string tmp[]={"preOrder.txt","history.txt","favorite.txt"};
    for(int i=0;i<n;++i)
    {
        string ID=to_string(arr[i])+'/';
        for(int j=0;j<3;++j)
            {
                myFile.open(link+ID+tmp[j]);
                vector<item> list;
                if(myFile.is_open())
                {
                    item sth;
                    while(myFile>>sth)
                    {
                        list.push_back(sth);
                    }
                    myFile.close();
                }
                else
                {
                    continue;
                }
                for(auto x:list)
                {
                    if(x.id==id)
                    {
                        x=*this;
                        break;
                    }
                }
            }
    }
}

item item::find(int ID)
{
    item a;
    if(!checkID(ID,2,false))
    {
        return a;
    }

    fstream myFile(url+"item/info.dat",ios::in);
    set<item> list;
    if(myFile.is_open())
    {
        item temp;
        while(myFile>>temp)
        {
            list.insert(temp);
        }
        myFile.close();
    }
    else
    {
        cout<<"Item info not found!\n";
        return a;
    }

    for(auto x: list)
    {
        if(x.id==ID)
        {
            a=x;
            break;
        }
    }

    return a;

}
void item::output()
{
    cout<<"ID     : "<<id<<endl;
    cout<<"Name   : "<<name<<endl;
    cout<<"Price  : "<<price<<endl;
    cout<<"Storage: "<<storage<<endl;
}
void item::input()
{
    while(true)
    {
        myRandom temp;
        id=temp.next(0,10000);
        if(checkID(id,2))
        {
            break;
        }
    }
    string link=url+"item/";
    fstream myFile(link+"info.dat",ios::in);
    set<item> list;
    if(myFile.is_open())
    {
        item temp;
        while(myFile>>temp)
        {
            list.insert(temp);
        }
        myFile.close();
    }
    else
    {
        cout<<"Item info not found!\n";
        return;
    }

    cout<<"Input your item's name: "; cinIg(cin,name);
    cout<<"Input your number: "; cinIg(cin,storage);
    cout<<"Input the price: "; cinIg(cin,price);
    item dum(id,name,storage,price);
    list.insert(dum);
    myFile.open(link+"info.dat",ios::out);
    if(myFile.is_open())
    {
        for(auto x:list)
    {
        myFile<<x;
    }
    }
    else
    {
        cout<<"Item info not found!\n";
        return;
    }
}
bool item::operator==(item rhs)
    {
        if((name!=rhs.name)||(id!=rhs.id)||(storage!=rhs.storage)||(price!=rhs.price))
        {
            return false;
        }
        return true;
    }
bool item::operator<(item rhs)
{
    return id<rhs.id;
}
bool item::operator<=(item rhs)
{
    return id<=rhs.id;
}
bool item::operator>(item rhs)
{
    return id>rhs.id;
}
bool item::operator>=(item rhs)
{
    return id>=rhs.id;
}

bool item::operator<(item rhs) const
{
    return id<rhs.id;
}
bool item::operator<=(item rhs) const
{
    return id<=rhs.id;
}
bool item::operator>(item rhs) const
{
    return id>rhs.id;
}
bool item::operator>=(item rhs) const
{
    return id>=rhs.id;
}
bool item::operator==(item rhs) const
{
    return id==rhs.id;
}

ostream& operator<<(std::ostream& out,item value)
{
    out<<value.id<<","<<value.name<<","<<value.storage<<","<<value.price<<endl;
    return out;
}
istream& operator>>(std::istream& in,item value)
{
    in>>value.id;
    in.ignore(1);
    std::string temp;
    getline(in,temp,',');
    value.name=temp;
    in>>value.storage;
    in.ignore(1);
    in>>value.price;
    in.ignore(1);
    return in;
}
