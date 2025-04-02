#include "Interseccion.h"
#include <cmath>

/**
 * Constructor que recibe dos círculos
 */
Interseccion::Interseccion(Circulo& c1, Circulo& c2) : _circulo1(c1), _circulo2(c2) {
}

/**
 * Calcula la distancia entre los centros de los círculos
 */
float Interseccion::distanciaCentros() {
    float dx = _circulo1.getX() - _circulo2.getX();
    float dy = _circulo1.getY() - _circulo2.getY();
    return std::sqrt(dx*dx + dy*dy);
}

/**
 * Verifica si hay intersección entre los círculos
 */
bool Interseccion::hayInterseccion() {
    float distancia = distanciaCentros();
    float sumaRadios = _circulo1.getRadio() + _circulo2.getRadio();
    float diferenciaRadios = std::abs(_circulo1.getRadio() - _circulo2.getRadio());
    
    // Hay intersección si la distancia es menor que la suma de los radios
    // y mayor que la diferencia absoluta de los radios
    return (distancia < sumaRadios && distancia > diferenciaRadios);
}

/**
 * Calcula el área de la intersección de los círculos
 */
float Interseccion::areaInterseccion() {
    if (!hayInterseccion()) {
        return 0.0;
    }
    
    float d = distanciaCentros();
    float r1 = _circulo1.getRadio();
    float r2 = _circulo2.getRadio();
    
    // Fórmula para calcular el área de intersección de dos círculos
    float parte1 = r1*r1 * std::acos((d*d + r1*r1 - r2*r2) / (2*d*r1));
    float parte2 = r2*r2 * std::acos((d*d + r2*r2 - r1*r1) / (2*d*r2));
    float parte3 = 0.5 * std::sqrt((-d+r1+r2) * (d+r1-r2) * (d-r1+r2) * (d+r1+r2));
    
    return parte1 + parte2 - parte3;
}

/**
 * Obtiene los puntos de intersección de los círculos
 * Devuelve la cantidad de puntos de intersección (0, 1 o 2)
 */
int Interseccion::puntosInterseccion(float& x1, float& y1, float& x2, float& y2) {
    float d = distanciaCentros();
    float r1 = _circulo1.getRadio();
    float r2 = _circulo2.getRadio();
    
    // No hay intersección
    if (d > r1 + r2 || d < std::abs(r1 - r2)) {
        return 0;
    }
    
    // Los círculos son tangentes (un solo punto de intersección)
    if (std::abs(d - (r1 + r2)) < 1e-6 || std::abs(d - std::abs(r1 - r2)) < 1e-6) {
        // Calcular el punto de tangencia
        float cx1 = _circulo1.getX();
        float cy1 = _circulo1.getY();
        float cx2 = _circulo2.getX();
        float cy2 = _circulo2.getY();
        
        // Si los círculos son tangentes externos
        if (std::abs(d - (r1 + r2)) < 1e-6) {
            x1 = cx1 + (r1 / d) * (cx2 - cx1);
            y1 = cy1 + (r1 / d) * (cy2 - cy1);
        } 
        // Si los círculos son tangentes internos
        else {
            if (r1 > r2) {
                x1 = cx1 + (r1 / d) * (cx2 - cx1);
                y1 = cy1 + (r1 / d) * (cy2 - cy1);
            } else {
                x1 = cx2 + (r2 / d) * (cx1 - cx2);
                y1 = cy2 + (r2 / d) * (cy1 - cy2);
            }
        }
        
        x2 = x1;
        y2 = y1;
        return 1;
    }
    
    // Dos puntos de intersección
    float cx1 = _circulo1.getX();
    float cy1 = _circulo1.getY();
    float cx2 = _circulo2.getX();
    float cy2 = _circulo2.getY();
    
    // Calculamos los puntos de intersección usando fórmulas geométricas
    float a = (r1*r1 - r2*r2 + d*d) / (2*d);
    float h = std::sqrt(r1*r1 - a*a);
    
    // Punto medio entre las intersecciones
    float px = cx1 + a * (cx2 - cx1) / d;
    float py = cy1 + a * (cy2 - cy1) / d;
    
    // Los dos puntos de intersección
    x1 = px + h * (cy2 - cy1) / d;
    y1 = py - h * (cx2 - cx1) / d;
    x2 = px - h * (cy2 - cy1) / d;
    y2 = py + h * (cx2 - cx1) / d;
    
    return 2;
}