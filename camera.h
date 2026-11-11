#ifndef CAMERA_H
#define CAMERA_H

void inicializaCamera(void);
void aplicaCamera(void);
void configuraProjecao(int largura, int altura);

void moveFrente(float d);
void moveLado(float d);
void moveVertical(float d);
void giraCamera(float dYaw, float dPitch);

#endif
