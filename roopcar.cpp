// cp.cpp : Defines the entry point for the console application.
//

#include "stdarg.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>

using namespace std;

// Dimensions, etc.
const GLfloat INNER_RADIUS = 180.0;
int drive_direction_flag=1;


// Colours
GLfloat grass[] = { 0.0, 0.8f, 0.2f };
GLfloat car_body[] = { 0.2f, 0.0, 0.9f };
GLfloat moun_tain[] = { 0.5f, 0.3f, 0.0f };
GLfloat car_rope[] = { 0.0, 0.0, 0.0 };
GLfloat house_wall[] = { 0.7f, 0.4f, 0.2f };
GLfloat house_roof[] = { 0.8f, 0.0, 0.2f };
GLfloat car[] = { 0.1f, 0.8f, 0.9f };
GLfloat fog[4] = { 0.7f, 0.7f, 0.7f, 1.0 };
GLfloat temple[] = { 0.8f,0.6f,0.5f} ;
GLfloat window[] = { 0.0f, 0.4f,0.9};
GLfloat treee[] = { 0.3f, 0.3f, 0.0f };
GLfloat tree_leaves[] = {0.0, 0.5f, 0.2f };
enum {	// Constants for different views
	DISTANT,CENTRE, OUTSIDE, UP, DOWN,
	HOUSE, HOUSE_M, BALLOON, HELICOPTER, AUTO
} view = DISTANT;

GLUquadricObj *p;				// Pointer for quadric objects.

// Global variables.
GLfloat car_y_direction = 0.0;	// Variables for moving car.
GLfloat car_z_direction = 0.0;
GLfloat car_x_pos = 49.5;
GLfloat car_y_pos = -130.0;
GLfloat car_z_pos = 0.0;
GLfloat height = 10.0;			// Viewer's height
GLfloat zoom = 50.0;			// Camera zoom setting
GLfloat mouse_x = 0.0;			// Mouse coordinates
GLfloat mouse_y = 0.0;
GLint win_width = 400;			// Window dimensions
GLint win_height = 300;
bool movie_mode = false;		// Change viewpoint periodically.
long pclock = 0;
long next_switch_time = 0;



  void draw_car()
  {
	// Draw the car: body first.  The car is facing +X,
	// and up is +Z.  Save current transformation.
	glPushMatrix();
		//glTranslatef(0.0, 0.0, 3.0);
		//glRotatef(95.0, 0.0, 1.0, 0.0);
		glBegin(GL_QUADS);
		   glColor3fv(car);
		glVertex3f(5.0, -5.0, 0.0);		// Wall 1
		glVertex3f(5.0, -5.0, 7.0);
		glVertex3f(-5.0, -5.0, 7.0);
		glVertex3f(-5.0, -5.0, 0.0);
		glColor3fv(window);
		glVertex3f(5.0, -5.0, 0.0);		// Wall 2
		glVertex3f(5.0, 5.0, 0.0);
		glVertex3f(5.0, 5.0, 3.0);
		glVertex3f(5.0, -5.0, 3.0);
		glColor3fv(car);
		glVertex3f(-5.0, 5.0, 0.0);		// Wall 3
		glVertex3f(-5.0, 5.0, 7.0);
		glVertex3f(5.0, 5.0, 7.0);
		glVertex3f(5.0, 5.0, 0.0);
		glColor3fv(window);
		glVertex3f(-5.0, -5.0, 3.0);	// Wall 4
		glVertex3f(-5.0, 5.0, 3.0);
		glVertex3f(-5.0, 5.0, 0.0);
		glVertex3f(-5.0, -5.0, 0.0);

		glColor3fv(car_body);
		glVertex3f(5.0, -5.0, 7.0);    //roof
		glVertex3f(-5.0, -5.0, 7.0);
		glVertex3f(-5.0, 5.0, 7.0);
		glVertex3f(5.0, 5.0, 7.0);
		glVertex3f(5.0, -5.0, 0.0);    //base
		glVertex3f(-5.0, -5.0, 0.0);
		glVertex3f(-5.0, 5.0, 0.0);
		glVertex3f(5.0, 5.0, 0.0);

	glEnd();
        glColor3fv(car_rope);
		glTranslatef(0.0, 0.0, 7.0);
		glRotatef(0.0, -1.0, 0.0, 0.0);
		gluCylinder(p, 1.0, 0.5, 7.0, 10, 10);
	glPopMatrix();

}


