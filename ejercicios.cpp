#include "ejercicios.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "auxiliares.h"

using namespace std;
//sajdnfaskjnfdk

/******++++**************************** EJERCICIO tiempoTotal
 * ***********+++***********************/
tiempo tiempoMinimo(viaje v) {
    tiempo aux = get<0>(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (get<0>(v[i]) < aux) {
            aux = get<0>(v[i]);
        }
    }
    return aux;
}

tiempo tiempoMaximo(viaje v) {
    tiempo aux = get<0>(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (get<0>(v[i]) > aux) {
            aux = get<0>(v[i]);
        }
    }
    return aux;
}

tiempo tiempoTotal(viaje v) {
    return tiempoMaximo(v) - tiempoMinimo(v);
}

/************++*********************** EJERCICIO distanciaTotal
 * ************++*********************/

viaje viajeOrdenado(viaje v) {
    viaje aux = v;



    return aux;
}

distancia distanciaTotal(viaje v) {
    distancia d;
    // codigo

    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad
 * **********************************/
bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    // codigo

    return resp;
}

/************************************ EJERCICIO recorridoCubierto
 * *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    // codigo

    return resp;
}

/***************************************** EJERCICIO flota
 * ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp;
    // codigo

    return resp;
}

/************************************** EJERCICIO construirGrilla
 * *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    // codigo

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos
 * ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp;
    // codigo

    return resp;
}

/************************************* EJERCICIO corregirViaje
 * ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores) {
    // codig

    return;
}
