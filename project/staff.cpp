#include "staff.hpp"

bool is_number(const string &s)
{
    return !s.empty() && find_if(s.begin(),
                                 s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void staff::input()
{
    while (true)
    {
        cout << "Input ID: ";
        cin >> id;
        if (is_number(id))
        {
            break;
        }
        else
        {
            cout << "Invalid input! Please input again!\n\n";
        }
    }
    person::input();
}

void staff::output()
{
    cout << "ID: " << id << endl;
    person::output();
}

void staff::checkIn()
{
    // get current time
    time_t raw;
    struct tm *timeinfo;
    time(&raw);
    timeinfo = localtime(&raw);

    // open file
    string path = "./data/staff/checkin/" + id + ".txt";
    ofstream outfile(path, ios::app);

    outfile << asctime(timeinfo);
    if (!outfile.is_open())
        throw "File cannnot open";
    else
    {
        if (timeinfo->tm_hour < 8)
        {
            cout << "Check-in Successfully!" << endl;
            outfile << "1" << endl;
        }
        else
        {
            cout << "Check-in Overdue!" << endl;
            outfile << "0" << endl;
        }
        outfile.close();
    }
}

void staff::addNewMem()
{
    char choice, cont;
    do
    {
        do
        {
            system("cls");
            cout << "Add New Member?(Y/ N)";
            cin >> choice;
        } while (choice != 'Y' || choice != 'y' || choice != 'N' || choice != 'n');
        switch (choice)
        {
        case 'Y':
        case 'y':
        {
            member *temp = new member;
            temp->input();
            // Missing File + Save Data;
            cout << "New Member Added!" << endl;
        }
        case 'N':
        case 'n':
        default:
        {
            cout << "No New Member Added" << endl;
        }
        }
        cout << "Continue to Add New Member?(Y/N)" << endl;
        cin >> cont;
    } while (cont == 'Y' || cont == 'y');
}

void staff::showMem()
{
    // Show by ID,rank,member point
}
