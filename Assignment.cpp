//  ========================================================================
//  Assignment 1 - COSC363-S1 2018 - Andrew French (ID: 11147452) (code: afr66)
//  
//  Filename: Assignment.cpp
//  See "Assignment Report" for details.
//  ========================================================================
 
#include <iostream>
#include <cmath> 
#include <GL/glut.h>
# include "loadBMP.h"
#include <stdio.h>

using namespace std;

GLuint texId[13];   //Texture ids
float angle=0, look_x, look_y = -1, look_z=-1., eye_x, eye_y = -1, eye_z = 150, prev_eye_x = eye_x, prev_eye_z=eye_z;  //Camera parameters
float fpsRotateAngle = 0;

//LIGHT POSITIONS
float topLightPos[] = {0, 40, 0, 1};
float leftLightPos[] = {-12.5,50,0,1};
float rightLightPos[] = {12.5,50,0,1};
float spotdirLeft[] = {-0.12, -1, -0.2};
float spotdirRight[] = {-0.04, -1, 0.3};
float shadowMatrix[16] = { 40,0,0,0, 
    0,0,0,-1, 
    0,0,40,0, 
    0,0,0,40 };


//GIRAFFE MOVEMENT VARIABLES

float giraffeAngle = 20;  //Rotation of the Giraffe angle
float giraffeFrontAngle = -20;
float giraffeBackAngle = 20;
int up_down_flag_giraffe_back = 0; //Flag to move the legs for the Giraffe legs
int up_down_flag_giraffe_front = 1; //Flag to move the legs for the Giraffe legs

//BIRD WING MOVEMENT VARIABLES

float birdLeftAngle = -15;
float birdRightAngle = 15;
int up_down_flag_bird_left = 0; //Flag to move the Bird Wings
int up_down_flag_bird_right = 1; //Flag to move the Bird Wings

//FIRST PERSON VIEW VARIABLES
int camera = 1;
float fpsEye_x = 0, fpsEye_z = 0, fpsLook_x, fpsLook_z;


//--------------------------------------------------------------------------------
void loadTexture()              
{
    glGenTextures(13, texId);     // Create 8 texture ids

    glBindTexture(GL_TEXTURE_2D, texId[0]);  //Use this texture
    //loadBMP("wallTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 

    glBindTexture(GL_TEXTURE_2D, texId[1]);  //Use this texture
    //loadBMP("houseFloorTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[2]);  //Use this texture
    //loadBMP("bambooTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[3]);  //Use this texture
    //loadBMP("welcomeMat.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glBindTexture(GL_TEXTURE_2D, texId[4]);  //Use this texture
    //loadBMP("roofTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glBindTexture(GL_TEXTURE_2D, texId[5]);  //Use this texture
    //loadBMP("greenLandscape.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glBindTexture(GL_TEXTURE_2D, texId[6]);  //Use this texture
    //loadBMP("sandTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glBindTexture(GL_TEXTURE_2D, texId[7]);  //Use this texture
    //loadBMP("topSkybox1.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glBindTexture(GL_TEXTURE_2D, texId[8]);  //Use this texture
    //loadBMP("poleTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[9]);  //Use this texture
    //loadBMP("middleWallTexture.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);  
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
    
    
}
//--------------------------------------------------------------------------------

void frontDoor() {
    ////////////////////// FRONT-TOP WALL ///////////////////////
    
     glBindTexture(GL_TEXTURE_2D, texId[3]);   //replace with a texture

     glBegin(GL_QUADS);

     glTexCoord2f(0.0, 1.0);
     glVertex3f(-1, 1, 5);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(-1, 0.5, 5);
     
     glTexCoord2f(1.0, 0.0);
     glVertex3f(1, 0.5, 5);
     
     glTexCoord2f(1.0, 1.0);
     glVertex3f(1, 1, 5);
     
     glEnd();

}

void houseWalls()
{
    glBindTexture(GL_TEXTURE_2D, texId[0]);   //replace with a texture

    glBegin(GL_QUADS);

    ////////////////////// BACK WALL ///////////////////////

    glTexCoord2f(0.0, 2.0);
    glVertex3f(-5, 1, -5);
    
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-5, -1, -5);
    
    glTexCoord2f(6.0, 0.0);
    glVertex3f(5, -1, -5);
    
    glTexCoord2f(6.0, 2.0);
    glVertex3f(5, 1, -5);

    ////////////////////// FRONT-LEFT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(-5, 1, 5);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(-5, -1, 5);
     
     glTexCoord2f(2.0, 0.0);
     glVertex3f(-1, -1, 5);
     
     glTexCoord2f(2.0, 2.0);
     glVertex3f(-1, 1, 5);
     
     ////////////////////// FRONT-RIGHT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(1, 1, 5);
     
     glTexCoord2f(0.0, 0.0); 
     glVertex3f(1, -1, 5);
     
     glTexCoord2f(2.0, 0.0);
     glVertex3f(5, -1, 5);
     
     glTexCoord2f(2.0, 2.0);
     glVertex3f(5, 1, 5);
    

    ////////////////////// LEFT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(-5, 1, -5);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(-5, -1, -5);
     
     glTexCoord2f(6.0, 0.0);
     glVertex3f(-5, -1, 5);
     
     glTexCoord2f(6.0, 2.0);
     glVertex3f(-5, 1, 5);


    ////////////////////// RIGHT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(5, 1, -5);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(5, -1, -5);
     
     glTexCoord2f(6.0, 0.0);
     glVertex3f(5, -1, 5);
     
     glTexCoord2f(6.0, 2.0);
     glVertex3f(5, 1, 5);

    glEnd();
}
//--------------------------------------------------------------------------------

