#include "manager.hpp"

bool checkStaffID(int ID, bool save)
{
    ifstream list("./data/staff/ID_List.txt");
    int *arr, n;
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
        saveStaffIDlist(arr, n);
    }
    delete[] arr;
    return res;
}
void saveStaffIDlist(int *list, int n)
{
    ofstream file("./data/staff/ID_List.txt");
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

void manager::addNewStaff()
{
    char choice, cont;
    do
    {
        do
        {
            system("cls");
            cout << "Add New Staff?(Y/ N)";
            cin >> choice;
        } while (choice != 'Y' || choice != 'y' || choice != 'N' || choice != 'n');
        switch (choice)
        {
        case 'Y':
        case 'y':
        {
            staff *temp = new staff;
            temp->input();
            // Missing File + Save Data;
            cout << "New Staff Added!" << endl;
            delete temp;
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
    } while (is_number(to_string(id)) == false);
    if (checkStaffID(id, false) == true)
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
        } while (is_number(to_string(id)) == false);
        if (checkStaffID(id, false) == false)
        {
            cout << "Do you want to delete this staff?(Y/N): ";
            cin >> cont;
            if (cont == 'Y' || cont == 'y')
            {
                rmdir(("./data/staff/" + to_string(id)).c_str());
                // Need an ID Update Function
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