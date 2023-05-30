
#define _CRT_SECURE_NO_WARNINGS


/*  Standard headers  */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stddef.h>
#include <wchar.h>

#include ".\include\GL\freeglut.h"

//사용할 라이브러리 지정
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32.lib")

/*  OpenGL and friends  */
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <windows.h>
#endif

/*  Includes  */

/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
/*  Determine number of elements in an array  */
#define Length(x) (sizeof (x) / sizeof *(x))

/*  Common #defines */
/*  Defaults for window sizing  */
#define DEF_WINDOW_HEIGHT 600
#define DEF_WINDOW_WIDTH 700
#define DEF_WINDOW_POS_H 150
#define DEF_WINDOW_POS_W 150

/*  Projection  */
#define DEF_ASP 1
#define DEF_DIM 25
#define DEF_TH 340
#define DEF_PH 30
#define DEF_FOV 50
#define DEF_ECX 0
#define DEF_ECY 0
#define DEF_ECZ 0

/*  Draw defaults  */
#define DEF_AXES 1
#define DEF_PARAMS 1
#define DEF_OVERLAY 0

/*  Skybox Textures  */
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5




#define ESC 27
#define A 97
#define Z 122

#define MOUSE 100 //마우스 회전 감도


/*  ID-used to keep screencasts separate  */
int screencastID = 0;

/*  WINDOW  */
char* windowName = "OpenGL screenscasts XX: Placeholder";
int windowHeight = DEF_WINDOW_HEIGHT;
int windowWidth = DEF_WINDOW_WIDTH;
int windowPosHeight = DEF_WINDOW_POS_H;
int windowPosWidth = DEF_WINDOW_POS_W;

/*  PROJECTION  */
double asp = DEF_ASP;
double dim = DEF_DIM;
int th = DEF_TH;
int ph = DEF_PH;
int fov = DEF_FOV;
double ecX = DEF_ECX;
double ecY = DEF_ECY;
double ecZ = DEF_ECZ;

/*  COLORS  */
float white[] = { 1,1,1,1 };

/*  TEXTURES  */
int skybox[6];


// 큐브 위치
float cubeX = 0.0;
float cubeY = 0.0;
float cubeZ = -4.0;

// 회전
float pitch = 0.0;
float yaw = 0.0;
float roll = 0.0;


// 마우스
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

// Cube Map
void displayInit(void);
void displayEye(void);
void displayReshape(int width, int height);
void displayProject(double fov, double asp, double dim);
void redisplayAll(void);
void drawScene();
void drawSkybox(double D);

#pragma once
void errCheck(char* where);
unsigned int loadTexBMP(char* file);

// Main Display function
void drawHuman();

/* 머리 */
void drawHead();
void drawHair();
void drawFace();
void drawEyes();
void drawNose();
void drawMouth();
void drawBrow();

/* 상체 */
void drawBody();
void drawTopTorso();
void drawBottomTorso();
void drawLeftArm();
void drawLeftBiceps();

void drawRightArm();
void drawRightBiceps();

void drawChair();
void drawLeftFoot();
void drawRightFoot();
void drawButton();

// 핸들러 등록
void reshape(GLsizei width, GLsizei height);
void keyboard(unsigned char key, int x, int y);
void init(void);

void mouseClick(GLint button, GLint state, GLint x, GLint y);
void mouseMove(GLint x, GLint y);

/*
 *  displayInit()
 *  -------
 *  Initializes display
 */
