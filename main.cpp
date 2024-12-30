#include <cstdlib>
#include <cmath>
#include <iostream>
#include <glew.h>
#include <freeglut.h>
#include "glm/glm.hpp"
#include <ctime>
#include <vector>
#include<string>
#include <fstream>
#include "getBMP.h"

// Globals.
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_10; // Font selection.
static int width, height; // Size of the OpenGL window.
static float angle = 0.0; // Angle of the car.
static float xVal = 0, zVal = 0.0; // Co-ordinates of the car.
static int frameCount = 0; // Number of frames

// Texture
static unsigned int texture[7]; // Array of texture indices.
static float d = 0.0; // Distance parameter in gluLookAt().
static int filter = 0; // Filter id.

// Globals: Light Properties
static float sunset_d = 1.0; // Diffuse and specular sunset light intensity.
static float sunset_m = 0.2; // Global ambient sunset light intensity.
static int localViewer = 1; // Local viewpoint?
static float p = 1.0; // Positional light?

int areWin = 0;
int collisionOccurred = 0;
int mainMenu, subMenu;
bool menuVisible = false;
std::string path1="road2.bmp";
std::string path2="lty.bmp";
void loadTextures();


void menuFunction(int value)
{   std::cout<<value;
    switch (value)

    {
        case 1:
//            loadTextures(path1,path2);
            path1="road2.bmp";
            path2="lty.bmp";

            break;
        case 2:
//            loadTextures(path3,path4);
            path1="road.bmp";
            path2="sky2.bmp";
            break;
        default:
            break;
    }

    loadTextures();
    glutPostRedisplay();



}
void createMenu()
{
    subMenu = glutCreateMenu(menuFunction);
    glutAddMenuEntry("Option 1", 1);
    glutAddMenuEntry("Option 2", 2);


    mainMenu = glutCreateMenu(menuFunction);
    glutAddSubMenu("Choose the texture", subMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glutPostRedisplay();  // Request a redraw to display the menu

    }
}
// Create the menu
struct Box {
    int x;
    int z;
};

std::vector<Box> generatedBoxes;
std::vector<glm::vec3> boxesVector;
static int numberOfBoxes = 15;
static int min_x = -20;
static int max_x = 20;
static int min_z = -130;
static int max_z = -20;
static int boxSize = 6;



