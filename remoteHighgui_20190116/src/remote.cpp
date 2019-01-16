#include"remote.h"
using namespace car;
remote::remote(int a)
{
    this->cols=a;
    this->rows=a;
    tri1=vector<Point>(3,Point(0,0));
    tri2=vector<Point>(3,Point(0,0));
    tri1[0].x=cols/8.0;
    tri1[0].y=rows/8.0;
    cout<<tri1[0]<<endl;
    tri1[1].x=cols-cols/8.0;
    tri1[1].y=rows/8.0;

    tri1[2].x=cols/2;
    tri1[2].y=rows/2;

    tri2[0].x=cols/8.0;
    tri2[0].y=rows-rows/8.0;
    tri2[1].x=cols-cols/8.0;
    tri2[1].y=rows-rows/8.0;
    tri2[2].x=cols/2;
    tri2[2].y=rows/2;

    center=tri2[2];
    r=20; 
    R=a*0.5*0.8;
    //set the triangle and the circle
    image=Mat(rows,cols,CV_8UC3);
    background=Mat(rows,cols,CV_8UC3);
    color=Scalar(0,0,255);
    double x,y;
    x=tri1[0].x-center.x;
    y=-(tri1[0].y-center.y);
    maxAngle=(atan2(y,x)-M_PI/2);
    setGear(lock);
    Resangle=0;
    Resvelocity=0;
}
vector<int> remote::getCommand(int mouse_x,int mouse_y)
{
    if(status==lock)
        return {0,0,0};
    if(isInCircle(mouse_x,mouse_y))
        {
            setGear(lock);
            return {0,0,0};
        }
    if(background.at<Vec3b>(mouse_y,mouse_x)==Vec3b(0,0,120))
        return{0,0,0};
    if(background.at<Vec3b>(mouse_y,mouse_x)==Vec3b(0,0,0))
    {
        return {Resvelocity,Resangle,status};
    }
    int x=mouse_x-center.x;
    int y=mouse_y-center.y;
    Resvelocity=(int)(sqrt(x*x+y*y)/R*max_velocity);
    image=background.clone();
    double mouse_angle=atan2(mouse_y-center.y,mouse_x-center.x);
    line(image,center+Point(r*cos(mouse_angle),r*sin(mouse_angle)),
    Point(mouse_x,mouse_y),Scalar(2555,255,255),3);
    Resangle=MapAngle(Point(mouse_x,mouse_y));
    return {Resvelocity,Resangle,status};
}

int remote::MapAngle(Point p)
{
    p=p-center;
    p.y=-p.y;
    double angle=atan2(p.y,p.x);
    if(angle>=0 && angle<M_PI/2)
        return (int)(((M_PI/2-angle)/maxAngle*angle_max));
    else if(angle>=M_PI/2 && angle<=M_PI)
        return (int)(((angle-M_PI/2)/maxAngle*angle_min));
    else if(angle<0 && angle>=-M_PI/2)
        return (int)(((M_PI/2+angle)/maxAngle*angle_max));
    else
        return (int)(((angle+M_PI/2)/maxAngle*angle_max));
}
int remote::isInCircle(int x,int y)
{
    x=x-center.x;
    y=y-center.y;
    if(sqrt(x*x+y*y)<=r)
        return 1;
    else
        return 0;
}
Mat remote::getMap()
{
    return image;
}
int remote::setGear(gear src)
{
    status=src;
    Resangle=0;
    Resvelocity=0;
    background=Mat::zeros(rows,cols,CV_8UC3);
    Point rookPoints[2][3];
    for(int i=0;i<3;i++)
        {
            rookPoints[0][i]=tri1[i];
            rookPoints[1][i]=tri2[i];
        }
    const Point* ppt1[1] = { rookPoints[0]};
	int npt1[] = { 3 };	
    const Point* ppt2[1] = { rookPoints[1]};
	int npt2[] = { 3 };	
    switch (src)
    {
        case forward:
        {
            ellipse(background,center,Size(rows*0.8*0.5,cols*0.8*0.5),M_PI/2-maxAngle,
            -90-maxAngle/M_PI*180,
            -90+maxAngle/M_PI*180,
            Scalar(0,255,0),-1);

            ellipse(background,center,Size(rows*0.8*0.5,cols*0.8*0.5),M_PI/2-maxAngle,
            90-maxAngle/M_PI*180,
            90+maxAngle/M_PI*180,
            Scalar(0,0,120),-1);

            line(background,Point(center.x,center.y-R),center,
            Scalar(0,0,255),2);
            break;
        }
        case back:
        {
            ellipse(background,center,Size(rows*0.8*0.5,cols*0.8*0.5),M_PI/2-maxAngle,
            -90-maxAngle/M_PI*180,
            -90+maxAngle/M_PI*180,
            Scalar(0,0,120),-1);

            ellipse(background,center,Size(rows*0.8*0.5,cols*0.8*0.5),M_PI/2-maxAngle,
            90-maxAngle/M_PI*180,
            90+maxAngle/M_PI*180,
            Scalar(0,255,0),-1);

            line(background,Point(center.x,center.y+R),center,
            Scalar(0,0,255),2);
            break;
        }
        case lock:
        {
            ellipse(background,center,Size(rows*0.8*0.5,cols*0.8*0.5),M_PI/2-maxAngle,
            -90-maxAngle/M_PI*180,
            -90+maxAngle/M_PI*180,
            Scalar(0,0,120),-1);

            ellipse(background,center,Size(rows*0.8*0.5,cols*0.8*0.5),M_PI/2-maxAngle,
            90-maxAngle/M_PI*180,
            90+maxAngle/M_PI*180,
            Scalar(0,0,120),-1);
            break;
        }
    }
    circle(background,center,r,Scalar(0,0,255),-1,7);
    circle(background,center,r-3,Scalar(0,0,0),-1,7);
    line(background,
        cv::Point(center.x+cos(M_PI*0.75)*(r-1.7),center.y-sin(M_PI*0.75)*(r-1.7)),
        cv::Point(center.x+cos(M_PI*1.75)*(r-1.5),center.y-sin(M_PI*1.75)*(r-1.5)),
        Scalar(0,0,255),3);
    if(status==lock)
    {
    circle(background,center,r,Scalar(0,255,0),-1,7);
    circle(background,center,r-3,Scalar(0,0,0),-1,7);
    line(background,
        cv::Point(center.x+cos(M_PI*0.75)*(r-1.7),center.y-sin(M_PI*0.75)*(r-1.7)),
        cv::Point(center.x+cos(M_PI*1.75)*(r-1.5),center.y-sin(M_PI*1.75)*(r-1.5)),
        Scalar(0,255,0),3);
    }
    image=background;
}