void houseFloor()
{
    glBindTexture(GL_TEXTURE_2D, texId[1]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 40.0);
         glVertex3f(-5, -0.74, -5);
         
         glTexCoord2f(0.0, 0.0);
         glVertex3f(-5, -0.74, 5);
         
         glTexCoord2f(40.0, 0.0);
         glVertex3f(5, -0.74, 5);
         
         glTexCoord2f(40.0, 40.0);
         glVertex3f(5, -0.74, -5);
    glEnd();
}

void penFloor()
{
    
    float white[4] = {1., 1., 1., 1.};
    float black[4] = {0};
    glColor4f(0.7, 0.7, 0.7, 1.0);  //The floor is gray in colour
    glNormal3f(0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    
    //glBindTexture(GL_TEXTURE_2D, texId[1]);  //replace with a texture
    glBegin(GL_QUADS);
         //glTexCoord2f(0.0, 40.0);
         glVertex3f(-5, -0.73, -5);
         
         //glTexCoord2f(0.0, 0.0);
         glVertex3f(-5, -0.73, 5);
         
         //glTexCoord2f(40.0, 0.0);
         glVertex3f(5, -0.73, 5);
         
         //glTexCoord2f(40.0, 40.0);
         glVertex3f(5, -0.73, -5);
         
    for(int i = -200; i < 200; i++)
    {
        for(int j = -200;  j < 200; j++)
        {
            glVertex3f(i, -0.73, j);
            glVertex3f(i, -0.73, j+1);
            glVertex3f(i+1, -0.73, j+1);
            glVertex3f(i+1, -0.73, j);
        }
    }
    glEnd();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}


void houseMiddleRoof()
{
    glBindTexture(GL_TEXTURE_2D, texId[9]);  //replace with a texture

    glBegin( GL_TRIANGLES ); // Draw a triangle
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-5 , 1, 5 );
    
    glTexCoord2f(3, 0); 
    glVertex3f(0 , 1, 5 ); 
    
    glTexCoord2f(3, 1);
    glVertex3f(0, 1.83, 5);
    
    glEnd(); 
    
    glBindTexture(GL_TEXTURE_2D, texId[9]);  //replace with a texture

    glBegin( GL_TRIANGLES ); // Draw a triangle
    glTexCoord2f(0.0, 0.0);
    glVertex3f(5 , 1, 5 );
    
    glTexCoord2f(3, 0); 
    glVertex3f(0 , 1, 5 ); 
    
    glTexCoord2f(3, 1);
    glVertex3f(0, 1.83, 5);
    
    glEnd(); 
    
    glBindTexture(GL_TEXTURE_2D, texId[9]);  //replace with a texture

    glBegin( GL_TRIANGLES ); // Draw a triangle
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-5 , 1, -5 );
    
    glTexCoord2f(3, 0); 
    glVertex3f(0 , 1, -5 ); 
    
    glTexCoord2f(3, 1);
    glVertex3f(0, 1.83, -5);
    
    glEnd(); 
    
    glBindTexture(GL_TEXTURE_2D, texId[9]);  //replace with a texture

    glBegin( GL_TRIANGLES ); // Draw a triangle
    glTexCoord2f(0.0, 0.0);
    glVertex3f(5 , 1, -5 );
    
    glTexCoord2f(3, 0); 
    glVertex3f(0 , 1, -5 ); 
    
    glTexCoord2f(3, 1);
    glVertex3f(0, 1.83, -5);
    
    glEnd(); 
}

void houseRightRoof()
{
    //RIGHT ROOF
    glBindTexture(GL_TEXTURE_2D, texId[4]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 3.0);
         glVertex3f(-1, 2, -5);
         
         glTexCoord2f(0.0, 0.0);
         glVertex3f(-1, 2, 5);
         
         glTexCoord2f(3.0, 0.0);
         glVertex3f(5, 2, 5);
         
         glTexCoord2f(3.0, 3.0);
         glVertex3f(5, 2, -5);
    glEnd();
    
}
    
void houseLeftRoof() 
{
    
    //~ //LEFT ROOF
    glBindTexture(GL_TEXTURE_2D, texId[4]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 3.0);
         glVertex3f(-5, 2, -5);
         
         glTexCoord2f(0.0, 0.0);
         glVertex3f(-5, 2, 5);
         
         glTexCoord2f(3.0, 0.0);
         glVertex3f(1, 2, 5);
         
         glTexCoord2f(3.0, 3.0);
         glVertex3f(1, 2, -5);
    glEnd();
    
}


