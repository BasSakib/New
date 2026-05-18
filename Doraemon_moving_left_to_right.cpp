#define GL_SILENCE_DEPRECATION
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// ---------- Function prototypes ----------
void drawSky1();
void drawSky2();
void drawSky3();
void Doracake();
void Doraemon();
void houseScene();
void drawHome();
void electricPole();
void drawFlower();

void drawEllipse(float cx, float cy, float rx, float ry, float r, float g, float b);
void drawCircle(float cx, float cy, float radius, float r, float g, float b);
void display();
void idle();
void init();

// ---------- Doracake animation variables ----------
float doracakeMoveX = -10.0f;
float doracakeAngle = 0.0f;

// ---------- Helper functions ----------
void drawEllipse(float cx, float cy, float rx, float ry, float r, float g, float b)
{
    int segments = 100;

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1416f * i / segments;
        glVertex2f(cx + rx * cos(theta), cy + ry * sin(theta));
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1416f * i / segments;
        glVertex2f(cx + rx * cos(theta), cy + ry * sin(theta));
    }
    glEnd();
}

void drawCircle(float cx, float cy, float radius, float r, float g, float b)
{
    int segments = 100;

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1416f * i / segments;
        glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1416f * i / segments;
        glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
    }
    glEnd();
}

void drawSky1()
   {
        glDisable(GL_LIGHTING);

        glBegin(GL_QUADS);


        glColor3f(0.0f, 0.4f, 0.8f);
        glVertex2f(-7.0, 7.0);
        glVertex2f(7.0, 7.0);


        glColor3f(0.6f, 0.8f, 1.0f);
         glVertex2f(7.0f, 0.0f);
        glVertex2f(-7.0f, 0.0f);


        glColor3f(0.4f, 0.7f, 0.992f);
        glVertex2f(-7.0f, -7.0f);
        glVertex2f(7.0f, -7.0f);

        glEnd();

        // glEnable(GL_LIGHTING);

   }
void drawSky2()
{   //glDisable(GL_LIGHTING);
    // TOP QUAD
    glBegin(GL_QUADS);
    glColor3f(0.36f, 0.41f, 0.53f); // cool blue-gray
    glVertex2f(0.0f, 20.0f);
    glVertex2f(18.0f, 20.0f);
    glColor3f(0.47f, 0.45f, 0.55f); // upper-mid
    glVertex2f(18.0f, 18.0f);
    glVertex2f(0.0f, 18.0f);
   // glVertex2f(18.0f, 17.0f);
   // glVertex2f(0.0f, 17.0f);
    glEnd();

    // MIDDLE QUAD
    glBegin(GL_QUADS);
    glColor3f(0.47f, 0.45f, 0.55f); // upper-mid
   // glVertex2f(0.0f, 17.0f);
   // glVertex2f(18.0f, 17.0f);
    glVertex2f(0.0f, 18.0f);
    glVertex2f(18.0f, 18.0f);
    glColor3f(0.67f, 0.55f, 0.50f); // lower-mid
    glVertex2f(18.0f, 13.5f);
    glVertex2f(0.0f, 13.5f);
    glEnd();

    // BOTTOM QUAD
    glBegin(GL_QUADS);
    glColor3f(0.67f, 0.55f, 0.50f); // lower-mid
    glVertex2f(0.0f, 13.5f);
    glVertex2f(18.0f, 13.5f);
    glColor3f(0.93f, 0.58f, 0.38f); // wbody sunset
    glVertex2f(18.0f, 10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();
    glFlush();
    //glEnable(GL_LIGHTING);
}
void drawSky3()
{
    // TOP QUAD
    glBegin(GL_QUADS);
    glColor3f(0.02f, 0.02f, 0.10f); // dark blue
    glVertex2f(0.0f, 20.0f);
    glVertex2f(18.0f, 20.0f);
    glColor3f(0.05f, 0.05f, 0.2f); // upper-mid
    glVertex2f(18.0f, 18.0f);
    glVertex2f(0.0f, 18.0f);
   // glVertex2f(18.0f, 17.0f);
   // glVertex2f(0.0f, 17.0f);
    glEnd();

    // MIDDLE QUAD
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.2f); // dark navy
   // glVertex2f(0.0f, 17.0f);
   // glVertex2f(18.0f, 17.0f);
    glVertex2f(0.0f, 18.0f);
    glVertex2f(18.0f, 18.0f);
    glColor3f(0.1f, 0.08f, 0.3f); // lower-mid
    glVertex2f(18.0f, 13.5f);
    glVertex2f(0.0f, 13.5f);
    glEnd();

    // BOTTOM QUAD
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.08f, 0.3f); // bluish purple
    glVertex2f(0.0f, 13.5f);
    glVertex2f(18.0f, 13.5f);
    glColor3f(0.2f, 0.12f, 0.4f); // faint purple
    glVertex2f(18.0f, 10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();
    glFlush();
}

void Doracake()
{
    float d1_cx = (-1.50f + 1.16f)/2;
    float d1_cy = (-0.72f + 0.89f)/2;
    float d1_rx = (1.53f - (-1.50f))/2;
    float d1_ry = (0.19f - (-0.72f))/2;
    drawEllipse(d1_cx, d1_cy, d1_rx, d1_ry, 0.65f, 0.32f, 0.12f);

    float c2_cx = (-1.68f + 1.32f)/2;
    float c2_cy = (-0.46f + 0.85f)/2;
    float c2_rx = (1.52f - (-1.68f))/2;
    float c2_ry = (0.43f - (-0.46f))/2;
    drawEllipse(c2_cx, c2_cy, c2_rx, c2_ry, 1.00f, 0.78f, 0.42f);

    float c_cx = (-1.88f + 1.59f)/2;
    float c_cy = (-0.14f + 0.76f)/2;
    float c_rx = (1.59f - (-1.88f))/2;
    float c_ry = (0.76f - (-0.14f))/2;
    drawEllipse(c_cx, c_cy, c_rx, c_ry, 1.00f, 0.86f, 0.50f);

    float d_cx = (-1.69f + 1.30f)/2;
    float d_cy = (0.28f + 0.6f)/2;
    float d_rx = (1.30f - (-1.69f))/2;
    float d_ry = (1.20f - 0.28f)/2;
    drawEllipse(d_cx, d_cy, d_rx, d_ry, 0.72f, 0.35f, 0.12f);

    glFlush();
}

void houseScene()
{

        glPushMatrix();
        glScalef(1.5f,1.5f,1.0f);
        drawHome();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(8.5f, -0.5f, 0.0f);
        glScalef(7.0f, 7.0f, 1.0f);
        electricPole();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5.5f, -0.5f, 0.0f);
        glScalef(7.0f, 7.0f, 1.0f);
        electricPole();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-8.0f, -2.650f, 0.0f);
        glScalef(.7f, .70f, 1.0f);
        drawFlower();
        glPopMatrix();



}

void drawHome()
{


    // RED  roof
    //SQUARE PART

    glColor3f(1.0f, 0.22f, 0.28f);
    glBegin(GL_POLYGON);
        glVertex2f(-3.1,3.07);
        glVertex2f(-3.1,3.20);
        glVertex2f(-0.05,4.55);
        glVertex2f(2.75,3.20);
        glVertex2f(2.75,3.07);
        glVertex2f(-0.05,4.5);
    glEnd();

    //SQUARE PART
    glColor3f(1.0f, 0.22f, 0.28f);
    glBegin(GL_POLYGON);

        glVertex2f(-0.20,4.60);
        glVertex2f(0.10,4.60);
        glVertex2f(0.10,4.3);
        glVertex2f(-0.20,4.3);
    glEnd();


// WHITE PART
   glColor3f(1.0f, 1.0f, 1.0f);
   glBegin(GL_POLYGON);
    glVertex2f(-2.58f, 3.11f);
    glVertex2f(-0.05f, 4.21f);
    glVertex2f(2.24f, 3.14f);
    glVertex2f(2.75f, 3.07f);
     glVertex2f(-0.05f, 4.4f);
    glVertex2f(-3.1f, 3.07f);
     glVertex2f(-2.56f, 2.89f);



glEnd();


    // 2nd floor body
    glColor3f(1.0f, 0.88f, 0.48f);
    glBegin(GL_POLYGON);
        glVertex2f(-2.58f, 0.54f);
         glVertex2f(-2.58f, 3.11f);
          glVertex2f(-0.05f, 4.21f);
          glVertex2f(2.24f, 3.11f);
           glVertex2f(2.24f, 1.19f);

    glEnd();
     glColor3f(1.0f, 0.75f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-2.58f, 0.54f);
         glVertex2f(-2.58f, 3.11f);
          glVertex2f(-0.05f, 4.21f);
          glVertex2f(2.24f, 3.11f);
           glVertex2f(2.24f, 1.19f);

    glEnd();


    // 1st window brown part
    glColor3f(0.64f, 0.36f, 0.16f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.71,3.14);
        glVertex2f(-1.71,1.71);
        glVertex2f(-0.65,1.71);
        glVertex2f(-0.65,3.14);
    glEnd();

    //  window borders
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1.71,3.14);
        glVertex2f(-1.71,1.71);
        glVertex2f(-0.65,1.71);
        glVertex2f(-0.65,3.14);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(-1.60,2.99);
        glVertex2f(-1.6,1.86);
        glVertex2f(-0.76,1.86);
        glVertex2f(-0.76,2.99);
    glEnd();

    glLineWidth(1.0);
   //brown window lines
    glBegin(GL_LINES);
        glVertex2f(-1.6,2.70); glVertex2f(-0.87,2.70);
        glVertex2f(-1.6,2.85); glVertex2f(-0.79,2.85);
        glVertex2f(-1.6,2.00); glVertex2f(-0.8,2.00);
        glVertex2f(-1.6,2.23); glVertex2f(-1.27,2.23);
        glVertex2f(-1.6,2.57); glVertex2f(-0.98,2.57);
        glVertex2f(-1.6,2.46); glVertex2f(-0.77,2.46);
        glVertex2f(-1.6,2.33); glVertex2f(-0.8,2.33);
        glVertex2f(-1.6,2.12); glVertex2f(-0.9,2.12);
    glEnd();

    // big window blue part
    glColor3f(0.02f, 0.22f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.65,3.14);
        glVertex2f(1.40,3.14);
        glVertex2f(1.40,1.71);
        glVertex2f(-0.65,1.71);
    glEnd();

    glColor3f(0.42f, 0.92f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.49,2.96);
        glVertex2f(1.22,2.96);
        glVertex2f(1.22,1.86);
        glVertex2f(-0.49,1.86);
    glEnd();

    glColor3f(0.02f, 0.22f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(0.32,2.96);
        glVertex2f(0.45,2.96);
        glVertex2f(0.45,1.86);
        glVertex2f(0.32,1.86);
    glEnd();

    glColor3f(0,0,0);
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.65,3.14);
        glVertex2f(1.40,3.14);
        glVertex2f(1.40,1.71);
        glVertex2f(-0.65,1.71);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.49,2.96);
        glVertex2f(1.22,2.96);
        glVertex2f(1.22,1.86);
        glVertex2f(-0.49,1.86);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.32,2.96);
        glVertex2f(0.45,2.96);
        glVertex2f(0.45,1.86);
        glVertex2f(0.32,1.86);
    glEnd();

    // white strip
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(-2,3.2);
        glVertex2f(-2,3.08);
        glVertex2f(1.59,3.08);
        glVertex2f(1.59,3.2);
    glEnd();

    // red top
    glColor3f(1.0f, 0.22f, 0.28f);
    glBegin(GL_POLYGON);
        glVertex2f(-2.0f, 3.2f);
        glVertex2f(-1.72f, 3.37f);
        glVertex2f(-0.4f, 3.37f);
        glVertex2f(1.27f, 3.37f);
        glVertex2f(1.59f, 3.2f);
    glEnd();

     // 1ST FLOOR  roof
     //red strip
     glColor3f(1.0f, 0.22f, 0.28f);
    glBegin(GL_POLYGON);
        glVertex2f(-3.20f, 0.5f);
        glVertex2f(-3.20f, 0.7f);
        glVertex2f(0.79f, 1.75f);
        glVertex2f(5.10f, 0.45f);
        glVertex2f(5.10f, 0.25f);
    glEnd();

