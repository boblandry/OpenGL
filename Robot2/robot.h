#include <gl\glut.h>
#include <math.h>
#include <iostream>
using namespace std;
void drawpoint(int x,int y,int r,int g,int b)
{
	glColor3ub(r,g,b);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex3f(x,y,0);
	glEnd();
	glFlush();
}
void gl_Point(int x,int y)
{
	glPointSize(1);
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
	if(dx==0){
		if(ys>ye){
			int t;
			t=ys;ys=ye;ye=t;
		}
		dy=ye-ys;y=ys;
		for (i=0;i<dy;i++){
			gl_Point(x,y);
			y++;
		}
	}
	else{
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
		if(y==0)gl_Point(x+x0,y+y0);
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
		if(y==0)gl_Point(x+x0,y+y0);
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
		if(y==0)gl_Point(x+x0,y+y0);
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
		if(y==0)gl_Point(x+x0,y+y0);
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
	if(y==0){
		if(num==1)
			gl_Point(x+x0,y+y0);
		else if(num==2)
			gl_Point(x0-x,y+y0);
		else if(num==3)
			gl_Point(x0-x,y0-y);
		else
			gl_Point(x+x0,y0-y);
	}
	
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
