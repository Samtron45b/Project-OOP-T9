#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include "Account.h"
#include "staff.hpp"
#include <vector>
#include <direct.h>
#include <filesystem>
#include <sstream>
#include <map>
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
    void monthlySales();
    void menu();
    void save();
    void get(int ID);
    int getID();
    void showStaff();
    void checkLog();
};

bool checkStaffID(int id, bool save, int type);
void saveStaffIDlist(int *list, int n, int type);
void deleteStaffID(int id, int type);
// NEED A ID DELETE FUNCTION

#endif // !_MANAGER_HPP_