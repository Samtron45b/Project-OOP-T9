#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include "staff.hpp"
#include <vector>
#include <direct.h>
#include <filesystem>
class manager : public person
{
private:
    int id;

public:
    virtual void input();
    virtual void output();
    void addNewStaff();
    void updateStaff();
    void deleteStaff();
    vector<double> monthlySales(); // ???
    virtual void menu();
    virtual void save();
    virtual void get(int ID); // DO NOT KNOW WHAT TO CODE HERE
    virtual int getID();
};

bool checkStaffID(int id, bool save, int type);
void saveStaffIDlist(int *list, int n, int type);
void deleteStaffID(int id, int type);
// NEED A ID DELETE FUNCTION

#endif // !_MANAGER_HPP_