void displayInit(void) {
    glClearColor(1, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
}

/*
 * displayEye()
 * ------
 * Set the eye position
 */
void displayEye(void) {
    double Ex = -2 * dim * Sin(th) * Cos(ph) + 40;
    double Ey = +2 * dim * Sin(ph) + 40;
    double Ez = +2 * dim * Cos(th) * Cos(ph) + 40;
    /* camera/eye position, aim of camera lens, up-vector */
    gluLookAt(Ex + ecX, Ey, Ez + ecZ, ecX, ecY, ecZ, 0, Cos(ph), 0);
}

/*
 *  displayReshape()
 *  ------
 *  GLUT calls this routine when the window is resized
 */
void displayReshape(int width, int height) {
    asp = (height > 0) ? (double)width / height : 1;
    glViewport(0, 0, width, height);
    displayProject(fov, asp, dim);
}

/*
 * displayProject()
 * ------
 * Sets the projection
 */
void displayProject(double fov, double asp, double dim) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, asp, dim / 16, 16 * dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



/*
 *  redisplayAll()
 *  ------
 *  This is called whenever we need to draw the display
 */

void redisplayAll(void) {
    displayProject(fov, asp, dim);
    glutPostRedisplay();
}

/*
 *  drawScene()
 *  ------
 *  Draw the entire Scene
 */
void drawScene() {
    //drawSkybox(3.5 * dim);
    drawSkybox(4.0 * dim);
}

/*
 *  drawSkybox(double D)
 *  ------
 *  Draws the skybox around the entire screen
 */
void drawSkybox(double D) {
    glColor3fv(white);
    glEnable(GL_TEXTURE_2D);

    /* Sides */
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_RIGHT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-D, -3, -D);
    glTexCoord2f(1, 0); glVertex3f(+D, -3, -D);
    glTexCoord2f(1, 1); glVertex3f(+D, +D, -D);
    glTexCoord2f(0, 1); glVertex3f(-D, +D, -D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_FRONT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(+D, -3, -D);
    glTexCoord2f(1, 0); glVertex3f(+D, -3, +D);
    glTexCoord2f(1, 1); glVertex3f(+D, +D, +D);
    glTexCoord2f(0, 1); glVertex3f(+D, +D, -D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_LEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(+D, -3, +D);
    glTexCoord2f(1, 0); glVertex3f(-D, -3, +D);
    glTexCoord2f(1, 1); glVertex3f(-D, +D, +D);
    glTexCoord2f(0, 1); glVertex3f(+D, +D, +D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_BACK]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-D, -3, +D);
    glTexCoord2f(1, 0); glVertex3f(-D, -3, -D);
    glTexCoord2f(1, 1); glVertex3f(-D, +D, -D);
    glTexCoord2f(0, 1); glVertex3f(-D, +D, +D);
    glEnd();

    /* Top and Bottom */
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_UP]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-D, +D, -D);
    glTexCoord2f(1, 0); glVertex3f(+D, +D, -D);
    glTexCoord2f(1, 1); glVertex3f(+D, +D, +D);
    glTexCoord2f(0, 1); glVertex3f(-D, +D, +D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_DOWN]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(+D, -3, -D);
    glTexCoord2f(0, 1); glVertex3f(-D, -3, -D);
    glTexCoord2f(0, 0); glVertex3f(-D, -3, +D);
    glTexCoord2f(1, 0); glVertex3f(+D, -3, +D);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void fatal(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}

/*
 * errCheck()
 * ------
 * Checks to see if there is an error and displays it if there was
 */
void errCheck(char* where) {
    int err = glGetError();
    if (err) fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), where);
}


static void reverse(void* x, const int n) {
    int k;
    char* ch = (char*)x;
    for (k = 0; k < n / 2; k++)
    {
        char tmp = ch[k];
        ch[k] = ch[n - 1 - k];
        ch[n - 1 - k] = tmp;
    }
}

/*
 *  Load texture from BMP file
 */
