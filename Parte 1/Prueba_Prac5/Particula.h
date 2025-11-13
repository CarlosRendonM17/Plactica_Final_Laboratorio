#ifndef PARTICULA_H
#define PARTICULA_H

#include "Vector2.h"

class Particula {
public:
    Vector2 pos, vel;
    double masa, radio;
    double gravedad;   // ← NUEVO
    bool activa;

    Particula(double x, double y, double vx, double vy, double m, double r);

    void mover(double dt);
};

#endif
