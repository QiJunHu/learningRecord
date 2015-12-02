//////////////////////////////////////////////////
/*    author huqijun ,20151111               */
//////////////////////////////////////////////////


#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>

using namespace std;

class Person
{
    public:
        Person():name("huqijun"),addr("hangzhou") {}
        Person(string ,string );

         // small function should be define as inline function
        string getName() const
        {
           return name;
        }
        string getAddr() const
        {
            return addr;
        }
    //private members
    private:
        string name;
        string addr;
};


Person::Person(string name1,string addr1)
{
    name = name1;
    addr = addr1;

}


int main(int argc,char* argv[])
{
   Person Huqijun;
   cout<<"Name: "<<Huqijun.getName()<<endl;
   cout<<"Addr: "<<Huqijun.getAddr()<<endl;

   Person She("Jianghanxia","hangzhou");

   cout<<"Name: "<<She.getName()<<endl;
   cout<<"Addr: "<<She.getAddr()<<endl;
    return 0;
}
