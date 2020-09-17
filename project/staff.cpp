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
        system("cls");
        cout << "Input ID: ";
        cin >> id;
        cin.ignore(1);
        if (checkStaffID(stoi(id), true, 1) == true)
        {
            break;
        }
        else
        {
            cout << "Invalid Input! Please Try Again!\n\n";
            system("pause");
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
        system("cls");
        if (timeinfo->tm_hour < 18)
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
        cout << "Add New Member?(Y/ N): ";
        cin >> choice;
        cin.ignore(1);
        switch (choice)
        {
        case 'Y':
        case 'y':
        {
            Account acc;
            acc.create(2);
            clearConsole();
            cout << "New Member Added!" << endl;
            break;
        }
        case 'N':
        case 'n':
        default:
        {
            cout << "No New Member Added" << endl;
            return;
        }
        }
        cout << "\nContinue to Add New Member?(Y/N): ";
        cin >> cont;
    } while (cont == 'Y' || cont == 'y');
}

void staff::showMem()
{
    int id;
    char cont;
    do
    {
        system("cls");
        cout << "Enter Member ID:";
        cin >> id;
        if (checkID(id, 1, false) == true)
        {
            cout << "ID not found!\n\n";
        }
        else
        {
            cout << "Member Found!" << endl;
            member *obj = new member;
            obj->get(id);
            obj->output();
        }
        cout << "Continue to Show Member(Y/N)?: ";
        cin >> cont;
        cin.ignore(1);
        switch (cont)
        {
        case 'Y':
        case 'y':
            break;
        case 'N':
        case 'n':
            return;
        }
    } while (cont == 'Y' || cont == 'y');
}

void staff::updateMem()
{

    int id;
    char cont;
    do
    {
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
            cout << "ID Found!" << endl;
            cout << "\nUpdate This Member?(Y/N): ";
            cin >> cont;
            cin.ignore(1);
            switch (cont)
            {
            case 'Y':
            case 'y':
            {
                clearConsole();
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
                    cout << "Update Member Successfully!\n\n"
                         << endl;
                    temp->output();
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
                system("pause");
                break;
            }
        }

        cout << "\nContinue to Update Member(Y/N)?: ";
        cin >> cont;
        cin.ignore(1);

        switch (cont)
        {
        case 'Y':
        case 'y':
            break;
        case 'N':
        case 'n':
            return;
        }
    } while (cont == 'Y' || cont == 'y');
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
        cout << "(9) Show Order" << endl;
        cout << "Input Your Choice: ";
        do
        {
            checkInput = cinIg(cin, choice, true);
        } while (choice < 0 || choice > 9 || checkInput == false);
        switch (choice)
        {
        case 0:
            clearConsole();
            cout << "See You Next Time!" << endl;
            system("pause");
            return;
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
        case 9:
            showOrder();
            break;
        }
        cout << "\n";
        system("pause");
        clearConsole();
        cout << "Return to Staff Menu(Y/N)?: ";
        cin >> cont;
        cin.ignore(1);

        clearConsole();
        switch (cont)
        {
        case 'Y':
        case 'y':
            break;
        case 'N':
        case 'n':
        default:
            cout << "See You Next Time!" << endl;
            system("pause");
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
            item obj;
            obj.input();
            cout << "\nNew Record Added!" << endl;
            system("pause");
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
    if (checkStaffID(ID, false, 1) == true)
        return;

    ifstream file("./data/staff/" + to_string(ID) + "/info.dat");
    if (!file.is_open())
        return;
    date DOB;
    string Name, Tel;
    getline(file, id);
    getline(file, Name);
    file >> DoB;
    file >> Tel;
    file.close();
    person::set(DoB, Name, Tel);
}

int staff::getID()
{
    return stoi(id);
}

void staff::showOrder()
{
    system("cls");
    date time;
    int count = 0, choice;
    char cont;
    vector<string> list;
    string path;
    do
    {
        system("cls");
        cout << "Enter Date of Order: " << endl;
        cin >> time;
        path = "./data/export/" + to_string(time.year) + "/" + to_string(time.month) + "/" + to_string(time.day);
        if (!filesystem::exists(path))
        {
            cout << "\nOrder does not exist! Try another date" << endl;
            system("pause");
        }
    } while (!filesystem::exists(path));

    do
    {
        system("cls");
        count = 0;
        cout << "List of Record\n\n";
        for (const auto &entry : filesystem::directory_iterator(path))
        {
            cout << "[" << count << "] ";
            std::cout << entry.path() << "\n\n";
            list.push_back((entry.path()).string());
            count++;
        }
        cout << "[" << count << "] Exit\n";
        cout << "\nChoose Record(0~" << count << "): ";
        cin >> choice;

        if (choice == count)
        {
            system("cls");
            cout << "See You Next Time!" << endl;
            system("pause");
            return;
        }

        ifstream file(list[choice]);
        if (file.is_open())
        {
            string line;
            system("cls");
            while (getline(file, line))
                cout << line << endl;
        }
        else
            cout << "Cannot Open Record!" << endl;

        cout << "\n\nContinue to Show Record(Y/N)?: ";
        cin >> cont;
        cin.ignore(1);

        switch (cont)
        {
        case 'Y':
        case 'y':
            break;
        case 'N':
        case 'n':
            system("cls");
            cout << "See You Next Time!" << endl;
        }
    } while (cont == 'Y' || cont == 'y');
}