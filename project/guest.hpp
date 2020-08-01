#ifndef _GUEST_H_
#define _GUEST_H_

#include "person.hpp"
#include <vector>
#include <map>

struct item{
    string name;
    int id, storage;
    double price;

    bool get();
    void save();
    bool save(int);
    item find(int);
};

bool operator<(const item& lhs,const item&rhs)
{
    return (lhs.id<rhs.id)||(lhs.id==rhs.id&&lhs.name<rhs.name);
}

class guest: public person{
    private:
        std::map<item,int> cart;
    public:
        guest(){}
        virtual ~guest(){}
        virtual void menu();
        virtual void input();
        virtual void output();
        virtual void export();
        virtual double payment();
        virtual void print(std::ostream&) const;
        virtual void load(std::istream&);
        friend std::istream& operator>>(std::istream& in,guest& a);
        friend std::ostream& operator<<(std::ostream& out,const guest& a);
        virtual bool buy(std::vector<item>,int);
        virtual void save()=0;
};

class member: public guest{
    private:
        int rank,memberPoint;
    public:
        member(){}
        virtual ~member(){}
        virtual void menu();
        virtual void input();
        virtual void output();
        virtual void export();
        virtual double payment();
        virtual void print(std::ostream&) const;
        virtual void load(std::istream&);
        friend std::istream& operator>>(std::istream& in,guest& a);
        friend std::ostream& operator<<(std::ostream& out,const guest& a);
        virtual bool buy(std::vector<item>,int);
        void viewHistory();
        std::vector<item> preOrder();
        std::vector<item> favoriteItem();
        void save();
};

#endif // !_GUEST_H_
