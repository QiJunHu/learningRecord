//////////////////////////////////////////////////
/*    author huqijun ,modify time 20151129      */
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





//class Foo
class Foo
{
    public:
        Foo():data(10,1) {}
        int& operator[] (const std::size_t);
        const int& operator[](const std::size_t)  const;
    private:
        std::vector<int> data;
};


int& Foo::operator[] (const std::size_t index)
{
    std::cout<<"operator[] of Foo is called"<<std::endl;
    return data[index];
}

const int& Foo::operator[](const std::size_t  index)  const
{
     std::cout<<"operator[] const of Foo is called"<<std::endl;
    return data[index];
}



//class HasPtr
class HasPtr
{

    public:
        //default constructor
        HasPtr():p(new int) {}
        //constructor
        HasPtr(int * i):p(i) {}
        //copy control
        HasPtr(const HasPtr &  m)  { *p = *(m.p) ;}
        int operator* () { return *p;}
        int * operator->() { return p;}
    private:
        int * p;
};


class autoAdd
{

    public:
        friend std::istream & operator>>(std::istream & , autoAdd &);
        friend std::ostream & operator<<(std::ostream &, const autoAdd &);
        //default constructor
        autoAdd():i(0) {  std::cout<<"default constructor  of autoAdd is called"<<std::endl;}
        //copy control
        autoAdd(const autoAdd& m):i(m.i)  {  std::cout<<"copy constructor  of autoAdd is called"<<std::endl;}
        autoAdd & operator=(const autoAdd & m) { std::cout<<"operator=  of autoAdd is called"<<std::endl; i = m.i;   return *this;}

        autoAdd& operator++() {  std::cout<<"prefix operator++   of autoAdd is called"<<std::endl;  ++i; return *this;}
        autoAdd operator++(int) {  std::cout<<"postfix operator++   of autoAdd is called"<<std::endl;  autoAdd ret(*this);  i++; return ret;}
        autoAdd& operator--() { std::cout<<"prefix operator--   of autoAdd is called"<<std::endl;   --i; return *this; }
        autoAdd operator--(int) {std::cout<<"postfix operator--   of autoAdd is called"<<std::endl; autoAdd ret(*this);  i--; return ret; }
    private:
        int i;
};


std::istream & operator>>(std::istream & i , autoAdd & a)
{
    std::cout<<"operator>> of autoAdd is called"<<std::endl;
    i>>a.i;
    return i;
}


std::ostream & operator<<(std::ostream & o, const autoAdd & a)
{
    std::cout<<"operator<< of autoAdd is called"<<std::endl;
    o<<a.i;
    return o;
}


//test code
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


   // test operator[]
   Foo f;
   std::cout<<f[2]<<std::endl;
   f[1] = 3;

    int t = 3;
    HasPtr has1(&t);
    std::cout<<*has1<<std::endl;
    std::cout<<*( has1.operator->() )<<std::endl;


   // test class autoAdd
   autoAdd a1;
   std::cout<<a1<<std::endl;
   std::cin>>a1;
   std::cout<<a1<<std::endl;
   ++a1;
   std::cout<<a1<<std::endl;
   a1++;
   std::cout<<a1<<std::endl;
   std::cout<<a1++<<std::endl;
   --a1;
   std::cout<<a1<<std::endl;
   a1--;
   std::cout<<a1<<std::endl;
   return 0;




}

