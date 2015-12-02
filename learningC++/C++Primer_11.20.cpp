//////////////////////////////////////////////////
/*    author huqijun ,20151107                  */
//////////////////////////////////////////////////


#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;


int main(int argc,char* argv[])
{


   istream_iterator<int> in_iter(cin),end_iter;
   vector<int> ivec(in_iter,end_iter);

   for(vector<int>::reverse_iterator i = ivec.rbegin() ; i != ivec.rend() ; ++i)
   {
       cout<<*i<<endl;
   }

   for(vector<int>::iterator i =  ivec.end() - 1 ; i !=  ivec.begin() -1 ; --i)
   {
       cout<<*i<<endl;
   }

    return 0;
}
