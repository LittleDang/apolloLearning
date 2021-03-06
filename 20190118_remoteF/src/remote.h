#ifndef REMOTE_H__
#define REMOTE_H__
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>
namespace car {
using namespace std;
using namespace cv;
#define max_velocity 50.0f
#define angle_min -360.0f
#define angle_max +360.0f
#define forward_key '1' //forward
#define back_key '2' //back
enum gear { forward = 1,
    back = -1,
    lock = 0 };
enum status {
    on = 1,
    off = 0
};
class remote {
public:
    remote(int a = 600); //边长
    vector<int> getCommand(int mouse_x, int mouse_y);
    //v[0-100] angle
    int setGear(gear src);
    Mat getMap();
    void setGearSatus(car::status st);
    void setAngleSatus(car::status st);
    void setVelocitySatus(car::status st);
    car::status getGearStatus() { return gear_status; };
    car::status getVelocityStatus() { return velocity_status; };
    car::status getAngleStatus() { return angle_status; };
    car::gear getGear() { return status; };
    vector<int> getMsg() { return { Resvelocity, Resangle, status }; };

private:
    int rows, cols;
    vector<Point> tri1, tri2;
    Point center;
    double r; //小圆
    double R; //大圆
    Scalar color;
    gear status;
    Mat image;
    Mat background;
    double maxAngle;
    int Resangle;
    int Resvelocity;
    car::status gear_status, velocity_status, angle_status;

    int MapAngle(Point p);
    int isInCircle(int x, int y);
};
};
#endif