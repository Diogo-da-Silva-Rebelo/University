#include<stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;
int r = 50, ri = 35, rc = 15;
int rand_seed = 10;
float px,pz;
int tick = 0;
int startX, startY, tracking = 0;
int alpha = 0;
unsigned int t, tw, th;
unsigned char *imageData;


// random number between limits min & max
float randomNumber(float Min, float Max){
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

void spherical2Cartesian() {
	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

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

int insideRadius(int rad, float x, float z){
    return (sqrt(pow(x,2) + pow(z,2)) > rad) ? 1:0;
}

void updateCoordinate(float x, float z) {
    // Enquanto estivermos dentro do circulo:
    do {
        px = randomNumber(-95,95);
        pz = randomNumber(-95,95);
    } while (!insideRadius(r,px,pz));
}

void drawtree(){
    GLfloat BROWN[] = {randomNumber(0.5, 0.65), randomNumber(0.5, 0.65), 0};
    GLfloat GREENTONES[] = {0, randomNumber(0.4, 0.8), 0};

    // body
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,BROWN);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(randomNumber(0.8, 1.2), randomNumber(8, 12), 15, 8);
    glRotatef(90, 1, 0, 0);

    // leafs
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,GREENTONES);
    // height - height/4
    glTranslatef(0, randomNumber(8, 12) - (randomNumber(8, 12) / 4), 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef((GLfloat) tick,0,0,1);
    glutSolidCone(randomNumber(0.8, 7), randomNumber(8, 12), 15, 8);
}

void drawOutterPots(){
    GLfloat RED[] = {1, 0, 0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,RED);
    //glColor3ub(255,0,0);
    for (int i=0; i<16; i++) {
        glPushMatrix(); //save previous state
        glRotated(22.5*i-tick,0,1,0);
        glTranslated(ri,1,0);
        glutSolidTeapot(3);
        glPopMatrix(); //restore unrotated coordinate system
    }
}

void drawInnerPots() {
    GLfloat BLUE[] = {0, 0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,BLUE);
    //glColor3ub(128,0,128);
    for (int i=0; i<8; i++) {
        glPushMatrix(); //save previous state
        glRotated(45*i+tick,0,1,0);
        glTranslated(rc,1,0);
        glutSolidTeapot(3);
        glPopMatrix(); //restore unrotated coordinate system
    }
}

void drawTorus() {
    GLfloat MAGENTA[] = {1, 0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,MAGENTA);
    glPushMatrix();
    glRotatef((GLfloat) tick*6,1,0,0);
    glutSolidTorus(1,3,10,10);
    glPopMatrix();
}

void drawPlane() {
    GLfloat EARTHTONE[] = {0.7, 0.3, 0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,EARTHTONE);
    glBegin(GL_TRIANGLES);
    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);

    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);
    glVertex3f(100.0f, 0, 100.0f);
    glEnd();
}

void drawTrees() {
    srand(rand_seed);
    for (int i = 0 ; i < 300 ; i++) {
        // position variables
        updateCoordinate(px,pz);
        glPushMatrix();
        glTranslatef(px, 0, pz);
        drawtree();
        glPopMatrix();
    }
}


// decided to draw all here and not each form in one function, but second option is more organized.
void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

    //draw plane
    drawPlane();

    // draw outter pots
    drawOutterPots();

    // draw inner pots
    drawInnerPots();

    // draw torus
    drawTorus();

    // random trees position drawing
    drawTrees();

    // increment angle for rotation of pots
    tick++;
    if (tick >= 360) tick = 0;
    glutPostRedisplay();

    //drawTerrain();

    glFlush();
	glutSwapBuffers();
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN)  {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}


void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {


        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * sin(betaAux * 3.14 / 180.0);
}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 3.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 3.0f;
    break;

	}
	spherical2Cartesian();
	glutPostRedisplay();
}

void drawTerrain() {

    // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
}

void init() {

    float buffer_grid[8][8];

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            buffer_grid[i][j] = 0.0f;
        }
    };


// 	Load the height map "terreno.jpg"
    ilGenImages(1,&t);
    ilBindImage(t);

// terreno.jpg is the image containing our height map
    ilLoadImage((ILstring)"Aula6_Terreno/terreno.jpg");

// convert the image to single channel per pixel
// with values ranging between 0 and 255
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
// important: check tw and th values
// both should be equal to 256
// if not there was an error loading the image
// most likely the image could not be found
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);

// imageData is a LINEAR array with the pixel values
    imageData = ilGetData();

// 	Build the vertex arrays

// 	OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// Callback registration for keyboard processing
	glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);
    ilInit();
    init();

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);                  // turn LIGHT0 on
    //glEnable(GL_CULL_FACE);

    spherical2Cartesian();
	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}