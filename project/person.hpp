#ifndef PERSON_H_
#define PERSON_H_
#include <string>
#include "date.hpp"
#include <vector>
class person
{
    private:
        std::string name,tel;
        date DoB;
        float age;
    public:
        person();
        virtual ~person();
        virtual void input();
        virtual void output();
        virtual void print(std::ostream&) const;
        virtual void load(std::istream&);
        friend std::istream& operator>>(istream& in,person& a);
        friend std::ostream& operator<<(std::ostream& out,const person& a);
        virtual void menu()=0;
};

class guest: public person{
    private:
        // ? std::vector<item> cart;
    public:
        virtual void menu();
        virtual void input();
        virtual void output();
        virtual void export();
        virtual double payment();
        virtual void print(std::ostream&) const;
        virtual void load(std::istream&);
        friend std::istream& operator>>(istream& in,guest& a);
        friend std::ostream& operator<<(std::ostream& out,const guest& a);
        // ? virtual bool buy(std::vector<item>,int);
};

class member: public guest{

};

#endif // !PERSON_H_
