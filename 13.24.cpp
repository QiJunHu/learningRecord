#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <set>

class HasPtr
{
    public:

        //constructor
        HasPtr(int *p,int i):ptr(p),val(i),pCount(new int) { *pCount = 1;}
        //copy control
        HasPtr(HasPtr & h):ptr(h.ptr),val(h.val),pCount(h.pCount) {  ++(*pCount) ;}
        HasPtr& operator=(HasPtr& );
        ~HasPtr();

        void print_reference_count() { std::cout<<"shared object used times: "<<*pCount<<std::endl; }
        int * get_prt() const {return  ptr;}
        int get_int() const { return val; }
        void set_ptr(int *p) { ptr =p;}
        void set_int(int i)  {val = i;}
        int get_ptr_val() const { return *ptr;}
        void set_ptr_val(int val) { *ptr = val;}

    private:
        int * ptr;
        int val;

        //reference count members
        int * pCount;
};


HasPtr&  HasPtr::operator= (HasPtr& h)
{
    ptr = h.ptr;
    val = h.val;

    ++(*(h.pCount));
    --(*pCount);

   pCount = h.pCount;

    return *this;

}

HasPtr::~HasPtr()
{
    --(*pCount);

    if(0  ==  (*pCount))
    {
         delete ptr;
         delete pCount;
    }
}



int main()
{
    int* p = new int(42);
    HasPtr test(p,50);
    test.print_reference_count();
    HasPtr test2(p,60);
    test2.print_reference_count();


    HasPtr test3(test);
    test.print_reference_count();
    test3.print_reference_count();

    test2 = test3;
    test.print_reference_count();
    test3.print_reference_count();
    test2.print_reference_count();


    return 0;
}


