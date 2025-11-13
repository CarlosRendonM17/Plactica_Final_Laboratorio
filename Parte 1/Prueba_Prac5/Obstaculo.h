#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Particula.h"

class Obstaculo {
public:
    double x, y, lado;

    Obstaculo(double x_, double y_, double lado_);
    bool colisiona(const Particula& p) const;
};

#endif