void skyboxEnvironment() {
    
    
    //FRONT SKYBOX WALL
    
    glBindTexture(GL_TEXTURE_2D, texId[5]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(-1000, -1, -1000);
         
         glTexCoord2f(0.0, 1);
         glVertex3f(-1000, 1000, -1000);
         
         glTexCoord2f(1, 1);
         glVertex3f(1000, 1000, -1000);
         
         glTexCoord2f(1, 0);
         glVertex3f(1000, -1, -1000);
    glEnd();
    
    //LEFT SKYBOX WALL
    
    glBindTexture(GL_TEXTURE_2D, texId[5]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(-1000, -1, 1000);
         
         glTexCoord2f(0.0, 1);
         glVertex3f(-1000, 1000, 1000);
         
         glTexCoord2f(1, 1);
         glVertex3f(-1000, 1000, -1000);
         
         glTexCoord2f(1, 0);
         glVertex3f(-1000, -1, -1000);
    glEnd();
    
    //RIGHT SKYBOX WALL
    
    glBindTexture(GL_TEXTURE_2D, texId[5]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(1000, -1, -1000);
         
         glTexCoord2f(0, 1);
         glVertex3f(1000, 1000, -1000);
         
         glTexCoord2f(1, 1);
         glVertex3f(1000, 1000, 1000);
         
         glTexCoord2f(1, 0);
         glVertex3f(1000, -1, 1000);
    glEnd();
    
    //BACK SKYBOX WALL
    
    glBindTexture(GL_TEXTURE_2D, texId[5]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(1000, -1, 1000);
         
         glTexCoord2f(0.0, 1);
         glVertex3f(1000, 1000, 1000);
         
         glTexCoord2f(1, 1);
         glVertex3f(-1000, 1000, 1000);
         
         glTexCoord2f(1, 0);
         glVertex3f(-1000, -1, 1000);
    glEnd();
}

void drawSkyBoxRoof()
{
    //TOP SKYBOX WALL
    
    glBindTexture(GL_TEXTURE_2D, texId[7]);  //replace with a texture
    glBegin(GL_QUADS);
         glTexCoord2f(1, 1);
         glVertex3f(1000, 1000, -1000);
         
         glTexCoord2f(0, 1);
         glVertex3f(1000, 1000, 1000);
         
         glTexCoord2f(0, 0);
         glVertex3f(-1000, 1000, 1000);
         
         glTexCoord2f(1, 0);
         glVertex3f(-1000, 1000, -1000);
    glEnd();
}

void drawEnclosureWalls() 
{
    glBindTexture(GL_TEXTURE_2D, texId[2]);   //replace with a texture

    glBegin(GL_QUADS);

    ////////////////////// BACK WALL ///////////////////////

    glTexCoord2f(0.0, 2.0);
    glVertex3f(-20, 1, -20);
    
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-20, -1, -20);
    
    glTexCoord2f(6.0, 0.0);
    glVertex3f(20, -1, -20);
    
    glTexCoord2f(6.0, 2.0);
    glVertex3f(20, 1, -20);

     
     ////////////////////// FRONT-RIGHT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(-20, 1, 20);
     
     glTexCoord2f(0.0, 0.0); 
     glVertex3f(-20, -1, 20);
     
     glTexCoord2f(2.0, 0.0);
     glVertex3f(20, -1, 20);
     
     glTexCoord2f(2.0, 2.0);
     glVertex3f(20, 1, 20);
    

    ////////////////////// LEFT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(-20, 1, -20);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(-20, -1, -20);
     
     glTexCoord2f(6.0, 0.0);
     glVertex3f(-20, -1, 20);
     
     glTexCoord2f(6.0, 2.0);
     glVertex3f(-20, 1, 20);


    ////////////////////// RIGHT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(20, 1, -20);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(20, -1, -20);
     
     glTexCoord2f(6.0, 0.0);
     glVertex3f(20, -1, 20);
     
     glTexCoord2f(6.0, 2.0);
     glVertex3f(20, 1, 20);

    glEnd();
}

void enclosureFloor()
{
    glBindTexture(GL_TEXTURE_2D, texId[6]);  //replace with a texture

    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 5.0);
         glVertex3f(-20, -1, -20);
         
         glTexCoord2f(0.0, 0.0);
         glVertex3f(-20, -1, 20);
         
         glTexCoord2f(5.0, 0.0);
         glVertex3f(20, -1, 20);
         
         glTexCoord2f(5.0, 5.0);
         glVertex3f(20, -1, -20);
    glEnd();
}

void penWalls()
{
    glBindTexture(GL_TEXTURE_2D, texId[0]);   //replace with a texture

    glBegin(GL_QUADS);

    ////////////////////// BACK WALL ///////////////////////

    glTexCoord2f(0.0, 2.0);
    glVertex3f(-5, 1, -5);
    
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-5, -1, -5);
    
    glTexCoord2f(6.0, 0.0);
    glVertex3f(5, -1, -5);
    
    glTexCoord2f(6.0, 2.0);
    glVertex3f(5, 1, -5);

    ////////////////////// FRONT-LEFT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(-5, 1, 5);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(-5, -1, 5);
     
     glTexCoord2f(2.0, 0.0);
     glVertex3f(-1, -1, 5);
     
     glTexCoord2f(2.0, 2.0);
     glVertex3f(-1, 1, 5);
     
     ////////////////////// FRONT-RIGHT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(1, 1, 5);
     
     glTexCoord2f(0.0, 0.0); 
     glVertex3f(1, -1, 5);
     
     glTexCoord2f(2.0, 0.0);
     glVertex3f(5, -1, 5);
     
     glTexCoord2f(2.0, 2.0);
     glVertex3f(5, 1, 5);
     
     //FRONT-MIDDLE WALL
     glTexCoord2f(0.0, 2.0);
     glVertex3f(1, 1, 5);
     
     glTexCoord2f(0.0, 0.0); 
     glVertex3f(1, -1, 5);
     
     glTexCoord2f(2.0, 0.0);
     glVertex3f(-1, -1, 5);
     
     glTexCoord2f(2.0, 2.0);
     glVertex3f(-1, 1, 5);
    

    ////////////////////// LEFT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(-5, 1, -5);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(-5, -1, -5);
     
     glTexCoord2f(6.0, 0.0);
     glVertex3f(-5, -1, 5);
     
     glTexCoord2f(6.0, 2.0);
     glVertex3f(-5, 1, 5);


    ////////////////////// RIGHT WALL ///////////////////////

     glTexCoord2f(0.0, 2.0);
     glVertex3f(5, 1, -5);
     
     glTexCoord2f(0.0, 0.0);
     glVertex3f(5, -1, -5);
     
     glTexCoord2f(6.0, 0.0);
     glVertex3f(5, -1, 5);
     
     glTexCoord2f(6.0, 2.0);
     glVertex3f(5, 1, 5);

    glEnd();
}

void drawGiraffe()
{
    glColor3f(0.6, 0.3, 0.1);
    //NECK
    
    glPushMatrix();
    glTranslatef(0, -0.5, 0.4);
    glRotatef(-60, 1, 0, 0);
    glScalef(1, 1, 2.5);
    GLUquadric *q;
    q = gluNewQuadric();
    gluCylinder(q, 0.5, 0.15, 1, 15,
    10);
    //gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
    
    //BODY
    glPushMatrix();
    glScalef(1, 1, -2);
    glTranslatef(0,-0.5,0);
    glutSolidSphere(0.5, 30, 30);
    glPopMatrix();
    
    //BACK Right LEG
    
    glPushMatrix();
    
    glRotatef(giraffeBackAngle, 1, 0, 0);
    
    glTranslatef(-0.25,-1.5,-0.35);
    glScalef(1, 8, -1.5);
    //glRotatef(-90, 0, 0, 1);
    glutSolidCube(0.20);
    glPopMatrix();
    
    //BACK Left LEG
    
    glPushMatrix();
    
    glRotatef(giraffeBackAngle, 1, 0, 0);
    
    glTranslatef(0.25,-1.5,-0.35);
    glScalef(1, 8, -1.5);
    glutSolidCube(0.20);
    glPopMatrix();
    
    //FRONT LEFT LEG
    
    glPushMatrix();
    
    glRotatef(giraffeFrontAngle, 1, 0, 0);
    
    glTranslatef(-0.25,-1.5,0.35);
    glScalef(1, 8, -1.5);
    glutSolidCube(0.20);
    glPopMatrix();
    
    //FRONT RIGHT LEG
    
    glPushMatrix();
    
    glRotatef(giraffeFrontAngle, 1, 0, 0);
    
    glTranslatef(0.25,-1.5,0.35);
    glScalef(1, 8, -1.5);
    glutSolidCube(0.20);
    glPopMatrix();
    
    //HEAD
    
    glColor3f(0.807, 0.654, 0.435);
    glPushMatrix();
    glTranslatef(0,1.6,1.8);
    glScalef(0.75, 0.75, 2);
    //glRotatef(-15, 0, 0, 1);
    glutSolidCube(0.5);
    glPopMatrix();
    
    //Mouth
    
    glColor3f(0.750, 0.600, 0.400);
    glPushMatrix();
    glTranslatef(0,0.8,-0.4);
    glRotatef(20, 1, 0, 0);
    glTranslatef(0,1.3,1.85);
    glScalef(0.7, 0.10, 2);
    glutSolidCube(0.5);
    glPopMatrix();
    
    //TAIL
    
    glColor3f(0.6, 0.3, 0.1);
    glPushMatrix();
    glTranslatef(0, -0.35, 0.8);
    glRotatef(45, 1, 0, 0);
    glTranslatef(0,-1.5,-1);
    glScalef(0.25, 8, -1);
    
    glutSolidCube(0.20);
    glPopMatrix();
    
    //EYES
    
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(0.15,1.7,1.6);
    glutSolidSphere(0.15, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.15,1.7,1.6);
    glutSolidSphere(0.15, 30, 30);
    glPopMatrix();
    
    //EARS
    
    glPushMatrix();
    glScalef(1, 2, 1);
    glTranslatef(0.1,0.9,1.3);
    glutSolidCube(0.1);
    glPopMatrix();
    
    glPushMatrix();
    glScalef(1, 2, 1);
    glTranslatef(-0.1,0.9,1.3);
    glutSolidCube(0.1);
    glPopMatrix();
    
    glColor3f(1,1,1);
    
    
}

void drawRanchKeeper(int shadow)
{
    if(shadow == 1) {
        glColor4f(0.2, 0.2, 0.2, 1.0); //Head
        glPushMatrix();
          glTranslatef(0, 7.7, 0);
          glutSolidCube(1.4);
        glPopMatrix();

                  //Torso
        glPushMatrix();
          glTranslatef(0, 5, 0);
          glScalef(3, 4, 1.4);
          glutSolidCube(1);
        glPopMatrix();

                 //Right leg
        glPushMatrix();
          glTranslatef(-0.8, 4, 0);
          glRotatef(giraffeBackAngle, 1, 0, 0);
          glTranslatef(0.8, -4, 0);
          glTranslatef(-0.8, 2.2, 0);
          glScalef(1, 4.4, 1);
          glutSolidCube(1);
        glPopMatrix();

                  //Left leg
        glPushMatrix();
         glTranslatef(0.8, 4, 0);
         glRotatef(giraffeFrontAngle, 1, 0, 0);
         glTranslatef(-0.8, -4, 0);
         glTranslatef(0.8, 2.2, 0);
         glScalef(1, 4.4, 1);
         glutSolidCube(1);
        glPopMatrix();

                 //Right arm
        glPushMatrix();
         glTranslatef(-2, 6.5, 0);
         glRotatef(giraffeFrontAngle, 1, 0, 0);
         glRotatef(180, 1, 0, 0);
         glTranslatef(2, -6.5, 0);
         glTranslatef(-2, 5, 0);
         glScalef(1, 4.4, 1);
         glutSolidCube(1);
        glPopMatrix();

                 //Left arm
        glPushMatrix();
          glTranslatef(2, 6.5, 0);
          glRotatef(giraffeBackAngle, 1, 0, 0);
          glRotatef(180, 1, 0, 0);
          glTranslatef(-2, -6.5, 0);
          glTranslatef(2, 5, 0);
          glScalef(1, 4, 1);
          glutSolidCube(1);
        glPopMatrix();
        
                 //Eyes
        glPushMatrix();
          glTranslatef(-0.3, 7.7, 0.9);
          glutSolidSphere(0.25, 30, 30);
        glPopMatrix();
        
                  //Eyes
        glPushMatrix();
          glTranslatef(0.3, 7.7, 0.9);
          glutSolidSphere(0.25, 30, 30);
        glPopMatrix();
        
            
                 //Hat
        glPushMatrix();
          glTranslatef(0, 8.5, 0);
          glScalef(2, 0.25, 2.25);
          glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix(); //Hat
          glTranslatef(0, 8.75, 0);
          glScalef(1.5, 0.5, 2);
          glutSolidCube(1);
        glPopMatrix();
        
    } else {
        glColor3f(0.913, 0.803, 0.647);      //Head
        glPushMatrix();
          glTranslatef(0, 7.7, 0);
          glutSolidCube(1.4);
        glPopMatrix();

        glColor3f(0.715, 0.5, 0.186);          //Torso
        glPushMatrix();
          glTranslatef(0, 5, 0);
          glScalef(3, 4, 1.4);
          glutSolidCube(1);
        glPopMatrix();

        glColor3f(0.341, 0.435, 0.047);          //Right leg
        glPushMatrix();
          glTranslatef(-0.8, 4, 0);
          glRotatef(giraffeBackAngle, 1, 0, 0);
          glTranslatef(0.8, -4, 0);
          glTranslatef(-0.8, 2.2, 0);
          glScalef(1, 4.4, 1);
          glutSolidCube(1);
        glPopMatrix();

        glColor3f(0.341, 0.435, 0.047);          //Left leg
        glPushMatrix();
         glTranslatef(0.8, 4, 0);
         glRotatef(giraffeFrontAngle, 1, 0, 0);
         glTranslatef(-0.8, -4, 0);
         glTranslatef(0.8, 2.2, 0);
         glScalef(1, 4.4, 1);
         glutSolidCube(1);
        glPopMatrix();

        glColor3f(0.715, 0.5, 0.186);          //Right arm
        glPushMatrix();
         glTranslatef(-2, 6.5, 0);
         glRotatef(giraffeFrontAngle, 1, 0, 0);
         glRotatef(180, 1, 0, 0);
         glTranslatef(2, -6.5, 0);
         glTranslatef(-2, 5, 0);
         glScalef(1, 4.4, 1);
         glutSolidCube(1);
        glPopMatrix();

        glColor3f(0.715, 0.5, 0.186);          //Left arm
        glPushMatrix();
          glTranslatef(2, 6.5, 0);
          glRotatef(giraffeBackAngle, 1, 0, 0);
          glRotatef(180, 1, 0, 0);
          glTranslatef(-2, -6.5, 0);
          glTranslatef(2, 5, 0);
          glScalef(1, 4, 1);
          glutSolidCube(1);
        glPopMatrix();
        
        glColor3f(0.039, 0.184, 0.419);          //Eyes
        glPushMatrix();
          glTranslatef(-0.3, 7.7, 0.9);
          glutSolidSphere(0.25, 30, 30);
        glPopMatrix();
        
        glColor3f(0.039, 0.184, 0.419);          //Eyes
        glPushMatrix();
          glTranslatef(0.3, 7.7, 0.9);
          glutSolidSphere(0.25, 30, 30);
        glPopMatrix();
        
            
        glColor3f(0.419, 0.282, 0.039);          //Hat
        glPushMatrix();
          glTranslatef(0, 8.5, 0);
          glScalef(2, 0.25, 2.25);
          glutSolidCube(1);
        glPopMatrix();
        
        glColor3f(0.419, 0.282, 0.039);          //Hat
        glPushMatrix();
          glTranslatef(0, 8.75, 0);
          glScalef(1.5, 0.5, 2);
          glutSolidCube(1);
        glPopMatrix();
    }
    
}

void drawBird(int shadow)
{
    if(shadow == 1) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
            //Body
        glPushMatrix();
          glScalef(2,0.5,0.5);
          glutSolidCube(1);
        glPopMatrix();
        
                 //Left Wing
        glPushMatrix();
        
          glRotatef(birdLeftAngle, 1, 0, 0);
        
          glTranslatef(0, 0.75, -0.5);
          glRotatef(45, 1, 0, 0);
          glScalef(0.5,0.25, 1.5);
          glTranslatef(0,0,1);
          glutSolidCube(1);
        glPopMatrix();
        
                  //Right Wing
        glPushMatrix();
        
          glRotatef(birdRightAngle, 1, 0, 0);
        
          glTranslatef(0, -1.6, -0.75);
          glRotatef(-45, 1, 0, 0);
          glTranslatef(0, 0.75, -0.5);
          glScalef(0.5,0.25, 1.5);
          glTranslatef(0,0,1);
          glutSolidCube(1);
        glPopMatrix();
        
                  //Tail
        glPushMatrix();
          
          glTranslatef(1.25, 0.5, 0);
          glRotatef(45, 0, 0, 1);
          glScalef(1.5, 0.25, 0.4);
          glutSolidCube(1);
        glPopMatrix();
        
                   //Head
        glPushMatrix();
          glTranslatef(-1, 0, 0);
          glutSolidSphere(0.325, 30, 30);
        glPopMatrix();
        
                  //Beak
        glPushMatrix();
        
          glTranslatef(-1.25, -0.2, 2);
          glRotatef(-90, 0, 1, 0);
          glTranslatef(-2, 0, 0);
          glutSolidCone(0.1, 0.5, 30, 30);
        glPopMatrix();
        
                 //Eyes
        glPushMatrix();
          
          glTranslatef(-1.3, 0, -0.1);
          glutSolidSphere(0.1, 30, 30);
          
        glPopMatrix();
        
        glPushMatrix();
          
          glTranslatef(-1.3, 0, 0.1);
          glutSolidSphere(0.1, 30, 30);
          
        glPopMatrix();
    } else {
        glColor3f(1., 1., 1.);          //Body
        glPushMatrix();
          glScalef(2,0.5,0.5);
          glutSolidCube(1);
        glPopMatrix();
        
        glColor3f(0.9, 0.9, 0.9);          //Left Wing
        glPushMatrix();
        
          glRotatef(birdLeftAngle, 1, 0, 0);
        
          glTranslatef(0, 0.75, -0.5);
          glRotatef(45, 1, 0, 0);
          glScalef(0.5,0.25, 1.5);
          glTranslatef(0,0,1);
          glutSolidCube(1);
        glPopMatrix();
        
        glColor3f(0.9, 0.9, 0.9);          //Right Wing
        glPushMatrix();
        
          glRotatef(birdRightAngle, 1, 0, 0);
        
          glTranslatef(0, -1.6, -0.75);
          glRotatef(-45, 1, 0, 0);
          glTranslatef(0, 0.75, -0.5);
          glScalef(0.5,0.25, 1.5);
          glTranslatef(0,0,1);
          glutSolidCube(1);
        glPopMatrix();
        
        glColor3f(0.9, 0.9, 0.9);          //Tail
        glPushMatrix();
          
          glTranslatef(1.25, 0.5, 0);
          glRotatef(45, 0, 0, 1);
          glScalef(1.5, 0.25, 0.4);
          glutSolidCube(1);
        glPopMatrix();
        
        glColor3f(0.9, 0.9, 0.9);           //Head
        glPushMatrix();
          glTranslatef(-1, 0, 0);
          glutSolidSphere(0.325, 30, 30);
        glPopMatrix();
        
        glColor3f(0.980, 0.584, 0);          //Beak
        glPushMatrix();
        
          glTranslatef(-1.25, -0.2, 2);
          glRotatef(-90, 0, 1, 0);
          glTranslatef(-2, 0, 0);
          glutSolidCone(0.1, 0.5, 30, 30);
        glPopMatrix();
        
        glColor3f(0., 0., 0.);          //Eyes
        glPushMatrix();
          
          glTranslatef(-1.3, 0, -0.1);
          glutSolidSphere(0.1, 30, 30);
          
        glPopMatrix();
        
        glPushMatrix();
          
          glTranslatef(-1.3, 0, 0.1);
          glutSolidSphere(0.1, 30, 30);
          
        glPopMatrix();
    }
}

