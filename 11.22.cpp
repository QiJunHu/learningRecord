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

   int a[]={1,2,3,4,5,6,7,8,9,10};
   vector<int> ivec(a,a+10);
   list<int>  ilist(ivec.rbegin()+3 ,ivec.rbegin()+8);
   ostream_iterator<int> out(cout,"\n");
   copy(ilist.begin(),ilist.end(),out);




    return 0;
}
