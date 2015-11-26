//////////////////////////////////////////////////
/*    author huqijun ,20151126               */
//////////////////////////////////////////////////


#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <set>
#include<utility>


class Date
{
    //overload operator>>
    friend std::istream&  operator>> (std::istream &, Date &);
    //overload operator<<
    friend std::ostream&  operator<< (std::ostream& , const Date &);
    //overload operator+
    friend Date operator+(const Date&,const Date&);
    //overload operator==
    friend bool operator==(const Date&,const Date&);
    //overload operator!=
    friend bool operator!=(const Date&,const Date&);
    public:
        //default constructor
        Date():year(2015),month(11),day(25) {  std::cout<<"default constructor is called"<<std::endl;}
        //copy control
        //copy constructor
        Date(const Date& d):year(d.year),month(d.month),day(d.day) {  std::cout<<"copy constructor is called"<<std::endl;};
        //operator =
        Date & operator=(const Date&);
        Date & operator+=(const Date&);
    private:
        unsigned  year;
        unsigned  month;
        unsigned  day;
};

std::istream&  operator>> (std::istream & in, Date & s)
{
    std::cout<<"operator>> of Date is called"<<std::endl;
    in>>s.year>>s.month>>s.day;
    return in;
}



std::ostream&  operator<< (std::ostream& out , const Date & s)
{
    std::cout<<"operator<< of Date is called"<<std::endl;
    out<<s.year<<"\t"<<s.month<<"\t"<<s.day;
    return out;
}


Date operator+(const Date& d1,const Date& d2)
{
    std::cout<<"operator+ of Date is called"<<std::endl;

   Date ret(d2);
   ret.year += d1.year;
   ret.month += d1.month;
   if(ret.month > 12)
    ret.month = 12;
   ret.day += d1.day;
   if(ret.day > 31 )
    ret.day = 31;
   return ret;
}


bool operator==(const Date& d1,const Date& d2)
{
    std::cout<<"operator== of Date is called"<<std::endl;
    return d1.day == d2.day && d1.month==d2.month && d1.year==d2.year  ;
}


bool operator!=(const Date& d1,const Date& d2)
{
    std::cout<<"operator!= of Date is called"<<std::endl;
    return !(d1 == d2);
}



Date& Date::operator=(const Date& d)
{
    std::cout<<"operator= of Date is called"<<std::endl;
    year = d.year;
    month = d.month;
    day = d.day;
    return *this;
}



Date & Date::operator+=(const Date& d)
{
    std::cout<<"operator+= of Date is called"<<std::endl;
    year += d.year;
    month == d.month;
    day += d.day;
    return *this;
}


int main()
{


    Date date1;
    std::cout<<date1<<std::endl;
    Date date2(date1);
    std::cout<<date2<<std::endl;
    std::cout<<"is equal :"<<(date1==date2) <<std::endl;
    Date date3 = date1 + date2;
    std::cout<<date3<<std::endl;
    std::cout<<"is not equal :"<<( date1 !=  date3)<<std::endl;


    Date date4 = date1;
    Date date5;
    date5 = date1;


    return 0;
}

