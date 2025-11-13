#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <vector>
#include <fstream>
#include <cmath>
#include "Particula.h"
#include "Obstaculo.h"

class Simulador {
private:
    double ancho, alto, c;
    std::vector<Particula> particulas;
    std::vector<Obstaculo> obstaculos;
    std::ofstream archivo;

public:
    Simulador(double ancho_, double alto_, double coef_rest);

    void agregarParticula(const Particula& p);
    void agregarObstaculo(const Obstaculo& o);

    void colisionesPared(Particula& p, double t);
    void colisionesObstaculos(Particula& p, double t);
    void colisionesParticulas(double t);

    void simular(double tiempo_total, double dt);
};

#endif
