#include <iostream>  
#include <iterator>  
#include <algorithm>  
#include <fstream>  
#include <list>  
#include <string>  
  
  
  
struct Noname  
{  
        //default constructor  
        Noname():pstring(new std::string),i(0),d(0) {  std::cout<<"default constructor called"<<std::endl;}  
        // constructor  
        Noname(int in,double dou):pstring(new std::string),i(in),d(dou) { std::cout<<"constructor called"<<std::endl;}  
        //copy constructor  
        Noname (const Noname & no):pstring(new std::string),i(no.i),d(no.d)  
        {  
            std::cout<<"copy constructor called"<<std::endl;  
            *pstring = * (no.pstring);  
        }  
  
        //assign operator  
        Noname& operator=(const Noname &);  
  
        ~Noname()  
        {  
            std::cout<<"destructor is called "<<std::endl;  
            delete pstring;  
  
        }  
  
    public:  
        std::string *pstring;  
        int i;  
        double d;  
};  
  
  
  
Noname& Noname::operator=(const Noname & no)  
{  
    std::cout<<"assign operator called "<<std::endl;  
    *pstring = * (no.pstring);  
    i = no.i;  
    d = no.d;  
}  
  
  
  
int main(int argc,char* argv[])  
{  
    Noname test(5,3);  
    std::cout<<test.i<<"   "<<test.d<<std::endl;  
    Noname test1(test);  
    std::cout<<test1.i<<"   "<<test1.d<<std::endl;  
    Noname test2;  
    std::cout<<test2.i<<"   "<<test2.d<<std::endl;  
    test2 =  test1;  
    std::cout<<test2.i<<"   "<<test2.d<<std::endl;  
  
    if(true)  
    {  
        Noname testk(5,5);  
  
    }  
  
    return 0;  
}  