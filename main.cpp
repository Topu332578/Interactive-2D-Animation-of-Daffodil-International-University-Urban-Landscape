#include <GL/glut.h>
#include <math.h>
#include <string.h>


float cloudX = -100.0;
float carX = 0.0;

void init(void) {
    glClearColor(0.4, 0.7, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// Text Rendering
void drawText(const char* text, float x, float y, void* font) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; i < (int)strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

// Circle Algorithm
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}

// Building Design
void drawBuilding(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glRectf(x, y, x + width, y + height);
    // Windows logic
    glColor3f(0.8, 0.9, 1.0);
    for (float i = x + 2; i < x + width - 2; i += 5) {
        for (float j = y + 5; j < y + height - 5; j += 8) {
            glRectf(i, j, i + 3, j + 5);
        }
    }
}

// DIU Special Building
void drawDIUBuilding(float x, float y) {
    glColor3f(0.1, 0.1, 0.1);
    glRectf(x, y, x + 50, y + 80);
    glColor3f(0.0, 0.4, 0.2);
    glRectf(x + 2, y + 65, x + 48, y + 75);
    drawText("DIU MAIN CAMPUS", x + 5, y + 68, GLUT_BITMAP_HELVETICA_12);
    // Glass panels
    glColor3f(0.2, 0.4, 0.6);
    for(float j=y+5; j<y+60; j+=12)
        for(float i=x+5; i<x+45; i+=12) glRectf(i, j, i+8, j+8);
}

// Cloud Design
void drawCloud(float x, float y) {
    drawCircle(x, y, 6, 1.0, 1.0, 1.0);
    drawCircle(x + 4, y + 3, 7, 1.0, 1.0, 1.0);
    drawCircle(x - 4, y + 2, 6, 1.0, 1.0, 1.0);
}

// Vehicles
void drawDIUBus(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.0, 0.4, 0.2); glRectf(0, 0, 40, 15); // Body
    glColor3f(1.0, 1.0, 1.0); glRectf(0, 8, 40, 15); // Top White part
    drawCircle(8, 0, 3, 0.1, 0.1, 0.1); drawCircle(32, 0, 3, 0.1, 0.1, 0.1);
    drawText("DIU TRANSPORT", 5, 3, GLUT_BITMAP_HELVETICA_10);
    glPopMatrix();
}

void drawCar(float x, float y, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(r, g, b); glRectf(0, 0, 18, 7); glRectf(3, 7, 15, 12);
    drawCircle(4, 0, 2.5, 0.1, 0.1, 0.1); drawCircle(14, 0, 2.5, 0.1, 0.1, 0.1);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 1. Sky & Sun
    drawCircle(75, 75, 12, 1.0, 0.9, 0.0);

    // 2. Many Clouds
    drawCloud(-80, 85);
    drawCloud(-40, 75);
    drawCloud(10, 85);
    drawCloud(50, 70);
    drawCloud(90, 80);

    // 3. Buildings
    drawBuilding(-98, -30, 15, 65, 0.3, 0.3, 0.3);
    drawDIUBuilding(-75, -30);
    drawBuilding(-18, -30, 20, 90, 0.4, 0.4, 0.4);
    drawBuilding(10, -30, 18, 55, 0.3, 0.4, 0.3);
    drawBuilding(35, -30, 22, 70, 0.4, 0.3, 0.2);
    drawBuilding(65, -30, 15, 85, 0.2, 0.2, 0.3);

    // 4. Road
    glColor3f(0.15, 0.15, 0.15); glRectf(-100, -100, 100, -30);
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -100; i < 100; i += 25) glRectf(i, -66, i + 12, -64);

    // 5. Vehicles
    drawDIUBus(-20, -55);              // Upper Lane
    drawCar(45, -90, 0.8, 0.1, 0.1);   // Red car
    drawCar(-70, -90, 0.1, 0.1, 0.8);  // Blue car

    drawText("DIU Cityscape - Full Infrastructure", -35, 95, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 750);
    glutCreateWindow("Day 4: Restored Buildings & Clouds + Vehicles");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