//white strip
glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-2.83f,0.4f);
        glVertex2f(0.79f,1.35f);
        glVertex2f(4.69,0.25);
        glVertex2f(5.10f,0.25f);
        glVertex2f(0.79f,1.55f);
        glVertex2f(-3.20f,0.5f);
          glVertex2f(-2.56f,0.0f);


    glEnd();


    // 1ST FLOOR body
    glColor3f(1.0f, 0.88f, 0.48f);
    glBegin(GL_POLYGON);
        glVertex2f(-2.83f,-2.72f);
        glVertex2f(-2.83f,0.4f);
        glVertex2f(0.79f,1.35f);
        glVertex2f(4.69f,0.25f);
        glVertex2f(4.69f,-2.72f);
    glEnd();

     glColor3f(1.0f, 0.75f, 0.0f);
 glLineWidth(1.0);
    glBegin(GL_LINE_LOOP);

        glVertex2f(-2.83f,-2.72f);
        glVertex2f(-2.83F,0.4f);
        glVertex2f(0.79f,1.35f);
        glVertex2f(4.69f,0.25f);
        glVertex2f(4.69f,-2.72f);
    glEnd();

// home road
 glColor3f(0.5f, 0.4f, 0.6f);

    glBegin(GL_POLYGON);
        glVertex2f(2.25f,-2.72f);
        glVertex2f(4.55f,-2.72f);
        glVertex2f(6.0f,-3.0f);
        glVertex2f(2.14f,-3.0f);

    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2.25f,-2.72f);
        glVertex2f(4.55f,-2.72f);
        glVertex2f(6.0f,-3.0f);
        glVertex2f(2.14f,-3.0f);

    glEnd();

    //2ND WINDOW BROWN PART
     glColor3f(0.64f, 0.36f, 0.16f);
    glBegin(GL_POLYGON);
        glVertex2f(-2.45,0.0);
        glVertex2f(-1.1,0.0);
        glVertex2f(-1.1,-2);
        glVertex2f(-2.45,-2);
    glEnd();
    // BORDER
    glColor3f(0,0,0);
    glLineWidth(1.5);
     glBegin(GL_LINE_LOOP);
       glVertex2f(-2.45,0.0);
        glVertex2f(-1.1,0.0);
        glVertex2f(-1.1,-2);
        glVertex2f(-2.45,-2);
    glEnd();
   // INSIDE BORDER
    glColor3f(0,0,0);
    glLineWidth(1.5);
     glBegin(GL_LINE_LOOP);
       glVertex2f(-2.28, -0.20);
        glVertex2f(-1.25, -0.20);
        glVertex2f(-1.25, -1.91);
        glVertex2f(-2.28, -1.91);
    glEnd();
    // BROWN WINDOW LINES
       glLineWidth(1.0);
   //brown window lines
    glBegin(GL_LINES);
        glVertex2f(-2.28, -0.35); glVertex2f(-1.25,-0.35);
         glVertex2f(-2.28, -0.50);glVertex2f(-1.50, -0.5);
         glVertex2f(-2.28, -0.65);glVertex2f(-1.80, -0.65);
         glVertex2f(-2.28, -0.80);glVertex2f(-1.40, -0.80);
         glVertex2f(-2.28, -0.95); glVertex2f(-1.25,-0.95);
         glVertex2f(-2.28, -1.10); glVertex2f(-1.60,-1.10);
         glVertex2f(-2.28, -1.25); glVertex2f(-1.25,-1.25);
         glVertex2f(-2.28, -1.40); glVertex2f(-1.30,-1.40);
    glEnd();
     //BLUE WIMDOW PART
      glColor3f(0.02f, 0.22f, 0.95f);
    glBegin(GL_POLYGON);

        glVertex2f(-1.1,0.0);
        glVertex2f(1.35, 0.0);
         glVertex2f(1.35, -2);
        glVertex2f(-1.1,-2);

    glEnd();
    glColor3f(0,0,0);
    glLineWidth(1.5);
     glBegin(GL_LINE_LOOP);
        glVertex2f(-1.1,0.0);
        glVertex2f(1.35, 0.0);
         glVertex2f(1.35, -2);
        glVertex2f(-1.1,-2);

    glEnd();
  //WINDOW SKYBLUE PART
     glColor3f(0.42f, 0.92f, 1.0f);
     glBegin(GL_POLYGON);
       glVertex2f(-0.90, -0.20);
        glVertex2f(1.15, -0.20);
        glVertex2f(1.15,-1.91);
        glVertex2f(-0.90,-1.91);
    glEnd();

   glColor3f(0,0,0);
    glLineWidth(1.5);
     glBegin(GL_LINE_LOOP);
     glVertex2f(-0.90, -0.20);
        glVertex2f(1.15, -0.20);
        glVertex2f(1.15,-1.91);
        glVertex2f(-0.90,-1.91);
    glEnd();
     glColor3f(0.02f, 0.22f, 0.95f);
     glBegin(GL_POLYGON);
       glVertex2f(0.0, -0.20);
        glVertex2f(0.2, -0.20);
        glVertex2f(0.2,-1.91);
        glVertex2f(0.0,-1.91);
    glEnd();

glColor3f(0,0,0);
    glLineWidth(1.5);
     glBegin(GL_LINE_LOOP);
     glVertex2f(0.0, -0.20);
        glVertex2f(0.2, -0.20);
        glVertex2f(0.2,-1.91);
        glVertex2f(0.0,-1.91);
    glEnd();

    //white strip
     glColor3f(1.0f, 1.0f, 1.0f);
     glBegin(GL_POLYGON);
       glVertex2f(-2.68, 0.1);
        glVertex2f(1.35, 0.10);
        glVertex2f(1.35,-0.1);
        glVertex2f(-2.68,-0.1);
    glEnd();
//red top
     glColor3f(1.0f, 0.22f, 0.28f);
glBegin(GL_POLYGON);
    glVertex2f(-2.68,  0.1);
    glVertex2f( -2.0, 0.3);
    glVertex2f( 1.53,0.3);
    glVertex2f(1.35, 0.1);
glEnd();
//window another part
 glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_POLYGON);
    glVertex2f(1.53, 0.3);
    glVertex2f( 1.35, 0.1);
    glVertex2f( 1.35,-0.1);
    glVertex2f(1.53, 0.1);
