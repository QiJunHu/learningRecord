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
#include<stdexcept>


//base class
class Item_base
{

friend std::ostream& operator<<(std::ostream &, Item_base &);

public:
    Item_base(const std::string& book="",double sale_price=0.0):isbn(book),price(sale_price) {}

    std::string book() const { return isbn;}

    virtual Item_base* clone() const
    {
        return new Item_base(*this);
    }

    virtual double net_price(std::size_t n) const
    {
        return price*n;
    }

    //debug function controlled by flag parameter
    virtual void debug1(bool flag) const
    {
        if(flag)
        std::cout<<"ISBN: "<<isbn<<std::endl
                <<"Price: "<<price<<std::endl;
    }


    //debug function controlled by flag member
    virtual void debug2() const
    {
        if(flag)
        std::cout<<"ISBN: "<<isbn<<std::endl
                <<"Price: "<<price<<std::endl;

    }

    virtual ~Item_base() {}

protected:
    double price;                // price of a book
    bool flag;
private:
    std::string isbn;         // isbn  of a book

};

std::ostream& operator<<(std::ostream &  os,Item_base& ib)
{
    os<<"\tUsing operator<<(std::ostream &,Item_base&);"<<std::endl
       <<"\tVisit Item_base's book():\t"<<ib.isbn<<std::endl
       <<"\tVisit Item_base's net_price():"
       <<"3 "<<ib.book()<<" , the price is:\t"
       <<ib.net_price(3)<<std::endl;
    return os;
}



//derived class
class Bult_Item :public Item_base
{
friend std::ostream & operator<<(std::ostream & ,Bult_Item &);

public:
    Bult_Item(const std::string& book="",double sale_price=0.0,std::size_t qty=0,double disc=0.0):Item_base(book,sale_price),min_qty(qty),discount(disc) {}

    Bult_Item* clone() const
    {
        return new Bult_Item(*this);
    }

    double net_price(std::size_t cnt) const
    {
        if(cnt > min_qty)
            return cnt*(1-discount)*price;

    }

    void debug1(bool flag) const
    {
        if(flag)
        std::cout<<"ISBN: "<<book()<<std::endl
                 <<"PriceL "<<price<<std::endl
                 <<"Min_quantiry: "<<min_qty<<std::endl
                 <<"Discount Rate: "<<discount<<std::endl;
    }


    void debug2() const
    {
        if(flag)
        std::cout<<"ISBN: "<<book()<<std::endl
                 <<"PriceL "<<price<<std::endl
                 <<"Min_quantiry: "<<min_qty<<std::endl
                 <<"Discount Rate: "<<discount<<std::endl;

    }

    ~Bult_Item() {}

private:
    std::size_t min_qty;                // min quantity of books to have a discount
    double discount;                 //discount rate
};


std::ostream & operator<<(std::ostream &  os,Bult_Item & bi)
{
    os<<"\tUsing operator<<(std::ostream &,Bulk_Item);"<<std::endl
       <<"\tVisit Item_base's book():\t"<<bi.book()<<std::endl
       <<"\tVisit Item_base's net_price():"
       <<"5 "<<bi.book()<<" , the price is:\t"
       <<bi.net_price(5)<<std::endl;
    return os;

}



//handle class 
class Sales_item
{
public:
    //default constructor:unbound handle
    Sales_item():p(0),use( new std::size_t(1)) {}
    //attaches a handle to copy of the Item_base object
    Sales_item(const Item_base & item):p(item.clone()),use(new std::size_t(1)) {}

    //copy control members to manage the use count and pointers
    Sales_item(const Sales_item & i):p(i.p),use(i.use) { ++ use; }

    Sales_item& operator=(const Sales_item&);


    ~Sales_item() { decr_use();}

    const Item_base* operator->() const
    {
        if(p)
            return p;
        else throw std::logic_error("unbound Sales_item");
    }

    const Item_base operator*() const
    {
        if(p)
            return *p;
        else throw std::logic_error("unbound Sales_item");
    }




private:
    Item_base *p;   //pointer to shared item
    std::size_t * use ;   // pointer to a shared use count( reference count);
    void decr_use()
    {
        if(--*use == 0)
        {
            delete p;
            delete use;
        }
    }
};




Sales_item& Sales_item::operator=(const Sales_item& rhs)
{
     ++*rhs.use;
     decr_use();
     p = rhs.p;
     use =  rhs.use;
     return * this;
}


//compare function of Sales_Item for multiset to use
inline bool compare(const Sales_item& rh1,const Sales_item& rh2)
{
    return rh1->book() < rh2->book() ;

}




//really class used in real business
class  Basket
{
    typedef bool (*Comp) (const Sales_item&,const Sales_item&);

public:
    typedef std::multiset<Sales_item,Comp> set_type;
    typedef set_type::size_type size_type;
    typedef set_type::const_iterator const_iter;

    //constructor
    Basket():items(compare) {}

    void add_item(const Sales_item& item)
    {
        items.insert(item);
    }

    size_type size(const Sales_item& i) const
    {
        return items.count(i);
    }

    double total() const;

private:
    std::multiset<Sales_item,Comp> items;


};


double Basket::total() const
{
    double sum = 0.0;

    for(const_iter i = items.begin() ;  i != items.end() ; i = items.upper_bound(*i))
    {
        sum += (*i)->net_price(items.count(*i));
    }


    return sum;

}


//test code
int main()
{

    return 0;

}


