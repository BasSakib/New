/*
 * =============================================================
 *  DORAEMON'S TREAT HUNT  —  FIXED & COMPLETE VERSION
 *  CSC4118: Computer Graphics — AIUB Fall 2025-2026
 *  Section N | Group 1
 *  Members: Tasmia Amin, Orpyta Karmokar Aupy, Sadia Ahmed
 *  Supervisor: Tonny Shekha Kar
 * =============================================================
 *
 *  BUILD — Windows (MinGW):
 *    g++ doraemon_treat_hunt.cpp -o doraemon.exe -lfreeglut -lopengl32 -lglu32
 *
 *  BUILD — Linux:
 *    g++ doraemon_treat_hunt.cpp -o doraemon -lGL -lGLU -lglut -lm
 *
 *  BUILD — macOS:
 *    g++ doraemon_treat_hunt.cpp -o doraemon -framework OpenGL -framework GLUT
 *
 *  CONTROLS:
 *    Left / Right Arrow  — Move Doraemon
 *    Up Arrow            — Jump (only when on the ground)
 *    Mouse               — Click buttons on menus
 * =============================================================
 *
 *  FIXED ISSUES vs previous version:
 *   1.  Jump physics — proper gravity each frame, single-jump guard,
 *       landing snaps exactly to GROUND_Y.
 *   2.  World scrolling — character stays on screen; worldOffset
 *       advances only when Doraemon approaches screen edges.
 *   3.  Collision detection — AABB uses per-type correct bounding
 *       boxes matching drawn size; hit-immunity timer works properly.
 *   4.  Collectibles — once taken they are permanently flagged;
 *       no re-collection bug.
 *   5.  Health — clamped [0,3]; game switches to ENDSCREEN instantly
 *       when health reaches 0.
 *   6.  Win condition — triggered the moment cakes == MAX_CAKES.
 *   7.  Level restart — ALL state (offset, position, physics,
 *       obstacles, collectibles) reset cleanly.
 *   8.  Obstacle patrol — bounds are world-space so obstacles never
 *       fly off to infinity regardless of scroll position.
 *   9.  End screen buttons — GLUT Y-flip applied correctly so clicks
 *       land on the right buttons.
 *  10.  Restart button relaunches the same level the player was on.
 * =============================================================
 */

#ifdef _WIN32
#  include <windows.h>
#endif
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <vector>

// ─────────────────────────────────────────────────────────────
//  CONSTANTS
// ─────────────────────────────────────────────────────────────
static const int   WIN_W        = 800;
static const int   WIN_H        = 500;
static const float PI_F         = 3.14159265f;
static const float GROUND_Y     = 80.0f;
static const float GRAVITY      = -0.55f;
static const float JUMP_VY      = 13.0f;
static const float MOVE_SPEED   = 3.5f;
static const int   MAX_CAKES    = 5;
static const int   HIT_IMMUNITY = 60;   // frames of invincibility after hit
static const float WORLD_LEN    = 2400.0f;
static const float CHAR_W       = 60.0f;
static const float CHAR_H       = 110.0f;

// ─────────────────────────────────────────────────────────────
//  GAME STATE
// ─────────────────────────────────────────────────────────────
enum GameState { HOME, LEVEL1, LEVEL2, LEVEL3, ENDSCREEN };
GameState gState    = HOME;
GameState lastLevel = LEVEL1;
bool      gWon      = false;

// ─────────────────────────────────────────────────────────────
//  WORLD
// ─────────────────────────────────────────────────────────────
float worldOffset = 0.0f;

// screen-x from world-x
inline float sx(float wx){ return wx - worldOffset; }

// ─────────────────────────────────────────────────────────────
//  DORAEMON STATE
// ─────────────────────────────────────────────────────────────
float dX = 220.0f;
float dY = GROUND_Y;
float dVY = 0.0f;
bool  onGround  = true;
int   health    = 3;
int   cakes     = 0;
float legAngle  = 0.0f;
float legSwing  = 1.0f;
bool  kLeft = false, kRight = false;
bool  hitActive = false;
int   hitFrames = 0;

// ─────────────────────────────────────────────────────────────
//  DATA STRUCTURES
// ─────────────────────────────────────────────────────────────
struct Collectible { float wx,wy; bool isHeart,taken; };
std::vector<Collectible> gCollect;

// type: 0=stone 1=log 2=ball 3=mouse 4=spiky
struct Obstacle {
    float wx,wy,vx,phase,angle;
    float minWX,maxWX;
    int   type;
    bool  active;
};
std::vector<Obstacle> gObs;

struct ManholeFire { float wx,height,maxH,speed; bool growing; };
std::vector<ManholeFire> gFire;

std::vector<float> gLamps;   // world-x of lamp posts

// ─────────────────────────────────────────────────────────────
//  AABB HELPERS
// ─────────────────────────────────────────────────────────────
bool aabb(float ax,float ay,float aw,float ah,
          float bx,float by,float bw,float bh){
    return ax<bx+bw && ax+aw>bx && ay<by+bh && ay+ah>by;
}

void charBox(float&x,float&y,float&w,float&h){
    x=dX-CHAR_W*.5f; y=dY; w=CHAR_W; h=CHAR_H;
}