void loadTextures()
{
    // Local storage for bmp image data.
    imageFile *image[7];

    // Load the images.
    image[0] = getBMP(path1);
    image[1] = getBMP(path2);


    // Bind grass image to texture[0] with specified mag and min filters.
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Bind grass image to texture[1] with specified mag and min filters.
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind grass image to texture[2] with specified mag and min filters.
    // Use mipmapping.
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind grass image to texture[3] with specified mag and min filters.
    // Use mipmapping.
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind grass image to texture[4] with specified mag and min filters.
    // Use mipmapping.
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind grass image to texture[5] with specified mag and min filters.
    // Use mipmapping.
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind sky image to texture[6]
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->width, image[1]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void writeBitmapString(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}
void writeData(void)
{
    switch (filter)
    {
        case 0:
            glRasterPos3f(-4.9, 4.8, -5.1); writeBitmapString((void*)font, (char*)"");
            glRasterPos3f(-4.9, 4.5, -5.1); writeBitmapString((void*)font, (char*)"");
            break;
        case 1:
            glRasterPos3f(-4.9, 4.8, -5.1); writeBitmapString((void*)font, (char*)"Grass mag filter: GL_LINEAR");
            glRasterPos3f(-4.9, 4.5, -5.1); writeBitmapString((void*)font, (char*)"Grass min filter: GL_LINEAR");
            break;
        case 2:
            glRasterPos3f(-4.9, 4.8, -5.1); writeBitmapString((void*)font, (char*)"Grass mag filter: GL_LINEAR");
            glRasterPos3f(-4.9, 4.5, -5.1); writeBitmapString((void*)font, (char*)"Grass min filter: GL_NEAREST_MIPMAP_NEAREST");
            break;
        case 3:
            glRasterPos3f(-4.9, 4.8, -5.1); writeBitmapString((void*)font, (char*)"Grass mag filter: GL_LINEAR");
            glRasterPos3f(-4.9, 4.5, -5.1); writeBitmapString((void*)font, (char*)"Grass min filter: GL_LINEAR_MIPMAP_NEAREST");
            break;
        case 4:
            glRasterPos3f(-4.9, 4.8, -5.1); writeBitmapString((void*)font, (char*)"Grass mag filter: GL_LINEAR");
            glRasterPos3f(-4.9, 4.5, -5.1); writeBitmapString((void*)font, (char*)"Grass min filter: GL_NEAREST_MIPMAP_LINEAR");
            break;
        case 5:
            glRasterPos3f(-4.9, 4.8, -5.1); writeBitmapString((void*)font, (char*)"Grass mag filter: GL_LINEAR");
            glRasterPos3f(-4.9, 4.5, -5.1); writeBitmapString((void*)font, (char*)"Grass min filter: GL_LINEAR_MIPMAP_LINEAR");
            break;
        default:
            break;
    }
}


///////////////////////////////////////////Create the car//////////////////////////////////////////////////////////////
GLuint carDisplayList;
void drawBody() {
    glLineWidth(3.0);
        // Body
        glPushMatrix();

        // Set material properties for the car body
        GLfloat matAmbient[] = {20, 0.1, 0.0, 1.0f};
        GLfloat matDiffuse[] = {0.5, 0.5, 0.5, 1.0f};
        GLfloat matSpecular[] = {1.0f, 0.0f, 0.0f, 1.0f};
        GLfloat matShininess = 50.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
        glEnable(GL_FRONT);
        glColor3f(1.0, 0.0, 0.0); // Red color for the car body
        glScalef(3.0, 1, 5.0);
        glutSolidCube(1.0);
        glPopMatrix();

        // Wireframe body
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0); // Black color for wireframe
        glScalef(3.0, 1.0, 5.0);
        glutWireCube(1.0);
        glPopMatrix();

}
void drawRoof() {

    glLineWidth(3.0);
    glPushMatrix();
    glTranslatef(0, 1, 0.0);
    glColor3f(1.0, 0, 0.0); // Green color for the roof
    glScalef(1.5, 1, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();
    // Roof
    glPushMatrix();
    glTranslatef(0, 1, 0.0);
    glColor3f(0.0, 0.0, 0.0); // Green color for the roof
    glScalef(1.5, 1, 2.5);
    glutWireCube(1.0);
    glPopMatrix();
}
void drawWheels() {
    // Wheels
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(j * 0.6, -0.7, i * 1.0);
            glColor3f(0.0, 0.0, 0.0); // Gray color for wheels
            glutSolidTorus(0.3, 0.5, 20, 20);
            glPopMatrix();
        }
    }
}
void drawFrontCube() {
    glLineWidth(3.0);

    glPushMatrix();
    glTranslatef(18.0, 1.0, 2.5); // Translate to the front of the car
    glColor3f(0.0, 0.0, 0.0); // Blue color for the front cube
    glutSolidCube(2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18.0, 1.0, 2.5); // Translate to the front of the car
    glColor3f(1.0, 0.0, 0.0); // Blue color for the front cube
    glutWireCube(2.5);
    glPopMatrix();



}
void createCarDisplayList() {
    carDisplayList = glGenLists(1);
    glNewList(carDisplayList, GL_COMPILE);

    drawBody();
    drawRoof();
//    drawWindows();
    drawWheels();
    if  (menuVisible){
        createMenu();

    }

//    drawFrontCube();

    glEndList();
}
void drawCar() {
    glCallList(carDisplayList);
}


void frameCounter(int value)
{
    std::cout<<value<<std::endl;
    if(value>3){
        xVal = 0.0;
        zVal = 0.0;
        angle = 0.0;
        collisionOccurred = 0;
        areWin = 0;
        frameCount = 0;
        glutPostRedisplay();
    }
    if(frameCount > 0 && frameCount<=4)
        glutTimerFunc(1000,frameCounter,frameCount++);

}

// Initialization routine.
void setup(void)
{
    createCarDisplayList();

// Define the spotlight properties
    GLfloat lightPos1[] = { 2.0f, 1.0f, 2.5f, 1.0f };
    GLfloat lightDir1[] = { 0.0f, 0.1, -1.0f };
    GLfloat lightCutoff1 = 35.0f;
    GLfloat lightAmbient1[] = { 10.0, 10.0, 10.0, 1.0f };
    GLfloat lightDiffuse1[] = { 1.0f, 1.0, 1.0, 1.0f };
    GLfloat lightSpecular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GLfloat lightAttenuation1[] = { 1.0f, 0.0f, 0.02f }; // Linear attenuation

    GLfloat lightPos2[] = { -2.0f, 1.0f, 2.5f, 1.0f };
    GLfloat lightDir2[] = { 0.0f, 0.1, -1.0f };
    GLfloat lightCutoff2 = 35.0f; // Cone angle
    GLfloat lightAmbient2[] = { 10.0, 10.0, 10.0, 1.0f };

   GLfloat lightDiffuse2[] = { 1.0f, 1.0, 1.0, 1.0f  };
    GLfloat lightSpecular2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightAttenuation2[] = { 1.0f, 0.0f, 0.02f }; // Linear attenuation

// Enable lighting
    glEnable(GL_LIGHTING);

// Enable the first spotlight (right headlight)
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lightCutoff1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
    glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, lightAttenuation1);

