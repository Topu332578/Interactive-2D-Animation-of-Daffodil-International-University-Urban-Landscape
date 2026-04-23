#include <GL/glut.h>
#include <math.h>
#include <string.h>

// --- Global Variables ---
float carX = 0.0;
float cloudX = -100.0;
float wheelAngle = 0.0;

void init(void) {
    glClearColor(0.4, 0.7, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// --- Algorithm 1: DDA Line Drawing Algorithm ---
void drawLineDDA(float x1, float y1, float x2, float y2, float r, float g, float b, int thickness) {
    glColor3f(r, g, b);
    glPointSize(thickness);
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
    glPointSize(1); // Reset point size
}

// --- Algorithm 2: Trigonometric/Midpoint Circle Drawing Algorithm ---
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}

// Text Rendering
void drawText(const char* text, float x, float y, void* font) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; i < (int)strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

// --- Ferris Wheel (Using DDA for spokes and stand) ---
void drawFerrisWheel(float x, float y) {
    // Stand using DDA
    drawLineDDA(x, y, x - 12, y - 30, 0.2, 0.2, 0.2, 3);
    drawLineDDA(x, y, x + 12, y - 30, 0.2, 0.2, 0.2, 3);

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(wheelAngle, 0, 0, 1);

    // Outer Ring
    glColor3f(0.4, 0.1, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(cos(theta) * 18, sin(theta) * 18);
    }
    glEnd();

    // Spokes using DDA
    for (int i = 0; i < 8; i++) {
        float theta = i * 45 * 3.14159 / 180;
        drawLineDDA(0, 0, cos(theta) * 18, sin(theta) * 18, 0.4, 0.1, 0.0, 2);
    }

    // Cabins
    for (int i = 0; i < 8; i++) {
        float theta = i * 45 * 3.14159 / 180;
        float cx = cos(theta) * 18;
        float cy = sin(theta) * 18;

        glPushMatrix();
        glTranslatef(cx, cy, 0);
        glRotatef(-wheelAngle, 0, 0, 1);
        glColor3f(1.0, 0.2, 0.2);
        glRectf(-3, -3, 3, 1);
        glColor3f(1.0, 1.0, 1.0);
        glRectf(-1.5, -0.5, 1.5, 0.5);
        glPopMatrix();
    }
    glPopMatrix();
    drawCircle(x, y, 2.0, 0.0, 0.0, 0.0);
}

// --- Vehicles & Buildings ---
void drawPrivateCar(float x, float y, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(r, g, b); glRectf(0, 0, 18, 7); glRectf(3, 7, 13, 12);
    glColor3f(0.8, 0.9, 1.0); glRectf(4, 8, 7, 11); glRectf(8, 8, 12, 11);
    glColor3f(1.0, 1.0, 0.7); glRectf(16.5, 4, 18, 6);
    drawCircle(4, 0, 2.5, 0.1, 0.1, 0.1); drawCircle(14, 0, 2.5, 0.1, 0.1, 0.1);
    glPopMatrix();
}

void drawDIUBus(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.0, 0.4, 0.2); glRectf(0, 0, 45, 15);
    glColor3f(1.0, 1.0, 1.0); glRectf(0, 8, 45, 15);
    glColor3f(0.2, 0.6, 0.9);
    for(float i=2; i<40; i+=9) glRectf(i, 9, i+7, 14);
    drawText("DIU TRANSPORT", 5, 3, GLUT_BITMAP_HELVETICA_10);
    drawCircle(10, 0, 3.5, 0.1, 0.1, 0.1); drawCircle(35, 0, 3.5, 0.1, 0.1, 0.1);
    glPopMatrix();
}

void drawDIUBuilding(float x, float y) {
    glColor3f(0.1, 0.1, 0.1); glRectf(x, y, x + 55, y + 85);
    glColor3f(0.0, 0.4, 0.2); glRectf(x + 2, y + 70, x + 53, y + 80);
    drawText("DIU MAIN CAMPUS", x + 10, y + 74, GLUT_BITMAP_HELVETICA_12);
    glColor3f(0.2, 0.5, 0.8);
    for (float j = y + 5; j < y + 65; j += 10)
        for (float i = x + 5; i < x + 50; i += 10) glRectf(i, j, i + 6, j + 6);
}

