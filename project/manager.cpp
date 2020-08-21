#include "manager.hpp"

bool checkStaffID(int ID)
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
    if (res)
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
    if (checkStaffID(id) == true)
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
        if (checkStaffID(id) == false)
        {
            cout << "Do you want to delete this staff?(Y/N): ";
            cin >> cont;
            if (cont == 'Y' || cont == 'y')
                rmdir("./data/staff/" + to_string(id));
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
    } while (cont == "Y" || cont == "y");