unsigned int loadTexBMP(char* file) {
    unsigned int   texture;    /* Texture name */
    FILE* f;          /* File pointer */
    unsigned short magic;      /* Image magic */
    unsigned int   dx, dy, size; /* Image dimensions */
    unsigned short nbp, bpp;    /* Planes and bits per pixel */
    unsigned char* image;      /* Image data */
    unsigned int   k;          /* Counter */

    /*  Open file */
    f = fopen(file, "rb");
    if (!f) fatal("Cannot open file %s\n", file);
    /*  Check image magic */
    if (fread(&magic, 2, 1, f) != 1) fatal("Cannot read magic from %s\n", file);
    if (magic != 0x4D42 && magic != 0x424D) fatal("Image magic not BMP in %s\n", file);
    /*  Seek to and read header */
    if (fseek(f, 16, SEEK_CUR) || fread(&dx, 4, 1, f) != 1 || fread(&dy, 4, 1, f) != 1 ||
        fread(&nbp, 2, 1, f) != 1 || fread(&bpp, 2, 1, f) != 1 || fread(&k, 4, 1, f) != 1)
        fatal("Cannot read header from %s\n", file);
    /*  Reverse bytes on big endian hardware (detected by backwards magic) */
    if (magic == 0x424D) {
        reverse(&dx, 4);
        reverse(&dy, 4);
        reverse(&nbp, 2);
        reverse(&bpp, 2);
        reverse(&k, 4);
    }
    /*  Check image parameters */
    printf("dx: %d dy: %d\n", dx, dy);
    if (dx < 1 || dx>65536) fatal("%s image width out of range: %d\n", file, dx);
    if (dy < 1 || dy>65536) fatal("%s image height out of range: %d\n", file, dy);
    if (nbp != 1)  fatal("%s bit planes is not 1: %d\n", file, nbp);
    if (bpp != 24) fatal("%s bits per pixel is not 24: %d\n", file, bpp);
    if (k != 0)    fatal("%s compressed files not supported\n", file);
#ifndef GL_VERSION_2_0
    /*  OpenGL 2.0 lifts the restriction that texture size must be a power of two */
    for (k = 1; k < dx; k *= 2);
    if (k != dx) fatal("%s image width not a power of two: %d\n", file, dx);
    for (k = 1; k < dy; k *= 2);
    if (k != dy) fatal("%s image height not a power of two: %d\n", file, dy);
#endif

    /*  Allocate image memory */
    size = 3 * dx * dy;
    image = (unsigned char*)malloc(size);
    if (!image) fatal("Cannot allocate %d bytes of memory for image %s\n", size, file);
    /*  Seek to and read image */
    if (fseek(f, 20, SEEK_CUR) || fread(image, size, 1, f) != 1)
        fatal("Error reading data from image %s\n", file);
    fclose(f);
    /*  Reverse colors (BGR -> RGB) */
    for (k = 0; k < size; k += 3) {
        unsigned char temp = image[k];
        image[k] = image[k + 2];
        image[k + 2] = temp;
    }

    /*  Sanity check */
    errCheck("loadTexBMP");
    /*  Generate 2D texture */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    /*  Copy image */
    glTexImage2D(GL_TEXTURE_2D, 0, 3, dx, dy, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    if (glGetError()) fatal("Error in glTexImage2D %s %dx%d\n", file, dx, dy);
    /*  Scale linearly when image size doesn't match */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    /*  Free image memory */
    free(image);
    /*  Return texture name */
    return texture;
}

/*
 * initGlobals()
 * ------
 * Initializes the global variables.
 */
void initGlobals(void) {
    /* WINDOW */
    windowHeight = DEF_WINDOW_HEIGHT;
    windowWidth = DEF_WINDOW_WIDTH;
    windowPosHeight = DEF_WINDOW_POS_H;
    windowPosWidth = DEF_WINDOW_POS_W;

    /* PROJECTION */
    dim = DEF_DIM;
    th = DEF_TH;
    ph = DEF_PH;
    fov = DEF_FOV;
    asp = DEF_ASP;
    ecX = DEF_ECX;//sangjun
    ecY = DEF_ECY;
    ecZ = DEF_ECZ;
}

/*
 *  initSkybox
 *  ------
 *  initializes all of our textures for the skybox background
 */
void initSkybox(void) {
    /*
      SKY_FRONT 0
      SKY_RIGHT 1
      SKY_LEFT 2
      SKY_BACK 3
      SKY_UP 4
      SKY_DOWN 5
     */

    skybox[SKY_FRONT] = loadTexBMP("pororo.bmp");
    skybox[SKY_RIGHT] = loadTexBMP("pororo.bmp");
    skybox[SKY_LEFT] = loadTexBMP("pororo.bmp");
    skybox[SKY_BACK] = loadTexBMP("pororo.bmp");
    skybox[SKY_UP] = loadTexBMP("top.bmp");
    skybox[SKY_DOWN] = loadTexBMP("my.bmp");
}


/* 메인 디스플레이 함수 */
void drawHuman() {
    //화면을 지운다. (컬러버퍼와 깊이버퍼)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // 배경색 설정 (검은색)
    //이후 연산은 ModelView Matirx에 영향을 준다. 객체 조작
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // 이동과 회전을 적용
    glTranslatef(cubeX, cubeY, cubeZ);
    glRotatef(pitch, 1.0, 0.0, 0.0); // x축에 대해 회전
    glRotatef(yaw, 0.0, 1.0, 0.0); // y축에 대해 회전
    glRotatef(roll, 0.0, 0.0, 1.0); // z축에 대해 회전


    drawHead();
    drawBody();

    drawScene();
    displayEye();
    glFlush();
    glutSwapBuffers();
    errCheck("display sanity check");
}

void drawHead() {
    // 머리 위 원
    glTranslatef(0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.33, 30, 30);

    drawFace();

    glTranslatef(0.0, 0.0, -0.2);

    // 머리 아래 원
    glTranslatef(0.0, -0.5, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.45, 30, 30);

    // 머리 아래 원뿔
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, -0.05, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.45, 1.4, 30, 30);
}

