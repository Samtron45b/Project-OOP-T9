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