// Per-type bounding boxes (screen-space)
void obsBox(int type,float osx,float osy,float&bx,float&by,float&bw,float&bh){
    switch(type){
        case 0: bx=osx-22; by=osy;    bw=44;  bh=28;  break; // stone
        case 1: bx=osx-28; by=osy;    bw=56;  bh=30;  break; // log
        case 2: bx=osx-15; by=osy;    bw=30;  bh=30;  break; // ball
        case 3: bx=osx-19; by=osy;    bw=38;  bh=50;  break; // mouse
        case 4: bx=osx-22; by=osy;    bw=44;  bh=38;  break; // spiky
        default:bx=osx-20; by=osy;    bw=40;  bh=40;  break;
    }
}

// ─────────────────────────────────────────────────────────────
//  DRAWING PRIMITIVES
// ─────────────────────────────────────────────────────────────
void fillEllipse(float cx,float cy,float rx,float ry,
                 float r,float g,float b,int seg=36){
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);
    for(int i=0;i<=seg;i++){
        float a=2*PI_F*i/seg;
        glVertex2f(cx+cosf(a)*rx, cy+sinf(a)*ry);
    }
    glEnd();
}
void fillCircle(float cx,float cy,float r2,float r,float g,float b,int seg=36){
    fillEllipse(cx,cy,r2,r2,r,g,b,seg);
}
void fillRect(float x,float y,float w,float h,float r,float g,float b){
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(x,y);glVertex2f(x+w,y);glVertex2f(x+w,y+h);glVertex2f(x,y+h);
    glEnd();
}
void fillTri(float x1,float y1,float x2,float y2,float x3,float y3,
             float r,float g,float b){
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);glVertex2f(x2,y2);glVertex2f(x3,y3);
    glEnd();
}
void lineLoop(float x,float y,float w,float h,float r,float g,float b,float lw=2){
    glColor3f(r,g,b);glLineWidth(lw);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x,y);glVertex2f(x+w,y);glVertex2f(x+w,y+h);glVertex2f(x,y+h);
    glEnd();
}

