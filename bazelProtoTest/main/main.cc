#include<iostream>
#include"main/test.pb.h"
using namespace std;
int main()
{
apollo::control::PadMessage * test=new apollo::control::PadMessage();
cout<<(test->has_header()?"Y":"N")<<endl;
test->set_header(35);
cout<<"hello world"<<(test->header()<<test->has_header()?"Y":"N")<<endl;
delete test;
return 0;
}
