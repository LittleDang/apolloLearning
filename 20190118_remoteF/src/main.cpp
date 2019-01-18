#include "remote.h"
#include "remoteF/control.h"
#include "ros/ros.h"
#include <iostream>
#include <string>
#include <thread>

using namespace car;

void onMouseHandle(int event, int x, int y, int flags, void* param);
void publishThreadFunc();
ros::Publisher controlPub;
remoteF::control msg;
ros::Rate* loop;
int main(int argc, char** argv)
{
    remote myRemote;
    string windowName = "this is a remote control";
    namedWindow(windowName);
    setMouseCallback(windowName, onMouseHandle, (void*)&myRemote);
    ros::init(argc, argv, "remoteF");
    ros::NodeHandle n;
    controlPub = n.advertise<remoteF::control>("remoteF/control", 1000);
    ros::Rate loop_rate(10); //指定自循环的频率
    loop = &loop_rate;
    std::thread publishThread(publishThreadFunc); //开线程
    publishThread.detach();
    while (1) {
        imshow(windowName, myRemote.getMap());
        int key = waitKey(30) & 255;
        if (key == 'q') {
            cout << "bye bye" << endl;
            break;
        }
        if (key == '1') {
            myRemote.setGear(car::gear::forward);
            myRemote.setAngleSatus(on);
            myRemote.setGearSatus(on);
            myRemote.setVelocitySatus(on);
            vector<int> res = myRemote.getMsg();
            msg.speed = res[0];
            msg.angle = res[1];
            msg.gear = res[2];
            cout << "status:forward" << endl;
        }
        if (key == '2') {
            myRemote.setGear(car::gear::back);
            myRemote.setAngleSatus(on);
            myRemote.setGearSatus(on);
            myRemote.setVelocitySatus(on);
            vector<int> res = myRemote.getMsg();
            msg.speed = res[0];
            msg.angle = res[1];
            msg.gear = res[2];

            cout << "status:back" << endl;
        }
        if (key == ' ') {
            myRemote.setGear(car::gear::lock);
            myRemote.setAngleSatus(on);
            myRemote.setGearSatus(on);
            myRemote.setVelocitySatus(on);
            vector<int> res = myRemote.getMsg();
            msg.speed = res[0];
            msg.angle = res[1];
            msg.gear = res[2];

            cout << "status:lock" << endl;
        }
        if (key == '3') //油门模式前进等价于有速度，有前进，有油门，没有角度{gear=forward,gear=on,velocity=on,angle=off}
        {
            myRemote.setGear(car::gear::forward);
            myRemote.setAngleSatus(off);
            myRemote.setGearSatus(on);
            myRemote.setVelocitySatus(on);
            vector<int> res = myRemote.getMsg();
            msg.speed = res[0];
            msg.angle = res[1];
            msg.gear = res[2];

            cout << "status:forward gear mode" << endl;
        }
        if (key == '4') //油门模式前进等价于有速度，有后进，有油门，没有角度{gear=backward,gear=on,velocity=on,angle=off}
        {
            myRemote.setGear(car::gear::back);
            myRemote.setAngleSatus(off);
            myRemote.setGearSatus(on);
            myRemote.setVelocitySatus(on);
            vector<int> res = myRemote.getMsg();
            msg.speed = res[0];
            msg.angle = res[1];
            msg.gear = res[2];

            cout << "status:back gear mode" << endl;
        }
        if (key == '5') //角度模式等价于没速度，有前进，每油门，有角度
        {
            myRemote.setGear(car::gear::forward);
            myRemote.setAngleSatus(on);
            myRemote.setGearSatus(off);
            myRemote.setVelocitySatus(off);
            vector<int> res = myRemote.getMsg();
            msg.speed = res[0];
            msg.angle = res[1];
            msg.gear = res[2];

            cout << "status:angle mode" << endl;
        }
    }
    return 0;
}
void onMouseHandle(int event, int x, int y, int flags, void* param)
{
    remote* myRemote = (remote*)param;
    vector<int> res = myRemote->getCommand(x, y);
    msg.speed = res[0];
    msg.angle = res[1];
    msg.gear = res[2];
    controlPub.publish(msg);
    //cout << res[0] << " " << res[1] << " " << res[2] << endl;
}
void publishThreadFunc()
{
    while (1) {
        controlPub.publish(msg);
        loop->sleep();
    }
}