// ─────────────────────────────────────────────────────────────
//  TEXT
// ─────────────────────────────────────────────────────────────
void txt18(float x,float y,const char*s,float r=1,float g=1,float b=1){
    glColor3f(r,g,b);glRasterPos2f(x,y);
    for(const char*c=s;*c;c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*c);
}
void txt12(float x,float y,const char*s,float r=1,float g=1,float b=1){
    glColor3f(r,g,b);glRasterPos2f(x,y);
    for(const char*c=s;*c;c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*c);
}
void txtBig(float x,float y,const char*s,float r=1,float g=1,float b=1){
    glColor3f(r,g,b);glRasterPos2f(x,y);
    for(const char*c=s;*c;c++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
}

// ─────────────────────────────────────────────────────────────
//  BUTTON
// ─────────────────────────────────────────────────────────────
void drawButton(float x,float y,float w,float h,const char*lbl,
                float br=0.15f,float bg=0.45f,float bb=0.85f){
    fillRect(x+4,y-4,w,h,0,0,0);          // shadow
    fillRect(x,y,w,h,br,bg,bb);
    lineLoop(x,y,w,h,1,1,1,2);
    float tw=strlen(lbl)*10.5f;
    txt18(x+(w-tw)*.5f,y+h*.5f-7,lbl);
}

// ─────────────────────────────────────────────────────────────
//  SKY / GROUND
// ─────────────────────────────────────────────────────────────
void drawSky1(){
    glBegin(GL_QUADS);
    glColor3f(.55f,.82f,1);glVertex2f(0,WIN_H);
    glColor3f(.55f,.82f,1);glVertex2f(WIN_W,WIN_H);
    glColor3f(.75f,.93f,1);glVertex2f(WIN_W,200);
    glColor3f(.75f,.93f,1);glVertex2f(0,200);
    glEnd();
    fillCircle(700,440,38,1,.95f,.35f); fillCircle(700,440,30,1,.98f,.55f);
    auto cloud=[](float cx,float cy){
        fillEllipse(cx,cy,42,20,1,1,1);
        fillEllipse(cx-32,cy-4,26,18,1,1,1);
        fillEllipse(cx+32,cy-4,26,18,1,1,1);
        fillEllipse(cx,cy+10,30,14,1,1,1);
    };
    cloud(130,430);cloud(400,415);cloud(610,425);
}
void drawSky2(){
    glBegin(GL_QUADS);
    glColor3f(.22f,.22f,.48f);glVertex2f(0,WIN_H);
    glColor3f(.22f,.22f,.48f);glVertex2f(WIN_W,WIN_H);
    glColor3f(.97f,.52f,.10f);glVertex2f(WIN_W,200);
    glColor3f(.97f,.52f,.10f);glVertex2f(0,200);
    glEnd();
    fillCircle(90,240,42,1,.75f,.2f); fillCircle(90,240,34,1,.88f,.4f);
}
void drawSky3(){
    glBegin(GL_QUADS);
    glColor3f(.02f,.02f,.15f);glVertex2f(0,0);
    glColor3f(.02f,.02f,.15f);glVertex2f(WIN_W,0);
    glColor3f(.04f,.04f,.22f);glVertex2f(WIN_W,WIN_H);
    glColor3f(.04f,.04f,.22f);glVertex2f(0,WIN_H);
    glEnd();
    srand(1337);
    for(int i=0;i<70;i++){
        float sx2=(float)(rand()%WIN_W),sy2=220+(float)(rand()%270);
        float br=.5f+.5f*(rand()%100)/100.f;
        fillCircle(sx2,sy2,1.5f,br,br,br);
    }
    srand((unsigned)time(NULL));
    fillCircle(690,440,30,.96f,.96f,.82f); fillCircle(704,447,26,.04f,.04f,.18f);
}
void drawGround(float r=.52f,float g2=.52f,float b=.52f){
    fillRect(0,0,WIN_W,GROUND_Y,r,g2,b);
    glColor3f(.9f,.85f,.1f);glLineWidth(2.5f);
    glBegin(GL_LINES);
    for(int x=0;x<WIN_W;x+=40){glVertex2f((float)x,38);glVertex2f((float)(x+22),38);}
    glEnd();
}

// ─────────────────────────────────────────────────────────────
//  ENVIRONMENT OBJECTS
// ─────────────────────────────────────────────────────────────
void drawWall(float x,float y,float w){
    for(float bx=x;bx<x+w;bx+=26)
        for(float by=y;by<y+50;by+=13){
            float ox=(int((by-y)/13)%2==0)?0:13;
            fillRect(bx+ox,by,24,11,.44f,.44f,.44f);
            glColor3f(.28f,.28f,.28f);glLineWidth(1);
            glBegin(GL_LINE_LOOP);
            glVertex2f(bx+ox,by);glVertex2f(bx+ox+24,by);
            glVertex2f(bx+ox+24,by+11);glVertex2f(bx+ox,by+11);
            glEnd();
        }
}
void drawFlower(float cx,float cy){
    float pc[4][3]={{1,.5f,0},{.9f,.1f,.5f},{.5f,.2f,.9f},{.2f,.8f,.4f}};
    for(int i=0;i<4;i++){float a=i*PI_F*.5f;fillCircle(cx+cosf(a)*7,cy+sinf(a)*7,5,pc[i][0],pc[i][1],pc[i][2]);}
    fillCircle(cx,cy,6,1,.9f,0);
}
void drawHouse(float x,float y){
    fillRect(x,y,200,130,.97f,.96f,.78f);
    fillTri(x-10,y+130,x+210,y+130,x+100,y+190,.95f,.75f,.75f);
    fillRect(x-5,y+110,210,14,.95f,.75f,.75f);
    fillRect(x+30,y+80,50,40,.5f,.75f,.95f);
    fillRect(x+120,y+80,50,40,.5f,.75f,.95f);
    fillRect(x+53,y+80,4,40,.4f,.4f,.9f);
    fillRect(x+143,y+80,4,40,.4f,.4f,.9f);
    fillRect(x+20,y+30,45,50,.5f,.75f,.95f);
    fillRect(x+82,y,36,55,.55f,.35f,.15f);
    fillCircle(x+112,y+28,3,.9f,.75f,0);
    fillRect(x+60,y+30,16,20,.65f,.35f,.1f);
    drawFlower(x+68,y+52);
    for(int i=0;i<6;i++) fillRect(x+120+i*12,y,6,30,.5f,.6f,.9f);
    fillRect(x+118,y+28,74,5,.4f,.5f,.8f);
}
void drawElecPole(float x,float y){
    fillRect(x-4,y,8,120,.55f,.55f,.55f);
    fillRect(x-30,y+100,60,6,.55f,.55f,.55f);
    fillCircle(x-28,y+103,4,.3f,.3f,.8f);
    fillCircle(x+28,y+103,4,.3f,.3f,.8f);
}
void drawWire(float x1,float y1,float x2,float y2){
    glColor3f(.2f,.2f,.2f);glLineWidth(1.5f);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<=24;i++){float t=i/24.f;glVertex2f(x1+(x2-x1)*t,y1+(y2-y1)*t-14*sinf(PI_F*t));}
    glEnd();
}
void drawTree(float x,float y){
    fillRect(x-8,y,16,40,.4f,.25f,.1f);
    fillTri(x-45,y+30,x+45,y+30,x,y+95,.1f,.6f,.1f);
    fillTri(x-35,y+55,x+35,y+55,x,y+110,.15f,.65f,.15f);
    fillTri(x-25,y+80,x+25,y+80,x,y+120,.2f,.7f,.2f);
}
void drawLampPost(float x,float y){
    fillRect(x-4,y,8,100,.42f,.42f,.42f);
    fillRect(x-4,y+100,38,6,.42f,.42f,.42f);
    fillCircle(x+34,y+103,8,1,.95f,.65f);
}
void drawSpotlight(float cx,float ty){
    glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1,1,.85f,.55f);glVertex2f(cx,ty);
    glColor4f(1,1,.85f,0);
    for(int i=0;i<=20;i++){float t=i/20.f;glVertex2f(cx-90*t,ty-190*t);}
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1,1,.85f,.55f);glVertex2f(cx,ty);
    glColor4f(1,1,.85f,0);
    for(int i=0;i<=20;i++){float t=i/20.f;glVertex2f(cx+90*t,ty-190*t);}
    glEnd();
    glDisable(GL_BLEND);
}

