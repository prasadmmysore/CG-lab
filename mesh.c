#include<stdlib.h>

#include<GL/glut.h>
#define dx 10
#define dy 10
GLfloat r=0.0,g=0.0,b=0.0;
GLfloat a=0.0,p=0.0,c=0.0;
void display()
{
GLint i,j;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(r,g,b);
for(i=10;i<300;i+=dx)
for(j=10;j<300;j+=dy)
{
glBegin(GL_LINE_LOOP);
glVertex2i(i,j);
glVertex2i(i+dx,j);
glVertex2i(i+dx,j+dy);
glVertex2i(i,j+dy);
glEnd();
}
glFlush();
}
int main(int argc,char **argv)
{
printf("enter r,g,b values for lines\n");
scanf("%f %f %f",&r,&g,&b);
printf("enter r,g,b values for background\n");
scanf("%f %f %f",&a,&b,&c);
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowPosition(500,40);
 glutInitWindowSize(600,500);
 glutCreateWindow("rectangular mesh");
 glClearColor(a,b,c,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(.0,500,.0,500);
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}