void normal(float x1, float y1, float z1, 
            float x2, float y2, float z2,
              float x3, float y3, float z3 )
{
      float nx, ny, nz;
      nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
      ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
      nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);

      glNormal3f(nx, ny, nz);
}

void drawSweepTexture()
{
    glBindTexture(GL_TEXTURE_2D, texId[8]);
    
    const int N = 50;
    float vx[N] = {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
              5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
              5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    float vy[N] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
                   19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                   39, 40, 41, 42, 43, 43, 42, 41, 40, 39};
    float vz[N] = {0};
    float wx[N], wy[N], wz[N]; 
    float angStep = 10.0*3.1415926/180.0;  //Rotate in 10 deg steps (converted to radians)
    
    
    for(int j = 0; j < 36; j++) //36 slices in 10 deg steps
    {
        for(int i = 0; i < N; i++) {
    
        wx[i] = vx[i]*cos(angStep) + vz[i]*sin(angStep);
        wy[i] = vy[i];
        wz[i] = -1 * vx[i]*sin(angStep) + vz[i]*cos(angStep);
        }
        
        glBegin(GL_TRIANGLE_STRIP);
         for(int i = 0; i < N; i++)
         {
             if(i > 0) normal( wx[i-1], wy[i-1], wz[i-1],
                             vx[i-1], vy[i-1], vz[i-1],
                            vx[i], vy[i], vz[i] );
            
             glTexCoord2f(0.01,0);
             glVertex3f(vx[i], vy[i], vz[i]);
             
             if(i > 0) normal( wx[i-1], wy[i-1], wz[i-1],
                             vx[i], vy[i], vz[i],
                            wx[i], wy[i], wz[i] );
            
             glTexCoord2f(0.01,0.01);
             glVertex3f(wx[i], wy[i], wz[i]);
         }
        glEnd();
        for(int i = 0; i < N; i++) {
            vx[i] = wx[i];
            vy[i] = wy[i];
            vz[i] = wz[i];
        }
    }
}

