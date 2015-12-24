#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <set>
#include<utility>
#include<functional>

struct Date
{
    unsigned year;
    unsigned month;
    unsigned day;
};

class Human
{
public:
    //default constructor
    Human():IdentifierID("123456"),Name("linzhiling"),birthDay(){ std::cout<<"Defaulted Constructor of Human is called"<<std::endl; }
    //copy control
    //copy constructor
    Human(Human &m):IdentifierID(m.IdentifierID),Name(m.Name) { std::cout<<"copy control of Human is called"<<std::endl;}
    // assign operator
    Human& operator=(Human& h){ IdentifierID = h.IdentifierID;  Name = h.Name;  std::cout<<"assign operator of Human is called"<<std::endl;  return *this; }

    //destructor
    virtual ~Human() { std::cout<<"destructor of Human is called"<<std::endl; }

    std::string getName() { return Name;}
protected:
    std::string IdentifierID;
    std::string Name;
    Date birthDay;
    std::string location;
    unsigned height;   // cm
    unsigned weight;
    unsigned educatedLevel;   //0: less than small school 1: small school 2: middle school 3: master 4:graduate 5: phd
    std::string occupation;
    unsigned relationState;   //0: single  1: has girlfriend or boyfriend 2: married 3:divorced

private:
    std::string Name2;
};


class Woman : public Human
{
public:
    //default constructor
    Woman():Husband("JustinHu"),Human(){ std::cout<<"Default constructor of Woman is called"<<std::endl;}
    //copy constructor
    Woman(Woman &m):Human(m) { std::cout<<"Copy constructor of Woman is called"<<std::endl; }
    //assign operator
    Woman& operator=(Woman & w)
    {
        std::cout<<"assign operator of Woman is called"<<std::endl;
        if( this != &w)
        {
            Human::operator=(w);
        }
        return *this;
    }
    //destructor
    ~Woman() {  std::cout<<"destructor of Woman is called"<<std::endl; }

    std::string showHusband() { return Husband;}
protected:

private:
    std::string Husband;
};








class Man : public Human
{
public:
   Man()
   {
       std::cout<<"defaulted constructor of Man is called"<<std::endl;
       std::cout<<Name<<std::endl;
       //std::cout<<Name2<<std::endl;
    }
protected:

private:



};

class Man2 : protected Human
{

public:
   Man2()
   {
       std::cout<<"defaulted constructor of Man is called"<<std::endl;
       std::cout<<Name<<std::endl;
       //std::cout<<Name2<<std::endl;
    }
protected:

private:





};


class Man3 : protected Human
{

public:
   Man3()
   {
       std::cout<<"defaulted constructor of Man is called"<<std::endl;
       std::cout<<Name<<std::endl;
       //std::cout<<Name2<<std::endl;
    }
protected:

private:





};






//test code
int main()
{
    std::cout<<"test access label and inherit level START"<<std::endl;

    Human  h1;
    std::cout<<h1.getName()<<std::endl;

    Man m1;
    std::cout<<m1.getName()<<std::endl;

    Man2 m2;
   // std::cout<<m2.getName()<<std::endl;

    Man3 m3;

    std::cout<<"test access label and inherit level END"<<std::endl;


    std::cout<<"test default constructor ,copy constructor ,assign operator ,destructor in inheritance hierarchy Start"<<std::endl;

    if(true)
    {
        Woman she;
    }

    std::cout<<"test default constructor ,copy constructor ,assign operator ,destructor in inheritance hierarchy  END"<<std::endl;




    return 0;

}


