# -*- coding: utf-8 -*-
"""
Created on Fri Nov 14 01:19:07 2025

@author: Andres Felipe
"""

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import re


# LECTURA DEL ARCHIVO DE SALIDA
with open("C:/Users/Andres Felipe/OneDrive/Escritorio/informatica II Andres Lafaurie/INFORMATICA 2/Practica 5-1/Plactica_Final_Laboratorio/Parte 1/Prueba_Prac5/salida.txt", "r", encoding="utf-8") as f:
    lineas = f.readlines() 

frames = []        # Lista de posiciones (x, y) por frame
frame_actual = []  # Frame temporal
tiempos = []

for linea in lineas:
    linea = linea.strip()

    # --- Detectar inicio de bloque temporal ---
    if linea.startswith("Tiempo"):
        # Guarda el frame anterior si tenía datos válidos
        if len(frame_actual) > 0:
            frames.append(frame_actual)
            frame_actual = []

        # Captura el número de tiempo (si existe)
        try:
            tiempo = float(linea.split()[1])
            tiempos.append(tiempo)
        except:
            pass

    # --- Detectar líneas de partículas ---
    elif linea.startswith("Particula"):
        # Extrae los números entre paréntesis
        numeros = re.findall(r"[-+]?\d*\.\d+|\d+", linea)
        if len(numeros) >= 2:
            x, y = map(float, numeros[:2])
            frame_actual.append((x, y))

    # --- Ignorar todo lo demás (colisiones, texto, líneas vacías) ---
    else:
        continue

# Agregar último frame si quedó pendiente
if len(frame_actual) > 0:
    frames.append(frame_actual)

# --- Filtrar frames vacíos o mal formados ---
frames = [f for f in frames if len(f) > 0]

print(f"Total de frames válidos: {len(frames)}")
print(f"Ejemplo de frame[0]: {frames[0]}")


# CONFIGURACIÓN DE LA FIGURA Y LOS OBSTÁCULOS
fig, ax = plt.subplots()
ax.set_xlim(0, 500)   # Mismo ancho de la caja
ax.set_ylim(0, 350)   # Mismo alto de la caja
ax.set_title("Simulación de partículas con colisiones")
ax.set_xlabel("Posición X")
ax.set_ylabel("Posición Y")

# Obstáculos definidos como en tu main.cpp
obstaculos = [
    (200, 120, 50),  # Centro izquierda
    (320, 100, 50),  # Centro derecha
    (260, 200, 40),  # Bien centrado
    (150, 150, 40),  # Para interacción de P2
]

# Dibujar los obstáculos como cuadrados azules
for (x, y, lado) in obstaculos:
    rect = plt.Rectangle((x, y), lado, lado, fill=False, edgecolor='blue', linewidth=2)
    ax.add_patch(rect)

# CONFIGURAR LOS ELEMENTOS GRÁFICOS DE LAS PARTÍCULAS

# Inicializa el scatter con un punto ficticio invisible
scat = ax.scatter([0], [0], s=60, c='orange', edgecolors='black', zorder=5)

#FUNCIONES DE ANIMACION
def init():
    scat.set_offsets([[0, 0]])  # Evita scatter vacío
    return scat,

def update(frame):
    # Si el frame está vacío o mal formado, usa un punto ficticio
    if frame is None or len(frame) == 0:
        scat.set_offsets([[0, 0]])
    else:
        # Asegura que frame sea array Nx2 válido
        try:
            scat.set_offsets(frame)
        except Exception as e:
            print("Frame inválido detectado:", e)
            scat.set_offsets([[0, 0]])
    return scat,


# Interval = 50 ms entre frames (~20 FPS)
ani = FuncAnimation(fig, update, frames=frames, init_func=init,
                    blit=True, interval=50, repeat=True)

plt.show()