// Scene building blocks (screen coords)
void houseScene(float worldX){
    float ox=sx(worldX);
    drawHouse(ox+100,GROUND_Y);
    drawWall(ox,GROUND_Y,100); drawWall(ox+300,GROUND_Y,200);
    drawElecPole(ox+60,GROUND_Y); drawElecPole(ox+500,GROUND_Y);
    drawWire(ox+90,GROUND_Y+203,ox+530,GROUND_Y+203);
}
void forestScene(float worldX){
    float ox=sx(worldX);
    drawWall(ox,GROUND_Y,520);
    for(int i=0;i<5;i++) drawTree(ox+50+i*100,GROUND_Y);
    drawElecPole(ox+20,GROUND_Y); drawElecPole(ox+480,GROUND_Y);
    drawWire(ox+48,GROUND_Y+203,ox+508,GROUND_Y+203);
}

// ─────────────────────────────────────────────────────────────
//  COLLECTIBLE DRAWINGS
// ─────────────────────────────────────────────────────────────
void drawDoracake(float cx,float cy){
    fillEllipse(cx,cy-2,18,5,.7f,.5f,.3f);
    fillRect(cx-13,cy-2,26,10,.92f,.75f,.5f);
    fillRect(cx-10,cy+8,20,6,.95f,.85f,.6f);
    fillEllipse(cx,cy+14,8,4,1,1,1);
    fillCircle(cx,cy+18,3,.9f,.1f,.1f);
}
void drawHeart(float cx,float cy,float sc=1){
    glPushMatrix(); glTranslatef(cx,cy,0); glScalef(sc,sc,1);
    fillCircle(-6,4,7,.9f,.1f,.2f); fillCircle(6,4,7,.9f,.1f,.2f);
    fillTri(-13,-8,13,-8,0,14,.9f,.1f,.2f);
    glPopMatrix();
}

// ─────────────────────────────────────────────────────────────
//  OBSTACLE DRAWINGS
// ─────────────────────────────────────────────────────────────
void drawStone(float cx,float y){
    fillEllipse(cx,y+12,22,14,.55f,.5f,.45f);
    fillEllipse(cx-8,y+20,14,9,.6f,.55f,.5f);
    fillEllipse(cx+10,y+18,12,8,.5f,.45f,.4f);
    fillEllipse(cx-4,y+20,5,4,.72f,.67f,.62f);
}
void drawLog(float cx,float y,float angle){
    glPushMatrix(); glTranslatef(cx,y+15,0); glRotatef(angle,0,0,1);
    fillRect(-28,-10,56,20,.5f,.3f,.1f);
    fillEllipse(-28,0,10,10,.55f,.35f,.12f);
    fillEllipse( 28,0,10,10,.55f,.35f,.12f);
    glColor3f(.45f,.28f,.08f);glLineWidth(1);
    for(float r2=.35f;r2<1;r2+=.32f){
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<=20;i++){float a=2*PI_F*i/20;glVertex2f(cosf(a)*10*r2,sinf(a)*10*r2);}
        glEnd();
    }
    glPopMatrix();
}
void drawFireObs(float cx,float y,float h){
    fillEllipse(cx,y,18,6,.3f,.3f,.3f);
    if(h<2) return;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,.8f,0);glVertex2f(cx,y+2);
    glColor3f(1,.15f,0);
    for(int i=0;i<=20;i++){float a=PI_F*i/20;glVertex2f(cx+sinf(a)*14,y+2+h*sinf(a*.5f));}
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,1,.5f);glVertex2f(cx,y+4);
    glColor3f(1,.5f,0);
    for(int i=0;i<=20;i++){float a=PI_F*i/20;glVertex2f(cx+sinf(a)*7,y+4+h*.6f*sinf(a*.5f));}
    glEnd();
}
void drawBall(float cx,float y){
    fillCircle(cx,y+15,15,.6f,.1f,.8f);
    fillCircle(cx-5,y+20,5,.8f,.5f,1);
    glColor3f(.3f,0,.5f);glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<=24;i++){float a=2*PI_F*i/24;glVertex2f(cx+cosf(a)*15,y+15+sinf(a)*15);}
    glEnd();
}
void drawMouse(float cx,float y,float sc=1){
    glPushMatrix();glTranslatef(cx,y,0);glScalef(sc,sc,1);
    fillEllipse(0,12,16,12,.6f,.6f,.6f);
    fillCircle(0,28,12,.65f,.65f,.65f);
    fillCircle(-10,38,6,.7f,.5f,.6f); fillCircle(10,38,6,.7f,.5f,.6f);
    fillCircle(-4,30,2,.1f,.1f,.1f);  fillCircle(4,30,2,.1f,.1f,.1f);
    fillCircle(0,25,2,.9f,.5f,.6f);
    glColor3f(.5f,.4f,.4f);glLineWidth(2);
    glBegin(GL_LINE_STRIP);glVertex2f(16,8);glVertex2f(28,5);glVertex2f(34,12);glEnd();
    glPopMatrix();
}
void drawSpiky(float cx,float y,float sc=1){
    glPushMatrix();glTranslatef(cx,y,0);glScalef(sc,sc,1);
    fillCircle(0,15,14,.08f,.08f,.08f);
    glColor3f(.05f,.05f,.05f);
    for(int i=0;i<12;i++){
        float a=2*PI_F*i/12;
        glBegin(GL_TRIANGLES);
        glVertex2f(cosf(a)*14,15+sinf(a)*14);
        glVertex2f(cosf(a+.2f)*12,15+sinf(a+.2f)*12);
        glVertex2f(cosf(a)*26,15+sinf(a)*26);
        glEnd();
    }
    glPopMatrix();
}

