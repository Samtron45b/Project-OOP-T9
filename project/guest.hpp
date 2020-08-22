#ifndef _GUEST_H_
#define _GUEST_H_

#include "person.hpp"
#include <vector>
#include <map>

struct item{
    std::string name;
    int id, storage;
    double price;

    bool get();
    void save();
    bool save(int);
    item find(int);
    void output();
    bool operator==(item rhs)
    {
        if((name!=rhs.name)||(id!=rhs.id)||(storage!=rhs.storage)||(price!=rhs.price))
        {
            return false;
        }
        return true;
    }
    friend std::ostream& operator<<(std::ostream& out,item value)
    {
        out<<value.id<<";"<<value.name<<";"<<value.storage<<";"<<value.price<<endl;
        return out;
    }
    friend std::istream& operator>>(std::istream& in,item value)
    {
        in>>value.id;
        in.ignore(1);
        std::string temp;
        getline(in,temp,';');
        value.name=temp;
        in>>value.storage;
        in.ignore(1);
        in>>value.price;
        in.ignore(1);
    }
};

bool operator<(const item& lhs,const item&rhs)
{
    return (lhs.id<rhs.id)||(lhs.id==rhs.id&&lhs.name<rhs.name);
}

class guest: public person{
    protected:
        std::map<item,int> cart;
        double money;//! For member only update when finished
    public:
        guest(){}
        virtual ~guest(){}
        virtual void menu();
        virtual void input();
        virtual void output();//! Use for display cart,etc
        virtual void export();
        virtual void print(std::ostream&) const;
        virtual void load(std::istream&);
        friend std::istream& operator>>(std::istream& in,guest& a);
        friend std::ostream& operator<<(std::ostream& out,const guest& a);
        bool buy(std::vector<item>,int);
        virtual void save()=0;
};

class member: public guest{
    private:
        int id;
        int rank;
        float memberPoint;
        bool use;
    public:
        member();
        member(int);
        virtual ~member(){}
        virtual void menu();
        virtual void input();
        virtual void output();//! Use for display cart,etc
        virtual void export();
        double payment(bool change =false);
        void save();//? I dunno
        virtual void print(std::ostream&) const;
        virtual void load(std::istream&);
        friend std::istream& operator>>(std::istream& in,guest& a);
        friend std::ostream& operator<<(std::ostream& out,const guest& a);
        std::vector<item> shoppingCookie(int);
        std::vector<item> viewHistory();
        std::vector<item> preOrder();
        std::vector<item> favoriteItem();
        //! Choice 0 to delete, choice=1 to add
        void updateFile(int type,item, int choice=1);
        void save();
};

#endif // !_GUEST_H_
