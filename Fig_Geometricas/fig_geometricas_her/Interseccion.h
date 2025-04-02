// Interseccion.h
#ifndef _INTERSECCION_H
#define _INTERSECCION_H

#include "Circulo.h"

class Interseccion {
public:
    /**
     * Constructor que recibe dos círculos
     * @param c1 Primer círculo
     * @param c2 Segundo círculo
     */
    Interseccion(Circulo& c1, Circulo& c2);
    
    /**
     * Verifica si hay intersección entre los círculos
     * @return true si hay intersección, false en caso contrario
     */
    bool hayInterseccion();
    
    /**
     * Calcula el área de la intersección de los círculos
     * @return Área de la intersección o 0 si no hay intersección
     */
    float areaInterseccion();
    
    /**
     * Obtiene los puntos de intersección de los círculos
     * @param x1 Coordenada x del primer punto de intersección
     * @param y1 Coordenada y del primer punto de intersección
     * @param x2 Coordenada x del segundo punto de intersección
     * @param y2 Coordenada y del segundo punto de intersección
     * @return Número de puntos de intersección (0, 1 o 2)
     */
    int puntosInterseccion(float& x1, float& y1, float& x2, float& y2);
    
private:
    Circulo _circulo1;
    Circulo _circulo2;
    
    /**
     * Calcula la distancia entre los centros de los círculos
     * @return Distancia entre centros
     */
    float distanciaCentros();
};

#endif // _INTERSECCION_H