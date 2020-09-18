#include "manager.hpp"
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
        cout << "Add New Staff(Y/ N)?: ";
        cin >> choice;
        cin.ignore(1);
        switch (choice)
        {
        case 'Y':
        case 'y':
        {
            Account *acc = new Account;
            acc->create(1);
            cout << "New Staff Added!" << endl;
            break;
        }
        case 'N':
        case 'n':
        default:
        {
            cout << "No New Staff Added!" << endl;
            system("pause");
            return;
        }
        }
        system("pause");
        system("cls");
        cout << "Continue to Add New Staff?(Y/N): ";
        cin >> cont;
    } while (cont == 'Y' || cont == 'y');
}

void manager::updateStaff()
{
    int id;
    char cont;
    do
    {
        do
        {
            system("cls");
            cout << "Enter Staff ID:";
            cin >> id;
        } while (is_Number(to_string(id)) == false);
        if (checkStaffID(id, false, 1) == true)
        {
            cout << "\nID not found!" << endl;
            system("pause");
        }
        else
        {
            char cont;
            cout << "ID Found!\n\n";
            cout << "Update This Staff(Y/N)?: ";
            cin >> cont;
            cin.ignore(1);
            switch (cont)
            {
            case 'Y':
            case 'y':
            {
                clearConsole();
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
                    system("pause");
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
                system("pause");
                break;
            }
        }
        system("cls");
        cout << "Continue to Update Staff?(Y/N):";
        cin >> cont;
        system("cls");
    } while (cont == 'Y' || cont == 'y');
}

void manager::deleteStaff()
{
    int id;
    char cont;
    do
    {
        do
        {
            system("cls");
            cout << "Enter Staff ID to delete: ";
            cin >> id;
        } while (is_Number(to_string(id)) == false);
        if (checkStaffID(id, false, 1) == false)
        {
            cout << "ID Found!" << endl;
            cout << "\nDo you want to delete this staff(Y/N)?: ";
            cin >> cont;
            if (cont == 'Y' || cont == 'y')
            {
                filesystem::remove_all("./data/staff/" + to_string(id));
                // Need an ID Update Function
                deleteStaffID(id, 1);
                cout << "\nStaff Deleted!" << endl;
            }
            else
            {
                cout << "\nNo Staff Deleted!\n";
                system("pause");
                break;
            }
        }
        else
        {
            cout << "No ID Found!" << endl;
        }
        system("pause");
        system("cls");
        cout << "Continue to delete Staff?(Y/N): ";
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
        cout << "(4) Find Staff by ID" << endl;
        cout << "(5) Show Monthly Sales" << endl;
        cout << "(6) Check Staff Log" << endl;
        cout << "Input Your Choice: ";
        do
        {
            checkInput = cinIg(cin, choice, true);
        } while (choice < 0 || choice > 6 || checkInput == false);
        switch (choice)
        {
        case 0:
            clearConsole();
            cout << "See You Next Time!" << endl;
            system("pause");
            return;
        case 1: //Add new Staff
            addNewStaff();
            break;
        case 2: //Update Staff
            updateStaff();
            break;
        case 3: //Delete Staff
            deleteStaff();
            break;
        case 4: //Find Staff
            showStaff();
            break;
        case 5: //Show Monthly Sales
            monthlySales();
            break;
        case 6: //Staff log
            checkLog();
            break;
        }

        system("cls");
        cout << "Return to Manager Menu(Y/N)?: ";
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
            cout << "See You Next Time!" << endl;
            system("pause");
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

void manager::monthlySales()
{
    system("cls");

    int year, month;
    cout << "Enter Year and Month (seperated by space): ";
    cin >> year >> month;
    ifstream sales("./data/export/" + to_string(year) + "/" + to_string(month) + "/total.csv");
    map<item, int> tmp;
    float total = 0;

    cout << "\nSales in " << month << "/" << year << endl;

    if (sales.is_open())
    {
        cout << "\nOpen File Successfully!" << endl;
        string line;
        string token;
        item dum;
        int foo;

        while (getline(sales, line))
        {
            stringstream check(line);
            if (line.find("Total:") != string::npos)
            {
                getline(check, token, ',');
                getline(check, token);
                total = stof(token);
                break;
            }

            getline(check, token, ',');
            dum.id = stoi(token);
            getline(check, token, ',');
            dum.name = token;
            getline(check, token, ',');
            foo = stoi(token);
            getline(check, token, ',');
            dum.price = stof(token);
            getline(check, token);
            tmp[dum] += foo;
        }
        sales.close();

        cout << "\n\n|" << left << setw(4) << "ID"
             << "|" << left << setw(10) << "Item Name"
             << "|" << left << setw(10) << "Quantity"
             << "|" << left << setw(8) << "Price"
             << "|" << endl;
        for (auto x : tmp)
        {
            cout << "\n|" << left << setw(4) << x.first.id << "|" << left << setw(10) << x.first.name << "|" << left << setw(10) << x.second << "|" << left << setw(8) << x.first.price << "|" << endl;
        }
        cout << "\nTotal: " << total << "\n\n";
    }
    else
    {
        cout << "Total: 0\n"
             << endl;
        system("pause");
    }
}

void manager::showStaff()
{
    int id;
    char cont;
    do
    {
        system("cls");
        cout << "Enter Staff ID:";
        cin >> id;
        if (checkStaffID(id, false, 1) == true)
        {
            cout << "ID not found!\n\n";
        }
        else
        {
            cout << "Staff Found!\n\n"
                 << endl;
            staff *obj = new staff;
            obj->get(id);
            obj->output();

            delete obj;
        }
        cout << "Continue to Show Staff(Y/N)?: ";
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

void manager::checkLog()
{
    system("cls");
    ifstream fin("./data/log/stafflog.txt");
    cout << "==========STAFF LOG=========="
         << "\n\n";

    string line;
    while (getline(fin, line))
        cout << line << endl;
    cout << "\n\n";
    system("pause");
}