//////////////////////////////////////////////////
/*    author huqijun ,20151111               */
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
    list<int> lis(in_iter,end_iter);
    ostream_iterator<int> out(cout,"\n");
    cout<<"content before unique "<<endl;
    copy(lis.begin(),lis.end(),out);
    lis.unique();
    cout<<"content after unique "<<endl;
    copy(lis.begin(),lis.end(),out);



    return 0;
}
