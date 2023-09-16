#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<gl/glew.h>
#include <gl/glut.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#define MAX_RECTANGLES 8
typedef struct rectangle {
    float x1, y1, x2, y2; // 위치 
    float r=0, g=0, b=0; // 색상
} rect;//사각형 데이터 저장

GLfloat red, green, blue; // RGB 색상 변수
float winWidth = 800;
float winHeight = 600;
bool left_botton = true; 
bool right_botton = true;

rect rectangles[MAX_RECTANGLES];
bool atStart = true;
GLvoid drawfirstScene(GLvoid);
void Reshape(int w, int h);
void Clickmouse(int button, int state, int x, int y);

void Clickmouse(int button, int state, int x, int y) {

    double nomalX = (x - winWidth / 2) / 400;
    double nomalY = (winHeight / 2 - y) / 300;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        left_botton = true;
        for (int i = 0; i < MAX_RECTANGLES; i++) {
            if (i < 4) {
                if ((rectangles[i].x1 <= nomalX && nomalX <= rectangles[i + 4].x1) ||
                    (rectangles[i].y1 <= nomalY && nomalY <= rectangles[i + 4].y1) ||
                    (rectangles[i + 4].x2 <= nomalX && nomalX <= rectangles[i].x2) ||
                    (rectangles[i + 4].y2 <= nomalY && nomalY <= rectangles[i].y2
                    )) {
                    printf("click\n");
                    rectangles[i].r = static_cast<float>(rand()) / RAND_MAX;
                    rectangles[i].g = static_cast<float>(rand()) / RAND_MAX;
                    rectangles[i].b = static_cast<float>(rand()) / RAND_MAX;
                }     
            }
            else if (i > 4) {

            }
        }
        glutPostRedisplay();
    }
    else if (state == GLUT_UP) {
        left_botton = false;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        right_botton = true;
        double nomalX = (x - winWidth / 2) / 400;
        double nomalY = (winHeight / 2 - y) / 300;

        for (int i = 0; i < MAX_RECTANGLES; i++) {
            if ((rectangles[i].x1 < nomalX && nomalX < rectangles[i].x2) ||
                (rectangles[i].y1 < nomalY && nomalY < rectangles[i].y2)) {
                //사각형 내부의 요소를 탐지함
                float newWidth = rectangles[i].x2 - rectangles[i].x1 - 0.1f;
                float newHeight = rectangles[i].y2 - rectangles[i].y1 - 0.1f;
                if (newWidth < 0.1f) {
                    newWidth = 0.1f;
                }
                if (newHeight < 0.1f) {
                    newHeight = 0.1f;
                }
                rectangles[i].x1 += (rectangles[i].x2 - rectangles[i].x1 - newWidth) / 2;
                rectangles[i].y1 += (rectangles[i].y2 - rectangles[i].y1 - newHeight) / 2;
                rectangles[i].x2 = rectangles[i].x1 + newWidth;
                rectangles[i].y2 = rectangles[i].y1 + newHeight;
            }
        }
        glutPostRedisplay();
    }
    else if (state == GLUT_UP) {
        right_botton = false;
    }
}
void handleKeyDown(unsigned char key, int x, int y) {
    if (key == 27 || key == 'q' || key == 'Q') {
        exit(0);
    }
}
void drawfirstScene(GLvoid) {
    glClear(GL_COLOR_BUFFER_BIT);
    // 그리기 코드 작성
    if (atStart) {
        for (int i = 0; i < MAX_RECTANGLES; i++) {
            rectangles[i].r = static_cast<float>(rand()) / RAND_MAX;
            rectangles[i].g = static_cast<float>(rand()) / RAND_MAX;
            rectangles[i].b = static_cast<float>(rand()) / RAND_MAX;
            if (i == 0||i==4) {
                rectangles[i].x1 = 0.0f;
                rectangles[i].y1 = 0.0f;
                rectangles[i].x2 = 1.0f;
                rectangles[i].y2 = 1.0f;
            }
            if (i == 1 || i == 5) {
                rectangles[i].x1 = -1.0f;
                rectangles[i].y1 = 0.0f;
                rectangles[i].x2 = 0.0f;
                rectangles[i].y2 = 1.0f;
            }
            if (i == 2 || i == 6) {
                rectangles[i].x1 = -1.0f;
                rectangles[i].y1 = -1.0f;
                rectangles[i].x2 = 0.0f;
                rectangles[i].y2 = 0.0f;
            }
            if (i == 3 || i == 7) {
                rectangles[i].x1 = 0.0f;
                rectangles[i].y1 = -1.0f;
                rectangles[i].x2 = 1.0f;
                rectangles[i].y2 = 0.0f;
            }
            glRectf(rectangles[i].x1, rectangles[i].y1, rectangles[i].x2, rectangles[i].y2);
            glColor3f(rectangles[i].r, rectangles[i].g, rectangles[i].b);
        }
        glutSwapBuffers();
        atStart = false;
    }
    else if (!atStart) {
        for (int i = 0; i < MAX_RECTANGLES; i++) {
            glRectf(rectangles[i].x1, rectangles[i].y1, rectangles[i].x2, rectangles[i].y2);
            glColor3f(rectangles[i].r, rectangles[i].g, rectangles[i].b);
        }
        glutSwapBuffers();
    }

}
void Reshape(int w, int h) {
    glViewport(0, 0, w, h);
}
//뷰포트 설정 당장은 만질일이 없다.
int main(int argc, char** argv) {
    srand(unsigned(time(NULL)));
    // GLUT 초기화
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize((int)winWidth, (int)winHeight);
    glutCreateWindow("EX 2");

    glutDisplayFunc(drawfirstScene);
    glutReshapeFunc(Reshape);

    glutMouseFunc(Clickmouse);
    glutKeyboardFunc(handleKeyDown);
    //glutMotionFunc(mousemotion);
    // 다른 콜백 함수 등록
    // 메인 루프 시작
    glutMainLoop();

    return 0;
}
