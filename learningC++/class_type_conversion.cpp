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


class testClassConversion
{
    public:
        //default constructor
        testClassConversion():i(0),s(" "),ivec(10) {}
        //copy control
        testClassConversion(const testClassConversion & m):i(m.i),s(m.s),ivec(m.ivec) {}

        testClassConversion & operator=(const testClassConversion & m){ i = m.i; s = m.s;  ivec = m.ivec;   return *this; }
        ~testClassConversion() {}

        //conversion operator
        operator int() const { std::cout<<"the conversion operator of testClassConversion is called"<<std::endl;   return i ;}

    private:
        int  i;
        std::string s;
        std::vector<int> ivec;


};



void fuck(int i)
{
    std::cout<<"value is : "<<i<<std::endl;
}


//test code
int main()
{
    testClassConversion t;
    
    //conversion operator in expression
    std::cout<<3+t<<std::endl;
    
    
    //conversion operator in condition statement
    if(t)
        std::cout<<"test  t"<<std::endl;
    if(t+1)
        std::cout<<"test t+1"<<std::endl;
    
    
    //conversion operator in copy parameter
    fuck(t+5);

    //conversion operator in obvious type conversion 
    int i = static_cast<int>(t) + 7;
    std::cout<<i<<std::endl;


    return 0;

}


