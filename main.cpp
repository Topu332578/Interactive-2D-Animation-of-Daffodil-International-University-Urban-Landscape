#include <GL/glut.h>
#include <math.h>
#include <string.h>


float cloudX = -100.0;

void init(void) {
    glClearColor(0.4, 0.7, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

//  Text Rendering Algorithm
void drawText(const char* text, float x, float y, void* font) {
    glColor3f(1.0, 1.0, 1.0); // White Text
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

// Algorithm: Trigonometric Circle
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}

// Buildings
void drawBuilding(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glRectf(x, y, x + width, y + height);
    // janala
    glColor3f(0.8, 0.9, 1.0);
    for (float i = x + 2; i < x + width - 2; i += 5) {
        for (float j = y + 5; j < y + height - 5; j += 8) {
            glRectf(i, j, i + 3, j + 5);
        }
    }
}

//  DIU Building
void drawDIUBuilding(float x, float y) {
    // Main Structure
    glColor3f(0.1, 0.1, 0.1); // Dark base
    glRectf(x, y, x + 55, y + 80);

    // Glass/Windows
    glColor3f(0.2, 0.5, 0.8);
    for (float j = y + 5; j < y + 60; j += 10)
        for (float i = x + 5; i < x + 50; i += 10)
            glRectf(i, j, i + 6, j + 6);

    // Green Header with Institution Name
    glColor3f(0.0, 0.4, 0.2); // DIU Green
    glRectf(x + 2, y + 65, x + 53, y + 75);
    drawText("Daffodil International University", x + 5, y + 68, GLUT_BITMAP_HELVETICA_12);
}

void drawCloud(float x, float y) {
    drawCircle(x, y, 5, 1.0, 1.0, 1.0);
    drawCircle(x + 4, y + 2, 6, 1.0, 1.0, 1.0);
    drawCircle(x - 4, y + 1, 5, 1.0, 1.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Sun ebong Road
    drawCircle(70, 70, 12, 1.0, 0.9, 0.0);
    glColor3f(0.2, 0.2, 0.2); glRectf(-100, -100, 100, -30);
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -100; i < 100; i += 25) glRectf(i, -66, i + 12, -64);

    // Clouds & Normal Buildings
    drawCloud(-50, 80); drawCloud(30, 85);
    drawBuilding(-95, -30, 15, 60, 0.3, 0.3, 0.3);
    drawBuilding(60, -30, 20, 50, 0.4, 0.3, 0.2);

    //  DIU Main Building
    drawDIUBuilding(-75, -30);


    drawText("Daffodil International University Cityscape", -30, 90, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("Day 3: Branding and Institution Layout");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
