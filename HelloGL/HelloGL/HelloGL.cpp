#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	camera = new Camera();

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	rotation = 0.0f;
	rotation2 = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::KeyBoard);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, 800, 800);

	// Set the correct perspective.
	gluPerspective(45, 1, 0, 1000);

	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene
	DrawPolygon(); //calls function of drawing shape
	glFlush(); //flushes the scene drawn to the graphics card
	
}




void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
	rotation += 0.5f;
	rotation2 += 1.0f;

	if (rotation2 > 360.0)
	{
		rotation2 = 0.0f;
	}

	if (rotation > 360.0)
	{
		rotation = 0.0f;
	}
}


void HelloGL::DrawPolygon()
{

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	


	glBegin(GL_POLYGON); //starts to draw a polygon
	{


		glColor3f(0.0f, 1.0f, 0.0f);//Green
		glVertex2f(-0.75, 0.5); //define the first point of the polygon,top left
		glColor3f(0.1f, 0.1f, 0.0f);//Bronze
		glVertex2f(0.75, 0.5); //next point, top right
		glColor3f(0.1f, 0.0f, 0.0f);//Brown
		glVertex2f(0.75, -0.5); //bottom right
		glColor3f(0.0f, 0.1f, 0.0f);//Forest Green
		glVertex2f(-0.75, -0.5); //last point of the polygon, bottom left
		glEnd(); // defines the end of the draw

	}


	glPopMatrix();

	glFlush();//flushes the scene drawn to the graphics card


	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rotation2, 1.0f, 0.0f, -1.0f);
	

	glBegin(GL_POLYGON); //starts to draw a polygon
	{


		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
		glVertex2f(-0.13f, -0.2f);//bottom left
		glVertex2f(0.13f, -0.2f);//bottom right
		glVertex2f(0.2f, 0.0f);//right
		glVertex2f(0.13f, 0.2f);//top right
		glVertex2f(-0.13f, 0.2f);//top left
		glVertex2f(-0.2f, 0.0f);//left

		glEnd(); // defines the end of the draw


	}
	glPopMatrix();

	glFlush();//flushes the scene drawn to the graphics card

	glutSwapBuffers();
}

HelloGL::~HelloGL(void)
{
	delete camera;
}


void HelloGL::KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'd')
		camera->up.x += 2.0f;

	if (key == 'a')
		camera->up.x -= 2.0f;

	if (key == 's')
		camera->eye.z += 0.5f;

	if (key == 'w')
		camera->eye.z -= 0.5f;
}