// ─────────────────────────────────────────────────────────────
//  DORAEMON CHARACTER
// ─────────────────────────────────────────────────────────────
void drawDoraemon(float x,float y){
    bool flash = hitActive && (hitFrames/5)%2==0;
    float blueR = flash?0.55f:0.10f;
    float blueG = flash?0.30f:0.65f;
    float blueB = flash?0.30f:0.90f;

    glPushMatrix(); glTranslatef(x,y,0);

    // Body
    fillEllipse(0,30,35,28,blueR,blueG,blueB);
    fillEllipse(0,24,22,20,.97f,.97f,.97f);
    fillRect(-35,56,70,8,.9f,.1f,.1f);
    fillCircle(0,56,6,.95f,.85f,0);
    fillCircle(0,56,2,.3f,.2f,0);

    // Legs
    glPushMatrix();glTranslatef(-14,0,0);glRotatef(-legAngle,0,0,1);
    fillRect(-7,-12,14,28,blueR,blueG,blueB);
    fillEllipse(0,-12,12,8,1,1,1);
    glPopMatrix();

    glPushMatrix();glTranslatef(14,0,0);glRotatef(legAngle,0,0,1);
    fillRect(-7,-12,14,28,blueR,blueG,blueB);
    fillEllipse(0,-12,12,8,1,1,1);
    glPopMatrix();

    // Arms
    glPushMatrix();glTranslatef(-35,42,0);glRotatef(28,0,0,1);
    fillRect(-6,-14,12,28,blueR,blueG,blueB);
    fillCircle(0,-14,8,1,1,1);
    glPopMatrix();

    glPushMatrix();glTranslatef(35,42,0);glRotatef(-28,0,0,1);
    fillRect(-6,-14,12,28,blueR,blueG,blueB);
    fillCircle(0,-14,8,1,1,1);
    glPopMatrix();

    // Head
    fillCircle(0,84,34,blueR,blueG,blueB);
    fillCircle(0,82,26,.97f,.97f,.97f);

    // Eyes
    fillCircle(-10,96,8,1,1,1); fillCircle(10,96,8,1,1,1);
    fillCircle(-10,96,5,.05f,.05f,.05f); fillCircle(10,96,5,.05f,.05f,.05f);
    fillCircle(-8,98,2,1,1,1); fillCircle(12,98,2,1,1,1);

    // Nose
    fillCircle(0,85,5,.9f,.1f,.1f);

    // Whiskers
    glColor3f(.3f,.3f,.3f);glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(-6,82);glVertex2f(-30,87);
    glVertex2f(-6,80);glVertex2f(-30,80);
    glVertex2f(-6,78);glVertex2f(-30,73);
    glVertex2f(6,82);glVertex2f(30,87);
    glVertex2f(6,80);glVertex2f(30,80);
    glVertex2f(6,78);glVertex2f(30,73);
    glEnd();

    // Mouth
    glColor3f(.3f,.3f,.3f);glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<=20;i++){float t=i/20.f;glVertex2f(-14+28*t,70-7*sinf(PI_F*t));}
    glEnd();

    glPopMatrix();
}

// ─────────────────────────────────────────────────────────────
//  HUD
// ─────────────────────────────────────────────────────────────
void drawHUD(){
    char buf[32];
    snprintf(buf,sizeof(buf),"Cakes: %d / %d",cakes,MAX_CAKES);
    txt18(10,WIN_H-30,buf);
    for(int i=0;i<health;i++) drawHeart(22+i*32,WIN_H-62,1.f);
    // ghost hearts
    glColor3f(.35f,.35f,.35f);glLineWidth(1.5f);
    for(int i=health;i<3;i++){
        glPushMatrix();glTranslatef(22+i*32,WIN_H-62,0);
        glBegin(GL_LINE_LOOP);
        for(int j=0;j<=24;j++){float a=2*PI_F*j/24;glVertex2f(cosf(a)*10,sinf(a)*10);}
        glEnd();glPopMatrix();
    }
}

// ─────────────────────────────────────────────────────────────
//  RENDER PASSES
// ─────────────────────────────────────────────────────────────
void renderCollectibles(){
    for(auto&c:gCollect){
        if(c.taken) continue;
        float itemSX=sx(c.wx);
        if(itemSX<-50||itemSX>WIN_W+50) continue;
        if(c.isHeart) drawHeart(itemSX,c.wy,1.2f);
        else          drawDoracake(itemSX,c.wy);
    }
}
void renderObstacles(){
    for(auto&o:gObs){
        if(!o.active) continue;
        float osx=sx(o.wx);
        if(osx<-80||osx>WIN_W+80) continue;
        switch(o.type){
            case 0: drawStone(osx,o.wy); break;
            case 1: drawLog(osx,o.wy,o.angle); break;
            case 2: drawBall(osx,o.wy); break;
            case 3: drawMouse(osx,o.wy,1.2f); break;
            case 4: drawSpiky(osx,o.wy,1.2f); break;
        }
    }
    for(auto&m:gFire){
        float msx=sx(m.wx);
        if(msx<-50||msx>WIN_W+50) continue;
        drawFireObs(msx,GROUND_Y,m.height);
    }
}

