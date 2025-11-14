#include "Simulador.h"

int main() {
    // Caja un poco más pequeña para que haya más choques visibles
    Simulador sim(500, 350, 0.6); // coef. restitución 0.6

    // --- Partículas bien espaciadas (trayectorias parabólicas limpias) ---
    Particula p1(80, 300, 70, -120, 2, 10);   p1.gravedad = 9.0;
    Particula p2(150, 250, 60, -140, 3, 10);  p2.gravedad = 9.0;
    Particula p3(300, 280, -70, -100, 4, 12); p3.gravedad = 9.0;
    Particula p4(420, 260, -90, -110, 2, 10); p4.gravedad = 9.0;

    sim.agregarParticula(p1);
    sim.agregarParticula(p2);
    sim.agregarParticula(p3);
    sim.agregarParticula(p4);

    // --- Obstáculos centrados para que las trayectorias los usen ---
    sim.agregarObstaculo(Obstaculo(200, 120, 50));  // Centro izquierda
    sim.agregarObstaculo(Obstaculo(320, 100, 50));  // Centro derecha
    sim.agregarObstaculo(Obstaculo(260, 200, 40));  // Bien centrado
    sim.agregarObstaculo(Obstaculo(150, 150, 40));  // Para interacción de P2

    // Correr simulación
    sim.simular(10, 0.05);

    return 0;
}