void draw_house (GLfloat x, GLfloat y, GLfloat size) {
	// Draw a house.  Save current transformation.
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(size, size, size);
	glBegin(GL_QUADS);
		glColor3fv(house_wall);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 1
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 2
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);	// Wall 4
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glColor3fv(house_roof);			// Roof side 1
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(0.0, -1.0, 1.5);
		glVertex3f(0.0, 1.0, 1.5);
		glVertex3f(1.0, 1.0, 1.0);		// Roof side 2
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(0.0, -1.0, 1.5);
		glVertex3f(0.0, 1.0, 1.5);
		glVertex3f(-1.0, 1.0, 1.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, -1.0, 1.0);	// Roof end 1
		glVertex3f(0.0, -1.0, 1.5);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);		// Roof end 2
		glVertex3f(0.0, 1.0, 1.5);
		glVertex3f(1.0, 1.0, 1.0);
	glEnd();
	glPopMatrix();
}
void mountain (GLfloat x, GLfloat y, GLfloat size) {
	// Draw a side mountain.  Save current transformation.
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(size, size, size);
	glBegin(GL_QUADS);
		glColor3fv(moun_tain);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 1
		glVertex3f(0.25, -0.25, 2.0);
		glVertex3f(-0.25, -0.25, 2.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 2
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(0.25, -0.25, 2.0);
		glVertex3f(-1.0, 1.0, 0.0);		// Wall 3
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(-0.25, -0.25, 2.0);	// Wall 4
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(0.25, -0.25, 2.0);   //roof
		glVertex3f(-0.25, -0.25, 2.0);
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(0.25, 0.25, 2.0);
	glEnd();
	glPopMatrix();
}
void mountain_m (GLfloat x, GLfloat y, GLfloat size) {
	// Draw a main mountain with house.  Save current transformation.
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(size, size, size);
	glBegin(GL_QUADS);
		glColor3fv(moun_tain);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 1
		glVertex3f(0.25, -0.25, 2.0);
		glVertex3f(-0.25, -0.25, 2.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 2
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(0.25, -0.25, 2.0);
		glVertex3f(-1.0, 1.0, 0.0);		// Wall 3
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(-0.25, -0.25, 2.0);	// Wall 4
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(0.25, -0.25, 2.0);   // roof
		glVertex3f(-0.25, -0.25, 2.0);
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(0.25, 0.25, 2.0);


        glColor3fv(house_wall);
		glVertex3f(0.25,0.25,2.0);     //hwall2
		glVertex3f(0.25,-0.25,2.0);
		glVertex3f(0.25,-0.25,2.5);
		glVertex3f(0.25,0.25,2.5);
		glVertex3f(-0.25, 0.25, 2.0); //hwall3
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(0.25, 0.25, 2.5);
		glVertex3f(-0.25, 0.25, 2.5);
		glVertex3f(-0.25, -0.25, 2.0);  //hwall4
        glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(-0.25, 0.25, 2.5);
		glVertex3f(-0.25, -0.25, 2.5);


		glColor3fv(house_roof);			// Roof side 1
		glVertex3f(0.25,-0.25,2.5);
		glVertex3f(0.25,0.25,2.5);
		glVertex3f(0.0,0.25,2.75);
		glVertex3f(0.0,-0.25,2.75);
		                         		// Roof side 2
		glVertex3f(-0.25, 0.25, 2.5);
		glVertex3f(-0.25, -0.25, 2.5);
		glVertex3f(0.0, -0.25, 2.75);
		glVertex3f(0.0, 0.25, 2.75);

	glEnd();
	glBegin(GL_TRIANGLES);
	 glVertex3f(0.25, -0.25, 2.5); //roof end 1
	 glVertex3f(0.0, -0.25, 2.75);
	 glVertex3f(-0.25, -0.25, 2.5);
	 glVertex3f(0.25, 0.25, 2.5); //roof end 2
	 glVertex3f(0.0, 0.25, 2.75);
	 glVertex3f(-0.25, 0.25, 2.5);
	glEnd();
	glPopMatrix();
}
void mountain_t (GLfloat x, GLfloat y, GLfloat size) {
	// Draw a main mountain with house.  Save current transformation.
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(size, size, size);
	glBegin(GL_QUADS);
		glColor3fv(moun_tain);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 1
		glVertex3f(0.25, -0.25, 2.0);
		glVertex3f(-0.25, -0.25, 2.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 2
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(0.25, -0.25, 2.0);
		glVertex3f(-1.0, 1.0, 0.0);		// Wall 3
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(-0.25, -0.25, 2.0);	// Wall 4
		glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
        glColor3fv(temple);
		glVertex3f(0.25,0.25,2.0);     //hwall2
		glVertex3f(0.25,-0.25,2.0);
		glVertex3f(0.25,-0.25,2.5);
		glVertex3f(0.25,0.25,2.5);
		glVertex3f(-0.25, 0.25, 2.0); //hwall3
		glVertex3f(0.25, 0.25, 2.0);
		glVertex3f(0.25, 0.25, 2.5);
		glVertex3f(-0.25, 0.25, 2.5);
		glVertex3f(-0.25, -0.25, 2.0);  //hwall4
        glVertex3f(-0.25, 0.25, 2.0);
		glVertex3f(-0.25, 0.25, 2.5);
		glVertex3f(-0.25, -0.25, 2.5);
//rounded mountain
		glColor3fv(moun_tain);
		glTranslatef(0.25, 0.25, 0.25);
		glRotatef(0.0, -1.0, 0.0, 0.0);
		gluCylinder(p, 2.0, 0.1, 2.0, 10, 10);
		glEnd();
	glPopMatrix();
}
void tomb()
{
	glPushMatrix();
	 glColor3fv(house_roof);
     glTranslatef(-100.0,60.0,125.0);
	 glRotatef(0.0,-1.0,0.0,0.0);
     gluCylinder(p,20.0,0.1,10.0,10,10);
	 glColor3fv(temple);
	 glTranslatef(0.0,0.0,10.0);
	 glRotatef(0.0,-1.0,0.0,0.0);
	 gluCylinder(p,1.0,1.0,15.0,10,10);
	 glColor3fv(house_roof);
	 glTranslatef(0.0,-2.5,9.0);
	 glRotatef(-2.0,0.0,0.0,0.0);
	 gluCylinder(p,4.0,0.1,7.0,2,4);

	 glPopMatrix();

}

void rope(){
	// draw a rope in which trolley travels. save a tranformation
	glPushMatrix();
		glTranslatef(50.0, 112.0, 88.0);
		glRotatef(107.0, 1.0, 0.0, 0.0);
		glColor3fv(car_rope);
		gluCylinder(p, 0.4, 0.4, 255.0, 10, 12);
	glPopMatrix();
}
void cylind(){
	// pillar inside house at mountain.
glPushMatrix();
		glColor3fv(car_rope);
		glTranslatef(49.5, 108.0, 82.0);
		glRotatef(0.0, -1.0, 0.0, 0.0);
		gluCylinder(p, 2.0, 0.5, 7.0, 10, 10);
	glPopMatrix();
}
void cyli(){
	//pillar inside house at base.
glPushMatrix();
		glColor3fv(car_rope);
		glTranslatef(49.5, -133.0, 10.0);
		glRotatef(0.0, -1.0, 0.0, 0.0);
		gluCylinder(p, 2.0, 0.5, 8.0, 10, 10);
	glPopMatrix();
}
void tree(GLfloat x,GLfloat y,GLfloat z)
{
	glPushMatrix();
		glColor3fv(treee);
		glTranslatef(x,y, z);
		glRotatef(0.0, -1.0, 0.0, 0.0);
		gluCylinder(p, 2.0, 2.0, 10.0, 10, 10);
		glColor3fv(tree_leaves);
		glTranslatef(0.0,0.0,9.0);
		gluCylinder(p,6.0,0.2,7.0,10,10);
	glPopMatrix();

}
void draw_scenery () {
	// Draw a patch of grass, a circular road, and some houses.
	glColor3fv(grass);
	gluDisk(p, 0.0, INNER_RADIUS, 50, 5);
	rope();
	cylind();
	cyli();
	draw_house(50.0, -140.0, 20.0);
	mountain_m(50.0,110.0,35.0);    //main
	mountain(90.0,110.0,25.0);    //n1
	mountain(80.0,100.0,25.0);    //n2
	mountain(20.0,100.0,20.0);    //f1
	mountain(0.0,95.0,25.0);      //f2
	mountain(10.0,90.0,35.0);
	mountain(-20.0,70.0,40);
	mountain(-20.0,115.0,35.0);
	mountain(110.0,120.0,35.0);
	mountain_t(-100.0,60.0,50.0);
	mountain_m(-125.0,-40.0,25.0);
	mountain_m(165.0,80.0,20.0);
	tomb();
	draw_house(90.0, -148.0, 10.0);
	draw_house(10.0,-130.0,15.0);
	draw_house(-90.0,-100.0,13.0);
	tree(120.0,-130.0,0.0);
	tree(140.0,-105.0,0.0);
    tree(172.0,-55.0,0.0);
	tree(178.0,-10.0,0.0);
	tree(175.0,30.0,0.0);
	tree(-30.0,-165.0,0.0);
	tree(-60.0,-160.0,0.0);
	tree(-90.0,-155.0,0.0);
	tree ( -130.0,-125.0,0.0);
	tree(10.0,10.0,0.0);
	tree(40.0,40.0,0.0);
	tree(70.0,65.0,0.0);
	tree(100.0,75.0,0.0);
    tree(130.0,80.0,0.0);


}


void set_viewpoint () {
	// Use the current viewpoint to display.
	switch (view) {

	case DISTANT:
		// Static viewpoint and stationary camera.
		gluLookAt(
			250.0, 0.0, 10.0 * height,
			0.0, 0.0, 0.0,
			0.0, 0.0, 1.0 );
		draw_scenery();
		// Move to position of car.
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		draw_car();
		break;

	case CENTRE:
		// Static viewpoint at centre; camera follows car.
		gluLookAt(
			45.0, 0.0, height,
			car_x_pos, car_y_pos, car_z_pos,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		draw_car();
		break;

	case OUTSIDE:
		// Static viewpoint from outside ; camera follows car.
		gluLookAt(
			140.0, 0.0, height,
			car_x_pos, car_y_pos, car_z_pos,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		draw_car();
		break;

	case UP:
		// MOVING car point of view.  gluLookAt() is defined in "car space".
		// After drawing the car, view of upper house from moving car.
		gluLookAt(
			car_x_pos, car_y_pos, car_z_pos,
			0.0, 130.0, 70.0,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, -car_y_pos, -car_z_pos);
		draw_car();
		break;

	case DOWN:
		// MOVING car point of view ; view of lower house from moving car.
		gluLookAt(
			car_x_pos, car_y_pos, car_z_pos,
			0.0, -105.0, 0.0,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, - car_y_pos, -car_z_pos);
		draw_car();
		break;

	case HOUSE:
		// View looking moving car from lower house.
		gluLookAt(
			55.0, -150.0, 5.0,
			car_x_pos, car_y_pos, car_z_pos,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos,car_z_pos );
		draw_car();

		break;

	case HOUSE_M:
		// View looking moving car from upper house.
		gluLookAt(
			53.0, 110.0, 82.0,
			car_x_pos, car_y_pos, car_z_pos,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef( car_x_pos, car_y_pos, car_z_pos);
		draw_car();
		break;

	case BALLOON:
		// View from a balloon.
		gluLookAt(
			150.0, 75.0, 250.0,
			200.0 * mouse_x, 200.0 * mouse_y, 0.0,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		draw_car();
		break;

	case HELICOPTER:
		// View from a helicopter.
		gluLookAt(
			200.0 * mouse_x, 200.0 * mouse_y, 200.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		draw_car();
		break;
	}
}

void display (void) {
	// The display callback function.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	set_viewpoint();
	glutSwapBuffers();
}

void set_projection () {
	// Reset the projection when zoom setting or window shape changes.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, GLfloat(win_width) / GLfloat(win_height),
		1.0, 500.0);
}

void reshape (GLint new_width, GLint new_height) {
	// Window reshaping function.
	win_width = new_width;
	win_height = new_height;
	glViewport(0, 0, win_width, win_height);
	set_projection();
}


void drive_up() {
	 // Idle callback function moves the car.  Since this function
	 // posts redisplay whenever there is nothing else to do,
	 // we do not need any other calls to glutPostRedisplay().


	if(car_y_direction<235.0 && drive_direction_flag==1)
	{
    car_y_direction += 0.1;
	car_x_pos = 49.5;
	car_y_pos = -130.0 + car_y_direction ;
	car_z_pos = 0.30435*car_y_direction;
    if(car_y_direction>=235.0)
	{
		drive_direction_flag=0;
		for(int i=0;i<99999;i++)
		{
			for(int i=0;i<19999;i++)
			{
				;
			}
		}
	}
	}
	else if(car_y_direction>0.0 && drive_direction_flag==0)
	{
		car_y_direction -= 0.1;

	car_x_pos = 49.5;
	car_y_pos = -130.0 + car_y_direction ;
	car_z_pos = 0.30435*car_y_direction;
    if(car_y_direction<=0.0)
	{
		drive_direction_flag=1;
		for(int i=0;i<99999;i++)
		{
			for(int i=0;i<9999;i++)
			{
				;
			}
		}
	}
	}


	if (movie_mode) {
		pclock++;
		if (pclock > next_switch_time) {
			next_switch_time += 20 + rand() % 200;
			cout <<
				"Time: " << clock <<
				".  Next change: " << next_switch_time <<
				'.' << endl;
			switch (rand() % 9) {
			case 0:
				view = DISTANT;
				break;
			case 1:
				view = CENTRE;
				break;
			case 2:
				view = OUTSIDE;
				break;
			case 3:
				view = UP;
				break;
			case 4:
				view = DOWN;
				break;
			case 5:
				view = HOUSE;
				break;
			case 6:
				view = HOUSE_M;
				break;
			case 7:
				view = BALLOON;
				break;
			case 8:
				view = HELICOPTER;
				break;

           }
		}
	}
	glutPostRedisplay();
}




void mouse (int x, int y) {
	// Get mouse position and scale values to [-1, 1].
	mouse_x = (2.0 * x) / win_width - 1.0;
	mouse_y = (2.0 * y) / win_height - 1.0;
}



void keys (int key, int x, int y) {
	// Set viewpoint from function keys.
	switch (key) {

	case GLUT_KEY_LEFT:
		zoom *= 1.2f;
		cout << "Zoom angle = " << zoom << endl;
		set_projection();
		break;

	case GLUT_KEY_RIGHT:
		zoom /= 1.2f;
		cout << "Zoom angle = " << zoom << endl;
		set_projection();
		break;

	case GLUT_KEY_UP:
		height += 1.0;
		cout << "Height = " << height << endl;
		break;

	case GLUT_KEY_DOWN:
		height -= 1.0;
		cout << "Height = " << height << endl;
		break;

	case GLUT_KEY_F1:
		movie_mode = false;
		view = DISTANT;
		cout << "Distant, fixed viewpoint." << endl;
		break;

	case GLUT_KEY_F2:
		movie_mode = false;
		cout << "View from a panning camera from centre of the field." << endl;
		view = CENTRE;
		break;

	case GLUT_KEY_F3:
		movie_mode = false;
		cout << "View from a panning camera outside the field." << endl;
		view = OUTSIDE;
		break;

	case GLUT_KEY_F4:
		movie_mode = false;
		view = UP;
		height = 6.0;
		zoom = 75.0;
		set_projection();
		cout << "View from the moving car of upper house" << endl;
		break;

	case GLUT_KEY_F5:
		movie_mode = false;
		view = DOWN;
		cout << "View from the moving car of lower house." << endl;
		break;

	case GLUT_KEY_F6:
		movie_mode = false;
		view = HOUSE;
		cout << "View from the lower house of moving car." << endl;
		break;

	case GLUT_KEY_F7:
		movie_mode = false;
		view = HOUSE_M;
		cout << "View from the upper house of moving car." << endl;
		break;

	case GLUT_KEY_F8:
		movie_mode = false;
		view = BALLOON;
		cout << "View from a balloon: use mouse to change viewing direction." << endl;
		break;

	case GLUT_KEY_F9:
		movie_mode = false;
		view = HELICOPTER;
		cout << "View from a helicopter: move mouse to fly around." << endl;
		break;

	case GLUT_KEY_F10:
		movie_mode = true;
		pclock = 0;
		next_switch_time = 0;
		cout << "Movie mode: views change at random intervals." << endl;
		break;

	case GLUT_KEY_END:
	exit(0);
	}
}


int main (int argc, char *argv[]) {

	// Initialize GLUT.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("An OpenGL Window");

	// Register callbacks.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(drive_up);
	glutPassiveMotionFunc(mouse);
	glutSpecialFunc(keys);

	// Select GL options.
	glEnable(GL_DEPTH_TEST);
	p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_FILL);
	glClearColor(fog[0], fog[1], fog[2], fog[3]);

	// Initialize projection.
	set_projection();

	// Instruct user.
	cout <<
		"Change view point:"									<< endl <<
		"   Press keys F1, F2, ..., F9 to change viewpoint.  Movie mode: F10."<< endl <<
		"ZOOM:"										            << endl <<
		"   Press keys 'LEFT' and 'RIGHT' to zoom out & zoom in respectively. " << endl <<
		"HEIGHT :"                                               <<endl <<
		"    Press keys 'UP' and 'DOWN' to increase & decrease height respectively."<< endl <<
		"Quit:"													<< endl <<
		"   Press ESC to stop program."							<< endl <<
		"Keep window small for fast action!"					<< endl;

	// "Drive!" he said.
	glutMainLoop();
	return 0;
}

