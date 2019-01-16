#include"remote.h"
#include<iostream>
#include<string>

using namespace car;

void onMouseHandle(int event,int x,int y,int flags,void *param);
int main()
{
    remote myRemote;
    string windowName="this is a remote control";
    namedWindow(windowName);
	setMouseCallback(windowName,onMouseHandle,(void*)&myRemote);
    while(1)
    {
        //imshow(windowName,myRemote.getMap());
        int key=waitKey(30)&255 ;
        if(key=='q')//'q'我也不知道为什么
        {
            cout<<"bye bye"<<endl;
            break;
        }
        if(key=='1')//'1'’
        {
            myRemote.setGear(car::gear::forward);
        }
        if(key=='2')//'2'
        {
            myRemote.setGear(car::gear::back);
        }
        if(key==' ')//' '
        {
            myRemote.setGear(car::gear::lock);
        }
    }
    return 0;
}
void onMouseHandle(int event,int x,int y,int flags,void *param)
{
    remote* myRemote=(remote*)param;
    vector<int> res=myRemote->getCommand(x,y);
    cout<<res[0]<<" "<<res[1]<<" "<<res[2]<<endl;
}

