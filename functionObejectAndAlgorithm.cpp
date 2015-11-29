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
    return 0;

}


