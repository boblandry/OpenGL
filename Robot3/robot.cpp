#include <gl\glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define PI 3.1415926
/* ÿ��ͼ�����Ķ����� */
#define MAX_VERTEX 10
/* ����ͼ�����ĸ��� */
#define MAX_PLOY 10
/* ���ڳ����һ�� */
int halfWidth, halfHeight;
/* ���ƶ���ε���ʼ��־��0�ǿ�ʼ���ƣ�1�ǽ������ƣ���ʼΪ-1 */
int	drawStatus	= -1;
int	moveNum		= -1;
/* ���������x,y*/
int clickX, clickY;
/* ����νṹ�� */
struct polygon {
	/* �������� */
	int	x[MAX_VERTEX];
	int	y[MAX_VERTEX];
	/* ����ڼ������� */
	int	verNum;
	GLubyte color[3];
};
/* ������ɫ */
GLubyte border[3] = { 0, 0, 0 };
GLubyte grey[3] = { 195, 195, 195 };
GLubyte yellow[3] = { 255, 243, 0 };
GLubyte red[3] = { 237, 28, 36 };
GLubyte darkGrey[3] = { 126, 126, 126 };
GLubyte white[3] = { 255, 255, 255 };
GLubyte startBtn[3] = { 10, 10, 10 };
GLubyte endBtn[3] = { 20, 20, 20 };
GLubyte delBtn[3] = { 30, 30, 30 };
GLubyte moveBtn[3] = { 40, 40, 40 };
GLubyte storeBtn[3] = {50, 50, 50};
GLubyte loadBtn[3] = {55, 55, 55};
/* ��ǰ��ɫ */
GLubyte nowColor[3] = { 0, 0, 0 };
/* ������������� */
polygon polygons[MAX_PLOY];
/* ��¼���˼�������� */
int con = 0;

int min(int a,int b){
	if(a<b)
		return a;
	else
		return b;
}

