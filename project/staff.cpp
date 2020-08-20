#include "staff.hpp"
#include "manager.hpp"
bool is_number(const string &s)
{
    return !s.empty() && find_if(s.begin(),
                                 s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void staff::input()
{
    ofstream id_list("./data/staff/ID_List.txt", ios::app);
    while (true)
    {
        cout << "Input ID: ";
        cin >> id;
        if (is_number(id) && checkStaffID(stoi(id)))
        {
            id_list << id << endl;
            break;
        }
        else
        {
            cout << "Invalid input! Please input again!\n\n";
        }
    }
    id_list.close();

    string path = "./data/staff/" + id + "/info.dat";
    makeDir(path);
    ofstream info(path);
    if (info.is_open())
    {
        this->person::input();
        auto [Date, Name, Tel] = this->person::get();
        info << id << endl;
        info << Name << endl;
        info << Date << endl;
        info << Tel << endl;
        info.close();
    }
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
            delete temp;
            break;
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
    int id;
    do
    {
        system("cls");
        cout << "Enter Member ID:";
        cin >> id;
    } while (is_number(to_string(id)) == false);
    if (checkID(id) == false)
    {
        cout << "ID not found!" << endl;
        return;
    }
    else
    {
        ifstream info("./data/member/" + to_string(id) + "info.dat");
        string temp;
        while (!info.eof())
        {
            getline(info, temp);
            cout << temp << endl;
        }
        info.close();
    }
}

void staff::updateMem()
{

    int id;
    do
    {
        system("cls");
        cout << "Enter Member ID:";
        cin >> id;
    } while (is_number(to_string(id)) == false);
    if (checkID(id) == false)
    {
        cout << "ID not found!" << endl;
    }
    else
    {
        char cont;
        do
        {
            cout << "Update This Member?(Y/N)" << endl;
            cout << "Your Choice:";
            cin >> cont;
        } while (cont != 'Y' || cont != 'y' || cont != 'N' || cont != 'n');
        switch (cont)
        {
        case 'Y':
        case 'y':
        {
            member *temp = new member(id);
            ofstream info("./data/member/" + to_string(id) + "/info.dat");
            if (info.is_open())
            {
                //Need a member save() function
                string name, tel;
                date d;
                cout << "Enter New Name: ";
                getline(cin, name);
                cout << "Enter New Telephone Number: ";
                getline(cin, tel);
                cout << "Date of Birth" << endl;
                cin >> d;
                temp->set(d, name, tel);
                temp->save();
                info.close();
                cout << "Update Member Successfully!" << endl;
            }
            else
            {
                cout << "Cannot Open File!" << endl;
            }
            break;
        }
        case 'N':
        case 'n':
        default:
            cout << "Stop Updating Member!" << endl;
            break;
        }
    }
}

void staff::menu()
{
    int choice = -1;
    bool checkInput = true;
    char cont;

    do
    {
        clearConsole();
        cout << "(0) Go Home" << endl;
        cout << "(1) Check-in Section" << endl;
        cout << "(2) Add New Member" << endl;
        cout << "(3) Find Member by ID" << endl;
        cout << "(4) Update Member Information" << endl;
        cout << "(5) Update Record" << endl;
        cout << "(6) Delete Record" << endl;
        cout << "(6) Search Record" << endl;

        cout << "Input Your Choice: " << endl;
        do
        {
            checkInput = cinIg(cin, choice, true);
        } while (choice < 0 || choice > 7 || checkInput == false);
        switch (choice)
        {
        case 0:
            cout << "See You Next Time!" << endl;
            clearConsole();
            break;
        case 1: //Checkin
            checkIn();
            break;
        case 2: //Add New Mem
            addNewMem();
            break;
        case 3: //Find Mem by ID
            showMem();
            break;
        case 4: //Update Mem
            updateMem();
            break;
        case 5: //Update Record
            break;
        case 6: //delete Record
            break;
        }
        do
        {
            cout << "Continue?";
            cin >> cont;
        } while (cont != 'Y' || cont != 'y' || cont != 'N' || cont != 'n');

        switch (cont)
        {
        case 'N':
        case 'n':
            cout << "See You Next Time" << endl;
            clearConsole();
            break;
        }
    } while (cont == 'Y' || cont == 'y');
}

void staff::save()
{
    string path = "./data/staff/" + id + "/info.dat";
    ofstream info(path);
    if (info.is_open())
    {
        auto [Date, Name, Tel] = person::get();
        info << id << endl;
        info << Name << endl;
        info << Date << endl;
        info << Tel << endl;
        info.close();
    }
}