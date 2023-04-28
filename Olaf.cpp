#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <GLU.h>
#include <glut.h>
#include <GLAUX.H>

#define ESC 27

float radius = 3.0f;

void drawHuman(); // 메인 display 함수
/* 머리 */
void drawHead();
void drawHair();
void drawFace();
void drawEyes();
void drawNose();
void drawMouth();
/* 몸통 */
void drawBody();
void drawTopTorso();
void drawBottomTorso();
void drawLeftArm();
void drawRightArm();
void drawLeftFoot();
void drawRightFoot();

void keyEventHandler(int key, int x, int y);

/* 메인 display 함수 */
void drawHuman() {
	drawHead();
	drawBody();
}

/* 머리 그리기 */
void drawHead() {
	drawHair();
	drawFace();
}

/* 머리 위 나뭇가지 그리기 */
void drawHair() {

}

/* 얼굴 그리기*/
void drawFace() {
	drawEyes();
	drawNose();
	drawMouth();
}

/* 눈 그리기 */
void drawEyes() {

}

/* 코(당근) 그리기 */
void drawNose() {

}

/* 입 그리기 */
void drawMouth() {

}

/* 올라프 Body 그리기*/
void drawBody() {
	drawTopTorso(); // 위쪽 몸통
	drawBottomTorso(); // 아래쪽 몸통
	drawLeftArm();
	drawRightArm();
	drawLeftFoot();
	drawRightFoot();
}

/* 위쪽 몸통 그리기 */
void drawTopTorso() {

}

/* 아래쪽 몸통 그리기*/
void drawBottomTorso() {

}

/* 왼쪽 팔 그리기 */
void drawLeftArm() {

}

/* 오른쪽 팔 그리기*/
void drawRightArm() {

}

/* 왼쪽 발 그리기 */
void drawLeftFoot() {

}

/* 오른쪽 발 그리기 */
void drawRightFoot() {

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // 디스플레이 default 설정
	glutInitWindowPosition(100, 100); // 화면의 좌/상단 기준 window 창이 뜰 위치 결정
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGL 3D Olaf");
	
	glutDisplayFunc(drawHuman);

	glutKeyboardFunc(keyEventHandler);
	glutMouseFunc(mouseCallback);
	glutMainLoop();

	return 0;
}

void keyEventHandler(unsigned char key, int x, int y) {
	if (key == ESC || key == 'q' || key == 'Q') exit(0);

	else if (key == 'a' && radius < 10) {
		radius = radius + 0.5;
	}
	else if (key == 'z' && radius > 1.5) {
		radius = radius - 0.5;
	}
}

void mouseCallback(int button, int state, int x, int y) {

	// 마우스 드래그로 시점 회전시키기
}