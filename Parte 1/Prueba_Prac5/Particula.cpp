#include "Particula.h"

Particula::Particula(double x, double y, double vx, double vy, double m, double r)
    : pos(x, y), vel(vx, vy), masa(m), radio(r), activa(true), gravedad(9.8) {}

void Particula::mover(double dt) {
    vel.y += gravedad * dt;      // aceleracion por gravedad
    pos = pos + vel * dt;
}
