#ifndef _GUEST_H_
#define _GUEST_H_

#include "person.hpp"
#include <vector>

struct item{
    
};

class guest: public person{
    private:
        std::vector<item> cart;
    public:
        guest();
        virtual ~guest(){};
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
};

class member: public guest{

};

#endif // !_GUEST_H_
