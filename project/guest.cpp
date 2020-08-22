#include "guest.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include "myLib.hpp"
#include <algorithm>

using namespace std;

const string url="./data/";

float point(float pay)
{
    return pay/10;
}

int ranked(float point)
{
    if(point <1500)
    {
        return 3;
    }
    if(point<5000)
        return 2;
    return 1;
}
float discount(int rank,bool birthday)
{
    float birth=0;
    if(birthday)
        birth+=0.05;
    if(rank==1) return birth+0.2;
    if(rank==2) return birth+0.15;
    if(rank==3) return birth+0.1;
}
void guest::menu()
{
    vector<item> pre;
    bool checkInput=true;
    int choice=-1;
    while(true)
    {
        clearConsole();
        while(choice!=0)
        {
        cout<<string(8,' ')<<"Hello customer! What are you up to? \n";
        if(cart.size()==0)
        {   cout<<"(0) Go home!\n";
            cout<<"(1) Shopping\n";
            cout<<"Input your choice: ";
            checkInput = cinIg(cin, choice, true);
            clearConsole();
            if((choice==0||choice==1)&&checkInput)
            {
                break;
            }
            else
            {
                cout << "Error! Choose again:" << endl;
				getchar();
				clearConsole();
            }
        }
        else{
            cout<<"(0) Go home!\n";
            cout<<"(1) Shopping\n";
            cout<<"(2) View cart\n";
            cout<<"Input your choice: ";
            checkInput = cinIg(cin, choice, true);
            clearConsole();
            if((choice>=0&&choice<=2)&&checkInput)
            {
                break;
            }
            else
            {
                cout << "Error! Choose again:" << endl;
				getchar();
				clearConsole();
            }
        }
        }

        switch(choice)
        {
            case 1:
                {
                    int cont=1;
                    while(true)
                    {
                        checkInput=true;
                        //? clq gì đây 

                        checkInput = cinIg(cin, choice, true);
                        if(!checkInput)
                            cont=0;
                        if(!cont) break;
                    }
                }
                    break;

            case 2:
                output();
                cout<<"Total       : "<<setfill(' ')<<setw(38)<<setprecision(3)<<money<<endl;
                getchar();
                clearConsole();
                break;
            default:
                {
                    if(cart.size())
                    {
                        cout<<"This is your bill!\n\n";
                        output();
                        cout<<"Total       : "<<setfill(' ')<<setw(35)<<setprecision(3)<<money<<"  |"<<endl;
                        export();
                        getchar();
                        clearConsole();

                        cout<<"Finish!\n";
                    }
                    cout<<"Have a nice day!\n";

                    getchar();
                    clearConsole();
                }
                    break;

        }
        if(choice==0)
        {
            break;
        }
    }
    clearConsole();
}
guest::guest()
{
    money=0;
}
void guest::input()
{
    person::input();
}
void guest::output()
{
    person::output(false);
    for(auto x:cart)
    {
        cout<<left<<setfill(' ')<<setw(25)<<x.first.name<<setw(4)<<'|'<<setw(4)<<x.second<<setw(4)<<'|'<<setw(4)<<x.first.price<<'|'<<right<<setw(7)<<setprecision(3)<<x.first.price*x.second<<"  |"<<endl;
        cout<<setfill('-')<<setw(50)<<"-\n";
    }
    cout<<"\n";
    // ! Sẽ được viết ở main sau output cout<<"Total: "<<money<<endl;
}

void guest::export()
{
    date today;
    string link=url+"export/"+to_string(today.year);
    makeDir(link);
    link+='/'+to_string(today.month);
    makeDir(link);
    link+='/'+to_string(today.day);
    bool test=makeDir(link);
    fstream myFile;
    if(test)
    {
        myFile.open(link+"/count.dat",ios::out);
        myFile<<0<<endl;
        myFile.close();
    }
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
        auto [hour,min,sec]=currentTime(true);
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
        file2<<"Total       : "<<setfill(' ')<<setw(38)<<setprecision(3)<<money<<endl;
        file2.close();
    }
}
bool guest::buy(std::vector<item> x,int id)
{
    x[id].output();
    int choice;
    cout<<"Do you want to buy\n";
    cout<<"(0): No\n";
    cout<<"(1): Yes\n";
    cout<<"Input your choice: ";
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(10000,'\n');
        choice=0;
    }
    if(choice)
    {
        cout<<"Input num: ";
        if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(10000,'\n');
        choice=1;
    }
        cart[x[id]]+=choice;
        money+=x[id].price*choice;
    }
    return choice;

}