glEnd();



    // door
    glColor3f(0.48f, 0.20f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(2.25f,-2.72f);
        glVertex2f(4.35f,-2.72f);
        glVertex2f(4.35f,0.0f);
        glVertex2f(2.25f,0.0f);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);

        glVertex2f(4.35f,-2.72f);
        glVertex2f(4.35f,0.0f);
        glVertex2f(2.25f,0.0f);
         glVertex2f(2.25f,-2.72f);
    glEnd();

    // border
    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(2.45f, -2.72f);
        glVertex2f(2.45f, -0.2f);
        glVertex2f(4.15f, -0.2f);
        glVertex2f(4.15f, -2.72f);

    glEnd();


    glEnd();
 // DOOR SIDE SKYBLUE PART
    glColor3f(0.25f, 0.65f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(3.75f,0.0f);
        glVertex2f(4.15f,0.0f);
        glVertex2f(4.15f,-2.72f);
        glVertex2f(3.75f,-2.72f);
    glEnd();
    // INSIDE PART
     glColor3f(0.55f, 0.10f, 0.95f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(3.85,-0.7f);
        glVertex2f(4.05f,-0.7f);
        glVertex2f(4.05f,-1.4f);
        glVertex2f(3.85f,-1.4f);
    glEnd();
     glColor3f(0.55f, 0.10f, 0.95f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(3.85,-1.5f);
        glVertex2f(4.05f,-1.5f);
        glVertex2f(4.05f,-2.2f);
        glVertex2f(3.85f,-2.2f);
    glEnd();
     glBegin(GL_LINE_LOOP);
        glVertex2f(3.85,-2.3f);
        glVertex2f(4.05f,-2.3f);
        glVertex2f(4.05f,-2.9f);
        glVertex2f(3.85f,-2.9f);
    glEnd();
    //SIDE PART BORDER
 glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(3.75f,-2.72f);
        glVertex2f(3.75f,0.0f);
        glVertex2f(4.15f,0.0f);
        glVertex2f(4.15f,-2.72f);

    glEnd();
    // DOOR TOP SKYBLUE PART
    glColor3f(0.25f, 0.65f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(2.45f,0.0f);
        glVertex2f(4.15f,0.0f);
        glVertex2f(4.15f,-0.4f);
        glVertex2f(2.45f,-0.4f);
    glEnd();
    // TOP SKY BLUE INSIDE PART
    glColor3f(0.55f, 0.10f, 0.95f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2.55f,-0.1f);
        glVertex2f(3.25f,-0.1f);
        glVertex2f(3.25f,-0.3f);
        glVertex2f(2.55f,-0.3f);
    glEnd();


     glColor3f(0.55f, 0.10f, 0.95f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(3.35f,-0.1f);
        glVertex2f(4.05f,-0.1f);
        glVertex2f(4.05f,-0.3f);
        glVertex2f(3.35f,-0.3f);
    glEnd();


    //border part
  glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(2.45f,-0.4f);
        glVertex2f(2.45f,0.0f);
        glVertex2f(4.15f,0.0f);
        glVertex2f(4.15f,-0.4f);

    glEnd();
   //border
    glBegin(GL_LINES);
    glVertex2f(2.45f,-0.4f);
    glVertex2f(3.75f,-0.4f);
      glEnd();
      //door white strip
     glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(2.05f,0.1f);
        glVertex2f(4.55f,0.1f);
        glVertex2f(4.55f,-0.1f);
        glVertex2f(2.05f,-0.1f);
    glEnd();
    // door REDtop part
         glColor3f(1.0f, 0.22f, 0.28f);
    glBegin(GL_POLYGON);
        glVertex2f(2.05f,0.1f);
        glVertex2f(2.45f,0.3f);
        glVertex2f(4.15f,0.3f);
        glVertex2f(4.55f,0.1f);

    glEnd();
    //DOOR MIDDLE BROWN PART
       glColor3f(0.48f, 0.20f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(2.45f,-0.4f);
        glVertex2f(4.15f,-0.4f);
        glVertex2f(4.15f,-0.6f);
        glVertex2f(2.45f,-0.6f);

    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
         glVertex2f(2.45f,-0.4f);
        glVertex2f(4.15f,-0.4f);
        glVertex2f(4.15f,-0.6f);
        glVertex2f(2.45f,-0.6f);

    glEnd();
    //DOOR SIDE BORDER
     glBegin(GL_LINES);
    glVertex2f(3.55f,-0.6f);
    glVertex2f(3.55f,-2.72f);
      glEnd();
    //DOOR INSIDE QUAD
    glColor3f(0.25f, 0.65f, 1.0f);
    glBegin(GL_POLYGON);
       glVertex2f(2.75f,-0.8f);
        glVertex2f(3.25f,-0.8f);
        glVertex2f(3.25f,-1.5f);
        glVertex2f(2.75f,-1.5f);


    glEnd();
     glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
         glVertex2f(2.75f,-0.8f);
        glVertex2f(3.25f,-0.8f);
        glVertex2f(3.25f,-1.5f);
        glVertex2f(2.75f,-1.5f);

    glEnd();
     glColor3f(0.55f, 0.10f, 0.95f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2.85f,-0.9f);
        glVertex2f(3.15f,-0.9f);
        glVertex2f(3.15f,-1.4f);
        glVertex2f(2.85f,-1.4f);
    glEnd();
    //DOOR  LOCK
    glColor3f(0.25f, 0.65f, 1.0f);
    glBegin(GL_POLYGON);
       glVertex2f(3.33f,-1.6f);
        glVertex2f(3.45f,-1.6f);
        glVertex2f(3.45f,-1.9f);
        glVertex2f(3.33f,-1.9f);
glEnd();
glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
          glVertex2f(3.33f,-1.6f);
        glVertex2f(3.45f,-1.6f);
        glVertex2f(3.45f,-1.9f);
        glVertex2f(3.33f,-1.9f);
    glEnd();
//CIRCLE PART
glBegin(GL_POLYGON);
for( int i=0;i<200;i++)
    {
glColor3f(0.5f,0.6f,1.0f);
float pi= 3.1416;
float A =(i*2*pi)/200;
float r = 0.07;
float x= 3.39+r* cos(A);
float y= -1.72+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

glLineWidth(1.5);

glBegin(GL_LINE_LOOP);

for( int i=0;i<100;i++)
    {
glColor3f(0.0f,0.0f,0.0f);
float pi= 3.1416;
float A =(i*2*pi)/100;
float r = 0.07;
float x= 3.39+r* cos(A);
float y= -1.72+r* sin(A);
glVertex2f(x,y);
    }
glEnd();


// main gate part
//1ST LEFT PART
float startX = 2.14f;
float width  = 0.09f;
float gap    = 0.15f;

for(int i = 0; i < 3; i++)
{
    float x1 = startX + i * gap;     // left
    float x2 = x1 + width;           // right
    float y1 = -1.6f;                // top
    float y2 = -2.9f;                // bottom

    // Filled polygon (body)
    glColor3f(0.00f, 0.75f, 1.0f);

    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();

    // Border (outline)
    glLineWidth(2.0f);          // border thickness
    glColor3f(0.0f, 0.0f, 0.0f); // border color black

    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}



//LEFT PART
glColor3f(0.00f, 0.75f, 1.0f);
    glBegin(GL_POLYGON);

        glVertex2f(2.14f, -1.6f);
        glVertex2f(2.47f, -1.5f);
         glVertex2f(2.47f, -1.6f);
         glVertex2f(2.14f, -1.7f);

    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2.14f, -1.6f);
        glVertex2f(2.47f, -1.5f);
         glVertex2f(2.47f, -1.6f);
         glVertex2f(2.14f, -1.7f);
glEnd();
glColor3f(0.00f, 0.75f, 1.0f);
    glBegin(GL_POLYGON);

        glVertex2f(2.14f, -2.9f);
        glVertex2f(2.47f, -2.8f);
         glVertex2f(2.47f, -2.9f);
         glVertex2f(2.14f, -3.0f);

    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2.14f, -2.9f);
        glVertex2f(2.47f, -2.8f);
         glVertex2f(2.47f, -2.9f);
         glVertex2f(2.14f, -3.0f);
glEnd();

    glBegin(GL_POLYGON);
for( int i=0;i<200;i++)
    {
glColor3f(0.0f,0.5f,1.0f);
float pi= 3.1416;
float A =(i*2*pi)/200;
float r = 0.07;
float x= 2.47+r* cos(A);
float y= -1.55+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

glLineWidth(1.5);

glBegin(GL_LINE_LOOP);

for( int i=0;i<100;i++)
    {
glColor3f(0.0f,0.0f,0.0f);
float pi= 3.1416;
float A =(i*2*pi)/100;
float r = 0.07;
float x= 2.47+r* cos(A);
float y= -1.55+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

 glBegin(GL_POLYGON);
for( int i=0;i<200;i++)
    {
glColor3f(0.0f,0.5f,1.0f);
float pi= 3.1416;
float A =(i*2*pi)/200;
float r = 0.07;
float x= 2.47+r* cos(A);
float y= -2.85+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

glLineWidth(1.5);

glBegin(GL_LINE_LOOP);

for( int i=0;i<100;i++)
    {
glColor3f(0.0f,0.0f,0.0f);
float pi= 3.1416;
float A =(i*2*pi)/100;
float r = 0.07;
float x= 2.47+r* cos(A);
float y= -2.85+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

//2ND GATE PART
 startX = 4.46f;
 width  = 0.10f;
 gap    = 0.20f;

for(int i = 0; i < 6; i++)
{
    float x1 = startX - i * gap;     // left
    float x2 = x1 + width;           // right
    float y1 = -1.7f;                // top
    float y2 = -2.9f;                // bottom

    // Filled polygon (body)
    glColor3f(0.00f, 0.75f, 1.0f);

    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();

    // Border (outline)
    glLineWidth(2.0f);          // border thickness
    glColor3f(0.0f, 0.0f, 0.0f); // border color black

    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

//1ST PART
//BLUE PART
glColor3f(0.00f, 0.75f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(3.52f, -1.6f);
        glVertex2f(4.56f, -1.6f);
        glVertex2f(4.56f, -1.7f);
        glVertex2f(3.52f, -1.7f);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(3.52f, -1.6f);
        glVertex2f(4.56f, -1.6f);
        glVertex2f(4.56f, -1.7f);
        glVertex2f(3.52f, -1.7f);
    glEnd();

glBegin(GL_POLYGON);
for( int i=0;i<200;i++)
    {
glColor3f(0.0f,0.5f,1.0f);
float pi= 3.1416;
float A =(i*2*pi)/200;
float r = 0.07;
float x= 3.52+r* cos(A);
float y= -1.65+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

glLineWidth(1.5);

glBegin(GL_LINE_LOOP);

for( int i=0;i<100;i++)
    {
glColor3f(0.0f,0.0f,0.0f);
float pi= 3.1416;
float A =(i*2*pi)/100;
float r = 0.07;
float x= 3.52+r* cos(A);
float y= -1.65+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

//2ND PART
//BLUE PART
glColor3f(0.00f, 0.75f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(3.52f, -2.9f);
        glVertex2f(4.56f, -2.9f);
        glVertex2f(4.56f, -3.0f);
        glVertex2f(3.52f, -3.0f);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(3.52f, -2.9f);
        glVertex2f(4.56f, -2.9f);
        glVertex2f(4.56f, -3.0f);
        glVertex2f(3.52f, -3.0f);
    glEnd();

glBegin(GL_POLYGON);
for( int i=0;i<200;i++)
    {
glColor3f(0.0f,0.5f,1.0f);
float pi= 3.1416;
float A =(i*2*pi)/200;
float r = 0.07;
float x= 3.52+r* cos(A);
float y= -2.95+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

glLineWidth(1.5);

glBegin(GL_LINE_LOOP);

for( int i=0;i<100;i++)
    {
glColor3f(0.0f,0.0f,0.0f);
float pi= 3.1416;
float A =(i*2*pi)/100;
float r = 0.07;
float x= 3.52+r* cos(A);
float y= -2.95+r* sin(A);
glVertex2f(x,y);
    }
glEnd();

    // first rectangle (wall)
    glColor3f(0.58f, 0.58f, 0.62f);
    glBegin(GL_POLYGON);
        glVertex2f(-6.34f, -3.0f);
        glVertex2f(2.14f, -3.0f);
        glVertex2f(2.14f, -1.44f);
        glVertex2f(-6.34f, -1.44f);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-6.34f, -3.0f);
        glVertex2f(2.14f, -3.0f);
        glVertex2f(2.14f, -1.44f);
        glVertex2f(-6.34f, -1.44f);
    glEnd();


    float y1 = -3.0f, y2 = -1.44f;
    float start_x1 = -6.36f, x_spacing1 = 0.5f;
    int num_vlines1 = 18;

    glLineWidth(0.5);
    glBegin(GL_LINES);
        for(int i=0;i<num_vlines1;i++){
            float x = start_x1 + i * x_spacing1;
            glVertex2f(x, y1);
            glVertex2f(x, y2);
        }
    glEnd();

    float h_start_y1 = -1.44f;
    float h_start_x1 = -6.36f, h_end_x1 = 2.14f;
    float h_spacing1 = (-1.44f - (-3.0f)) / 6;
    int num_hlines1 = 7;

    glBegin(GL_LINES);
        for(int i=0;i<num_hlines1;i++){
            float y = h_start_y1 - i * h_spacing1;
            glVertex2f(h_start_x1, y);
            glVertex2f(h_end_x1, y);
        }
    glEnd();

    // second rectangle
    glColor3f(0.58f, 0.58f, 0.62f);
    glBegin(GL_POLYGON);
        glVertex2f(4.56f, -3.0f);
        glVertex2f(4.56f, -1.44f);
        glVertex2f(6.76f, -1.44f);
        glVertex2f(6.76f, -3.0f);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(4.56f, -3.0f);
        glVertex2f(4.56f, -1.44f);
        glVertex2f(6.76f, -1.44f);
        glVertex2f(6.76f, -3.0f);
    glEnd();

    float start_x2 = 4.56f, x_spacing2 = 0.5f;
    int num_vlines2 = 5;

    glBegin(GL_LINES);
        for(int i=0;i<num_vlines2;i++){
            float x = start_x2 + i * x_spacing2;
            glVertex2f(x, y1);
            glVertex2f(x, y2);
        }
    glEnd();

    float h_start_x2 = 4.56f, h_end_x2 = 6.76f;
    float h_spacing2 = (-1.44f - (-3.0f)) / 6;
    int num_hlines2 = 7;

    glBegin(GL_LINES);
        for(int i=0;i<num_hlines2;i++){
            float y = -1.44f - i * h_spacing2;
            glVertex2f(h_start_x2, y);
            glVertex2f(h_end_x2, y);
        }
    glEnd();
    glFlush();
}

void electricPole()
{
    glPointSize(10.0f);

    //Borders
    glLineWidth(4);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    float al = 0.03f;
    float bl = 0.03f;
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1416f / 180.0f;
        float x =  al * cos(angle);
        float y = 0.6 + bl * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    float al1 = 0.03f;
    float bl1 = 0.03f;
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1416f / 180.0f;
        float x =  al1 * cos(angle);
        float y = -0.6 + bl1 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.175f, 0.5f);
    glVertex2f(0.175f, 0.5f);
    glVertex2f(0.135f, 0.45f);
    glVertex2f(-0.135f, 0.45f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.105f, 0.4f);
    glVertex2f(0.105f, 0.4f);
    glVertex2f(0.065f, 0.35f);
    glVertex2f(-0.065f, 0.35f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.03f, 0.6f);
    glVertex2f(-0.03f, 0.6f);
    glVertex2f(-0.03f, -0.6f);
    glVertex2f(0.03f, -0.6f);
    glEnd();
    glFlush();


    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(0.03f, 0.6f);
    glVertex2f(-0.03f, 0.6f);
    glVertex2f(-0.03f, -0.6f);
    glVertex2f(0.03f, -0.6f);
    glEnd();
    glFlush();


    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    float a = 0.03f;
    float b = 0.03f;
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1416f / 180.0f;
        float x =  a * cos(angle);
        float y = 0.6 + b * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();

    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    float a1 = 0.03f;
    float b1 = 0.03f;
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1416f / 180.0f;
        float x =  a1 * cos(angle);
        float y = -0.6 + b1 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();

    glLineWidth(0.25);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(1.0f, 0.47f);
    glVertex2f(0.135f, 0.47f);
    glEnd();
    glFlush();

    //WIRES
    glLineWidth(2);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.47f);
    glVertex2f(-0.135f, 0.47f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(1.0f, 0.37f);
    glVertex2f(0.065f, 0.37f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.37f);
    glVertex2f(-0.065f, 0.37f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(1.0f, 0.47f);
    glVertex2f(0.135f, 0.47f);
    glEnd();
    glFlush();

    glLineWidth(0.25);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.175f, 0.5f);
    glVertex2f(0.175f, 0.5f);
    glVertex2f(0.135f, 0.45f);
    glVertex2f(-0.135f, 0.45f);
    glEnd();
    //glFlush();

    glLineWidth(0.25);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.105f, 0.4f);
    glVertex2f(0.105f, 0.4f);
    glVertex2f(0.065f, 0.35f);
    glVertex2f(-0.065f, 0.35f);
    glEnd();
    //glFlush();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.175f, 0.5f);
    glVertex2f(0.175f, 0.5f);
    glVertex2f(0.135f, 0.45f);
    glVertex2f(-0.135f, 0.45f);
    glEnd();
    glFlush();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.105f, 0.4f);
    glVertex2f(0.105f, 0.4f);
    glVertex2f(0.065f, 0.35f);
    glVertex2f(-0.065f, 0.35f);
    glEnd();
    glFlush();
}

void drawFlower()
{ glColor3f(0.6,0.2,0);
    glBegin(GL_POLYGON);
    glVertex2f(11,1.11);
    glVertex2f(11,0.57);
    glVertex2f(11.01,0.5555);
    glVertex2f(11.03,0.54);
    glVertex2f(11.93,0.54);
    glVertex2f(11.95,0.5555);
    glVertex2f(11,0.57);
    glVertex2f(11.96,0.57);
    glVertex2f(11.96,1.11);
    glEnd();

    glColor3f(0.8,0.4,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(11,1.11);
    glVertex2f(10.97,1.12);
    glVertex2f(10.97302,1.11894);
    glVertex2f(10.95455,1.15131);
    glVertex2f(10.96995,1.4031);
    glVertex2f(11,1.4);
    glVertex2f(11.97808,1.41);
    glVertex2f(12,1.4);
    glVertex2f(12.01195,1.35994);
    glVertex2f(12.01041,1.14412);
    glVertex2f(11.98886,1.11894);
    glVertex2f(11.95826,1.11117);
    glEnd();

    //pata

    float x0 = 10.76139f, y0 = 1.8923f;
    float x1 = 11.15541f, y1 = 1.82755f;
    float x2 = 11.45708f, y2 = 1.42828f;

    glColor3f(0.0f, 0.0f, 0.0f); // curve color
    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
    for(float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        float x = (1-t)*(1-t)*x0
        + 2*(1-t)*t*x1
        + t*t*x2;

        float y = (1-t)*(1-t)*y0
        + 2*(1-t)*t*y1
        + t*t*y2;

        glVertex2f(x, y);
    }
    glEnd();
    float x10 = 10.76139f, y10 = 1.8923f;
    float x11 = 10.87683f, y11 = 1.59375f;
    float x12 = 11.07692f,  y12 = 1.4067f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
    for(float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        float x = (1-t)*(1-t)*x10
                + 2*(1-t)*t*x11
                + t*t*x12;

        float y = (1-t)*(1-t)*y10
                + 2*(1-t)*t*y11
                + t*t*y12;

        glVertex2f(x, y);
    }
    glEnd();
//pata color
        glColor3f(0.0f, 0.45f, 0.0f);
        glBegin(GL_POLYGON);

        for(float t = 0.0f; t <= 1.0f; t += 0.02f)
        {
            float x = (1-t)*(1-t)*x0
                    + 2*(1-t)*t*x1
                    + t*t*x2;

            float y = (1-t)*(1-t)*y0
                    + 2*(1-t)*t*y1
                    + t*t*y2;

            glVertex2f(x, y);
        }

        for(float t = 1.0f; t >= 0.0f; t -= 0.02f)
        {
            float x = (1-t)*(1-t)*x10
                    + 2*(1-t)*t*x11
                    + t*t*x12;

            float y = (1-t)*(1-t)*y10
                    + 2*(1-t)*t*y11
                    + t*t*y12;

            glVertex2f(x, y);
        }

        glEnd();

    //pata right
    float x20 = 11.52173f, y20 = 1.41749f;
    float x21 = 11.8157f,  y21 = 1.82755f;
    float x22 = 12.24359f, y22 = 1.88151f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
    for(float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        float x = (1-t)*(1-t)*x20
                + 2*(1-t)*t*x21
                + t*t*x22;

        float y = (1-t)*(1-t)*y20
                + 2*(1-t)*t*y21
                + t*t*y22;

        glVertex2f(x, y);
    }
    glEnd();
    float x30 = 11.93576f, y30 = 1.41749f;
    float x31 = 12.10814f,  y31 = 1.55058f;
    float x32 = 12.24359f, y32 = 1.88151f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
    for(float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        float x = (1-t)*(1-t)*x30
                + 2*(1-t)*t*x31
                + t*t*x32;

        float y = (1-t)*(1-t)*y30
                + 2*(1-t)*t*y31
                + t*t*y32;

        glVertex2f(x, y);
    }
    glEnd();
    //pata color
    glColor3f(0.0f, 0.45f, 0.0f);
    glBegin(GL_POLYGON);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x = (1-t)*(1-t)*x20
                + 2*(1-t)*t*x21
                + t*t*x22;

        float y = (1-t)*(1-t)*y20
                + 2*(1-t)*t*y21
                + t*t*y22;

        glVertex2f(x, y);
    }

    for(float t = 1.0f; t >= 0.0f; t -= 0.02f)
    {
        float x = (1-t)*(1-t)*x30
                + 2*(1-t)*t*x31
                + t*t*x32;

        float y = (1-t)*(1-t)*y30
                + 2*(1-t)*t*y31
                + t*t*y32;

        glVertex2f(x, y);
    }

    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(10.91223,1.7664);
    glVertex2f(11.35242,1.41749);

    glVertex2f(11.66333,1.41389);
    glVertex2f(12.1,1.8);
    glEnd();
    //LOMBA
    glLineWidth(2.0);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.45f, 0.0f);
    glVertex2f(11.45708,1.42828);
    glVertex2f(11.46,1.81);

    glVertex2f(11.51,1.85);
    glVertex2f(11.52173,1.41749);
    glEnd();

    //full
    drawCircle(11.31,2.69,0.19771922640362516,0.8,0.4,1);
    drawCircle(11.15,2.44,0.17034343770221755,0.8,0.4,1);
    drawCircle(11.16,2.13,0.16801150074766016,0.8,0.4,1);
    drawCircle(11.39,1.96,0.1634418553389585,0.8,0.4,1);
    drawCircle(11.66,1.96,0.18765000067862558,0.8,0.4,1);
    drawCircle(11.86,2.17,0.17,0.8,0.4,1);
    drawCircle(11.86,2.49,0.18,0.8,0.4,1);
    drawCircle(11.61,2.72,0.19,0.8,0.4,1);

    drawCircle(11.49888,2.31652,0.28,1,0.84,0);
    glFlush();
}


// ---------- Display ----------
void display()
{
    glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT);

    // One scenario from your code
    glPushMatrix();
        glScalef(1.45f, 1.45f, 1.0f);
        drawSky1();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -1.2f, 0.0f);
        houseScene();
    glPopMatrix();

    // Doraemon moving left to right
    glPushMatrix();
        glTranslatef(doracakeMoveX, -5.8f, 0.0f);
        glScalef(0.45f, 0.45f, 1.0f);
        Doraemon();
    glPopMatrix();

    glutSwapBuffers();
}

// ---------- Idle function ----------
void idle()
{
    doracakeMoveX += 0.03f;

    if (doracakeMoveX > 10.0f)
    {
        doracakeMoveX = -10.0f;
    }

    glutPostRedisplay();
}

// ---------- Init ----------
void init()
{
    glDisable(GL_LIGHTING);
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -7.0, 7.0);
    glMatrixMode(GL_MODELVIEW);
}

// ---------- Main ----------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Doraemon Moving Left to Right");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

void Doraemon()
{
    //NOSE
    glLineWidth(3);
    glBegin(GL_POLYGON);

    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 0.0, 0.0);
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 300.0f;
        float r = 0.33f;

        float x = 7.53 + r * cos(A);
        float y = 8.39 + r * sin(A);

        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(3);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);

    for(int i = 0; i < 300; i++)
    {
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 300.0f;
        float r = 0.33f;

        float x = 7.53 + r * cos(A);
        float y = 8.39 + r * sin(A);

        glVertex2f(x, y);
    }


    glEnd();
    //HEAD
    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0); // white fill
        float pi = 3.1416;
        float A = (i * pi) / 300; // only half circle
        float r = 2.1;
        float x = 5.46 + r * cos(A);
        float y = 7.42 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();



    // Black border only on the curved edge
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(int i = 20; i <= 90; i++)   // 300 steps → 20–90 mapped
    {
        float pi = 3.1416f;
        float A = (i * pi) / 300.0f;

        float r = 2.1f;
        float x = 5.46f + r * cos(A);
        float y = 7.42f + r * sin(A);

        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(0.6,0.8,0.9);
        // white fill
        float pi = 3.1416;
        float A = (i *2* pi) / 300; // only half circle
        float r = 0.86;
        float x = 4.88 + r * cos(A);
        float y = 6.3 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();

    // Black border only on the curved edge

    glEnd();



    glBegin(GL_POLYGON);

    float angleOfRotationNew = 60.0f;
    float rotationAngleNew = angleOfRotationNew * (3.1416f / 180.0f);

    float txNew = 0.2f;
    float tyNew = -0.03f;

    float cxNew = 5.24f;
    float cyNew = 7.45f;

    float rNew = 2.1f;

    for (int i = 0; i < 300; i++) {

        glColor3f(0.6,0.8,0.9);

        float pi = 3.1416f;
        float theta = (i * pi) / 300.0f;

        float x = rNew * cos(theta);
        float y = rNew * sin(theta);

        // Rotate
        float x_rot = x * cos(rotationAngleNew) - y * sin(rotationAngleNew);
        float y_rot = x * sin(rotationAngleNew) + y * cos(rotationAngleNew);

        // Translate + center
        float x_final = x_rot + cxNew + txNew;
        float y_final = y_rot + cyNew + tyNew;

        glVertex2f(x_final, y_final);
    }

    glEnd();

    // Black border
    glLineWidth(3);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < 300; i++) {

        float pi = 3.1416f;
        float theta = (i * pi) / 300.0f;

        float x = rNew * cos(theta);
        float y = rNew * sin(theta);

        float x_rot = x * cos(rotationAngleNew) - y * sin(rotationAngleNew);
        float y_rot = x * sin(rotationAngleNew) + y * cos(rotationAngleNew);

        float x_final = x_rot + cxNew + txNew;
        float y_final = y_rot + cyNew + tyNew;

        glVertex2f(x_final, y_final);
    }

    glEnd();

    //HAND(ROUND)
    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i=0;i<300;i++)
    {
        glColor3f(1.0,1.0,1.0);
        float pi=3.1416;
        float A=(i*2*pi)/300;
        float r=0.43;
        float x = 3.2+r * cos(A);
        float y =5.71+ r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<500;i++)
    {
        glColor3f(0.0,0.0,0.0);
        float pi=3.1416;
        float A=(i*2*pi)/500;
        float r=0.43;
        float x = 3.2+r * cos(A);
        float y =5.71+ r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    //hand(blue)
    glLineWidth(4.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(5.12f, 5.3f);
    glVertex2f(4.01f, 5.78f);
    glVertex2f(3.78f, 5.82f);
    glVertex2f(3.61f, 5.81f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(3.43f, 5.39f);
    glVertex2f(3.55f, 5.28f);
    glVertex2f(3.65f, 5.19f);
    glVertex2f(3.8f,  5.08f);
    glVertex2f(3.93f, 4.99f);
    glVertex2f(4.09f, 4.89f);
    glVertex2f(4.26f, 4.78f);
    glVertex2f(4.43f, 4.67f);
    glEnd();

    glColor3f(0.6f, 0.8f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(5.12f,5.3f);
    glVertex2f(4.01f,5.78f);
    glVertex2f(3.78f,5.82f);
    glVertex2f(3.61f,5.81f);
    glVertex2f(3.43f,5.39f);
    glVertex2f(3.55f,5.28f);
    glVertex2f(3.65f,5.19f);
    glVertex2f(3.8f,5.08f);
    glVertex2f(3.93f,4.99f);
    glVertex2f(4.09f,4.89f);
    glVertex2f(4.26f,4.78f);
    glVertex2f(4.43f,4.67f);
    glEnd();


    //HEADWHITE

    glBegin(GL_POLYGON);

    float angleOfRotation = 73.5f;
    float rotationAngle = angleOfRotation * (3.1416 / 180.0f);

    float tx = -0.134f;
    float ty = -0.272f;

    float cx = 6.7f;
    float cy = 6.99f;

    for (int i = 0; i < 300; i++) {

        glColor3f(1.0f, 1.0f, 1.0f);

        float pi = 3.1416f;
        float A = (i * pi) / 300.0f;
        float r = 1.95f;

        float x = r * cos(A);
        float y = r * sin(A);

        float x_rot = x * cos(rotationAngle) - y * sin(rotationAngle);
        float y_rot = x * sin(rotationAngle) + y * cos(rotationAngle);

        float x_final = x_rot + cx + tx;
        float y_final = y_rot + cy + ty;

        glVertex2f(x_final, y_final);
    }

    glEnd();

    glLineWidth(3);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < 300; i++) {

        float pi = 3.1416f;
        float A = (i * pi) / 300.0f;
        float r = 1.95f;

        float x = r * cos(A);
        float y = r * sin(A);

        float x_rot = x * cos(rotationAngle) - y * sin(rotationAngle);
        float y_rot = x * sin(rotationAngle) + y * cos(rotationAngle);

        float x_final = x_rot + cx + tx;
        float y_final = y_rot + cy + ty;

        glVertex2f(x_final, y_final);
    }

    glEnd();



    //nicher thot er line
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(6.99f, 5.75f);
    glVertex2f(6.98f,5.83f);
    glVertex2f(6.98f,5.83f);
    glVertex2f(7.08f,5.95f);
    glVertex2f(7.08f,5.95f);
    glVertex2f(7.18,6.05f);
    glVertex2f(7.18,6.05f);
    glVertex2f(7.28f,6.16f);
    glVertex2f(7.28f,6.16f);
    glVertex2f(7.30f,6.18f);
    glVertex2f(7.30f,6.18f);
    glVertex2f(7.31f,6.23f);

    glEnd();
    //nicher thot er khali jyga
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(7.28f, 6.16f);
    glVertex2f(7.03f,6.11f);
    glVertex2f(6.93f,6.12f);
    glVertex2f(6.21f,5.67f);
    // glVertex2f(6.97f,5.75f);
    //  glVertex2f(6.90f,5.82f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(6.21f,5.67f);
    glVertex2f(6.99f,5.75f);
    glVertex2f(6.92f,5.82f);
    glVertex2f(7.30f,6.18f);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(7.24f, 6.27f);
    glVertex2f(7.07f,6.28f);
    glVertex2f(6.93f,6.12f);
    glVertex2f(7.03f,6.11f);
    glVertex2f(7.28f,6.16f);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(6.21f, 5.67f);
    glVertex2f(6.8f, 6.2f);
    glVertex2f(6.16f,6.94f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(6.8f, 6.2f);
    glVertex2f(6.21f, 5.67f);
    glVertex2f(7.19f,6.28f);
    glEnd();

    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0); // white fill
        float pi = 3.1416;
        float A = (i * pi) / 300; // only half circle
        float r = 0.09;
        float x = 7.2 + r * cos(A);
        float y = 6.2 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(3);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < 300; i++)
    {
        float pi = 3.1416;
        float A = (i * pi) / 300; // only half circle
        float r = 0.09;
        float x = 7.2 + r * cos(A);
        float y = 6.2 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();

    //nicher thot er line
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(6.99f, 5.75f);
    glVertex2f(6.98f,5.83f);
    glVertex2f(6.98f,5.83f);
    glVertex2f(7.08f,5.95f);
    glVertex2f(7.08f,5.95f);
    glVertex2f(7.18,6.05f);
    glVertex2f(7.18,6.05f);
    glVertex2f(7.28f,6.16f);
    glVertex2f(7.28f,6.16f);
    glVertex2f(7.30f,6.18f);
    glVertex2f(7.30f,6.18f);
    glVertex2f(7.31f,6.23f);

    glEnd();
    //nicher thot er khali jyga
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(7.28f, 6.16f);
    glVertex2f(7.03f,6.11f);
    glVertex2f(6.93f,6.12f);
    glVertex2f(6.21f,5.67f);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(6.21f,5.67f);
    glVertex2f(6.99f,5.75f);
    glVertex2f(6.92f,5.82f);
    glVertex2f(7.30f,6.18f);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(7.24f, 6.27f);
    glVertex2f(7.07f,6.28f);
    glVertex2f(6.93f,6.12f);
    glVertex2f(7.03f,6.11f);
    glVertex2f(7.28f,6.16f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(6.21f, 5.67f);
    glVertex2f(6.8f, 6.2f);
    glVertex2f(6.16f,6.94f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(6.8f, 6.2f);
    glVertex2f(6.21f, 5.67f);
    glVertex2f(7.19f,6.28f);
    glEnd();


    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0); // white fill
        float pi = 3.1416;
        float A = (i * pi) / 300; // only half circle
        float r = 0.09;
        float x = 7.2 + r * cos(A);
        float y = 6.2 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(3);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < 300; i++)
    {
        float pi = 3.1416;
        float A = (i * pi) / 300; // only half circle
        float r = 0.09;
        float x = 7.2 + r * cos(A);
        float y = 6.2 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();


    //SMILE RED HALF CIRCLE

    glBegin(GL_POLYGON);

    float angleOfRotationH1 = 160.0;
    float rotationAngleH1 = angleOfRotationH1 * (3.1416f / 180.0f);

    float txH1 = -0.225f;
    float tyH1 = -0.10f;


    float cxH1 = 6.78f;
    float cyH1 = 7.39f;

    float rH1 = 0.76f;

    for (int i = 0; i < 300; i++) {

        glColor3f(1.0f, 0.0f, 0.0f);

        float pi = 3.1416f;
        float AH1 = (i * pi) / 300.0f;

        float xH1 = rH1 * cos(AH1);
        float yH1 = rH1 * sin(AH1);

        // Rotate
        float xH1_rot = xH1 * cos(rotationAngleH1) - yH1 * sin(rotationAngleH1);
        float yH1_rot = xH1 * sin(rotationAngleH1) + yH1 * cos(rotationAngleH1);

        // Translate + center
        float xH1_final = xH1_rot + cxH1 + txH1;
        float yH1_final = yH1_rot + cyH1 + tyH1;

        glVertex2f(xH1_final, yH1_final);
    }

    glEnd();
    //HALF RED BORDER
    glLineWidth(3);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < 300; i++) {

        float pi = 3.1416f;
        float AH1 = (i * pi) / 300.0f;

        float xH1 = rH1 * cos(AH1);
        float yH1 = rH1 * sin(AH1);

        float xH1_rot = xH1 * cos(rotationAngleH1) - yH1 * sin(rotationAngleH1);
        float yH1_rot = xH1 * sin(rotationAngleH1) + yH1 * cos(rotationAngleH1);

        float xH1_final = xH1_rot + cxH1 + txH1;
        float yH1_final = yH1_rot + cyH1 + tyH1;

        glVertex2f(xH1_final, yH1_final);
    }
    glEnd();
    //MUKHER lal hasir plane edge border
    float x_start = rH1 * cos(0);
    float y_start = rH1 * sin(0);
    float x_end = rH1 * cos(3.1416f);
    float y_end = rH1 * sin(3.1416f);

    // Rotate
    float x_start_rot = x_start * cos(rotationAngleH1) - y_start * sin(rotationAngleH1);
    float y_start_rot = x_start * sin(rotationAngleH1) + y_start * cos(rotationAngleH1);

    float x_end_rot = x_end * cos(rotationAngleH1) - y_end * sin(rotationAngleH1);
    float y_end_rot = x_end * sin(rotationAngleH1) + y_end * cos(rotationAngleH1);

    x_start_rot += cxH1 + txH1;
    y_start_rot += cyH1 + tyH1;

    x_end_rot += cxH1 + txH1;
    y_end_rot += cyH1 + tyH1;

    glBegin(GL_LINES);
    glVertex2f(x_start_rot, y_start_rot);
    glVertex2f(x_end_rot, y_end_rot);
    glEnd();

    float txT = 0.02f;
    float tyT = -0.15f;

    float angle = 5.0f;
    glPushMatrix();
    glTranslatef(txT, tyT, 0.0f);

    glTranslatef(cx, cy, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-cx, -cy, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(7.33f, 7.3f);
    glVertex2f(6.73f, 7.42f);
    glVertex2f(7.13f, 6.89f);
    glEnd();

    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(7.33f, 7.3f);
    glVertex2f(6.73f, 7.42f);
    glVertex2f(7.13f, 6.89f);
    glEnd();

    glPopMatrix();

    //UPPER THOT
    glLineWidth(3);
    glBegin(GL_POLYGON);

    float rotAngle2_deg = -75.0f;
    float rotAngle2_rad = rotAngle2_deg * (3.1416f / 180.0f);


    float transX2 = -0.05f;
    float transY2 = -.19f;


    float centerX2 = 7.61f;
    float centerY2 = 7.74f;

    for (int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0);

        float pi = 3.1416f;
        float A = (i * pi) / 300.0f;
        float r = 0.33f;


        float ox = r * cos(A);
        float oy = r * sin(A);


        float rx = ox * cos(rotAngle2_rad) - oy * sin(rotAngle2_rad);
        float ry = ox * sin(rotAngle2_rad) + oy * cos(rotAngle2_rad);


        float finalX = rx + centerX2 + transX2;
        float finalY = ry + centerY2 + transY2;

        glVertex2f(finalX, finalY);
    }

    glEnd();
    //THOTER BORDER
    glLineWidth(3);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < 300; i++)
    {
        float pi = 3.1416f;
        float A = (i * pi) / 300.0f;
        float r = 0.33f;

        float ox = r * cos(A);
        float oy = r * sin(A);

        float rx = ox * cos(rotAngle2_rad) - oy * sin(rotAngle2_rad);
        float ry = ox * sin(rotAngle2_rad) + oy * cos(rotAngle2_rad);

        float finalX = rx + centerX2 + transX2;
        float finalY = ry + centerY2 + transY2;

        glVertex2f(finalX, finalY);
    }
    glEnd();
    glBegin(GL_POLYGON);//majhe khali chilo seta fill koreci
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(6.66f, 7.55f);
    glVertex2f(6.73f, 7.27f);
    glVertex2f(7.07f, 7.25f);
    glVertex2f(7.3f, 7.22f);
    glVertex2f(7.7f, 7.26f);
    glVertex2f(7.75f, 7.72f);

    glEnd();

    //EYE(
    float I_x = 6.22, I_y = 9.29;
    float J_x = 7.08, J_y = 8.41;   // Point J (major axis reference)
    float K_x = 6.6, K_y = 8.55;  // Point K (minor axis reference)

    // major (vertical) & minor (horizontal)
    float a = sqrt(pow(J_x - I_x, 2) + pow(J_y - I_y, 2)); // semi-major
    float b = sqrt(pow(K_x - I_x, 2) + pow(K_y - I_y, 2)); // semi-minor

    float scale = 0.5;
    a *= scale;
    b *= scale;

    // ellipse center at I
    float centerX = I_x;
    float centerY = I_y;

    // TRANSLATION
    float tx1 = 0.325;
    float ty1 = -0.55;

    centerX += tx1;
    centerY += ty1;

    float angleDeg = 52.0;
    float phi = angleDeg * 3.1416 / 180.0;

    glColor3f(1.0, 1.0, 1.0);   // White fill
    glBegin(GL_POLYGON);

    for(int i = 0; i < 360; i++)
    {
        float theta = i * 3.1416 / 180.0;

        float x0 = b * cos(theta);
        float y0 = a * sin(theta);

        float xr = x0 * cos(phi) - y0 * sin(phi);
        float yr = x0 * sin(phi) + y0 * cos(phi);

        glVertex2f(centerX + xr, centerY + yr);
    }

    glEnd();

    // BLACK BORDER

    glColor3f(0, 0, 0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);

    for(int i = 0; i < 360; i++)
    {
        float theta = i * 3.1416 / 180.0;

        float x0 = b * cos(theta);
        float y0 = a * sin(theta);

        float xr = x0 * cos(phi) - y0 * sin(phi);
        float yr = x0 * sin(phi) + y0 * cos(phi);

        glVertex2f(centerX + xr, centerY + yr);
    }
    glEnd();

    //black part
    float O1_x = 6.83f, O1_y = 8.81f;  // ellipse center
    float P1_x = 7.09f, P1_y = 8.48f;  // point on major axis
    float Q1_x = 6.96f, Q1_y = 8.50f;  // point on minor axis

    float a2 = sqrt(pow(P1_x - O1_x, 2) + pow(P1_y - O1_y, 2));  // semi-major
    float b2 = sqrt(pow(Q1_x - O1_x, 2) + pow(Q1_y - O1_y, 2));  // semi-minor

    float scale2 = 0.5f;
    a2 *= scale2;
    b2 *= scale2;


    // Translation
    float tx2 = -.7f;
    float ty2 = 0.81f;
    centerX2 += tx2;
    centerY2 += ty2;

    float angleDeg2 = 30.0f;
    float phi2 = angleDeg2 * 3.1416f / 180.0f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);

    for(int i = 0; i < 360; i++)
    {
        float theta = i * 3.1416f / 180.0f;

        float x0 = b2 * cos(theta);
        float y0 = a2 * sin(theta);

        float xr = x0 * cos(phi2) - y0 * sin(phi2);
        float yr = x0 * sin(phi2) + y0 * cos(phi2);

        glVertex2f(centerX2 + xr, centerY2 + yr);
    }

    glEnd();
    //CHOKHER white part

    float R3_x = 6.97f, R3_y = 8.69f;  // ellipse center reference
    float S3_x = 7.07f, S3_y = 8.54f;  // point on major axis
    float T3_x = 7.02f, T3_y = 8.57f;  // point on minor axis

    float a3 = sqrt(pow(S3_x - R3_x, 2) + pow(S3_y - R3_y, 2));  // semi-major
    float b3 = sqrt(pow(T3_x - R3_x, 2) + pow(T3_y - R3_y, 2));  // semi-minor

    float scale3 = 0.5f;
    a3 *= scale3;
    b3 *= scale3;

    float centerX3 = R3_x;
    float centerY3 = R3_y;

    float tx3 = -0.0099f;
    float ty3 = -0.179f;
    centerX3 += tx3;
    centerY3 += ty3;

    float angleDeg3 = 25.0f;
    float phi3 = angleDeg3 * 3.1416f / 180.0f;

    glColor3f(1.0f, 1.0f, 1.0f);  // white fill
    glBegin(GL_POLYGON);

    for(int i = 0; i < 360; i++)
    {
        float theta = i * 3.1416f / 180.0f;

        float x0 = b3 * cos(theta);
        float y0 = a3 * sin(theta);

        // rotate
        float xr = x0 * cos(phi3) - y0 * sin(phi3);
        float yr = x0 * sin(phi3) + y0 * cos(phi3);

        // translate + center
        glVertex2f(centerX3 + xr, centerY3 + yr);
    }

    glEnd();

    //muuchstac
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(5.56f, 8.26f);
    glVertex2f(6.39f, 7.98f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(6.3f, 7.82f);
    glVertex2f(5.16f, 7.8579f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(6.27f, 7.63f);
    glVertex2f(5.22f, 7.37f);
    glEnd();


    //mouth
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(7.665f, 7.229f);//u
    glVertex2f(7.396f, 7.20f);//v
    glVertex2f(7.396f, 7.20f);
    glVertex2f(7.147f, 7.21f);//w
    glVertex2f(7.147f, 7.21f);
    glVertex2f(7.13f, 7.23f);//z
    glVertex2f(7.13, 7.23f);
    glVertex2f(7.11f, 7.25f);//A1
    glVertex2f(7.11f, 7.25f);
    glVertex2f(6.9f, 7.27f);
    glVertex2f(6.9f, 7.27f);
    glVertex2f(6.77, 7.28f);
    glVertex2f(6.77, 7.28f);
    glVertex2f(6.65f, 7.29f);
    glEnd();

    // RED SMILE FILL
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);

    //  Curve A (first)
    float x0_A = 6.20,    y0_A = 6.82;
    float x1_A = 6.67,    y1_A = 6.41;
    float x2_A = 7.18,    y2_A = 6.33;
    float txA  = -0.1f,   tyA  = -0.18f;

    for (float t = 0; t <= 1.0f; t += 0.01f) {
        float x = (1 - t)*(1 - t)*x0_A + 2*(1 - t)*t*x1_A + t*t*x2_A;
        float y = (1 - t)*(1 - t)*y0_A + 2*(1 - t)*t*y1_A + t*t*y2_A;
        glVertex2f(x + txA, y + tyA);
    }

    //Curve B (second)
    float x0_B = 7.12978f, y0_B = 6.89011f;
    float x1_B = 7.1489f,  y1_B = 6.60329f;
    float x2_B = 7.07242f, y2_B = 6.28461f;
    float txB  = 0.05f,    tyB  = -0.09f;

    for (float t = 0; t <= 1.0f; t += 0.01f) {
        float x = (1 - t)*(1 - t)*x0_B + 2*(1 - t)*t*x1_B + t*t*x2_B;
        float y = (1 - t)*(1 - t)*y0_B + 2*(1 - t)*t*y1_B + t*t*y2_B;
        glVertex2f(x + txB, y + tyB);
    }

    glEnd();


    // BLACK BORDER
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);

    // Curve A border
    for (float t = 0; t <= 1.0f; t += 0.01f) {
        float x = (1 - t)*(1 - t)*x0_A + 2*(1 - t)*t*x1_A + t*t*x2_A;
        float y = (1 - t)*(1 - t)*y0_A + 2*(1 - t)*t*y1_A + t*t*y2_A;
        glVertex2f(x + txA, y + tyA);
    }

    // Curve B border
    for (float t = 0; t <= 1.0f; t += 0.01f) {
        float x = (1 - t)*(1 - t)*x0_B + 2*(1 - t)*t*x1_B + t*t*x2_B;
        float y = (1 - t)*(1 - t)*y0_B + 2*(1 - t)*t*y1_B + t*t*y2_B;
        glVertex2f(x + txB, y + tyB);
    }

    glEnd();
    //pet er nil color fill

    // right leg color

    glColor3f(0.6f, 0.8f, 0.9f);
    glBegin(GL_POLYGON);


    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
            (1 - t)*(1 - t)*5.56f +
            2*(1 - t)*t*5.45f +
            t*t*5.60f;

        float y =
            (1 - t)*(1 - t)*3.42f +
            2*(1 - t)*t*3.02f +
            t*t*2.59f;

        glVertex2f(x, y);
    }

    for(float t = 1.0f; t >= 0.0f; t -= 0.02f)
    {
        float x =
            (1 - t)*(1 - t)*7.14f +
            2*(1 - t)*t*7.29f +
            t*t*6.75f;

        float y =
            (1 - t)*(1 - t)*5.09f +
            2*(1 - t)*t*3.93f +
            t*t*2.59f;

        glVertex2f(x, y);
    }

    glEnd();

    //pet er kichu jayga
    glColor3f(0.6,0.8,0.9);
    glBegin(GL_POLYGON);
    glVertex2f(4.43,4.77);
    glVertex2f(5.93,4.77);
    glVertex2f(5.93,3.27);
    glVertex2f(4.43,3.27);
    glEnd();

    // right leg color

    glColor3f(0.6f, 0.8f, 0.9f);
    glBegin(GL_POLYGON);


    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*5.56f +
        2*(1 - t)*t*5.45f +
        t*t*5.60f;

        float y =
        (1 - t)*(1 - t)*3.42f +
        2*(1 - t)*t*3.02f +
        t*t*2.59f;

        glVertex2f(x, y);
    }

    for(float t = 1.0f; t >= 0.0f; t -= 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*7.14f +
        2*(1 - t)*t*7.29f +
        t*t*6.75f;

        float y =
        (1 - t)*(1 - t)*5.09f +
        2*(1 - t)*t*3.93f +
        t*t*2.59f;

        glVertex2f(x, y);
    }

    glEnd();
    //pet er boro sada color fill
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);

        // Curve 1
        for(float t = 0.0f; t <= 1.0f; t += 0.02f)
        {
            float x =
            (1 - t)*(1 - t)*5.73f +
            2*(1 - t)*t*5.37f +
            t*t*5.50f;

            float y =
            (1 - t)*(1 - t)*5.49f +
            2*(1 - t)*t*4.93f +
            t*t*4.89f;

            glVertex2f(x, y);
        }

        // Bottom straight line
        glVertex2f(5.50f, 4.16f);
        glVertex2f(6.75f, 4.93f);

        //Curve 2 (reverse direction)
        for(float t = 1.0f; t >= 0.0f; t -= 0.02f)
        {
            float x =
            (1 - t)*(1 - t)*7.14f +
            2*(1 - t)*t*7.29f +
            t*t*6.75f;

            float y =
            (1 - t)*(1 - t)*5.09f +
            2*(1 - t)*t*4.93f +
            t*t*4.89f;

            glVertex2f(x, y);
        }

        //Top straight line
        glVertex2f(7.14f, 5.09f);
        glVertex2f(5.73f, 5.49f);

        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(7.1f, 4.6385f);
        glVertex2f(5.78f,4.81f)  ;
        glVertex2f(5.12f, 5.3f);
        glVertex2f(6.69f,5.48f)  ;
        glEnd();

        //bellly...
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(7.1f, 4.6385f);
        glVertex2f(5.78f,4.81f)  ;
        glVertex2f(5.12f, 5.3f);
        glVertex2f(6.69f,5.48f)  ;
        glEnd();

        glBegin(GL_POLYGON);

        float angleOfRotationBelly = 118.5f;
        float rotationAngleBelly = angleOfRotationBelly * (3.1416f / 180.0f);

        float txBelly = 0.37f;
        float tyBelly = -0.03f;

        float cxBelly = 6.16f;
        float cyBelly = 4.29f;

        float rBelly = 1.05f;

        for (int i = 0; i < 300; i++) {

            glColor3f(1.0,1.0,1.0);

            float pi = 3.1416f;
            float theta = (i * pi) / 300.0f;

            float xBelly = rBelly * cos(theta);
            float yBelly = rBelly * sin(theta);

            // Rotate
            float x_rotBelly = xBelly * cos(rotationAngleBelly) - yBelly * sin(rotationAngleBelly);
            float y_rotBelly = xBelly * sin(rotationAngleBelly) + yBelly * cos(rotationAngleBelly);

            // Translate + center
            float x_finalBelly = x_rotBelly + cxBelly + txBelly;
            float y_finalBelly = y_rotBelly + cyBelly + tyBelly;

            glVertex2f(x_finalBelly, y_finalBelly);
        }

        glEnd();

        // Black border
        glLineWidth(3);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_STRIP);

        for (int i = 110; i <= 300; i++) {

            float pi = 3.1416f;
            float theta = (i * pi) / 300.0f;

            float xBelly = rBelly * cos(theta);
            float yBelly = rBelly * sin(theta);

            float x_rotBelly = xBelly * cos(rotationAngleBelly) - yBelly * sin(rotationAngleBelly);
            float y_rotBelly = xBelly * sin(rotationAngleBelly) + yBelly * cos(rotationAngleBelly);

            float x_finalBelly = x_rotBelly + cxBelly+ txBelly;
            float y_finalBelly = y_rotBelly + cyBelly + tyBelly;

            glVertex2f(x_finalBelly, y_finalBelly);
        }

        glEnd();


        glLineWidth(3);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 300; i++)
        {
            glColor3f(1.0, 1.0, 1.0); // white fill
            float pi = 3.1416;
            float A = (i * 2*pi) / 300; // only half circle
            float r = 0.75;
            float x = 6.38 + r * cos(A);
            float y = 4.04 + r * sin(A);
            glVertex2f(x, y);
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_POLYGON);
        for(int i = 0; i < 300; i++)
        {
            glColor3f(1.0, 1.0, 1.0); // white fill
            float pi = 3.1416;
            float A = (i * 2*pi) / 300; // only half circle
            float r = 0.45;
            float x = 6.67 + r * cos(A);
            float y = 3.73 + r * sin(A);
            glVertex2f(x, y);
        }
        glEnd();



        glLineWidth(3.0f);
        glColor3f(0.0f, 0.0f, 0.0f);

        glBegin(GL_LINE_STRIP);

        for(float t = 0.0f; t <= 1.0f; t += 0.02f)
        {
            float x =
            (1 - t)*(1 - t)*5.73f +
            2*(1 - t)*t*5.37f +
            t*t*5.50f;

            float y =
            (1 - t)*(1 - t)*5.49f +
            2*(1 - t)*t*4.37f +
            t*t*4.16f;

            glVertex2f(x, y);
        }

        glEnd();



        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(7.14f,5.06f);
        glVertex2f(6.78f,5.08f)  ;
        glVertex2f(6.8f, 3.97f);
        glVertex2f(6.97f,3.97f)  ;
        glVertex2f(7.16f,4.06f);
        glEnd();

        //pocket

        glBegin(GL_POLYGON);

        float pi = 3.1416f;
        float rotationAnglePocket = 180.0f * pi / 180.0f;

        float cxPocket = 6.23f;
        float cyPocket = 4.24f;
        float rPocket  = 1.2;

        float txPocket = 0.8f;
        float tyPocket = 0.5f;

        glColor3f(1.0f, 1.0f, 1.0f);


        for (int i = 0; i <= 75; i++) {
            float theta = (i * pi) / 150.0f;

            float x = rPocket * cos(theta);
            float y = rPocket * sin(theta);

            float xr = x * cos(rotationAnglePocket) - y * sin(rotationAnglePocket);
            float yr = x * sin(rotationAnglePocket) + y * cos(rotationAnglePocket);

            glVertex2f(xr + cxPocket + txPocket,
                       yr + cyPocket + tyPocket);
        }

        // center point
        glVertex2f(cxPocket + txPocket, cyPocket + tyPocket);

        glEnd();

        glLineWidth(3);
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= 75; i++) {
            float theta = (i * pi) / 150.0f;

            float x = rPocket * cos(theta);
            float y = rPocket * sin(theta);

            float xr = x * cos(rotationAnglePocket) - y * sin(rotationAnglePocket);
            float yr = x * sin(rotationAnglePocket) + y * cos(rotationAnglePocket);

            glVertex2f(xr + cxPocket + txPocket,
                       yr + cyPocket + tyPocket);
        }
        glEnd();

        glBegin(GL_LINES);

        // edge 1
        glVertex2f(cxPocket + txPocket, cyPocket + tyPocket);
        glVertex2f(cxPocket + txPocket + rPocket * cos(rotationAnglePocket),
                   cyPocket + tyPocket + rPocket * sin(rotationAnglePocket));

        glEnd();
        glLineWidth(3);
        glColor3f(0.0f,0.0f,0.0f);


        glBegin(GL_LINE_STRIP);
        glVertex2f(7.0f, 4.74f);
        glVertex2f(7.15f, 4.74f);


        glEnd();

        //pet er nil ektu baki seta
        glBegin(GL_POLYGON);
        glColor3f(0.6f, 0.8f, 0.9f);
        glVertex2f(4.43, 4.67f);
        glVertex2f(5.1f,5.43f)  ;
        glVertex2f(5.715f, 5.47f);
        glVertex2f(5.44f,4.59f)  ;
        glEnd();

    //belt er line
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(6.99f, 5.75f);
    glVertex2f(4.73325f,5.50063f)  ;
    glVertex2f(5.12f, 5.3f);
    glVertex2f(6.69f,5.48f)  ;
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(6.99f, 5.75f);
    glVertex2f(4.73325f,5.50063f)  ;
    glVertex2f(5.12f, 5.3f);
    glVertex2f(6.69f,5.48f)  ;
    glEnd();

    //BELL
    float centerXB = 7.03f;
    float centerYB = 5.41f;
    float r = 0.35f;
   // float pi=3.1416;

    glColor3f(1.0f, 0.84f, 0.0f);   // golden color (R=1, G=0.84, B=0)
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++) {
        float B = (i * 2 * pi) / 300.0f;
        float x = centerXB + r * cos(B);
        float y = centerYB + r * sin(B);
        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(3);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 300; i++) {
        float B = (i * 2 * pi) / 300.0f;
        float x = centerXB + r * cos(B);
        float y = centerYB + r * sin(B);
        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(6.69f, 5.48f);
    glVertex2f(7.13f, 5.74f);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(6.68f, 5.37f);    // x, y
    glVertex2f(7.22f, 5.69f);    // x, y
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(7.35f, 5.53f);    // x, y
    glVertex2f(7.18f, 5.45f);    // x, y
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(7.18f, 5.45f);    // x, y
    glVertex2f(7.37f, 5.4f);    // x, y
    glEnd();

    //right leg


    //RIGHT LEG
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*7.14f +
        2*(1 - t)*t*7.29f +
        t*t*6.75f;

        float y =
        (1 - t)*(1 - t)*5.09f +
        2*(1 - t)*t*3.93f +
        t*t*2.59f;

        glVertex2f(x, y);
    }

    glEnd();
    //juta
    //colour
    glPushMatrix();
    glRotatef(legAngle, 0, 0, -1);
    glTranslatef(0.05f, 0.0f, 0.0f); // move to hip
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);

    //Right straight line
    glVertex2f(6.93f, 2.64f);
    glVertex2f(6.89f, 1.99f);

    //Lower Bezier
    for(float t = 1.0f; t >= 0.0f; t -= 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*6.89f +
        2*(1 - t)*t*5.78f +
        t*t*5.23f;

        float y =
        (1 - t)*(1 - t)*1.99f +
        2*(1 - t)*t*1.75f +
        t*t*2.23f;

        glVertex2f(x, y);
    }

    // Left straight line
    glVertex2f(5.23f, 2.23f);
    glVertex2f(5.54f, 2.5f);

    glEnd();
    //right circle
    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0); // white fill
        float pi = 3.1416;
        float A = (i *2* pi) / 300;
        float r = 0.34;
        float x = 6.84+ r * cos(A);
        float y = 2.35 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();

    // Black border only on the curved edge
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(int i = 230; i <= 400; i++)   // 300 steps → 20–90 mapped
    {
        float pi = 3.1416f;
        float A = (i*2 * pi) / 300.0f;

        float r = 0.34f;
        float x = 6.84f + r * cos(A);
        float y = 2.35f + r * sin(A);

        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*6.93 +
        2*(1 - t)*t*6.29f +
        t*t*5.54f;

        float y =
        (1 - t)*(1 - t)*2.69f +
        2*(1 - t)*t*2.51f +
        t*t*2.61f;

        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*6.89f +
        2*(1 - t)*t*5.78f +
        t*t*5.23f;

        float y =
        (1 - t)*(1 - t)*1.99f +
        2*(1 - t)*t*1.75f +
        t*t*2.23f;

        glVertex2f(x, y);
    }
    glEnd();
    //left circle
    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0); // white fill
        float pi = 3.1416;
        float A = (i *2* pi) / 300;
        float r = 0.27;
        float x = 5.5+ r * cos(A);
        float y = 2.35 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();

    // Black border only on the curved edge
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(int i =60; i <= 230; i++)   // 300 steps → 20–90 mapped
    {
        float pi = 3.1416f;
        float A = (i*2 * pi) / 300.0f;

        float r = 0.27f;
        float x = 5.5f + r * cos(A);
        float y = 2.35f + r * sin(A);

        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*5.56f +
        2*(1 - t)*t*5.45f +
        t*t*5.60f;

        float y =
        (1 - t)*(1 - t)*3.42 +
        2*(1 - t)*t*3.02f +
        t*t*2.59f;

        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    //left leg
    //left leg


    glLineWidth(4.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);
    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t) * (1 - t) * 4.43f +
        2 * (1 - t) * t * 4.08f +
        t * t * 4.55f;

        float y =
        (1 - t) * (1 - t) * 4.77f +
        2 * (1 - t) * t * 3.13f +
        t * t * 2.09f;

        glVertex2f(x, y);
    }
    glEnd();


    //pa colour
    glColor3f(0.6f, 0.8f, 0.9f);   // WHITE fill
    glBegin(GL_POLYGON);

    // Curve 1
    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*4.43f +
        2*(1 - t)*t*4.08f +
        t*t*4.55f;

        float y =
        (1 - t)*(1 - t)*4.77f +
        2*(1 - t)*t*3.13f +
        t*t*2.09f;

        glVertex2f(x, y);
    }

    // Bottom straight line
    glVertex2f(4.55f, 2.09f);
    glVertex2f(6.00f, 2.36f);

    // Curve 2 (reverse direction)
    for(float t = 1.0f; t >= 0.0f; t -= 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*6.20f +
        2*(1 - t)*t*5.95f +
        t*t*6.00f;

        float y =
        (1 - t)*(1 - t)*3.03f +
        2*(1 - t)*t*2.51f +
        t*t*2.36f;

        glVertex2f(x, y);
    }

    // Top straight line
    glVertex2f(6.20f, 3.03f);
    glVertex2f(4.43f, 4.77f);

    glEnd();
    //juta
    //colour juta

    glPushMatrix();
    glTranslatef(-0.05f, 0.0f, 0.0f);
    glRotatef(legAngle, 0, 0, 1);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);

    // Right straight line
    glVertex2f(6.0f, 2.25);
    glVertex2f(6.2f, 1.73f);

    //  Lower Bezier curve
    for(float t=1.0f; t>=0.0f; t-=0.02f)
    {
        float x = (1-t)*(1-t)*4.3f + 2*(1-t)*t*5.26f + t*t*6.2f;

        float y = (1-t)*(1-t)*2.0f + 2*(1-t)*t*1.52f + t*t*1.73f;

        glVertex2f(x,y);
    }

    //Left straight line
    glVertex2f(4.3f, 1.95f);
    glVertex2f(4.49f, 2.56f);

    glEnd();


    //left side circle
    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0); // white fill
        float pi = 3.1416;
        float A = (i *2* pi) / 300;
        float r = 0.34;
        float x = 4.43 + r * cos(A);
        float y = 2.3 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();

    // Black border only on the curved edge
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(int i = 67; i <= 230; i++)   // 300 steps → 20–90 mapped
    {
        float pi = 3.1416f;
        float A = (i*2 * pi) / 300.0f;

        float r = 0.34f;
        float x = 4.43f + r * cos(A);
        float y = 2.3f + r * sin(A);

        glVertex2f(x, y);
    }
    glEnd();
    //curve
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*4.49f +
        2*(1 - t)*t*5.32f +
        t*t*6.0f;

        float y =
        (1 - t)*(1 - t)*2.65f +
        2*(1 - t)*t*2.2f +
        t*t*2.4f;

        glVertex2f(x, y);
    }

    glEnd();

    //right side circle
    glLineWidth(3);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        float pi = 3.1416;
        float A = (i *2* pi) / 300;
        float r = 0.34;
        float x = 6.15 + r * cos(A);
        float y = 2.09 + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();

    // Black border only on the curved edge
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(int i = 225; i <= 410; i++)
    {
        float pi = 3.1416f;
        float A = (i*2 * pi) / 300.0f;

        float r = 0.34f;
        float x = 6.15f + r * cos(A);
        float y = 2.09f + r * sin(A);

        glVertex2f(x, y);
    }
    glEnd();
    //curve
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*4.3f +
        2*(1 - t)*t*5.26f +
        t*t*6.2f;

        float y =
        (1 - t)*(1 - t)*2.0f +
        2*(1 - t)*t*1.52f +
        t*t*1.73f;

        glVertex2f(x, y);
    }

    glEnd();

    //jutar uporer curve
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for(float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        float x =
        (1 - t)*(1 - t)*6.2f +
        2*(1 - t)*t*5.95f +
        t*t*6.0f;

        float y =
        (1 - t)*(1 - t)*3.03f +
        2*(1 - t)*t*2.51f +
        t*t*2.36f;

        glVertex2f(x, y);
    }

    glEnd();

    //tail
    glLineWidth(4.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(4.25, 3.64f);
    glVertex2f(4.00f, 3.72f);
    glEnd();

    //dim
    glLineWidth(3);
    glBegin(GL_POLYGON);

    for(int i = 0; i < 300; i++)
    {
        glColor3f(1.0, 0.0, 0.0);
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 300.0f;
        float r = 0.25f;

        float x = 3.80 + r * cos(A);
        float y = 3.75 + r * sin(A);

        glVertex2f(x, y);
    }

    glEnd();

    glLineWidth(3);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);

    for(int i = 0; i < 300; i++)
    {
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 300.0f;
        float r = 0.25f;

        float x = 3.80 + r * cos(A);
        float y = 3.750 + r * sin(A);

        glVertex2f(x, y);
    }

    glEnd();
    glPopMatrix();
    glFlush();
}