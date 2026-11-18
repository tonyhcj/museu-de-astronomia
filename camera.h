#ifndef CAMERA_H
#define CAMERA_H

void inicializaCamera(void);
void aplicaCamera(void);
void configuraProjecao(int largura, int altura);
void movimentaCamera(float frente, float lado);
void giraCamera(float dyaw, float dpitch);


#endif