void guest::print(ostream& out) const
{
    person::print(out);
    out<<';'<<setprecision(3)<<money;
}
void guest::load(istream& in)
{
    person::load(in);
    in>>money;
}
istream& operator>>(istream& in,guest& a)
{
    a.load(in);
    return in;
}
ostream& operator<<(ostream& out,const guest& a)
{
    a.print(out);
    return out;
}
member::member()
{
    rank=0;
    memberPoint=0;
}
member::member(int ID)
{
    string link=url+"member/"+to_string(ID)+"/info.dat";
    ifstream info(link);

    if(info.is_open())
    {
        string Name,Tel;
        date Date;
        info>>id;
        info.ignore(1);
        info>>Name;
        info>>Date;
        info.ignore(1);
        info>>Tel;
        info>>rank;
        info>>memberPoint;
        info>>use;
        person::set(Date,Name,Tel);
        info.close();
    }
}
void member::menu()
{
    //TODO export,shopping[view cart ,buy,add(fav,his,pre)],view[fav,his,pre],update info
    int choice=-1;
    vector<item> tmp;
    bool checkInput=true;
    int choice=-1;
    string content="";
    {
    auto[Date,Name,Tel]=person::get();
    unsigned int first_of_blank=Name.find_first_of(' '),last_of_blank=Name.find_last_of(' ');
    content+= Name.substr(0,first_of_blank)+Name.substr(last_of_blank,Name.size());
    }
    content+="! What are you up to?";
    cout<<string((52-9-content.size())/2,' ')<<"Welcome, "<<content<<endl;;
    while(true)
    {
        while(choice!=0)
        {
            if(cart.size()==0)
            {
                cout<<"(0) Go home\n";
                cout<<"(1) Update info";
                cout<<"(2) Shopping\n";
                cout<<"(3) View favorite\n";
                cout<<"(4) View search history\n";
                cout<<"(5) View pre-order\n";
                cout<<"Input your choice: ";
                checkInput = cinIg(cin, choice, true);
                clearConsole();
                if((choice>=0&&choice<=5)&&checkInput)
                {
                    break;
                }
                else
                {
                    cout << "Error! Choose again:" << endl;
				    getchar();
				    clearConsole();
                }
            }
            else
            {
                cout<<"(0) Go home\n";
                cout<<"(1) Update info";
                cout<<"(2) Shopping\n";
                cout<<"(3) View cart\n";
                cout<<"(4) View favorite\n";
                cout<<"(5) View search history\n";
                cout<<"(6) View pre-order\n";
                cout<<"Input your choice: ";
                checkInput = cinIg(cin, choice, true);
                clearConsole();
                if((choice>=0&&choice<=6)&&checkInput)
                {
                    if(choice==2)
                        choice+=5;
                    else if(choice >2)
                        --choice;
                    break;
                }
                else
                {
                    cout << "Error! Choose again:" << endl;
				    getchar();
				    clearConsole();
                }
            }
            
        }

        switch (choice)
        {
        case 0:
            payment(true);
            if(cart.size())
                {
                    cout<<"This is your bill!\n\n";
                    output();
                    cout<<"Total       : "<<setfill(' ')<<setw(35)<<setprecision(3)<<payment()<<"  |"<<endl;
                    export();

                    cout<<"\n\n";
                }
            cout<<"Goodbye!\n";
            cout<<"Have a nice day!\n";
            export();
            getchar();
            clearConsole();
            break;
        case 1:
            {
                int type;
                cout<<"(0) None\n";
                cout<<"(1) Name\n";
                cout<<"(2) Day of birth\n";
                cout<<"(3) Telephone";
                cout<<"Input your choice: ";
                checkInput=cinIg(cin,type);
                if(!checkInput)
                    type=0;
                switch (type)
                {
                case 1:
                    {
                        date tmp;
                        cout<<"Input your date:\n";
                        cin>>tmp;
                        update(tmp,choice);
                    }
                    break;
                case 2:
                    {
                        string tmp;
                        cout<<"Input name: ";cin>>tmp;
                        update(tmp,choice);
                    }
                    break;
                case 3:
                    {
                        int tmp;
                        cout<<"Input telephone: ";cin>>tmp;
                        update('0'+to_string(tmp),choice);
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case 2:
            {
                output();
                cout<<"Total       : "<<setfill(' ')<<setw(38)<<setprecision(3)<<payment()<<endl;
                getchar();
                clearConsole();
                break;
            }
            break;
        case 3:
        case 4:
        case 5:
            tmp=shoppingCookie(choice-2);
            cout<<setfill(' ')<<setw(30)<<"List: \n";
            if(tmp.size()!=0)
                for(int i=0;i<tmp.size();++i)
            {
                cout<<string(4,' ')<<left<<setfill(' ')<<setw(5)<<tmp[i].id<<setw(4)<<'|'<<setw(25)<<tmp[i].name<<setw(4)<<'|'<<right<<setw(10)<<setprecision(3)<<tmp[i].price<<endl;
            }
            else
            {
                cout<<"Empty\n";
            }
            
            cout<<"Press Enter to continue... ";
            getchar();
            clearConsole();
            tmp.clear();
            break;
        default:
            break;
        }

        getchar();
        clearConsole();
            if(choice==0)
        {
            break;
        }
        cout<<string((52-content.size())/2,' ')<<content<<endl;
    }
}
void member::input()
{
    guest::input();
    while(true)
    {
        myRandom temp;
        id=temp.next(10000,20000);
        if(checkID(id,1))
        {
            break;
        }
    }
    string link=url+"member/"+to_string(id);
    makeDir(link);
    ofstream info(link+"/info.dat");
    if(info.is_open())
    {
        auto[Date,Name,Tel]=person::get();
        info<<id<<endl;
        info<<Name<<endl;
        info<<Date<<endl;
        info<<Tel<<endl;
        info<<rank<<endl;
        info<<memberPoint<<endl;
        info<<use<<endl;
        info.close();
    }
    ofstream pre(link+"/preOrder.txt");
    pre.close();
    ofstream his(link+"/history.txt");
    his.close();
    ofstream fav(link+"/favorite.txt");
    fav.close();
}
void member::output()
{
    guest::output();
    cout<<"Discount: "<<setfill(' ')<<setw(39)<<discount(rank,DoB.birthdayMonth())<<"  |";
}
void member::export()
{
    date today;
    string link=url+"export/"+to_string(today.year);
    makeDir(link);
    link+='/'+to_string(today.month);
    makeDir(link);
    link+='/'+to_string(today.day);
    bool test=makeDir(link);
    fstream myFile;
    if(test)
    {
        myFile.open(link+"/count.dat",ios::out);
        myFile<<0<<endl;
        myFile.close();
    }
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
        auto [hour,min,sec]=currentTime(true);
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
        file2<<"Total       : "<<setfill(' ')<<setw(38)<<setprecision(3)<<money<<endl;
        file2.close();
    }
}
double member::payment(bool change=false)
{
    double res=0;
    if(DoB.birthdayMonth())
        {
            if(!use)
                {
                    res=money*(1-discount(rank,true));
                    use=true;
                }
        }
    if(res==0)
        res=money*(1-discount(rank,false));
    if(change)money=res;
    return res;
}
void member::print(ostream& out) const
{
    person::print(out);
    out<<";"<<setprecision(3)<<money;
}
void member::load(istream& in)
{
    person::load(in);
    in>>money;
}
istream& operator>>(istream& in,guest& a)
{
    a.load(in);
    return in;
}
ostream& operator<<(ostream& out,const guest& a)
{
    a.print(out);
    return out;
}
void member::updateFile(int type,item value,int choice=1)
{
    //! Choice 0 to delete, choice=1 to add
    string link= url+"member/"+to_string(id)+'/';
    fstream myFile;
    int pos;
    switch (type)
    {
    // TODO 1:  favorite

    case 1:
        {
            if(choice)
            {
                myFile.open(link+"favorite.txt",ios::out|ios::app);
                if(myFile.is_open())
                {
                    myFile<<value<<endl;
                    myFile.close();
                }
                else
                {
                    cout<<"File not found!\n";
                    getchar();
                    clearConsole();
                }
            }
            else
            {
                vector<item> tmp;
                myFile.open(link+"favorite.txt",ios::in);
                if(myFile.is_open())
                {
                    item temp;
                    while(myFile>>temp)
                    {
                        tmp.push_back(temp);
                    }
                    pos=-1;
                    for(int i=0;i<tmp.size();++i)
                    {
                        if(tmp[i]==value)
                        {
                            pos=i;
                            break;
                        }
                    }
                    if(pos!=-1)
                        tmp.erase(tmp.begin()+pos);
                    myFile.close();
                }
                else
                {
                    cout<<"File not found!\n";
                    getchar();
                    clearConsole();
                }

                myFile.open(link+"favorite.txt",ios::out);
                if(myFile.is_open())
                {
                    for(auto x:tmp)
                    {
                        myFile<<x<<endl;
                    }
                    myFile.close();
                }
                else
                {
                    cout<<"File not found!\n";
                    getchar();
                    clearConsole();
                }
            }
        }
        break;
    // TODO 2:  history
    case 2:
        {
            pos=0;
            vector<item> tmp;
                myFile.open(link+"history.txt",ios::in);
                if(myFile.is_open())
                {
                    item temp;
                    while(myFile>>temp)
                    {
                        tmp.push_back(temp);
                    }
                    for(int i=0;i<tmp.size();++i)
                    {
                        if(tmp[i]==value)
                        {
                            pos=i;
                            break;
                        }
                    }
                    myFile.close();
                }
                else
                {
                    cout<<"File not found!\n";
                    getchar();
                    clearConsole();
                }

            tmp.erase(tmp.begin()+pos);
            if(choice)
                tmp.push_back(value);
            if(tmp.size()>20)
            {
                tmp.erase(tmp.begin());
            }
            myFile.open(link+"history.txt",ios::out);
            if(myFile.is_open())
            {
                for(auto x: tmp)
                {
                    myFile<<x<<endl;
                }
                myFile.close();
            }
            else
            {
                cout<<"File not found!\n";
                getchar();
                clearConsole();
            }
        }
        break;
    // TODO 3:  preorder
    default:
    {
        vector<item> tmp;
        if(choice)
        {
            myFile.open(link+"preOrder.txt",ios::out|ios::app);
            if(myFile.is_open())
            {
                myFile<<value<<endl;
            }
            else
            {
                cout<<"File not found!\n";
                getchar();
                clearConsole();
            }
        }
        else
        {
            myFile.open(link+"preOrder.txt",ios::in);
            if(myFile.is_open())
                {
                    item temp;
                    while(myFile>>temp)
                    {
                        tmp.push_back(temp);
                    }
                    pos=-1;
                    for(int i=0;i<tmp.size();++i)
                    {
                        if(tmp[i]==value)
                        {
                            pos=i;
                            break;
                        }
                    }
                    if(pos!=-1)
                        tmp.erase(tmp.begin()+pos);
                    myFile.close();
                }
                else
                {
                    cout<<"File not found!\n";
                    getchar();
                    clearConsole();
                }
            myFile.open(link+"preOrder.txt",ios::out);
            if(myFile.is_open())
            {
                for(auto x: tmp)
                {
                    myFile<<x<<endl;
                }
                myFile.close();
            }
            else
            {
                cout<<"File not found!\n";
                getchar();
                clearConsole();
            }
        }
    }
        break;
    }
}
vector<item> member::shoppingCookie(int type)
{
    if(type==1)
    {
        return favoriteItem();
    }
    else if(type==2)
    {
        return viewHistory();
    }
    return preOrder();
}
vector<item> member::viewHistory()
{
    string link=url+"member/"+to_string(id)+"history.txt";
    vector<item>tmp;
    ifstream myFile(link);
    if(myFile.is_open())
    {
        item temp;
        while(myFile>>temp)
        {
            tmp.push_back(temp);
        }
        myFile.close();
    }
    else
    {
        cout<<"File not found!\n";
        getchar();
        clearConsole();
    }
    return tmp;
}
vector<item> member::preOrder()
{
    string link=url+"member/"+to_string(id)+"preOrder.txt";
    vector<item>tmp;
    ifstream myFile(link);
    if(myFile.is_open())
    {
        item temp;
        while(myFile>>temp)
        {
            tmp.push_back(temp);
        }
        myFile.close();
    }
    else
    {
        cout<<"File not found!\n";
        getchar();
        clearConsole();
    }
    return tmp;
}
void member::save(){
    string link=url+"member/"+to_string(id);
    makeDir(link);
    ofstream info(link+"/info.dat");
    if(info.is_open())
    {
        auto[Date,Name,Tel]=person::get();
        info<<id<<endl;
        info<<Name<<endl;
        info<<Date<<endl;
        info<<Tel<<endl;
        info<<rank<<endl;
        info<<memberPoint<<endl;
        info<<use<<endl;
        info.close();
    }
}
vector<item> member::favoriteItem()
{
    string link=url+"member/"+to_string(id)+"favorite.txt";
    vector<item>tmp;
    ifstream myFile(link);
    if(myFile.is_open())
    {
        item temp;
        while(myFile>>temp)
        {
            tmp.push_back(temp);
        }
        myFile.close();
    }
    else
    {
        cout<<"File not found!\n";
        getchar();
        clearConsole();
    }
    return tmp;
}