// Enable the second spotlight (left headlight)
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDir2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lightCutoff2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular2);
    glLightfv(GL_LIGHT2, GL_LINEAR_ATTENUATION, lightAttenuation2);

    GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);


    // Define the spotlight properties (existing code) ...

    // Set up directional light to represent the sun.
    GLfloat sunLightDirection[] = {1.0f, 1, -1.0f, 0.0f};
    // Direction from the light to the scene (infinite light from the sun)
    //GLfloat sunLightColor[] = {251.0 / 255, 144.0 / 255, 98.0 / 255, 1.0};       // Sunset-like color
    GLfloat sunLightColor[] = {1, 1, 0.8, 1.0};       // Sunset-like color
//    GLfloat sunLightColor[] = {251.0 / 255, 144.0 / 255, 98.0 / 255, 1.0};       // Sunset-like color
    glLightfv(GL_LIGHT0, GL_POSITION, sunLightDirection);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunLightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunLightColor);
    glEnable(GL_LIGHT0);

// Enable the spotlights
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    // Adjust ambient, diffuse, and specular components for a warm sunset lighting
    glEnable(GL_DEPTH_TEST);
    // glClearColor(0, 0.0, 0.0, 1.0);
    // Create texture ids.
    glGenTextures(8, texture);

    // Load external textures.
    loadTextures();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);


}
// Function to check collision with a box
bool checkCollisionWithBox(const glm::vec3& boxCenter)
{
    float distance = glm::length(glm::vec3(xVal, 0, zVal) - boxCenter);
    return (distance <= 6); // Adjust the threshold as needed
}

void detectCollision()
{


    glm::vec3 targetBox(0,0,min_z-50);
    for(int i=0 ; i<15 ; i++){
        if(checkCollisionWithBox(boxesVector[i]))
        {
            // Set collision state
            collisionOccurred++;
            break;
        }
    }
    if(collisionOccurred == 1){
        frameCount++;
        glutTimerFunc(0,frameCounter,0);
    }

    if(checkCollisionWithBox(targetBox)){
        areWin++;
    }
    if(areWin == 1){
        frameCount++;
        glutTimerFunc(0,frameCounter,0);
    }


}