/* 얼굴 */
void drawFace() {
    drawEyes();
    drawNose();
    drawMouth();
    drawBrow();
}

/* 눈 */
void drawEyes() {
    // 검은 눈 왼
    glTranslatef(-0.11, 0.0, 0.2);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.14, 30, 30);
    // 흰 눈 왼
    glTranslatef(-0.004, 0.0, 0.015);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.13, 30, 30);
    // 위치 눈 시작으로
    glTranslatef(0.0, 0.0, -0.015);
    // 눈동자
    glTranslatef(0.0, 0.0, 0.05);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.10, 30, 30);

    glTranslatef(0.003, 0.0, -0.05);


    // 검은 눈 오
    glTranslatef(0.22, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.14, 30, 30);
    // 흰 눈 오
    glTranslatef(0.004, -0.0, 0.015);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.13, 30, 30);
    // 위치 눈 시작으로
    glTranslatef(0.0, 0.0, -0.015);
    // 눈동자
    glTranslatef(0.0, 0.0, 0.05);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.10, 30, 30);

    glTranslatef(-0.003, 0.0, -0.05);
}

/* 코 */
void drawNose() {
    glTranslatef(-0.1, -0.15, 0.0);
    glColor3f(1.0, 0.647059, 0.0);
    glutSolidCone(0.14, 0.4, 30, 30);

    glTranslatef(-0.01, 0.15, 0.0);
}

