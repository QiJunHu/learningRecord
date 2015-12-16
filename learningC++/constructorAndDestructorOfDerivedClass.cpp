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


class Item_base
{
    public:
        Item_base(const std::string & book = "",double sales_price = 0.0):isbn(book),price(sales_price) {   std::cout<<"constructor of Item_base has been called"<<std::endl; }
        std::string bokk() const { return isbn;}

        virtual double net_price(std::size_t n) const;
        virtual ~Item_base() {  std::cout<<"destructor of Item_base has been called"<<std::endl;}
    private:
        std::string isbn;
    protected:
        double price;
};


double Item_base::net_price(std::size_t n) const
{
    std::cout<<"net_price() of Item_base has been called"<<std::endl;
    return 0.9*n*price;
}






class Bulk_Item : public Item_base
{
    public:
        Bulk_Item(std::size_t num = 0,double real_discount = 0.0):min_qty(num),discount(real_discount) { std::cout<<"constructor of Bulk_Item has been called"<<std::endl;}
        double net_price(std::size_t n) const;
        ~Bulk_Item() { std::cout<<"destructor of Bulk_Item has been called"<<std::endl;}
    private:
        std::size_t min_qty;
        double discount;
};


double Bulk_Item::net_price(std::size_t n) const
{
    std::cout<<"net_price() of Bulk_Item has been called"<<std::endl;
    if(n > min_qty)
        return n*(1 - discount)*price;
    else
        return n*price;
}





//test code
int main()
{
    //Item_base book1("BaseBook",13.5);
    Bulk_Item book2(10,0.1);


    return 0;

}
