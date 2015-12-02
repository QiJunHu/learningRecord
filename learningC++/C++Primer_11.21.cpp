//////////////////////////////////////////////////
/*    author huqijun ,20151107                  */
//////////////////////////////////////////////////


#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>

using namespace std;


int main(int argc,char* argv[])
{


   istream_iterator<int> in_iter(cin),end_iter;
   list<int> ilist(in_iter,end_iter);
   list<int>::reverse_iterator searOut = find(ilist.rbegin(),ilist.rend(),0);
   if(searOut != ilist.rend())
   {
       cout<<"we found"<<endl;
   }
   else
   {
       cout<<"do not find"<<endl;
   }



    return 0;
}
