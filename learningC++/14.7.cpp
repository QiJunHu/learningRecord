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
    friend std::istream&  operator>> (std::istream &, Date &);
    friend std::ostream&  operator<< (std::ostream& , const Date &);
    public:
        Date():year(2015),month(11),day(25) {}
    private:
        unsigned  year;
        unsigned  month;
        unsigned  day;
};

std::istream&  operator>> (std::istream & in, Date & s)
{
    in>>s.year>>s.month>>s.day;
    return in;
}



std::ostream&  operator<< (std::ostream& out , const Date & s)
{
    out<<s.year<<"\t"<<s.month<<"\t"<<s.day;
    return out;
}



class CheckoutRecord
{
    //operator <<
    friend std::ostream&  operator<< (std::ostream& , const CheckoutRecord &);

    public:
        //constructor
        CheckoutRecord():book_id(0),title("testBook") {}

    private:
        double book_id;
        std::string title;
        Date date_borrowed;
        Date date_due;
        std::pair<std::string,std::string> borrower;
        std::vector< std::pair<std::string,std::string>*  >wait_list;

};








std::ostream&  operator<< (std::ostream& out  , const CheckoutRecord & s)
{
     out<<s.book_id<< "\t"<<s.title<<" \t"
        <<s.date_borrowed<<"\t"<<s.date_due<<"\t"<<s.borrower.first<<" "<<s.borrower.second;

    for(std::vector<std::pair<std::string,std::string>* >::const_iterator i  = s.wait_list.cbegin()   ;   i != s.wait_list.cend()  ;   ++i)
    {
        out<< (*i)->first<<" "<< (*i)->second;
    }
    return out;
}




int main()
{
    CheckoutRecord record1;
    std::cout<<record1<<std::endl;


    Date date1;
    std::cout<<date1<<std::endl;
    std::cin>>date1;
    std::cout<<date1<<std::endl;

    return 0;
}


