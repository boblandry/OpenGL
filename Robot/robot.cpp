#include <gl\glut.h>
#include <math.h>
#include <iostream>
using namespace std;
void gl_Point(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex3f(x,y,0);
	glEnd();
}
void dda(int x1,int y1,int x2,int y2)//直线dda算法
{
	
	int k,i; 
	float x,y,dx,dy;
	k=abs(x2-x1); 
	if (abs(y2-y1)>k) k=abs(y2-y1);
	dx=float(x2-x1)/k;
	dy=float(y2-y1)/k;
	x=float(x1);
	y=float(y1);
	for (i=0;i<k;i++)
	{
		gl_Point(int(x+0.5),int(y+0.5));
		x=x+dx;
		y=y+dy;
	}
}
void midpointline(int xs,int ys,int xe,int ye)//直线正负法
{
	int a,b,dt1,dt2,dt3,dt4,d,x,y;
	if (ys>ye)
	{
		int t1,t2;
		t1=xs;xs=xe;xe=t1;
		t2=ys;ys=ye;ye=t2;
	}
	a=ys-ye;b=xe-xs;
	double k=-a/double(b);
	if(k<1 && k>0)
		d=2*a+b;
	else if(k>=1)
		d=2*b+a;
	else if(k<=-1)
		d=2*b-a;
	else
		d=b-2*a;
	dt1=2*a;
	dt2=2*(a+b);
	dt3=2*b;
	dt4=2*(b-a);
	x=xs;y=ys;
	gl_Point(x,y);
	if (k>=1 || k<=-1)
	{
		if(k<=-1){
			while(x>xe){
				if(d<0){
					x--;y++;d=d+dt4;
				}
				else{
					y++;d=d+dt3;
				}
				gl_Point(x,y);
			}
		}
		else{
			while(x<xe)
			{
				if(d>=0){
					x++;y++;d=d+dt2;
				}
				else{
					y++;d=d+dt3;
				}
				gl_Point(x,y);
			}
		}	
	}
	else
	{
		if(k<0){
			while(x>xe){
				if(d>0){
					x--;y++;d=d+dt4;
				}
				else{
					x--;d=d-dt1;
				}
				gl_Point(x,y);
			}
		}
		else{
			while(x<xe){
				if(d<0){	
					x++;y++;d=d+dt2;	
				}
				else{
					x++;d=d+dt1;
				}
				gl_Point(x,y);
			}	
		}
		
	}
	
}
void bresenhamline(int xs,int ys,int xe,int ye)//直线bresenham算法
{
	if(xs>xe){
		int t1,t2;
		t1=xs;xs=xe;xe=t1;
		t2=ys;ys=ye;ye=t2;
	}
	int dy=ye-ys;
	int dx=xe-xs;
	int x=xs,y=ys,i;
	double m=(double)dy/(double)dx;//斜率
	double e=m-0.5;
	int count=0;
	//cout<<e<<endl;
	if (m>=0 && m<1){
		for(i=0;i<dx;i++){
			//cout<<e<<endl;
			gl_Point(x,y);
			if(e>=0){
				y++;e--;
			}
			x++;e=e+m;
		}
	}
	else if (m>1){
		m=1/m;e=m-0.5;
		for(i=0;i<dy;i++){
			count++;
			gl_Point(x,y);
			if(e>=0){
				x++;e--;
			}
			y++;e=e+m;
		}
	}
	else if (m>-1){
		for(i=0;i<dx;i++){
			gl_Point(x,y);
			//cout<<e<<endl;
			if(e<0){
				y--;e++;
			}
			x++;e=e+m;
		}
	}
	else if (m<-1){
		m=1/m;e=m-0.5;
		for (i=0;i>dy;i--){
			gl_Point(x,y);
			if(e<0){
				x++;e++;
			}
			y--;e=e+m;
		}
	}
	//cout<<count<<endl;
}
void pnarc(int r,int x0,int y0,int num)//圆弧正负法
{
	int x,y,f;
	x=0;f=0;
	if(num==1 || num==2)
		y=r;
	else if(num==3 || num==4)
		y=-r;
	else
		num=1;
	if(num==1){
		while(y>0){
			gl_Point(x+x0,y+y0);
			if(f>0){
				f=f-2*y+1;y--;
			}
			else{
				f=f+2*x+1;x++;
			}
		}
		//if(y==0)gl_Point(x,y);
	}
	else if (num==2){
		while(y>0){
			gl_Point(x+x0,y+y0);
			if(f>0){
				f=f-2*y+1;y--;	
			}
			else{
				f=f-2*x+1;x--;
			}
		}
		//if(y==0)gl_Point(x,y);
	}
	else if (num==3){
		while(y<0){
			gl_Point(x+x0,y+y0);
			if(f>0){
				f=f+2*y+1;y++;
			}
			else{
				f=f-2*x+1;x--;
			}
		}
		//if(y==0)gl_Point(x,y);
	}
	else{
		while(y<0){
			gl_Point(x+x0,y+y0);
			if(f>0){
				f=f+2*y+1;y++;
			}
			else{
				f=f+2*x+1;x++;
			}
		}
		//if(y==0)gl_Point(x,y);
	}
	
}  
void pnarc1(int r,int x0,int y0,int num)//圆弧正负法代码简洁版 
{
	int x,y,f;
	x=0;f=0;y=r;
	if(num!=1 && num!=2 && num!=3 && num!=4)
		num=1;
	while(y>0){
		if(num==1)
			gl_Point(x+x0,y+y0);
		else if(num==2)
			gl_Point(x0-x,y+y0);
		else if(num==3)
			gl_Point(x0-x,y0-y);
		else
			gl_Point(x+x0,y0-y);
		if(f>0){
			f=f-2*y+1;y--;
		}
		else{
			f=f+2*x+1;x++;
		}
	}
	//if(y==0)gl_Point(x,y);  
	
}
void bresenhamarc(int r,int x0,int y0,int num)
{
	int x,y,d;
	x=0;y=r;d=3-2*r;
	if (num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6 && num!=7 && num!=8)
		num=1;
	while(x<y){
		if (num==2)
			gl_Point(x+x0,y+y0);
		if (num==1)
			gl_Point(y+x0,x+y0);
		if (num==3)
			gl_Point(x0-x,y+y0);
		if (num==4)
			gl_Point(x0-y,y0+x);
		if (num==5)
			gl_Point(x0-y,y0-x);
		if (num==6)
			gl_Point(x0-x,y0-y);
		if (num==7)
			gl_Point(x+x0,y0-y);
		if (num==8)
			gl_Point(x0+y,y0-x);
		if(d<0)d=d+4*x+6;
		else{
			d=d+4*(x-y)+10;
			y--;
		}
		x++;
	}
	//if(x==y)gl_Point();
}
void mydisplay(void)
{
	glClearColor(1.0,1.0,1.0,0);//将清空颜色设置为白色
	glClear(GL_COLOR_BUFFER_BIT);//将窗口背景设置为当前清空颜色
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);//设定窗口左下角和右上角的xy坐标
	glViewport(0,0,600,600);
	//dda(200,600,100,200);
	//midpointline(100,300,550,100);
	//bresenhamline(500,100,100,200);
	//pnarc1(150,300,300,3);
	//bresenhamarc(150,300,300,1);
	//画圆
	pnarc1(15,300,300,1);
	pnarc1(15,300,300,2);
	pnarc1(15,300,300,3);
	pnarc1(15,300,300,4);
	//画三角形
	bresenhamline(266,280,334,280);
	bresenhamline(266,280,300,340);
	bresenhamline(334,280,300,340);
	//画中心 圆角矩阵
	dda(400,360,400,240);
	dda(200,360,200,240);
	dda(220,380,380,380);
	dda(220,220,380,220);
	pnarc1(20,380,360,1);
	pnarc1(20,380,240,4);
	pnarc1(20,220,240,3);
	pnarc1(20,220,360,2);
	//画脖子
	dda(325,380,325,400);
	dda(275,380,275,400);
	//画头 圆角矩阵
	midpointline(240,400,360,400);
	dda(380,420,380,480);
	dda(220,420,220,480);
	midpointline(240,500,360,500);
	pnarc1(20,360,480,1);
	pnarc1(20,360,420,4);
	pnarc1(20,240,420,3);
	pnarc1(20,240,480,2);
	//画眼睛
	pnarc1(15,330,450,1);
	pnarc1(15,330,450,2);
	pnarc1(15,330,450,3);
	pnarc1(15,330,450,4);

	pnarc1(15,270,450,1);
	pnarc1(15,270,450,2);
	pnarc1(15,270,450,3);
	pnarc1(15,270,450,4);
	//画嘴巴
	bresenhamarc(20,300,435,6);
	bresenhamarc(20,300,435,7);
	//画天线
	dda(340,500,340,530);
	dda(260,500,260,530);
	//画右耳
	pnarc1(5,385,470,2);
	bresenhamline(385,475,395,475);
	pnarc1(5,395,470,1);
	bresenhamline(400,470,400,430);
	pnarc1(5,395,430,4);
	bresenhamline(385,425,395,425);
	pnarc1(5,385,430,3);
	//画左耳
	pnarc1(5,215,470,1);
	bresenhamline(215,475,205,475);
	pnarc1(5,205,470,2);
	bresenhamline(199,470,199,430);//算法精度问题  x坐标为200时 左耳有点怪异
	pnarc1(5,205,430,3);
	bresenhamline(205,425,215,425);
	pnarc1(5,215,430,4);
	//画右手
	bresenhamline(400,350,410,350);
	bresenhamline(400,330,410,330);
	bresenhamline(410,360,450,360);
	bresenhamline(410,290,450,290);
	bresenhamline(410,290,410,360);
	bresenhamline(450,290,450,360);

	bresenhamline(420,290,420,280);
	bresenhamline(440,290,440,280);

	bresenhamline(410,280,450,280);
	bresenhamline(410,280,410,230);
	bresenhamline(450,280,450,230);
	bresenhamline(410,230,450,230);
	pnarc1(10,430,220,1);
	pnarc1(10,430,220,2);
	pnarc1(10,430,220,3);
	pnarc1(10,430,220,4);
	//画左手
	bresenhamline(200,350,190,350);
	bresenhamline(200,330,190,330);
	bresenhamline(190,360,150,360);
	bresenhamline(190,290,150,290);
	bresenhamline(190,360,190,290);
	bresenhamline(150,360,150,290);

	bresenhamline(180,290,180,280);
	bresenhamline(160,290,160,280);

	bresenhamline(190,280,150,280);
	bresenhamline(190,280,190,230);
	bresenhamline(150,280,150,230);
	bresenhamline(190,230,150,230);
	pnarc1(10,170,220,1);
	pnarc1(10,170,220,2);
	pnarc1(10,170,220,3);
	pnarc1(10,170,220,4);
	//画右脚
	bresenhamline(330,220,330,210);
	bresenhamline(350,220,350,210);
	bresenhamline(330,210,350,210);
	pnarc1(10,330,200,2);
	pnarc1(10,350,200,1);
	bresenhamline(319,200,319,150);//从320修正到319
	bresenhamline(360,200,360,150);
	pnarc1(10,330,150,3);
	pnarc1(10,350,150,4);
	bresenhamline(330,140,350,140);
	bresenhamline(330,140,330,130);
	bresenhamline(350,140,350,130);
	bresenhamline(315,130,365,130);
	bresenhamline(315,130,315,110);
	bresenhamline(365,130,365,110);
	bresenhamline(315,110,365,110);
	//画左脚
	bresenhamline(270,220,270,210);
	bresenhamline(250,220,250,210);
	bresenhamline(270,210,250,210);
	pnarc1(10,270,200,1);
	pnarc1(10,250,200,2);
	bresenhamline(239,200,239,150);//从240修正到239
	bresenhamline(280,200,280,150);
	pnarc1(10,250,150,3);
	pnarc1(10,270,150,4);
	bresenhamline(250,140,270,140);
	bresenhamline(250,140,250,130);
	bresenhamline(270,140,270,130);
	bresenhamline(235,130,285,130);
	bresenhamline(235,130,235,110);
	bresenhamline(285,130,285,110);
	bresenhamline(235,110,285,110);

	glFlush();
}
int main(int argc,char *argv[])
{                                            
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("机器人");
	glutDisplayFunc(&mydisplay);
	glutMainLoop();
	return 0;
}
