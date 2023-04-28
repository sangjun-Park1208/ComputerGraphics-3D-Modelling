#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <GLU.h>
#include <glut.h>
#include <GLAUX.H>

#define ESC 27

float radius = 3.0f;

void drawHuman(); // ���� display �Լ�
/* �Ӹ� */
void drawHead();
void drawHair();
void drawFace();
void drawEyes();
void drawNose();
void drawMouth();
/* ���� */
void drawBody();
void drawTopTorso();
void drawBottomTorso();
void drawLeftArm();
void drawRightArm();
void drawLeftFoot();
void drawRightFoot();

void keyEventHandler(int key, int x, int y);

/* ���� display �Լ� */
void drawHuman() {
	drawHead();
	drawBody();
}

/* �Ӹ� �׸��� */
void drawHead() {
	drawHair();
	drawFace();
}

/* �Ӹ� �� �������� �׸��� */
void drawHair() {

}

/* �� �׸���*/
void drawFace() {
	drawEyes();
	drawNose();
	drawMouth();
}

/* �� �׸��� */
void drawEyes() {

}

/* ��(���) �׸��� */
void drawNose() {

}

/* �� �׸��� */
void drawMouth() {

}

/* �ö��� Body �׸���*/
void drawBody() {
	drawTopTorso(); // ���� ����
	drawBottomTorso(); // �Ʒ��� ����
	drawLeftArm();
	drawRightArm();
	drawLeftFoot();
	drawRightFoot();
}

/* ���� ���� �׸��� */
void drawTopTorso() {

}

/* �Ʒ��� ���� �׸���*/
void drawBottomTorso() {

}

/* ���� �� �׸��� */
void drawLeftArm() {

}

/* ������ �� �׸���*/
void drawRightArm() {

}

/* ���� �� �׸��� */
void drawLeftFoot() {

}

/* ������ �� �׸��� */
void drawRightFoot() {

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // ���÷��� default ����
	glutInitWindowPosition(100, 100); // ȭ���� ��/��� ���� window â�� �� ��ġ ����
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

	// ���콺 �巡�׷� ���� ȸ����Ű��
}