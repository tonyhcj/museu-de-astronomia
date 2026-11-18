#include <GL/glut.h>
#include <math.h>
#include "camera.h"

#define DEG2RAD 0.017453292519943295f

static float camX, camY, camZ;
static float yaw, pitch;

void inicializaCamera()
{
    camX = 0.0f; camY = 3.0f; camZ = 11.0f;
    yaw = -90.0f;
    pitch = -8.0f;
}

void aplicaCamera()
{
    float cy = cosf(yaw * DEG2RAD),   sy = sinf(yaw * DEG2RAD);
    float cp = cosf(pitch * DEG2RAD), sp = sinf(pitch * DEG2RAD);

    float dx = cy * cp, dy = sp, dz = sy * cp;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              camX + dx, camY + dy, camZ + dz,
              0.0f, 1.0f, 0.0f);
}
void movimentaCamera(float frente, float lado)
{
    float fx = cosf(yaw * DEG2RAD), fz = sinf(yaw * DEG2RAD);
    camX += fx * frente - fz * lado;
    camZ += fz * frente + fx * lado;


    if (camX < -11.0f) camX = -11.0f;
    if (camX >  11.0f) camX =  11.0f;
    if (camZ <  -7.0f) camZ =  -7.0f;
    if (camZ >  11.0f) camZ =  11.0f;
}

void giraCamera(float dyaw, float dpitch)
{
    yaw += dyaw;
    pitch += dpitch;
    if (pitch >  80.0f) pitch =  80.0f;
    if (pitch < -80.0f) pitch = -80.0f;
}
void configuraProjecao(int largura, int altura)
{
    float aspecto = (altura == 0) ? 1.0f : (float)largura / (float)altura;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspecto, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
