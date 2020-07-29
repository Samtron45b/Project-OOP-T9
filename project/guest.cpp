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

    cout<<"Total: "<<payment()<<endl;
}

void guest::export()
{
    
}

double guest::payment()
{

}