void drawDetailedBuilding(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b); glRectf(x, y, x + w, y + h);
    glColor3f(0.9, 0.9, 1.0);
    for (float j = y + 5; j < y + h - 5; j += 10)
        for (float i = x + 3; i < x + w - 3; i += 7) glRectf(i, j, i + 4, j + 5);
}

void drawTrafficLight(float x, float y) {
    // Pole using DDA
    drawLineDDA(x+1, y, x+1, y+25, 0.2, 0.2, 0.2, 4);
    glColor3f(0.1, 0.1, 0.1); glRectf(x - 2, y + 25, x + 4, y + 42);
    drawCircle(x + 1, y + 38, 1.5, 1.0, 0.0, 0.0);
    drawCircle(x + 1, y + 33.5, 1.5, 1.0, 0.9, 0.0);
    drawCircle(x + 1, y + 29, 1.5, 0.0, 0.9, 0.0);
}

void drawFlowerBush(float x, float y) {
    drawCircle(x, y, 4, 0.0, 0.5, 0.0);
    drawCircle(x + 2, y + 2, 1.2, 1.0, 0.0, 0.0);
    drawCircle(x - 2, y + 1, 1.2, 1.0, 0.8, 0.0);
}

void drawCloud(float x, float y) {
    drawCircle(x, y, 6, 1.0, 1.0, 1.0);
    drawCircle(x + 4, y + 3, 7, 1.0, 1.0, 1.0);
}

float getContinuousX(float currentPos, float offset) {
    float x = currentPos + offset;
    while (x > 140) x -= 280;
    while (x < -140) x += 280;
    return x;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawCircle(75, 75, 10, 1.0, 0.9, 0.0); // Sun

    glPushMatrix();
    glTranslatef(cloudX, 0, 0);
    drawCloud(-130, 85); drawCloud(-90, 75); drawCloud(-60, 65);
    drawCloud(-20, 85);  drawCloud(20, 80);  drawCloud(60, 90);
    drawCloud(100, 70);  drawCloud(140, 80); drawCloud(180, 65);
    drawCloud(220, 85);
    glPopMatrix();

    drawFerrisWheel(45, 10);

    drawDetailedBuilding(-98, -20, 15, 60, 0.3, 0.3, 0.3);
    drawDIUBuilding(-78, -20);
    drawDetailedBuilding(-15, -20, 22, 65, 0.4, 0.4, 0.45);
    drawDetailedBuilding(15, -20, 20, 90, 0.2, 0.2, 0.25);
    drawDetailedBuilding(75, -20, 22, 70, 0.4, 0.5, 0.5);

    glColor3f(0.15, 0.15, 0.15); glRectf(-100, -95, 100, -20);
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -100; i < 100; i += 25) {
        glRectf(i, -45, i + 12, -43); glRectf(i, -70, i + 12, -68);
    }

    drawFlowerBush(-88, -20); drawFlowerBush(-25, -20);
    drawFlowerBush(35, -20); drawFlowerBush(65, -20);
    drawTrafficLight(-95, -20); drawTrafficLight(92, -20);

    drawDIUBus(getContinuousX(carX, 0), -38);
    drawPrivateCar(getContinuousX(carX, 65), -40, 0.8, 0.1, 0.1);
    drawDIUBus(getContinuousX(carX, 130), -38);

    drawDIUBus(getContinuousX(carX, -85), -63);
    drawPrivateCar(getContinuousX(carX, -20), -65, 0.1, 0.1, 0.8);
    drawDIUBus(getContinuousX(carX, 110), -63);

    drawDIUBus(getContinuousX(carX, 40), -88);
    drawPrivateCar(getContinuousX(carX, -45), -90, 1.0, 0.8, 0.0);
    drawPrivateCar(getContinuousX(carX, -110), -90, 0.5, 0.5, 0.5);

    drawText("DIU Endless Cityscape - Algorithm Integrated", -40, 95, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

void update(int value) {
    carX += 0.8;
    if (carX > 1000) carX = 0;
    cloudX += 0.03;
    if (cloudX > 250) cloudX = -450;
    wheelAngle += 1.2;
    if (wheelAngle > 360) wheelAngle -= 360;
    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1300, 750);
    glutCreateWindow("Endless DIU Cityscape with DDA & Circle Algorithms");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