// ─────────────────────────────────────────────────────────────
//  LEVEL SETUP
// ─────────────────────────────────────────────────────────────
void resetCommon(){
    worldOffset=0; dX=220; dY=GROUND_Y; dVY=0; onGround=true;
    health=3; cakes=0; legAngle=0; legSwing=1;
    hitActive=false; hitFrames=0; kLeft=kRight=false; gWon=false;
    gCollect.clear(); gObs.clear(); gFire.clear(); gLamps.clear();
}
void addCake(float wx,float wy=130){
    Collectible c; c.wx=wx;c.wy=wy;c.isHeart=false;c.taken=false;
    gCollect.push_back(c);
}
void addHeart(float wx,float wy=115){
    Collectible c; c.wx=wx;c.wy=wy;c.isHeart=true;c.taken=false;
    gCollect.push_back(c);
}
void addObs(int type,float wx,float wy,float vx,float minWX,float maxWX){
    Obstacle o;
    o.type=type;o.wx=wx;o.wy=wy;o.vx=vx;o.phase=0;o.angle=0;o.active=true;
    o.minWX=minWX;o.maxWX=maxWX;
    gObs.push_back(o);
}

void setupLevel1(){
    resetCommon();
    addCake(420);addCake(750);addCake(1050);addCake(1380);addCake(1750);
    addHeart(600);addHeart(1200);
    addObs(0,370,GROUND_Y,0,370,370);
    addObs(0,620,GROUND_Y,0,620,620);
    addObs(0,920,GROUND_Y,0,920,920);
    addObs(0,1250,GROUND_Y,0,1250,1250);
    addObs(0,1600,GROUND_Y,0,1600,1600);
}
void setupLevel2(){
    resetCommon();
    addCake(480);addCake(850);addCake(1200);addCake(1580);addCake(1950);
    addHeart(680);addHeart(1400);
    addObs(1,420,GROUND_Y,1.6f,280,560);
    addObs(1,780,GROUND_Y,-1.6f,640,920);
    addObs(1,1100,GROUND_Y,1.6f,960,1240);
    addObs(1,1450,GROUND_Y,-1.6f,1310,1590);
    float mhPos[]={600,1000,1350};
    for(int i=0;i<3;i++){
        ManholeFire m;
        m.wx=mhPos[i];m.height=0;m.maxH=55+i*12;m.speed=1.1f+i*.2f;m.growing=true;
        gFire.push_back(m);
    }
}
void setupLevel3(){
    resetCommon();
    addCake(500);addCake(950);addCake(1300);addCake(1700);addCake(2100);
    addHeart(750);
    addObs(2,450,GROUND_Y,2.0f,300,600);
    addObs(2,800,GROUND_Y,-2.0f,650,950);
    addObs(2,1150,GROUND_Y,2.0f,1000,1300);
    addObs(2,1550,GROUND_Y,-2.0f,1400,1700);
    addObs(2,1900,GROUND_Y,2.0f,1750,2050);
    addObs(3,600,GROUND_Y,1.8f,450,750);
    addObs(3,1250,GROUND_Y,-1.8f,1100,1400);
    addObs(4,870,GROUND_Y,0,870,870);
    addObs(4,1480,GROUND_Y,0,1480,1480);
    float lpPos[]={300,620,940,1260,1580,1900};
    for(int i=0;i<6;i++) gLamps.push_back(lpPos[i]);
}

// ─────────────────────────────────────────────────────────────
//  APPLY HIT
// ─────────────────────────────────────────────────────────────
void applyHit(){
    if(hitActive) return;
    health--;
    if(health<0) health=0;
    hitActive=true;
    hitFrames=HIT_IMMUNITY;
    if(health==0){ gState=ENDSCREEN; gWon=false; }
}

