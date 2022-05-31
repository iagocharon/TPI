#include "ejercicios.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "auxiliares.h"

using namespace std;

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

tiempo tiempoTotal(viaje v) { return tiempoMaximo(v) - tiempoMinimo(v); }

/************++*********************** EJERCICIO distanciaTotal
 * ************++*********************/
viaje viajeOrdenado(viaje v) {
    viaje aux = v;
    sort(aux.begin(), aux.end(),
         [](auto a, auto b) { return get<1>(a) < get<1>(b); });
    return aux;
}

distancia distanciaEntre(gps a, gps b) {
    return sqrt(pow(get<0>(a) - get<0>(b), 2) + pow(get<1>(a) - get<1>(b), 2));
}

distancia distanciaTotal(viaje v) {
    distancia d = 0;
    viaje aux = viajeOrdenado(v);
    for (int i = 0; i < aux.size(); i++) {
        d += distanciaEntre(get<1>(aux[i - 1]), get<1>(aux[i]));
    }
    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad
 * **********************************/
bool hayExceso(puntoViaje a, puntoViaje b) {
    return distanciaEntre(get<1>(a), get<1>(b)) / (get<0>(b) - get<0>(a)) > 80;
}

bool excesoDeVelocidad(viaje v) {
    for (int i = 0; i < v.size() - 1; i++) {
        if (hayExceso(v[i], v[i + 1])) {
            return true;
        }
    }
    return false;
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
