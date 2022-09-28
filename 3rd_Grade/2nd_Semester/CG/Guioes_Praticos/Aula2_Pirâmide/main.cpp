#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int mode = GL_FILL, face = GL_FRONT_AND_BACK;

float x = 0, y = 0,
      angle = 0,
      unit = 0.5f,
      rx = 0, ry = 0, rz = 0,
      sx = 1, sy = 1, sz = 1,
      red = 0.0f, green = 0.0f, blue = 0.0f;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene() {
    int a, b;

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(red,green,blue,1.0f);

    // drawing mode
    glPolygonMode(face, mode);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

// put the geometric transformations here
    glTranslatef(x, 0.0, y);
    glRotatef(angle, rx, ry, rz);   //X
    glRotatef(angle, rx, ry, rz);   //Y
    glRotatef(angle, rx, ry, rz);   //Z
    glScalef(sx,sy,sz);

//Axis
        glBegin(GL_LINES);
        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);
        // Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
        // Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
        glEnd();

//Pyramid
        // FACE DA FRENTE
        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(1.0f, 0.0f, 1.0f); //A
        glVertex3f(0.0f, 2.0f, 0.0f); //B
        glVertex3f(-1.0f, 0.0f, 1.0f); //C
        glEnd();

        // FACE TRASEIRA
        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(1.0f, 0.0f, -1.0f); //D
        glVertex3f(-1.0f, 0.0f, -1.0f); //E
        glVertex3f(0.0f, 2.0f, 0.0f); //B
        glEnd();


        // FACE DIREITA
        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(1.0f, 0.0f, -1.0f); //D
        glVertex3f(0.0f, 2.0f, 0.0f); //B
        glVertex3f(1.0f, 0.0f, 1.0f); //A
        glEnd();

        // FACE ESQUERDA
        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(-1.0f, 0.0f, -1.0f); //E
        glVertex3f(-1.0f, 0.0f, 1.0f); //C
        glVertex3f(0.0f, 2.0f, 0.0f); //B
        glEnd();

        // BASE TRIÂNGULO FRENTE
        glBegin(GL_TRIANGLES);
        glColor3f(2.0, 5.0, 1.0);
        glVertex3f(-1.0f, 0.0f, -1.0f); //E
        glVertex3f(1.0f, 0.0f, 1.0f); //A
        glVertex3f(-1.0f, 0.0f, 1.0f); //C
        glEnd();

        // BASE TRIÂNGULO TRÁS
        glBegin(GL_TRIANGLES);
        glColor3f(2.0, 5.0, 1.0);
        glVertex3f(-1.0f, 0.0f, -1.0f); //E
        glVertex3f(1.0f, 0.0f, -1.0f); //D
        glVertex3f(1.0f, 0.0f, 1.0f); //A
        glEnd();

        glFlush();

        // End of frame
        glutSwapBuffers();
    }

    // write function to process keyboard events
    void move(int key, int a, int b) {
        switch (key) {
            case GLUT_KEY_UP:
                x += unit;
                break;
            case GLUT_KEY_DOWN:
                x -= unit;
                break;
            case GLUT_KEY_LEFT:
                y -= unit;
                break;
            case GLUT_KEY_RIGHT:
                y += unit;
                break;
        }
        glutPostRedisplay();
    }

    void roda(unsigned char key, int a, int b) {
        switch (key) {
            case 'a':
                rx = 1.0f;
                ry = 0.0f;
                rz = 0.0f;
                angle -= 90;
                break;
            case 'd':
                rx = 1.0f;
                ry = 0.0f;
                rz = 0.0f;
                angle += 90;
                break;
            case 'w':
                rx = 0.0f;
                ry = 1.0f;
                rz = 0.0f;
                angle -= 90;
                break;
            case 's':
                rx = 0.0f;
                ry = 1.0f;
                rz = 0.0f;
                angle += 90;
                break;
            case 'z':
                rx = 0.0f;
                ry = 0.0f;
                rz = 1.0f;
                angle -= 90;
                break;
            case 'x':
                rx = 0.0f;
                ry = 0.0f;
                rz = 1.0f;
                angle += 90;
                break;

            case '+':
                sx += 0.1;
                sy += 0.1;
                sz += 0.1;
                break;
            case '-':
                sx -= 0.1;
                sy -= 0.1;
                sz -= 0.1;
                break;
            case 'f':
                mode = GL_FILL;
                break;
            case 'l':
                mode = GL_LINE;
                break;
            case 'p':
                mode = GL_POINT;
                break;
        }
        glutPostRedisplay();
    }



    int random(int min, int max) {
        return rand() % (max - min + 1) + min;
    }


    void mouse(int a, int b) {
        red = (float) random(0,255)/255;
        green = (float) random(0,255)/255;
        blue = (float) random(0,255)/255;
        glutPostRedisplay();
    }


int main(int argc, char **argv) {
// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
    glutSpecialFunc(move);
    glutKeyboardFunc(roda);
   glutPassiveMotionFunc(mouse);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}