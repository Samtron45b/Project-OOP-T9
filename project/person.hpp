#ifndef PERSON_H_
#define PERSON_H_
#include <string>
#include "date.hpp"
#include <tuple>

class person
{
private:
    std::string name, tel;
    float age;
protected:
    date DoB;
public:
    person();
    virtual ~person();
    virtual void input();
    virtual void output(bool real_age = true);
    virtual void print(std::ostream&) const;
    virtual void load(std::istream&);
    void update(date value);
    void update(std::string, int);
    friend std::istream& operator>>(std::istream& in, person& a);
    friend std::ostream& operator<<(std::ostream& out, const person& a);
    virtual void menu() = 0;
    virtual void save() = 0;
    virtual void get(int ID) = 0;
    std::tuple<date, std::string, std::string> get();
    void set(date, std::string, std::string);
};



#endif // !PERSON_H_