void drawLights()
{
    glColor3f(0.372, 0.643, 0.784);    
    glPushMatrix();
      glScalef(15,2,2);
      glTranslatef(0.75, 15, 0);
      glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.372, 0.643, 0.784);    
    glPushMatrix();
      glScalef(15,2,2);
      glTranslatef(-0.75, 15, 0);
      glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(1, 1, 1);    
    glPushMatrix();
      glScalef(3,2.5,2);
      glTranslatef(5.5, 11, 0);
      glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(1, 1, 1);    
    glPushMatrix();
      glScalef(3,2.5,2);
      glTranslatef(-5.5, 11, 0);
      glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.905, 0.882, 0.015);    
    glPushMatrix();
      glScalef(1.5,1.5,1.5);
      glTranslatef(-11, 17, 0);
      glutSolidSphere(1, 30, 30);
    glPopMatrix();
    
    glColor3f(0.905, 0.882, 0.015);    
    glPushMatrix();
      glScalef(1.5,1.5,1.5);
      glTranslatef(11, 17, 0);
      glutSolidSphere(1, 30, 30);
    glPopMatrix();
}


//--------------------------------------------------------------------------------

void display() 
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    

    
    glMatrixMode(GL_PROJECTION);                        
    glLoadIdentity();
    gluPerspective(90., 1., 1., 5000.);

    glMatrixMode(GL_MODELVIEW);                             
    glLoadIdentity();
    
    if(camera == 1) {
        gluLookAt(eye_x, eye_y, eye_z,  look_x, look_y, look_z,   0, 1, 0);  
    } 
    else {
        gluLookAt(fpsEye_x, 10, fpsEye_z,  fpsLook_x, 10, fpsLook_z,   0,1, 0);  
       
    }
    
    
    //TOP LIGHT POSITION SET
    glLightfv(GL_LIGHT2, GL_POSITION, leftLightPos);    
    
    glPushMatrix();
    glRotatef(giraffeAngle, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, leftLightPos);    
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotdirLeft); 
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(giraffeAngle, 0, 1, 0);
    glLightfv(GL_LIGHT1, GL_POSITION, rightLightPos);    
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdirRight); 
    glPopMatrix();

    glPushMatrix();
    drawSkyBoxRoof();
    glPopMatrix();
    
    skyboxEnvironment();
    
    glPushMatrix();
    glRotatef(90, 0, 1 ,0);
    glScalef(10, 15, 10);
    enclosureFloor();
    drawEnclosureWalls();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -12, 0);
    glScalef(7, 3, 7);
    penWalls();
    glPopMatrix();
    
    glPushMatrix();
    glScalef(0.025, 1, 0.025);
    glTranslatef(0, -12, 0);
    glScalef(7, 3, 7);
    glDisable(GL_TEXTURE_2D);
    penFloor();
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    
    glPushMatrix();
    glScalef(15, 20, 10);
    houseMiddleRoof();
    frontDoor();
    houseFloor();
    houseWalls();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -4.15, 0);
    glRotatef(-13, 0, 0, 1);
    glScalef(15, 20, 11.5);
    houseRightRoof();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -4.15, 0);
    glRotatef(13, 0, 0, 1);
    glScalef(15, 20, 11.5);
    houseLeftRoof();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(giraffeAngle, 0, 1, 0);
    glTranslatef(10, 0, 0);
    glScalef(6, 6, 6);
    glDisable(GL_TEXTURE_2D);
    drawGiraffe();
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(giraffeAngle, 0, 1, 0);
    glRotatef(180, 0, 1, 0);
    glTranslatef(20, 0, 0);
    glScalef(6, 6, 6);
    glDisable(GL_TEXTURE_2D);
    drawGiraffe();
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    
    glDisable(GL_LIGHTING);
    glPushMatrix(); //Draw Shadow Object
    glTranslatef(0, -14, 0);
    glMultMatrixf(shadowMatrix);
    glRotatef(giraffeAngle, 0, 1, 0);
    glRotatef(180, 0, 1, 0);
    glTranslatef(20, 0, 15);
    glTranslatef(0, -15, 0);
    glScalef(1.5, 1.5, 1.5);
    glDisable(GL_TEXTURE_2D);
    drawRanchKeeper(1);
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    glPushMatrix(); //Draw Actual Object
    glRotatef(giraffeAngle, 0, 1, 0);
    glRotatef(180, 0, 1, 0);
    glTranslatef(20, 0, 15);
    glTranslatef(0, -15, 0);
    glScalef(1.5, 1.5, 1.5);
    glDisable(GL_TEXTURE_2D);
    drawRanchKeeper(0);
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    glPushMatrix(); //Draw Shadow Object
    glTranslatef(0, -14, 0);
    glMultMatrixf(shadowMatrix);
    glRotatef(giraffeAngle, 0, 1, 0);
    glTranslatef(6, 8, 16);
    glRotatef(-45, 0, 1, 0);
    glRotatef(90, 0, 1, 0);
    glDisable(GL_TEXTURE_2D);
    drawBird(1);
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    glPushMatrix(); //Draw Actual Object
    glRotatef(giraffeAngle, 0, 1, 0);
    glTranslatef(6, 8, 16);
    glRotatef(-45, 0, 1, 0);
    glRotatef(90, 0, 1, 0);
    glDisable(GL_TEXTURE_2D);
    drawBird(0);
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(giraffeAngle, 0, 1, 0);
    glScalef(1, 1.25, 1);
    glTranslatef(0, -15, 0);
    drawSweepTexture();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(giraffeAngle, 0, 1, 0);
    glRotatef(-20, 0, 1, 0);
    glDisable(GL_TEXTURE_2D);
    drawLights();
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();


    glutSwapBuffers();      
    
                            
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{   
    if(key == GLUT_KEY_F1) {
        camera = -camera;
    } else {
        if(key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
        else if(key == GLUT_KEY_RIGHT) angle += 0.1;

        else {
            if(key == GLUT_KEY_DOWN)
            {  //Move backward
                eye_x -= 3*sin(angle);
                eye_z += 3*cos(angle);
                
            }
            else if(key == GLUT_KEY_UP)
            { //Move forward
                eye_x += 3*sin(angle);
                eye_z -= 3*cos(angle);
            }
        }

        look_x = eye_x + 100*sin(angle);
        look_z = eye_z - 100*cos(angle);
        
        //Collision Detection for Pen
        if((eye_x < 40) && (eye_x > -40) && (eye_z < 40) && (eye_z > -40)) {
            eye_x = prev_eye_x;
            eye_z = prev_eye_z;
        }
        
        //Collision Detection for Left Wall
        if((eye_x > -76.0) && (eye_x < -73.0) && ((eye_z > -50) && (eye_z < 50))) {
            eye_x = prev_eye_x;
            eye_z = prev_eye_z;
        }
        //Collision Detection for Right Wall
        if((eye_x < 76.0) && (eye_x > 73.0) && ((eye_z > -50) && (eye_z < 50))) {
            eye_x = prev_eye_x;
            eye_z = prev_eye_z;
        }
        //Collision Detection for Front-Left Wall
        if((eye_x > -76) && (eye_x < -15) && ((eye_z < 51) && (eye_z > 49))) {
            eye_x = prev_eye_x;
            eye_z = prev_eye_z;
        }
        //Collision Detection for Front-Right Wall
        if((eye_x > 15) && (eye_x < 76) && ((eye_z < 51) && (eye_z > 49))) {
            eye_x = prev_eye_x;
            eye_z = prev_eye_z;
        }
        //Collision Detection for Back Wall
        if((eye_x > -76.0) && (eye_x < 76.0) && ((eye_z > -51) && (eye_z < -49))) {
            eye_x = prev_eye_x;
            eye_z = prev_eye_z;
        }
        
        prev_eye_x = eye_x;
        prev_eye_z = eye_z;
        
        //Collision detection for yard walls.
        if(eye_x < -198) 
        {
            eye_x = -198;
        } else if(eye_x > 198) {
            eye_x = 198;
        } else if(eye_z > 196) {
            eye_z = 196;
        } else if(eye_z < -196) {
            eye_z = -196;
        }
        glutPostRedisplay();
        //printf("eye_x %f, eye_z %f", eye_x, eye_z); 
    }
}

//--------------------------------------------------------------------------------

void initialise()
{ 
    
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float greyWhite[4] = {0.4, 0.4, 0.4, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0}; 
    
    loadTexture(); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE); 
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 9);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,0.01);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 9);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
    
    glLightfv(GL_LIGHT2, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, greyWhite);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    
    
    glClearColor (1, 1, 1, 1);   
       
}