// Drawing routine.
void drawScene(void)
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer); // Enable local viewpoint

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    // Draw car.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Display the menu when menuVisible is true
    if (menuVisible)
    {
        glutSetMenu(mainMenu);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        menuVisible = false;  // Reset the flag after displaying the menu
    }

    if(collisionOccurred) {
        glPushMatrix();
        glDisable(GL_LIGHTING); // Disable lighting.
        glRasterPos3f( xVal-10 , 25, zVal - 10);
        glColor3f(0, 1, 1);
        writeBitmapString((void *) GLUT_BITMAP_8_BY_13, (char *) "You Collided !");
        glEnable(GL_LIGHTING); // Re-enable lighting.
        glPopMatrix();
    }

    if(areWin) {
        glPushMatrix();
        glDisable(GL_LIGHTING); // Disable lighting.
        glRasterPos3f(xVal-10 , 25, zVal - 10);
        glColor3f(0, 1, 0);
        writeBitmapString((void *) GLUT_BITMAP_8_BY_13, (char *) "You Win !");
        glEnable(GL_LIGHTING); // Re-enable lighting.
        glPopMatrix();
    }

    if(xVal >= max_x ){
        xVal = max_x;
    }
    if(xVal <= min_x ){
        xVal = min_x;
    }

    gluLookAt(xVal,
              10,
              zVal,

              xVal - 11 * sin((M_PI / 180.0) * angle),
              0.0,
              zVal - 11 * cos((M_PI / 180.0) * angle),

              0.0,
              1.0,
              0.0);

    for(int i = 0; i < 15; i++)
    {
        glPushMatrix();
        glTranslatef(generatedBoxes[i].x, 3, generatedBoxes[i].z);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidCube(6);
        glColor3f(0.0, 0.0, 0.0);
        glutWireCube(6);

        // Set material properties for the boxes
        GLfloat boxMatAmbient[] = {1.0, 0.0, 0.0, 1.0f};
        GLfloat boxMatDiffuse[] = {1, 0.0, 0.0, 1.0f};
        GLfloat boxMatSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat boxMatShininess = 50.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, boxMatAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, boxMatDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, boxMatSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, boxMatShininess);
        glPopMatrix();
    }


    // the target box
    glPushMatrix();
    glTranslatef(0,3,min_z-50);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidCube(6);
    glColor3f(1.0, 0.0, 0.0);
    glutWireCube(6);


    // Set material properties for the target box
    GLfloat boxMatAmbient[] = {0.0, 0.0, 0.0, 1.0f};
    GLfloat boxMatDiffuse[] = {1, 1.0, 0.0, 1.0f};
    GLfloat boxMatSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat boxMatShininess = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, boxMatAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, boxMatDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, boxMatSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, boxMatShininess);
    glPopMatrix();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(xVal, 0.0, zVal);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glCallList(carDisplayList);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Draw the rest of the scene.
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();


    gluLookAt(xVal,
              10,
              zVal+ d,

              xVal - 11 * sin((M_PI / 180.0) * angle),
              0.0,
              zVal - 11 * cos((M_PI / 180.0) * angle)+ d,

              0.0,
              1.0,
              0.0);
    // Draw the grass texture.

    glBindTexture(GL_TEXTURE_2D, texture[filter]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-300.0, 0.0, 200.0);
    glTexCoord2f(8.0, 0.0); glVertex3f(300.0, 0.0, 200.0);
    glTexCoord2f(8.0, 8.0); glVertex3f(300.0, 0.0, -200.0);
    glTexCoord2f(0.0, 8.0); glVertex3f(-300.0, 0.0, -200.0);
    glEnd();

    // Draw the sky texture.
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-300.0, 0.0, -200.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(300.0, 0.0, -200.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(300.0, 120.0, -200.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-300.0, 120.0, -200.0);
    glEnd();

    // Write data.
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
//    writeData();

    glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
    glMatrixMode(GL_MODELVIEW);

    // Pass the size of the OpenGL window.
    width = w;
    height = h;
}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'm':
            std::cout<<"sfa";
            menuVisible = true;

            glutPostRedisplay();  // Request a redraw to display the menu
            break;
        default:
            break;

    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    float tempxVal = xVal, tempzVal = zVal, tempAngle = angle;

    // Compute next position.
    if (key == GLUT_KEY_LEFT) {tempAngle = angle + 5.0;
    }
    if (key == GLUT_KEY_RIGHT) tempAngle = angle - 5.0;
    if (key == GLUT_KEY_UP)
    {
        tempxVal = xVal - sin(angle * M_PI / 180.0);
        tempzVal = zVal - cos(angle * M_PI / 180.0);
//        d -= 0.5;
    }
    if (key == GLUT_KEY_DOWN)
    {
        tempxVal = xVal + sin(angle * M_PI / 180.0);
        tempzVal = zVal + cos(angle * M_PI / 180.0);
//        d += 0.05;
    }

    // Angle correction.
    if (tempAngle > 360.0) tempAngle -= 360.0;
    if (tempAngle < 0.0) tempAngle += 360.0;

    // Move car to next position only if there will not be collision with an asteroid.


    if (!collisionOccurred && !areWin)
    {
        xVal = tempxVal;
        zVal = tempzVal;
        angle = tempAngle;
    }

    detectCollision();




    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press the left/right arrow keys to turn the car." << std::endl
              << "Press the up/down arrow keys to move the car." << std::endl;
}

bool checkCollision(const std::vector<Box>& boxes, int newX, int newZ, int boxSize) {
    for (const Box& box : boxes) {
        if (newX < box.x + boxSize + 8 && newX + boxSize +8 > box.x  &&
            newZ < box.z + boxSize +8 && newZ + boxSize + 8 > box.z ) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}

// Main routine.
int main(int argc, char **argv)
{

    srand(static_cast<unsigned>(time(0)));


    while (numberOfBoxes--) {
        int x = min_x + rand() % (max_x - min_x + 1);
        int z = min_z + rand() % (max_z - min_z + 1);

        // Check for collision
        while (checkCollision(generatedBoxes, x, z, boxSize)) {
            x = min_x + rand() % (max_x - min_x + 1);
            z = min_z + rand() % (max_z - min_z + 1);
        }

        // Store the position of the generated box
        generatedBoxes.push_back({x, z});
        boxesVector.push_back(glm::vec3(x, 0, z));


        std::cout << "Box at (" << x << ", " << z << ")" << std::endl;
    }




    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(750, 650);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Car Game");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();
    createMenu();  // Call the function to create the menu

    std::cout<<path1<< std:: endl;
    std::cout<<path2<< std::endl;
    loadTextures();

    glutMouseFunc(mouseClick);  // Register the mouse click function
    glutMainLoop();

}

