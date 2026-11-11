#include <GL/glut.h>
#include "scene.h"

static GLUquadric* quad;

static void material(float r, float g, float b, float spec, float brilho)
{
    GLfloat esp[] = { spec, spec, spec, 1.0f };
    float c = 0.299f * r + 0.587f * g + 0.114f * b;
    glColor3f(c, c, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, esp);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

static void superficie(float ox, float oy, float oz,
                       float ux, float uy, float uz,
                       float vx, float vy, float vz,
                       float nx, float ny, float nz,
                       int nu, int nv)
{
    int i, j;
    glNormal3f(nx, ny, nz);
    glBegin(GL_QUADS);
    for (i = 0; i < nu; i++)
        for (j = 0; j < nv; j++)
        {
            float a0 = (float)i / nu, a1 = (float)(i + 1) / nu;
            float b0 = (float)j / nv, b1 = (float)(j + 1) / nv;
            glVertex3f(ox + ux*a0 + vx*b0, oy + uy*a0 + vy*b0, oz + uz*a0 + vz*b0);
            glVertex3f(ox + ux*a1 + vx*b0, oy + uy*a1 + vy*b0, oz + uz*a1 + vz*b0);
            glVertex3f(ox + ux*a1 + vx*b1, oy + uy*a1 + vy*b1, oz + uz*a1 + vz*b1);
            glVertex3f(ox + ux*a0 + vx*b1, oy + uy*a0 + vy*b1, oz + uz*a0 + vz*b1);
        }
    glEnd();
}

static void pedestal(float x, float z, float largura, float altura)
{
    glPushMatrix();
        glTranslatef(x, altura / 2.0f, z);
        glScalef(largura, altura, largura);
        material(0.85f, 0.85f, 0.88f, 0.2f, 10.0f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaAmbiente()
{
    material(0.35f, 0.35f, 0.40f, 0.5f, 40.0f);
    superficie(-12,0,-12,  24,0,0,  0,0,24,  0,1,0, 24,24);

    material(0.30f, 0.32f, 0.40f, 0.05f, 5.0f);
    superficie(-12,0,-8,   24,0,0,  0,8,0,   0,0,1, 24,8);
    superficie(-12,0,-8,   0,0,16,  0,8,0,   1,0,0, 16,8);
    superficie( 12,0,-8,   0,0,16,  0,8,0,  -1,0,0, 16,8);
}

static void exposicaoSistemaSolar()
{
    GLfloat emissaoSol[] = { 0.85f, 0.85f, 0.85f, 1.0f };
    GLfloat semEmissao[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    pedestal(0.0f, -4.0f, 1.2f, 2.0f);

    glPushMatrix();
        glTranslatef(0.0f, 3.2f, -4.0f);

        glPushMatrix();
            material(1.0f, 0.8f, 0.1f, 0.0f, 1.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissaoSol);
            glutSolidSphere(0.8, 32, 16);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, semEmissao);
        glPopMatrix();

        glPushMatrix();
            glRotatef(40.0f, 0, 1, 0);
            glTranslatef(2.2f, 0.0f, 0.0f);
            material(0.1f, 0.4f, 0.9f, 0.9f, 80.0f);
            glutSolidSphere(0.3, 24, 12);
        glPopMatrix();
    glPopMatrix();
}

static void exposicaoSaturno()
{
    pedestal(-7.0f, -4.0f, 1.2f, 1.5f);

    glPushMatrix();
        glTranslatef(-7.0f, 2.8f, -4.0f);
        glRotatef(20.0f, 0, 0, 1);

        material(0.85f, 0.7f, 0.45f, 0.3f, 20.0f);
        glutSolidSphere(0.9, 32, 16);

        glPushMatrix();
            glRotatef(90.0f, 1, 0, 0);
            glScalef(1.0f, 1.0f, 0.1f);
            material(0.7f, 0.6f, 0.5f, 0.1f, 5.0f);
            glutSolidTorus(0.25, 1.5, 16, 48);
        glPopMatrix();
    glPopMatrix();
}

static void exposicaoTelescopio()
{
    int i;
    glPushMatrix();
        glTranslatef(7.0f, 0.0f, -4.0f);

        material(0.2f, 0.2f, 0.2f, 0.3f, 20.0f);
        for (i = 0; i < 3; i++)
        {
            glPushMatrix();
                glRotatef(i * 120.0f, 0, 1, 0);
                glTranslatef(0.4f, 0.8f, 0.0f);
                glRotatef(15.0f, 0, 0, 1);
                glScalef(0.08f, 1.7f, 0.08f);
                glutSolidCube(1.0);
            glPopMatrix();
        }

        glTranslatef(0.0f, 1.7f, 0.0f);
        glRotatef(30.0f, 0, 1, 0);
        glRotatef(-45.0f, 1, 0, 0);
        glTranslatef(0.0f, 0.0f, -0.9f);
        material(0.1f, 0.2f, 0.6f, 0.8f, 70.0f);
        gluCylinder(quad, 0.2, 0.25, 1.8, 24, 1);
    glPopMatrix();
}

void desenhaObjetosDoMuseu()
{
    exposicaoSistemaSolar();
    exposicaoSaturno();
    exposicaoTelescopio();
}

void configuraIluminacao()
{
    GLfloat ambiente[]  = { 0.22f, 0.22f, 0.22f, 1.0f };
    GLfloat difusa[]    = { 0.58f, 0.58f, 0.58f, 1.0f };
    GLfloat especular[] = { 0.80f, 0.80f, 0.80f, 1.0f };
    GLfloat posicao[]   = { 0.0f, 7.0f, 4.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao);
}

void desenhaCena()
{
    glMatrixMode(GL_MODELVIEW);

    configuraIluminacao();

    desenhaAmbiente();
    desenhaObjetosDoMuseu();
}

void inicializaCena()
{
    quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    glShadeModel(GL_SMOOTH);
}
