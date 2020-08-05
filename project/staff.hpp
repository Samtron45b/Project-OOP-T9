#include "person.hpp"
#include "utility"
class staff :public person
{
private:
    int id;
public:
    staff();
    ~staff();
    void checkIn();
    bool addNewMem();
    void showMem();
    void updateRecord();
    bool deleteRecord();
    pair<item, int> searchRecord();
    void menu();
    member updateMem();
    void save();


};