#include "staff.hpp"
#include "manager.hpp"

bool is_Number(const string &s)
{
    return !s.empty() && find_if(s.begin(),
                                 s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

staff::staff(int id)
{
    ifstream info("./data/staff/" + to_string(id) + "/info.dat");
    if (info.is_open())
    {
        string Name, Tel;
        date Date;
        info >> this->id;
        info >> Name;
        info >> Date;
        info.ignore(1);
        info >> Tel;
        person::set(Date, Name, Tel);
        info.close();
    }
}

void staff::input()
{
    while (true)
    {
        cout << "Input ID: ";
        cin >> id;
        cin.ignore(1);
        if (checkStaffID(stoi(id), true) == true)
        {
            break;
        }
        else
        {
            cout << "Invalid Input! Please Try Again!\n\n";
        }
    }

    string path = "./data/staff/" + id;
    makeDir(path);
    ofstream info(path + "/info.dat");
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
    string path = "./data/staff/" + id + "/checkin.txt";
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
        system("cls");
        cout << "Add New Member?(Y/ N)";
        cin >> choice;
        cin.ignore(1);
        switch (choice)
        {
        case 'Y':
        case 'y':
        {
            member *temp = new member;
            temp->input();
            // Missing File + Save Data;
            clearConsole();
            cout << "New Member Added!" << endl;
            temp->output();
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
    system("cls");
    cout << "Enter Member ID:";
    cin >> id;
    if (checkID(id, 1, false) == true)
    {
        cout << "ID not found!" << endl;
        return;
    }
    else
    {
        cout << "Member Found!" << endl;
        member *obj = new member;
        obj->get(id);
        obj->output();
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
    } while (is_Number(to_string(id)) == false);
    if (checkID(id, 1, false) == true)
    {
        cout << "ID not found!" << endl;
    }
    else
    {
        char cont;
        cout << "Update This Member?(Y/N)" << endl;
        cout << "Your Choice:";
        cin >> cont;
        cin.ignore(1);
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
        cout << "(5) Input New Record" << endl;
        cout << "(6) Update Record" << endl;
        cout << "(7) Delete Record" << endl;
        cout << "(8) Search Record" << endl;

        cout << "Input Your Choice: ";
        do
        {
            checkInput = cinIg(cin, choice, true);
        } while (choice < 0 || choice > 8 || checkInput == false);
        switch (choice)
        {
        case 0:
            cout << "See You Next Time!" << endl;
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
        case 5: //Input Record
            inputItem();
            break;
        case 6: //Update Record
            updateRecord();
            break;
        case 7: //delete Record
            deleteRecord();
            break;
        case 8:
            searchRecord();
            break;
        }

        cout << "Continue?";
        cin >> cont;
        cin.ignore(1);

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

void staff::inputItem()
{
    char cont;
    do
    {
        clearConsole();
        cout << "Input New Item?(Y/N): ";
        cin >> cont;
        cin.ignore(1);

        switch (cont)
        {
        case 'Y':
        case 'y':
        {
            item *obj = new item;
            obj->input();
            delete obj;
            cout << "\nNew Record Added!" << endl;
            break;
        }
        case 'N':
        case 'n':
            cout << "\nNo New Record Added!" << endl;
            break;
        }
    } while (cont == 'Y' || cont == 'y');
}

void staff::updateRecord()
{
    int id;
    char cont;
    item *temp = new item;
    do
    {
        system("cls");
        cout << "Enter Item's ID:";
        cin >> id;
    } while (is_Number(to_string(id)) == false);
    if (temp->get(id))
    {
        cout << "Item Found!" << endl;
        temp->output();
        cout << "Update This Record? (Y/N):";
        cin >> cont;
        cin.ignore(1);
        switch (cont)
        {
        case 'Y':
        case 'y':
            temp->update();
            cout << "\nItem's Updated!" << endl;
            break;
        case 'N':
        case 'n':
        default:
            cout << "\nNo Record Updated!" << endl;
            break;
        }
    }
    else
    {
        cout << "No Item's Found!" << endl;
    }
}

bool staff::deleteRecord()
{
    bool res = true;
    int id;
    char cont;
    item *temp = new item;
    do
    {
        do
        {
            system("cls");
            cout << "Enter Item's ID:";
            cin >> id;
        } while (is_Number(to_string(id)) == false);
        if (temp->get(id))
        {
            cout << "Item Found!" << endl;
            temp->output();

            cout << "\nDelete This Record? (Y/N):";
            cin >> cont;
            cin.ignore();
            switch (cont)
            {
            case 'Y':
            case 'y':
                // Need an ID Update Function;
                cout << "Item's Deleted!" << endl;
                res = true;
                break;
            case 'N':
            case 'n':
            default:
                res = false;
                break;
            }
        }
        else
        {
            cout << "No Item's Found!" << endl;
            res = false;
        }

        cout << "Continute?(Y/N):";
        cin >> cont;

    } while (cont == 'Y' || cont == 'y');
    return res;
}

pair<item, int> staff::searchRecord()
{
    int id;
    char cont;
    pair<item, int> temp;
    do
    {
        do
        {
            system("cls");
            cout << "Enter Item's ID:";
            cin >> id;
        } while (is_Number(to_string(id)) == false);
        if (temp.first.get(id))
        {
            cout << "Item's Found!" << endl;
            temp.second = id;
            temp.first.output();
        }
        else
            cout << "No Item's Found!" << endl;

        cout << "Continue?(Y/N):";
        cin >> cont;
    } while (cont == 'Y' || cont == 'y');

    return temp;
}

void staff::get(int ID)
{
}