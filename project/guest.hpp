#ifndef _GUEST_H_
#define _GUEST_H_

#include "person.hpp"
#include <vector>
#include <map>
#include "item.hpp"

class guest : public person {
protected:
    std::map<item, int> cart;
    double money;//! For member only update when finished
public:
    guest();
    virtual ~guest() {}
    virtual void menu();
    virtual void input();
    virtual void output(bool real_age = true);//! Use for display cart,etc
    virtual void exportFile();
    virtual void print(std::ostream&) const;
    virtual void load(std::istream&);
    friend std::istream& operator>>(std::istream& in, guest& a);
    friend std::ostream& operator<<(std::ostream& out, const guest& a);
    virtual bool buy(std::vector<item>, int);
    virtual void save() {}
    virtual void get(int ID) {}
};

class member : public guest {
private:
    int id;
    int rank;
    float memberPoint;
    bool use;
public:
    member();
    member(int);
    virtual ~member() {}
    virtual void menu();
    virtual void input();
    virtual void output(bool real_age = true);//! Use for display cart,etc
    void exportFile();
    double payment(bool change = false);
    void save();//? I dunno
    virtual void print(std::ostream&) const;
    virtual void load(std::istream&);
    friend std::istream& operator>>(std::istream& in, member& a);
    friend std::ostream& operator<<(std::ostream& out, const member& a);
    std::vector<item> shoppingCookie(int);
    std::vector<item> viewHistory();
    std::vector<item> preOrder();
    std::vector<item> favoriteitem();
    void get(int ID);
    bool buy(std::vector<item>, int);
    //! Choice 0 to delete, choice=1 to add
    void updateFile(int type, item, int choice = 1);
};

#endif // !_GUEST_H_