int max(int a,int b){
	if(a>b)
		return a;
	else
		return b;
}
/* �������е�ͼ�� */
void savePolygons()
{
	FILE *fp;
	int i;
	if ((fp = fopen("shapes.txt", "w")) == NULL)
	{
		printf("���ܴ��ļ�!");
		return;
	}
	/* ����һ�����ٸ�ͼ�� */
	fprintf(fp, "%d", con);
	fprintf(fp, "\n");
	for (i = 0; i < con; i++){
		/* ������ɫֵ */
		fprintf(fp, "%d %d %d ", polygons[i].color[0], polygons[i].color[1], polygons[i].color[2]);
		/* ���涥������ */
		fprintf(fp, "%d ", polygons[i].verNum);
		/* ���涥������ */
		for (int j = 0; j < polygons[i].verNum; j++)
			fprintf(fp, "%d ", polygons[i].x[j]);
		for (int m = 0; m < polygons[i].verNum; m++)
			fprintf(fp, "%d ", polygons[i].y[m]);
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("����ɹ���\n");
}

/* ��ȡ�浵 */
void readPolygons()
{
	FILE *fp;
	int i;
	if ((fp = fopen("shapes.txt", "r")) == NULL)
	{
		printf("���ܴ��ļ�!");
		return;
	}
	fscanf(fp, "%d", &con);
	printf("count%d",con);
	fscanf(fp, "\n");
	for (i = 0; i < con; i++){
		/* ��ȡ��ɫֵ */
		fscanf(fp, "%d %d %d ", &polygons[i].color[0], &polygons[i].color[1], &polygons[i].color[2]);
		/* ��ȡ�������� */
		fscanf(fp, "%d ", &polygons[i].verNum);
		/* ��ȡ�������� */
		for (int j = 0; j < polygons[i].verNum; j++)
			fscanf(fp, "%d ", &polygons[i].x[j]);
		for (int k = 0; k < polygons[i].verNum; k++)
			fscanf(fp, "%d ", &polygons[i].y[k]);
		fscanf(fp, "\n");
	}
	fclose(fp);
	printf("��ȡ�ɹ���\n");

}

/* ���ƶ���� */
void glPolygons()
{
	if ( con >= 0 )
	{
		for ( int i = 0; i <= con; i++ )
		{
			/* ȡ���������� */
			polygon poly = polygons[i];
			/* ������� */
			glBegin( GL_LINE_LOOP );
			int num = poly.verNum;
			printf( "num:%d\n", num );
			for ( int j = 0; j < num; j++ )
			{
				glColor3ub( poly.color[0], poly.color[1], poly.color[2] );
				glVertex2d( poly.x[j] - halfWidth, halfHeight - poly.y[j] );
				printf( "polyx:%d,polyy:%d", poly.x[j], poly.y[j] );
			}
			/* �������� */
			glEnd();
			/* ˢ�� */
			glFlush();
		}
	}
}


/* ��������Բ�� */
void glColorCircle( int x, int y, int R, GLubyte color[3] )
{
	/* ��ʼ�������� */
	glBegin( GL_POLYGON );
	/* ������ɫ */
	glColor3ub( color[0], color[1], color[2] );
	/* ÿ�λ����ӵĻ��� */
	double delta_angle = PI / 180;
	/* ��Բ�� */
	for ( double i = 0; i <= 2 * PI; i += delta_angle )
	{
		/* ���Զ�λ�����Ǻ���ֵ */
		double	vx	= x + R * cos( i );
		double	vy	= y + R*sin( i );
		glVertex2d( vx, vy );
	}
	/* �����滭 */
	glEnd();
	glFlush();
}


/* �����Σ�����������½�XY��������Ͻ�XY���� */
void glRect( int leftX, int leftY, int rightX, int rightY )
{
	/* ��������� */
	glBegin( GL_LINE_LOOP );
	/* ���½� */
	glVertex2d( leftX, leftY );
	/* ���½� */
	glVertex2d( rightX, leftY );
	/* ���Ͻ� */
	glVertex2d( rightX, rightY );
	/* ���Ͻ� */
	glVertex2d( leftX, rightY );
	/* �������� */
	glEnd();
}


/* ��Բ�Ǿ��Σ�������ο�ߣ��ǰ뾶���������ĵ����� */
void glRoundRec( int centerX, int centerY, int width, int height, float cirR )
{
	/* ����֮PI��һ�����޵ĽǶ� */
	float PI_HALF = PI / 2;
	/* ���̶ֳ�,ֵԽ�󻭵�Խ��ϸ */
	float divide = 20.0;
	/* Բ�Ǿ��ε����� */
	float tx, ty;
	/* ��������� */
	glBegin( GL_LINE_LOOP );
	/* �ĸ����޲�ͬ�Ĳ����� */
	int	opX[4]	= { 1, -1, -1, 1 };
	int	opY[4]	= { 1, 1, -1, -1 };
	/* �����������ӵ�һ���޵��������� */
	float x = 0;
	/* x����ʱ�ӵ�ֵ */
	float part = 1 / divide;
	/* �����ھ��ο��һ�����ֵ */
	int	w	= width / 2 - cirR;
	int	h	= height / 2 - cirR;
	/* ѭ������ */
	for ( x = 0; x < 4; x += part )
	{
		/* ������� */
		float rad = PI_HALF * x;
		/* ��������ֵ */
		tx	= cirR * cos( rad ) + opX[(int) x] * w + centerX;
		ty	= cirR * sin( rad ) + opY[(int) x] * h + centerY;
		/*�������껭�� */
		glVertex2f( tx, ty );
	}
	/* �������� */
	glEnd();
}


/* �����ߣ����ƫ����XY����ʼ�Ļ��ȣ������Ļ��ȣ��뾶 */
void glArc( double x, double y, double start_angle, double end_angle, double radius )
{
	/* ��ʼ�������� */
	glBegin( GL_LINE_STRIP );
	/* ÿ�λ����ӵĻ��� */
	double delta_angle = PI / 180;
	/* ��Բ�� */
	for ( double i = start_angle; i <= end_angle; i += delta_angle )
	{
		/* ���Զ�λ�����Ǻ���ֵ */
		double	vx	= x + radius * cos( i );
		double	vy	= y + radius*sin( i );
		glVertex2d( vx, vy );
	}
	/* �����滭 */
	glEnd();
}


/* ��Բ */
void glCircle( double x, double y, double radius )
{
	/* ��ȫԲ */
	glArc( x, y, 0, 2 * PI, radius );
}


/* �������Σ���������������� */
void glTri( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	/* ������� */
	glBegin( GL_LINE_LOOP );
	/* һ�� */
	glVertex2d( x1, y1 );
	/* ���� */
	glVertex2d( x2, y2 );
	/*���� */
	glVertex2d( x3, y3 );
	/* �������� */
	glEnd();
}


/* ���ߣ������������� */
void glLine( int x1, int y1, int x2, int y2 )
{
	/* ������� */
	glBegin( GL_LINE_STRIP );
	/* һ�� */
	glVertex2d( x1, y1 );
	/* ���� */
	glVertex2d( x2, y2 );
	/* �������� */
	glEnd();
}


/* ����������ͼ */
void display( void )
{
	/* GL_COLOR_BUFFER_BIT��ʾ�����ɫ */
	glClear( GL_COLOR_BUFFER_BIT );
	/* ���û�����ɫ */
	glColor3f( 0.5, 0.5, 0.5 );
	/* �����С */
	glPointSize( 2 );
	/* ��Բ�Ǿ��Σ������ */
	glRoundRec( 0, 0, 146, 120, 15 );
	/* ��Բ���м�СȦ */
	glCircle( 0, 0, 10 );
	/* �����Σ����� */
	glRect( -25, 60, 25, 76 );
	/* ��Բ�Ǿ��Σ����� */
	glRoundRec( 0, 113, 128, 74, 10 );
	/* �����۾� */
	glCircle( -30, 111, 10 );
	glCircle( 30, 111, 10 );
	/* �������� */
	glLine( -35, 150, -35, 173 );
	glLine( 35, 150, 35, 173 );
	/* Բ�Ǿ��Σ��������� */
	glRoundRec( 81, 115, 20, 34, 5 );
	glRoundRec( -81, 115, 20, 34, 5 );
	/* Բ�������� */
	glArc( 0, 133, 11 * PI / 8, 13 * PI / 8, 45 );
	/* �����ǣ������������ */
	glTri( -30, -15, 30, -15, 0, 28 );
	/* �����Σ��첲���Ӵ� */
	glRect( -81, 43, -73, 25 );
	glRect( 81, 43, 73, 25 );
	/* �����Σ��ϱ� */
	glRect( -108, 45, -81, 0 );
	glRect( 108, 45, 81, 0 );
	/* �����Σ��б� */
	glRect( -101, 0, -88, -4 );
	glRect( 101, 0, 88, -4 );
	/* �����Σ��±� */
	glRect( -108, -4, -81, -37 );
	glRect( 108, -4, 81, -37 );
	/* ��Բ�Σ����� */
	glCircle( -95, -47, 10 );
	glCircle( 95, -47, 10 );

	/* ����ȡɫ�� */
	glColorCircle( -280, 280, 10, red );
	glColorCircle( -250, 280, 10, yellow );
	glColorCircle( -220, 280, 10, grey );
	glColorCircle( -180, 280, 10, nowColor );
	glColorCircle( 250, 280, 10, startBtn );
	glColorCircle( 280, 280, 10, endBtn );
	glColorCircle( 220, 280, 10, delBtn );
	glColorCircle( 190, 280, 10, moveBtn );
	glColorCircle( 160, 280, 10, storeBtn );
	glColorCircle( 130, 280, 10, loadBtn );

	/* ��֤ǰ���OpenGL��������ִ�У��������������ڻ������еȴ� */
	/* ���ƶ���� */
	glPolygons();
	glFlush();
}


/* ���ڴ�С�仯ʱ���õĺ��� */
void ChangeSize( GLsizei w, GLsizei h )
{
	/* ����߶�Ϊ0 */
	if ( h == 0 )
	{
		h = 1;
	}
	/* �����ӿڴ�С�����һ�� */
	glViewport( 0, 0, w, h );
	int half = 300;
	/* �����ߵ�һ�� */
	halfHeight	= 300;
	halfWidth	= 300;
	/* ��������ϵͳ��ʹͶӰ�任��λ */
	glMatrixMode( GL_PROJECTION );
	/* ����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ���� */
	glLoadIdentity();
	/* �������������� */
	if ( w < h )
	{
		/* ����߶ȴ��ڿ�ȣ��򽫸߶��ӽ�����ͼ����ʾ���� */
		glOrtho( -half, half, -half * h / w, half * h / w, -half, half );
	} else {
		/* �����ȴ��ڸ߶ȣ��򽫿���ӽ�����ͼ����ʾ���� */
		glOrtho( -half * w / h, half * w / h, -half, half, -half, half );
	}
}


/* �ж�������ɫ�Ƿ���� */
bool sameColor( GLubyte color1[3], GLubyte color2[3] )
{
	if ( color1[0] - color2[0] < 5 && color1[1] - color2[1] < 5 && color1[2] - color2[1] < 5 )
	{
		return(true);
	} else {
		return(false);
	}
}


/* ���� */
void glPoints( int x, int y )
{
	glBegin( GL_POINTS );
	/* ��ֱ������Ϊ��ɫ */
	glColor3ub( 0, 0, 0 );
	glVertex2d( x - halfWidth, halfHeight - y );
	glEnd();
	glFlush();
}


/* �ж�һ�����Ƿ��ڶ�����ڲ� */
bool pointInPoly( polygon poly, int x, int y )
{
	int nCross = 0;
	for ( int i = 0; i < poly.verNum; i++ )
	{
		int	p1x	= poly.x[i];
		int	p1y	= poly.y[i];
		int	p2x	= poly.x[(i + 1) % poly.verNum];
		int	p2y	= poly.y[(i + 1) % poly.verNum];
		/* ƽ�л����ӳ����ϣ����� */
		if ( p1y == p2y || y < min( p1y, p2y ) || y > max( p1y, p2y ) )
		{
			continue;
		}
		/* ���㽻������� */
		double m = (double) (y - p1y) * (double) (p2x - p1x) / (double) (p2y - p1y) + p1x;
		if ( m > x )
			nCross++;
	}
	return(nCross % 2 == 1);
}


/* �ƶ������ */
void movePoly( int x, int y )
{
	/* ȡ��Ҫ�ƶ���ͼ�� */
	int verNum = polygons[moveNum].verNum;
	printf( "verNum%d,x%d,y%d,clickX%d,clickY%d\n", verNum, x, y, clickX, clickY );
	for ( int i = 0; i < verNum; i++ )
	{
		polygons[moveNum].x[i]	+= (x - clickX);
		polygons[moveNum].y[i]	+= (y - clickY);
		printf( "polyx%d\n", polygons[moveNum].x[i] );
	}
	/* �ƶ����֮�����¼�¼��ǰ�ĵ� */
	clickX	= x;
	clickY	= y;
	/* ���»��� */
	glutPostRedisplay();
}


/* ɾ������� */
void removePoly( int index )
{
	if ( index > con )
	{
		printf( "Out Of Index\n" );
	}
	for ( int i = index; i < con; i++ )
	{
		polygons[i] = polygons[i + 1];
	}
	con--;
}


/* ɾ������� */
void deletePoly( int x, int y )
{
	int delenum = -1;
	for ( int i = 0; i < con; i++ )
	{
		if ( pointInPoly( polygons[i], x, y ) )
		{
			delenum = i;
		}
	}
	if ( delenum != -1 )
	{
		removePoly( delenum );
	}
	/* ���»��� */
	glutPostRedisplay();
}


/* ������¼� */
void mouseClick( int btn, int state, int x, int y )
{
	/* ��ֵȫ�ֱ��� */
	clickX	= x;
	clickY	= y;
	/* ѡ��ķֽ緶Χ */
	int	optionHeight	= 40;
	int	optionWidth	= 250;
	if ( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		/* �������ɫѡ��е�� */
		if ( y < optionHeight && x < optionWidth )
		{
			glReadPixels( x, 2 * halfHeight - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &nowColor );
			/* ���û�ͼ��ɫ����ʾ��ǰȡɫ����ɫ */
			glColorCircle( -180, 280, 10, nowColor );
			/* �����������Ҳ�ѡ�ť */
		}else if ( y < optionHeight && x > optionWidth )
		{
			/* ȡ��ǰ�ĵ� */
			GLubyte color[3];
			glReadPixels( x, 2 * halfHeight - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color );
			/* �������˿�ʼ���Ƶİ�ť */
			if ( sameColor( color, startBtn ) )
			{
				drawStatus = 0;
				/* ��ʼ��һ��ͼ�Σ������������ */
				polygons[con].verNum = 0;
				/* �������˽������Ƶİ�ť */
			} else if ( sameColor( color, endBtn ) )
			{
				glutPostRedisplay();
				/* ����ͼ�θ�����һ */
				con++;
			} else if ( sameColor( color, delBtn ) )
			{
				/* ɾ��ʱ����drawStatusΪ2 */
				drawStatus = 2;
			} else if ( sameColor( color, moveBtn ) )
			{
				/* �ƶ�ʱ����drawStatusΪ3 */
				drawStatus = 3;
			} else if ( sameColor( color, storeBtn ) )
			{
				/* ����ʱ����drawStatusΪ4 */
				drawStatus = 4;
				glutPostRedisplay();
				savePolygons();
			} else if ( sameColor( color, loadBtn ) )
			{
				/* ����ʱ����drawStatusΪ5 */
				drawStatus = 5;
				readPolygons();
				glutPostRedisplay();
			}

			/* �����������·��Ļ�ͼҳ�� */
		}else{
			/* �����ǰ������ȡ��״̬ */
			if ( drawStatus == 0 )
			{
				/* ����ÿ���㣬Ȼ���ͼ�ζ��������һ */
				polygons[con].x[polygons[con].verNum]	= x;
				polygons[con].y[polygons[con].verNum]	= y;
				/* ���� */
				glPoints( x, y );
				/* ���õ�ǰ��ɫRGB�����ȡɫ�б䶯��������ȡɫΪ׼ */
				polygons[con].color[0]	= nowColor[0];
				polygons[con].color[1]	= nowColor[1];
				polygons[con].color[2]	= nowColor[2];
				polygons[con].verNum++;
			}else if ( drawStatus == 2 )
			{
				/* ɾ��ͼ�� */
				deletePoly( x, y );
			} else if ( drawStatus == 3 )
			{
				moveNum = -1;
				for ( int i = 0; i < con; i++ )
				{
					if ( pointInPoly( polygons[i], x, y ) )
					{
						moveNum = i;
					}
				}
			}
		}
	}
}


/* ����ƶ��¼� */
void mouseMove( int x, int y )
{
	if ( drawStatus == 3 && moveNum != -1 )
	{
		printf( "move x:%d,y:%dmoveNum:%d\n", x, y, moveNum );
		movePoly( x, y );
	}
}


/*������� */
int main( int argc, char *argv[] )
{
	/* ��GLUT���г�ʼ�������������е������в��� */
	glutInit( &argc, argv );
	/* ָ��RGB��ɫģʽ�͵����崰�� */
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
	/* ���崰�ڵ�λ�� */
	glutInitWindowPosition( 100, 100 );
	/* ���崰�ڵĴ�С */
	glutInitWindowSize( 600, 600 );
	/* �������ڣ�ͬʱΪ֮���� */
	glutCreateWindow( "OpenGL" );
	/* ���ô��������ɫΪ��ɫ */
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	/* ����Ϊһ����������ͼʱ��������ͻᱻ���� */
	glutDisplayFunc( &display );
	/* ����Ϊһ�������������ڴ�С�ı�ʱ�ᱻ���� */
	glutReshapeFunc( ChangeSize );
	/*������¼�������������ɿ�ʱ���� */
	glutMouseFunc( mouseClick );
	/*����ƶ��¼�����갴�²��ƶ�ʱ���� */
	glutMotionFunc( mouseMove );
	/* �ú�����GLUT��ܿ�ʼ���У��������õĻص�������ʼ������ֱ���û���ֹ����Ϊֹ */
	glutMainLoop();
	/*���򷵻� */
	return(0);
}