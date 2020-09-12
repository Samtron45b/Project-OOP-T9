#include "manager.hpp"
#include "Account.h"
bool checkStaffID(int ID, bool save, int type)
{
    ifstream list;
    if (type == 1)
        list.open("./data/staff/ID_List.txt");
    else
        list.open("./data/manager/ID_List.txt");
    int *arr = NULL, n;
    if (list.is_open())
    {
        list >> n;
        arr = new int[n + 1];
        for (int i = 0; i < n; ++i)
        {
            list >> arr[i];
        }
        list.close();
    }
    bool res = true;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] == ID)
            res = false;
    }
    if (res && save)
    {
        arr[n] = ID;
        sort(arr, arr + n + 1);
        ++n;
        saveStaffIDlist(arr, n, type);
    }
    delete[] arr;
    return res;
}
void saveStaffIDlist(int *list, int n, int type)
{
    ofstream file;
    if (type == 1)
        file.open("./data/staff/ID_List.txt");
    else
        file.open("./data/manager/ID_List.txt");
    if (file.is_open())
    {
        file << n << endl;
        for (int i = 0; i < n; ++i)
        {
            file << list[i] << endl;
        }
        file.close();
    }
}

void deleteStaffID(int id, int type)
{
    ifstream list;
    if (type == 1)
        list.open("./data/staff/ID_List.txt");
    else
        list.open("./data/manager/ID_List.txt");
    int *arr, n;
    vector<int> temp;
    if (list.is_open())
    {
        list >> n;
        arr = new int[n + 1];
        for (int i = 0; i < n; ++i)
        {
            list >> arr[i];
            if (arr[i] != id)
                temp.push_back(arr[i]);
        }
        list.close();
        delete[] arr;
        --n;
        arr = new int[n];
        std::copy(temp.begin(), temp.end(), arr);
        saveStaffIDlist(arr, n, type);
    }
}

void manager::addNewStaff()
{
    char choice, cont;
    do
    {
        system("cls");
        cout << "Add New Staff?(Y/ N)";
        cin >> choice;
        cin.ignore(1);
        switch (choice)
        {
        case 'Y':
        case 'y':
        {
            Account acc;
            acc.create(1);
            break;
        }
        case 'N':
        case 'n':
        default:
        {
            cout << "No New Staff Added" << endl;
        }
        }
        cout << "Continue to Add New Staff?(Y/N)" << endl;
        cin >> cont;
    } while (cont == 'Y' || cont == 'y');
}

void manager::updateStaff()
{

    int id;
    do
    {
        system("cls");
        cout << "Enter Staff ID:";
        cin >> id;
    } while (is_Number(to_string(id)) == false);
    if (checkStaffID(id, false, 1) == true)
    {
        cout << "ID not found!" << endl;
    }
    else
    {
        char cont;
        do
        {
            cout << "Update This Staff?(Y/N)" << endl;
            cout << "Your Choice:";
            cin >> cont;
        } while (cont != 'Y' || cont != 'y' || cont != 'N' || cont != 'n');
        switch (cont)
        {
        case 'Y':
        case 'y':
        {
            staff *temp = new staff(id);
            ofstream info("./data/staff/" + to_string(id) + "/info.dat");
            if (info.is_open())
            {
                //Update staff basic info
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
                cout << "Update Staff Successfully!" << endl;
            }
            else
            {
                cout << "Cannot Open File!" << endl;
            }
            delete temp;
            break;
        }
        case 'N':
        case 'n':
        default:
            cout << "Stop Updating Staff!" << endl;
            break;
        }
    }
}

void manager::deleteStaff()
{
    int id;
    char cont;
    do
    {
        do
        {
            cout << "Enter Staff ID to delete: ";
            cin >> id;
        } while (is_Number(to_string(id)) == false);
        if (checkStaffID(id, false, 1) == false)
        {
            cout << "Do you want to delete this staff?(Y/N): ";
            cin >> cont;
            if (cont == 'Y' || cont == 'y')
            {
                filesystem::remove_all("./data/staff/" + to_string(id));
                // Need an ID Update Function
                deleteStaffID(id, 1);
            }
            else
                break;
        }
        else
        {
            cout << "No ID Found!" << endl;
        }

        cout << "Continue?(Y/N): ";
        cin >> cont;

        switch (cont)
        {
        case 'Y':
        case 'y':
            break;
        case 'N':
        case 'n':
            cout << "See You Next Time!" << endl;
            break;
        }
    } while (cont == 'Y' || cont == 'y');
}

void manager::menu()
{
    int choice = -1;
    bool checkInput = true;
    char cont;

    do
    {
        clearConsole();
        cout << "(0) Go Home" << endl;
        cout << "(1) Add New Staff" << endl;
        cout << "(2) Update Staff" << endl;
        cout << "(3) Delete Staff" << endl;
        cout << "(4) Show Monthly Sales" << endl;

        cout << "Input Your Choice: " << endl;
        do
        {
            checkInput = cinIg(cin, choice, true);
        } while (choice < 0 || choice > 4 || checkInput == false);
        switch (choice)
        {
        case 0:
            cout << "See You Next Time!" << endl;
            clearConsole();
            break;
        case 1: //Add new Staff
            addNewStaff();
            break;
        case 2: //Update Staff
            updateStaff();
            break;
        case 3: //Delete Staff
            deleteStaff();
            break;
        case 4: //Show Monthly Sales
            //  monthlySales();
            break;
        }

        cout << "Continue?";
        cin >> cont;
        cin.ignore(1);
        switch (cont)
        {
        case 'Y':
        case 'y':
            break;
        case 'N':
        case 'n':
        default:
            cout << "See You Next Time" << endl;
            clearConsole();
            break;
        }
    } while (cont == 'Y' || cont == 'y');
}

void manager::save()
{
    string link = "./data/manager/" + to_string(id);
    makeDir(link);
    ofstream info(link + "/info.dat");
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

void manager::get(int ID)
{
    if (checkStaffID(ID, false, 2) == true)
        return;

    ifstream file("./data/manager/" + to_string(ID) + "/info.dat");
    if (!file.is_open())
        return;
    date DOB;
    string Name, Tel;
    file >> id;
    file.ignore(1);
    getline(file, Name);
    file >> DoB;
    file >> Tel;
    file.close();
    person::set(DoB, Name, Tel);
}

void manager::input()
{
    while (true)
    {
        cout << "Input ID: ";
        cin >> id;
        cin.ignore(1);
        if (checkStaffID(id, true, 2) == true)
        {
            break;
        }
        else
        {
            cout << "Invalid Input! Please Try Again!\n\n";
        }
    }

    string path = "./data/manager/" + to_string(id);
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

void manager::output()
{
    cout << "ID: " << id << endl;
    person::output();
}

int manager::getID()
{
    return id;
}