// ─────────────────────────────────────────────────────────────
//  UPDATE (game loop ~60fps)
// ─────────────────────────────────────────────────────────────
void update(int){
    if(gState==LEVEL1||gState==LEVEL2||gState==LEVEL3){

        // ── Movement ──────────────────────────────────────────
        if(health>0){
            // Horizontal movement + scroll
            if(kLeft){
                dX -= MOVE_SPEED;
                if(dX<150 && worldOffset>0){
                    float diff=150-dX;
                    worldOffset-=diff;
                    if(worldOffset<0) worldOffset=0;
                    dX=150;
                }
                if(dX<80) dX=80;
            }
            if(kRight){
                dX+=MOVE_SPEED;
                if(dX>550){
                    worldOffset+=(dX-550);
                    dX=550;
                }
                float maxOff=WORLD_LEN-WIN_W;
                if(worldOffset>maxOff) worldOffset=maxOff;
                if(dX>WIN_W-60) dX=WIN_W-60;
            }

            // Gravity
            dVY+=GRAVITY;
            dY +=dVY;
            if(dY<=GROUND_Y){ dY=GROUND_Y; dVY=0; onGround=true; }

            // Leg animation
            if(kLeft||kRight){
                legAngle+=legSwing*5;
                if(legAngle>28||legAngle<-28) legSwing=-legSwing;
            } else { legAngle*=0.8f; }
        }

        // ── Hit immunity countdown ─────────────────────────────
        if(hitActive){ hitFrames--; if(hitFrames<=0) hitActive=false; }

        // ── Update & collide obstacles ─────────────────────────
        {
            float cx,cy,cw,ch; charBox(cx,cy,cw,ch);

            for(auto&o:gObs){
                if(!o.active) continue;

                // Move
                if(o.type==1){  // rolling log
                    o.wx+=o.vx; o.angle+=3.5f;
                    if(o.wx>o.maxWX){o.wx=o.maxWX;o.vx=-fabsf(o.vx);}
                    if(o.wx<o.minWX){o.wx=o.minWX;o.vx= fabsf(o.vx);}
                }
                else if(o.type==2){  // bouncing ball
                    o.wx+=o.vx;
                    o.phase+=0.08f;
                    o.wy=GROUND_Y+fabsf(sinf(o.phase))*55;
                    if(o.wx>o.maxWX){o.wx=o.maxWX;o.vx=-fabsf(o.vx);}
                    if(o.wx<o.minWX){o.wx=o.minWX;o.vx= fabsf(o.vx);}
                }
                else if(o.type==3){  // mouse
                    o.wx+=o.vx;
                    if(o.wx>o.maxWX){o.wx=o.maxWX;o.vx=-fabsf(o.vx);}
                    if(o.wx<o.minWX){o.wx=o.minWX;o.vx= fabsf(o.vx);}
                }
                else if(o.type==4){  // spiky — vertical oscillation
                    o.phase+=0.05f;
                    o.wy=GROUND_Y+fabsf(sinf(o.phase))*40;
                }

                // Collision
                if(!hitActive && health>0){
                    float osx2=sx(o.wx);
                    float bx,by,bw,bh;
                    obsBox(o.type,osx2,o.wy,bx,by,bw,bh);
                    if(aabb(cx,cy,cw,ch,bx,by,bw,bh)) applyHit();
                }
            }

            // Manhole fire
            for(auto&m:gFire){
                if(m.growing){m.height+=m.speed;if(m.height>=m.maxH)m.growing=false;}
                else          {m.height-=m.speed;if(m.height<=0)m.growing=true;}

                if(!hitActive&&health>0&&m.height>4){
                    float msx=sx(m.wx);
                    float bx=msx-14,by=GROUND_Y,bw=28,bh=m.height;
                    if(aabb(cx,cy,cw,ch,bx,by,bw,bh)) applyHit();
                }
            }
        }

        // ── Collect items ──────────────────────────────────────
        {
            float cx,cy,cw,ch; charBox(cx,cy,cw,ch);
            for(auto&c:gCollect){
                if(c.taken) continue;
                float itemSX=sx(c.wx);
                if(aabb(cx,cy,cw,ch, itemSX-15,c.wy-15,30,30)){
                    c.taken=true;
                    if(c.isHeart){ health++; if(health>3) health=3; }
                    else          cakes++;
                }
            }
        }

        // ── Win check ──────────────────────────────────────────
        if(cakes>=MAX_CAKES){
            gWon=true; gState=ENDSCREEN;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16,update,0);
}

// ─────────────────────────────────────────────────────────────
//  SCREENS
// ─────────────────────────────────────────────────────────────
void homeScreen(){
    glBegin(GL_QUADS);
    glColor3f(.04f,.12f,.38f);glVertex2f(0,0);
    glColor3f(.04f,.12f,.38f);glVertex2f(WIN_W,0);
    glColor3f(.08f,.28f,.60f);glVertex2f(WIN_W,WIN_H);
    glColor3f(.08f,.28f,.60f);glVertex2f(0,WIN_H);
    glEnd();
    srand(88);
    for(int i=0;i<55;i++){
        float x2=(float)(rand()%WIN_W),y2=(float)(rand()%WIN_H);
        fillCircle(x2,y2,1.5f,1,1,.8f);
    }
    srand((unsigned)time(NULL));

    glPushMatrix();glTranslatef(610,100,0);glScalef(1.35f,1.35f,1);
    drawDoraemon(0,0);glPopMatrix();

    txtBig(90,430,"DORAEMON'S TREAT HUNT",1,.9f,0);
    txt12(215,405,"CSC4118: Computer Graphics  |  AIUB  |  Fall 2025-2026",.78f,.88f,1);

    drawButton( 60,280,170,52,"LEVEL 1",0.0f,0.55f,0.15f);
    drawButton(315,280,170,52,"LEVEL 2",0.70f,0.40f,0.02f);
    drawButton(570,280,170,52,"LEVEL 3",0.60f,0.02f,0.10f);

    txt12( 90,268,"Easy — Morning", .55f,1,.55f);
    txt12(335,268,"Medium — Sunset",1,.8f,.4f);
    txt12(580,268,"Hard — Night",   1,.4f,.4f);

    txt12(165,228,"Arrow Keys: Move & Jump   |   Mouse: Click buttons",.7f,.85f,1);
    txt12(20,25,"Tasmia Amin  |  Orpyta Karmokar Aupy  |  Sadia Ahmed",.65f,.65f,.75f);
    txt12(20,10,"Supervised by: Tonny Shekha Kar",.65f,.65f,.75f);
}

void drawEndScreen(){
    glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0,0,0,.72f);
    glBegin(GL_QUADS);
    glVertex2f(0,0);glVertex2f(WIN_W,0);glVertex2f(WIN_W,WIN_H);glVertex2f(0,WIN_H);
    glEnd();glDisable(GL_BLEND);

    fillRect(180,155,440,250,.08f,.08f,.22f);
    lineLoop(180,155,440,250,.75f,.65f,1,3);

    if(gWon) txtBig(188,370,"YOU WIN!  All cakes collected!",1,.9f,0);
    else     txtBig(255,370,"GAME OVER!",1,.25f,.25f);

    char buf[32];
    snprintf(buf,sizeof(buf),"Cakes: %d / %d",cakes,MAX_CAKES);
    txt18(330,330,buf);

    drawButton(205,225,170,52,"RESTART",  0.0f,0.50f,0.15f);
    drawButton(425,225,170,52,"MAIN MENU",0.1f,0.15f,0.60f);
}