/* 입 */
void drawMouth() {
    glTranslatef(0.0, -0.5, -0.0);
    glColor3f(0.745098, 0.745098, 0.745098);
    glutSolidSphere(0.3, 30, 30);

    glTranslatef(0.0, 0.5, 0.0);

    // 입술..?
    glTranslatef(0.0, -0.31, 0.07);
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(-67, 1.0, 0.0, 0.0);
    glutSolidCone(0.3, 0.25, 30, 30);

    glRotatef(67, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.31, -0.07);

    // 이빨
    glTranslatef(0.05, -0.42, 0.25);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(0.1);

    glTranslatef(-0.1, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(0.1);

    glTranslatef(0.05, 0.42, -0.25);
}

void drawBrow() {
    // 왼
    glTranslatef(-0.1, 0.13, 0.0);
    glRotatef(80.0, 1.0, 0.0, 0.0);
    glRotatef(-5.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidCone(0.13, 0.03, 30, 30);

    glRotatef(5.0, 0.0, 1.0, 0.0);
    glRotatef(-80.0, 1.0, 0.0, 0.0);
    glTranslatef(0.1, -0.13, 0.0);

    // 오
    glTranslatef(0.12, 0.13, 0.0);
    glRotatef(80.0, 1.0, 0.0, 0.0);
    glRotatef(5.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidCone(0.13, 0.03, 30, 30);


    glRotatef(-5.0, 0.0, 1.0, 0.0);
    glRotatef(-80.0, 1.0, 0.0, 0.0);
    glTranslatef(-0.12, -0.13, 0.0);
}

/* 상체 */
void drawBody() {
    drawTopTorso(); // 위쪽 몸통
    drawBottomTorso(); // 아래쪽 몸통
    drawLeftArm(); // 왼쪽 팔
    drawLeftBiceps(); // 왼쪽 팔뚝
    drawRightArm(); // 오른쪽 팔
    drawRightBiceps(); // 오른쪽 팔뚝
    drawLeftFoot(); // 왼발
    drawRightFoot(); // 오른발
    drawButton(); // 단추
    drawChair(); // 의자

    glFlush();
}

/* 위쪽 몸통 */
void drawTopTorso() {
    // 여기 아래 줄 추가 !!
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, -0.8, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.4, 30, 10);
    glPopMatrix();
}

/* 아래쪽 몸통: 파란색 */
void drawBottomTorso() {
    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.7, 50, 50);
    glPopMatrix();
}

/* 왼쪽 팔 */
void drawLeftArm() {
    glPushMatrix();
    glTranslated(0.0, -0.35, 0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glColor3f(0.545098, 0.270588, 0.07451);

    glBegin(GL_QUADS);
    glVertex3f(-0.7, -0.2, 0.0); // 1
    glVertex3f(-0.7, -0.25, 0.0); // 2
    glVertex3f(-0.7, -0.25, 0.05); // 3
    glVertex3f(-0.7, -0.2, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.2, -0.4, 0.0); // 1
    glVertex3f(-0.2, -0.45, 0.0); // 2
    glVertex3f(-0.2, -0.45, 0.05); // 3
    glVertex3f(-0.2, -0.4, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS); // 1, 2
    glVertex3f(-0.7, -0.2, 0.0);
    glVertex3f(-0.7, -0.25, 0.0);
    glVertex3f(-0.2, -0.4, 0.0);
    glVertex3f(-0.2, -0.45, 0.0);
    glEnd();

    glBegin(GL_QUADS); // 2, 3
    glVertex3f(-0.7, -0.25, 0.0);
    glVertex3f(-0.7, -0.25, 0.05);
    glVertex3f(-0.2, -0.45, 0.0);
    glVertex3f(-0.2, -0.45, 0.05);
    glEnd();

    glBegin(GL_QUADS); // 3, 4
    glVertex3f(-0.7, -0.25, 0.05);
    glVertex3f(-0.7, -0.2, 0.05);
    glVertex3f(-0.2, -0.45, 0.05);
    glVertex3f(-0.2, -0.4, 0.05);
    glEnd();

    glBegin(GL_QUADS); // 4, 1
    glVertex3f(-0.7, -0.2, 0.05);
    glVertex3f(-0.7, -0.2, 0.0);
    glVertex3f(-0.2, -0.4, 0.05);
    glVertex3f(-0.2, -0.4, 0.0);
    glEnd();

    glPopMatrix();
}

/* 왼쪽 팔뚝 : 노란색 */
void drawLeftBiceps() {
    glPushMatrix();

    glRotatef(30.0, 0.0, 1.0, 0.0); // 3) y축으로 돌림
    glTranslated(-0.7, -0.55, 0.0); // 2) 이동하고
    glRotatef(-30.0, 0.0, 0.0, 1.0); // 1) z축으로 돌리고
    glColor3f(0.545098, 0.270588, 0.07451);

    glBegin(GL_QUADS);
    glVertex3f(-0.5, 0.05, 0.0); // 1
    glVertex3f(-0.5, 0.0, 0.0); // 2
    glVertex3f(-0.5, 0.0, 0.05); // 3
    glVertex3f(-0.5, 0.05, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0); // 1
    glVertex3f(0.0, -0.05, 0.0); // 2
    glVertex3f(0.0, -0.05, 0.05); // 3
    glVertex3f(0.0, 0.0, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS); // 1, 2
    glVertex3f(-0.5, 0.05, 0.0);
    glVertex3f(-0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -0.05, 0.0);
    glEnd();

    glBegin(GL_QUADS); // 2, 3
    glVertex3f(-0.5, 0.0, 0.0);
    glVertex3f(-0.5, 0.0, 0.05);
    glVertex3f(0.0, -0.05, 0.0);
    glVertex3f(0.0, -0.05, 0.05);
    glEnd();

    glBegin(GL_QUADS); // 3, 4
    glVertex3f(-0.5, 0.0, 0.05);
    glVertex3f(-0.5, 0.05, 0.05);
    glVertex3f(0.0, -0.05, 0.05);
    glVertex3f(0.0, 0.0, 0.05);
    glEnd();

    glBegin(GL_QUADS); // 4, 1
    glVertex3f(-0.5, 0.05, 0.05);
    glVertex3f(-0.5, 0.05, 0.0);
    glVertex3f(0.0, 0.0, 0.05);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

    glPopMatrix();
}


/* 오른쪽 팔 */
void drawRightArm() {
    glPushMatrix();
    glTranslated(0.0, -0.35, 0);
    glRotatef(330.0, 0.0, 1.0, 0.0);
    glColor3f(0.545098, 0.270588, 0.07451);

    glBegin(GL_QUADS);
    glVertex3f(0.8, -0.2, 0.0); // 1
    glVertex3f(0.8, -0.25, 0.0); // 2
    glVertex3f(0.8, -0.25, 0.05); // 3
    glVertex3f(0.8, -0.2, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.2, -0.4, 0.0); // 1
    glVertex3f(0.2, -0.45, 0.0); // 2
    glVertex3f(0.2, -0.45, 0.05); // 3
    glVertex3f(0.2, -0.4, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS); // 1, 2
    glVertex3f(0.8, -0.2, 0.0);
    glVertex3f(0.8, -0.25, 0.0);
    glVertex3f(0.2, -0.4, 0.0);
    glVertex3f(0.2, -0.45, 0.0);
    glEnd();

    glBegin(GL_QUADS); // 2, 3
    glVertex3f(0.8, -0.25, 0.0);
    glVertex3f(0.8, -0.25, 0.05);
    glVertex3f(0.2, -0.45, 0.0);
    glVertex3f(0.2, -0.45, 0.05);
    glEnd();


    glBegin(GL_QUADS); // 3, 4
    glVertex3f(0.8, -0.25, 0.05);
    glVertex3f(0.8, -0.2, 0.05);
    glVertex3f(0.2, -0.45, 0.05);
    glVertex3f(0.2, -0.4, 0.05);
    glEnd();

    glBegin(GL_QUADS); // 4, 1
    glVertex3f(0.8, -0.2, 0.05);
    glVertex3f(0.8, -0.2, 0.0);
    glVertex3f(0.2, -0.4, 0.05);
    glVertex3f(0.2, -0.4, 0.0);
    glEnd();

    glPopMatrix();
}

/* 오른쪽 팔뚝 */
void drawRightBiceps() {
    glPushMatrix();

    glRotatef(-30.0, 0.0, 1.0, 0.0); // 3) y축으로 돌림
    glTranslated(0.8, -0.55, 0.0); // 2) 이동하고
    glRotatef(30.0, 0.0, 0.0, 1.0); // 1) z축으로 돌리고
    glColor3f(0.545098, 0.270588, 0.07451);

    glBegin(GL_QUADS);
    glVertex3f(0.3, 0.1, 0.0); // 1
    glVertex3f(0.3, 0.05, 0.0); // 2
    glVertex3f(0.3, 0.05, 0.05); // 3
    glVertex3f(0.3, 0.1, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0); // 1
    glVertex3f(0.0, -0.05, 0.0); // 2
    glVertex3f(0.0, -0.05, 0.05); // 3
    glVertex3f(0.0, 0.0, 0.05); // 4
    glEnd();

    glBegin(GL_QUADS); // 1, 2
    glVertex3f(0.3, 0.1, 0.0);
    glVertex3f(0.3, 0.05, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -0.05, 0.0);
    glEnd();

    glBegin(GL_QUADS); // 2, 3
    glVertex3f(0.3, 0.05, 0.0);
    glVertex3f(0.3, 0.05, 0.05);
    glVertex3f(0.0, -0.05, 0.0);
    glVertex3f(0.0, -0.05, 0.05);
    glEnd();

    glBegin(GL_QUADS); // 3, 4
    glVertex3f(0.3, 0.05, 0.05);
    glVertex3f(0.3, 0.1, 0.05);
    glVertex3f(0.0, -0.05, 0.05);
    glVertex3f(0.0, 0.0, 0.05);
    glEnd();

    glBegin(GL_QUADS); // 4, 1
    glVertex3f(0.3, 0.1, 0.05); // 4
    glVertex3f(0.3, 0.1, 0.0); // 1
    glVertex3f(0.0, 0.0, 0.05); // 4
    glVertex3f(0.0, 0.0, 0.0); // 1
    glEnd();

    glPopMatrix();
}



/* 의자 : Cubic 3개 */
void drawChair() {
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-1.0, -2.5, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(0.0, -2.5, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(1.0, -2.5, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
}



/* 왼쪽 발 */
void drawLeftFoot() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-0.3, -1.9, 0.5);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
}

/* 오른쪽 발 */
void drawRightFoot() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.3, -1.9, 0.5);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
}

