#ifndef PERSON_H_
#define PERSON_H_
#include <string>
#include "date.hpp"

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
        virtual void load(std::istream&);
        virtual void output();
        virtual void print(std::ostream&) const;
        friend std::istream& operator>>(istream& in,person& a);
        friend std::ostream& operator<<(std::ostream& out,const person a);
};

#endif // !PERSON_H_
