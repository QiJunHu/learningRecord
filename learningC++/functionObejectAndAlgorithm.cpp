#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <set>
#include<utility>



bool GT6(const std::string &s)
{
    return s.size() >6;
}



class GT_cls
{
    public:
      GT_cls(std::size_t val = 0):bound(val) {}
      bool operator() (const std::string & s) { return s.size() >= bound;}
    private:
      std::string::size_type bound;
};


class equal_cls
{
    public:
        equal_cls(int i = 0):val(i) {}
        bool operator() (const int & i ) { return  i==val; }
    private:
       int val;
};




//test code
int main()
{

    std::vector<std::string> words;
    std::string word;
    while(std::cin>>word)
    {
        words.push_back(word);
    }

    std::vector<std::string>::size_type wc = std::count_if(words.begin(),words.end(),GT6);
    std::cout<<wc<<std::endl;

    std::vector<std::string>::size_type wc1 = std::count_if(words.begin(),words.end(),GT_cls(6));
    std::cout<<wc1<<std::endl;

    std::vector<std::string>::size_type wc2 = std::count_if(words.begin(),words.end(),GT_cls(2));
    std::cout<<wc2<<std::endl;

    std::vector<std::string>::iterator i = std::find_if(words.begin(), words.end(),GT_cls(2));
    std::cout<<*i<<std::endl;



    //test equal_cls
    std::vector<int> ivec(10);
    std::vector<int>::size_type cn = std::count_if(ivec.begin(), ivec.end(),equal_cls());
    std::cout<<cn<<std::endl;
    std::vector<int>::size_type cn1 = std::count_if(ivec.begin(),ivec.end(),equal_cls(10));
    std::cout<<cn1<<std::endl;
    
    
    
    //use std::functional  and function adapter
    
    
    std::vector<int> ivec;
    ivec.reserve(1030);
    for(int i = 0 ; i <1030 ;++i)
    {
        ivec.push_back(i);
    }


    //find all value that is greater than 1024
    std::vector<int>::iterator result = std::find_if(ivec.begin() ,  ivec.end() , std::bind2nd(std::greater<int>() ,1024) );

    while(result != ivec.end())
    {
        std::cout<<*result<<std::endl;
        result = std::find_if( ++result ,  ivec.end() , std::bind2nd(std::greater<int>() ,1024) );
    }



    std::vector<std::string> svec;
    svec.push_back("hello world");
    svec.push_back("test");
    svec.push_back("huqijun");
    svec.push_back("pooh");

    //find all value that is not equal to "pooh"
    std::vector<std::string>::iterator ret = std::find_if(svec.begin(),svec.end(),std::bind2nd(std::not_equal_to<std::string>(),"pooh") );
    while(ret != svec.end())
    {
        std::cout<<*ret<<std::endl;
        ret = std::find_if(++ret,svec.end(),std::bind2nd(std::not_equal_to<std::string>(),"pooh") );
    }


    //double every value
    std::vector<int> ivec2;
    ivec2.reserve(12);
    for(int i = 0; i<12 ; ++i)
    {
        ivec2.push_back(i);
    }

   // std::for_each(ivec2.begin(),ivec2.end(),std::bind2nd(std::multiplies<int>(),2) );
   //std::for_each will igonre the result of funciont
    std::transform(b.begin(),b.end(), b.begin(),std::bind2nd(std::multiplies<int>(),2) );
    for(std::vector<int>::iterator i = ivec2.begin() ;  i!= ivec2.end()  ; ++i)
    {
        std::cout<<*i<<std::endl;
    }
    
    
    
    
    
    
    return 0;

}