/* 단추 */
void drawButton() {
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);

    glTranslatef(0.0, -0.7, 0.4);
    glutSolidSphere(0.1, 30, 30);

    glTranslatef(0.0, -0.4, 0.2);
    glutSolidSphere(0.1, 30, 30);

    glTranslatef(0.0, -0.4, 0.1);
    glutSolidSphere(0.1, 30, 30);

    glPopMatrix();
}

void reshape(GLsizei width, GLsizei height) {
    asp = (height > 0) ? (double)width / height : 1;
    glViewport(0, 0, width, height);
    displayProject(fov, asp, dim);


    glMatrixMode(GL_PROJECTION); //이후 연산은 Projection Matrix에 영향을 준다. 카메라로 보이는 장면 같은거 설정 
    glLoadIdentity();

    //Field of view angle(단위 degrees), 윈도우의 aspect ratio, Near와 Far Plane설정
    gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW); //이후 연산은 ModelView Matirx에 영향을 준다. 객체 조작
}

void init() {
    /* 초기화 색: #ffffff로 설정 */
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClearDepth(1.0);
    /* Enable the depth buffer */
    glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ESC) exit(0);
    else if (key == Z) fov += 1;
    else if (key == A) fov -= 1;

    redisplayAll();
}

int main(int argc, char** argv) {
    initGlobals();

    /* screencast specific variables */
    windowName = "Frozen : Olaf";
    screencastID = 1337;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosWidth, windowPosHeight);
    glutCreateWindow(windowName);

    init();
    initSkybox();

    glutDisplayFunc(drawHuman);
    glutKeyboardFunc(keyboard); // redisplay 추가
    glutReshapeFunc(reshape);

    redisplayAll();

    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutMainLoop();

    return 0;
}

void mouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
        TopLeftX = X; // 버튼 눌린 위치 x 좌표
        TopLeftY = Y; // 버튼 눌린 위치 y 좌표
    }
}

void mouseMove(GLint X, GLint Y) {
    BottomRightX = X; // move 후의 위치 x 좌표
    BottomRightY = Y; // move 후의 위치 y 좌표

    yaw -= (TopLeftX - BottomRightX) / MOUSE;
    pitch -= (TopLeftY - BottomRightY) / MOUSE;

    //glutPostRedisplay();
    redisplayAll();
}