void myTimer(int value) {
    giraffeAngle -= 1;
    
    
    //GIRAFFE MOVEMENT
    if(up_down_flag_giraffe_back == 0) {
        giraffeBackAngle--;
        if(giraffeBackAngle == -20) {
            up_down_flag_giraffe_back = 1;
        }
    } else {
        giraffeBackAngle++;
        if(giraffeBackAngle == 20) {
            up_down_flag_giraffe_back = 0;
        }
    }
    
    if(up_down_flag_giraffe_front == 0) {
        giraffeFrontAngle--;
        if(giraffeFrontAngle == -20) {
            up_down_flag_giraffe_front = 1;
        }
    } else {
        giraffeFrontAngle++;
        if(giraffeFrontAngle == 20) {
            up_down_flag_giraffe_front = 0;
        }
    }
    
    //BIRD MOVEMENT
    
    if(up_down_flag_bird_left == 0) {
        birdLeftAngle -= 8;
        if(birdLeftAngle == -15) {
            up_down_flag_bird_left = 1;
        }
    } else {
        birdLeftAngle += 8;
        if(birdLeftAngle == 15) {
            up_down_flag_bird_left = 0;
        }
    }
    
    if(up_down_flag_bird_right == 0) {
        birdRightAngle -= 8;
        if(birdRightAngle == -15) {
            up_down_flag_bird_right = 1;
        }
    } else {
        birdRightAngle += 8;
        if(birdRightAngle == 15) {
            up_down_flag_bird_right = 0;
        }
    }
    
    //FIRST PERSON VIEW 
    fpsLook_x = -17*sin((-giraffeAngle - 34.9) * 3.14159265359/180);
    fpsLook_z = 17*cos((-giraffeAngle - 34.9) * 3.14159265359/180);
    fpsEye_x = 17*cos((-giraffeAngle + 55) * 3.14159265359/180);
    fpsEye_z = 17*sin((-giraffeAngle + 55) * 3.14159265359/180);

    
    glutPostRedisplay();
    glutTimerFunc(4, myTimer, 0);
}


//--------------------------------------------------------------------------------

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (1000, 1000); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("COSC363: Assignment 1 - Andrew French - The Ranch");
   initialise();

   glutDisplayFunc(display); 
   glutTimerFunc(4, myTimer, 0);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}