// ─────────────────────────────────────────────────────────────
//  LEVEL RENDERERS
// ─────────────────────────────────────────────────────────────
void renderLevel1(){
    drawSky1(); drawGround(.52f,.52f,.52f);
    houseScene(100); forestScene(660); houseScene(1320);
    renderCollectibles(); renderObstacles();
    drawDoraemon(dX,dY); drawHUD();
}
void renderLevel2(){
    drawSky2(); drawGround(.36f,.28f,.22f);
    houseScene(100); forestScene(660); houseScene(1320);
    renderCollectibles(); renderObstacles();
    drawDoraemon(dX,dY); drawHUD();
}
void renderLevel3(){
    drawSky3(); drawGround(.18f,.18f,.26f);
    for(float lpwx:gLamps){
        float lpsx=sx(lpwx);
        if(lpsx>-60&&lpsx<WIN_W+60){
            drawLampPost(lpsx,GROUND_Y);
            drawSpotlight(lpsx+34,GROUND_Y+103);
        }
    }
    houseScene(100); forestScene(660); houseScene(1320);
    renderCollectibles(); renderObstacles();
    drawDoraemon(dX,dY); drawHUD();
}

// ─────────────────────────────────────────────────────────────
//  GLUT CALLBACKS
// ─────────────────────────────────────────────────────────────
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    switch(gState){
        case HOME:      homeScreen();  break;
        case LEVEL1:    renderLevel1(); break;
        case LEVEL2:    renderLevel2(); break;
        case LEVEL3:    renderLevel3(); break;
        case ENDSCREEN:
            switch(lastLevel){
                case LEVEL1: renderLevel1(); break;
                case LEVEL2: renderLevel2(); break;
                case LEVEL3: renderLevel3(); break;
                default:     break;
            }
            drawEndScreen();
            break;
    }
    glutSwapBuffers();
}

void specialKeyDown(int key,int,int){
    if(gState!=LEVEL1&&gState!=LEVEL2&&gState!=LEVEL3) return;
    if(health<=0) return;
    if(key==GLUT_KEY_LEFT)  kLeft=true;
    if(key==GLUT_KEY_RIGHT) kRight=true;
    if(key==GLUT_KEY_UP && onGround){ dVY=JUMP_VY; onGround=false; }
}
void specialKeyUp(int key,int,int){
    if(key==GLUT_KEY_LEFT)  kLeft=false;
    if(key==GLUT_KEY_RIGHT) kRight=false;
}

void mouseClick(int btn,int state,int mx,int my){
    if(btn!=GLUT_LEFT_BUTTON||state!=GLUT_DOWN) return;
    float x=(float)mx;
    float y=(float)(WIN_H-my);   // ← correct Y flip

    if(gState==HOME){
        if(x>=60 &&x<=230&&y>=280&&y<=332){setupLevel1();lastLevel=LEVEL1;gState=LEVEL1;}
        if(x>=315&&x<=485&&y>=280&&y<=332){setupLevel2();lastLevel=LEVEL2;gState=LEVEL2;}
        if(x>=570&&x<=740&&y>=280&&y<=332){setupLevel3();lastLevel=LEVEL3;gState=LEVEL3;}
    }
    else if(gState==ENDSCREEN){
        // Restart
        if(x>=205&&x<=375&&y>=225&&y<=277){
            switch(lastLevel){
                case LEVEL1:setupLevel1();break;
                case LEVEL2:setupLevel2();break;
                case LEVEL3:setupLevel3();break;
                default:setupLevel1();break;
            }
            gState=lastLevel;
        }
        // Main menu
        if(x>=425&&x<=595&&y>=225&&y<=277) gState=HOME;
    }
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);glLoadIdentity();
    gluOrtho2D(0,WIN_W,0,WIN_H);
    glMatrixMode(GL_MODELVIEW);glLoadIdentity();
}

// ─────────────────────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────────────────────
int main(int argc,char**argv){
    srand((unsigned)time(NULL));
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(WIN_W,WIN_H);
    glutInitWindowPosition(120,80);
    glutCreateWindow("Doraemon's Treat Hunt");
    glClearColor(.04f,.08f,.20f,1);
    glMatrixMode(GL_PROJECTION);glLoadIdentity();
    gluOrtho2D(0,WIN_W,0,WIN_H);
    glMatrixMode(GL_MODELVIEW);glLoadIdentity();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);
    glutMouseFunc(mouseClick);
    glutTimerFunc(16,update,0);
    glutMainLoop();
    return 0;
}
