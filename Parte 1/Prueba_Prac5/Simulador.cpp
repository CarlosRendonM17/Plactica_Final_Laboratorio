#include "Simulador.h"
#include <iostream>

Simulador::Simulador(double ancho_, double alto_, double coef_rest)
    : ancho(ancho_), alto(alto_), c(coef_rest)
{
    archivo.open("C:/Users/Andres Felipe/OneDrive/Escritorio/informatica II Andres Lafaurie/Practicafinal_lab-main/Parte1/PRUEBAS/Prueba_Prac5/salida.txt");
}

void Simulador::agregarParticula(const Particula& p) {
    particulas.push_back(p);
}

void Simulador::agregarObstaculo(const Obstaculo& o) {
    obstaculos.push_back(o);
}

void Simulador::colisionesPared(Particula& p, double t) {
    if (p.pos.x - p.radio <= 0 || p.pos.x + p.radio >= ancho) {
        p.vel.x *= -1;
        archivo << "t=" << t << " -> Choque con pared vertical\n";
    }
    if (p.pos.y - p.radio <= 0 || p.pos.y + p.radio >= alto) {
        p.vel.y *= -1;
        archivo << "t=" << t << " -> Choque con pared horizontal\n";
    }
}

void Simulador::colisionesObstaculos(Particula& p, double t) {
    for (auto& o : obstaculos) {
        if (o.colisiona(p)) {
            double dxL = fabs(p.pos.x - o.x);
            double dxR = fabs(p.pos.x - (o.x + o.lado));
            double dyT = fabs(p.pos.y - o.y);
            double dyB = fabs(p.pos.y - (o.y + o.lado));

            double minD = std::min(std::min(dxL, dxR), std::min(dyT, dyB));

            if (minD == dxL || minD == dxR)
                p.vel.x *= -c;
            else
                p.vel.y *= -c;

            archivo << "t=" << t << " -> Colision con obstaculo cuadrado\n";
        }
    }
}

void Simulador::colisionesParticulas(double t) {
    for (size_t i = 0; i < particulas.size(); ++i) {
        for (size_t j = i + 1; j < particulas.size(); ++j) {
            Particula& A = particulas[i];
            Particula& B = particulas[j];

            if (!A.activa || !B.activa) continue;

            double dist = (A.pos - B.pos).magnitude();
            if (dist <= A.radio + B.radio) {
                archivo << "t=" << t << " -> Fusion particulas " << i << " y " << j << "\n";

                double M = A.masa + B.masa;
                double vxf = (A.vel.x*A.masa + B.vel.x*B.masa) / M;
                double vyf = (A.vel.y*A.masa + B.vel.y*B.masa) / M;
                double xf = (A.pos.x*A.masa + B.pos.x*B.masa) / M;
                double yf = (A.pos.y*A.masa + B.pos.y*B.masa) / M;

                A.pos = {xf, yf};
                A.vel = {vxf, vyf};
                A.masa = M;
                A.radio = sqrt(A.radio*A.radio + B.radio*B.radio);
                B.activa = false;
            }
        }
    }
}

void Simulador::simular(double tiempo_total, double dt) {
    double t = 0;

    while (t <= tiempo_total) {
        archivo << "\nTiempo " << t << "\n";

        for (auto& p : particulas) {
            if (!p.activa) continue;

            p.mover(dt);
            colisionesPared(p, t);
            colisionesObstaculos(p, t);

            archivo << "Particula (" << p.pos.x << ", " << p.pos.y << ")\n";
        }

        colisionesParticulas(t);
        t += dt;
    }

    archivo.close();
    std::cout << "Simulacion finalizada. Datos guardados en salida.txt\n";
}

