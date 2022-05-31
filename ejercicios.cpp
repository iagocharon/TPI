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
    viaje auxViaje = v;
    for (int i = 0; i < auxViaje.size(); i++) {
        for (int j = 0; j < auxViaje.size() - i; j++) {
            if (get<0>(auxViaje[j]) > get<0>(auxViaje[j + 1])) {
                puntoViaje auxPunto = auxViaje[j];
                auxViaje[j] = auxViaje[j + 1];
                auxViaje[j + 1] = auxPunto;
            }
        }
    }
    return auxViaje;
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

/***************************************** EJERCICIO flota
 * ***************************************/
bool estabaEnViaje(viaje v, tiempo t0, tiempo tf) {
    for (int i = 0; i < v.size(); i++) {
        if (get<0>(v[i]) >= t0 && get<0>(v[i]) <= tf) {
            return true;
        }
    }
    return false;
}

int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    for (int i = 0; i < f.size(); i++) {
        if (estabaEnViaje(f[i], t0, tf)) {
            resp++;
        }
    }
    return resp;
}

/************************************ EJERCICIO recorridoCubierto
 * *******************************/
bool estaCubierto(gps p, viaje v, distancia u) {
    for (int i = 0; i < v.size(); i++) {
        if (distanciaEntre(p, get<1>(v[i])) <= u) {
            return true;
        }
    }
    return false;
}

vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    for (int i = 0; i < r.size(); i++) {
        if (!estaCubierto(r[i], v, u)) {
            resp.push_back(r[i]);
        }
    }
    return resp;
}

/************************************** EJERCICIO construirGrilla
 * *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    int ladoHorizontal = (get<0>(esq2) - get<0>(esq1)) / n;
    int ladoVertical = (get<1>(esq2) - get<1>(esq1)) / m;
    grilla resp = {};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            gps auxEsq1 = {get<0>(esq1) + i * ladoHorizontal,
                           get<1>(esq1) + j * ladoVertical};
            gps auxEsq2 = {get<0>(esq1) + (i + 1) * ladoHorizontal,
                           get<1>(esq1) + (j + 1) * ladoVertical};
            resp.push_back({auxEsq1, auxEsq2, {i, j}});
        }
    }

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos
 * ******************************/
nombre getNombreCelda(gps p, grilla g) {
    for (int i = 0; i < g.size(); i++) {
        if (p >= get<0>(g[i]) && p <= get<1>(g[i])) {
            return get<2>(g[i]);
        }
    }
    return {-1, -1};
}

int distanciaEnCeldas(gps p1, gps p2, grilla g) {
    nombre n1 = getNombreCelda(p1, g);
    nombre n2 = getNombreCelda(p2, g);
    return abs(get<0>(n1) - get<0>(n2)) + abs(get<1>(n1) - get<1>(n2));
}

int cantidadDeSaltos(grilla g, viaje v) {
    int resp = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        if (distanciaEnCeldas(get<1>(v[i]), get<1>(v[i + 1]), g) >= 2) {
            resp++;
        }
    }

    return resp;
}

/************************************* EJERCICIO corregirViaje
 * ******************************/

bool esError(puntoViaje p, vector<tiempo> errores) {
    for (int i = 0; i < errores.size(); i++) {
        if (get<0>(p) == errores[i]) {
            return true;
        }
    }
    return false;
}

void setPuntosCercanos(tiempo error, viaje v, vector<tiempo> errores,
                       puntoViaje puntoCercano1, puntoViaje puntoCercano2) {
    puntoCercano1 = v[0];
    puntoCercano2 = v[0];
    tiempo minimo = (tiempoMaximo(v) - tiempoMinimo(v));
    for (int i = 0; i < v.size(); i++) {
        if ((abs(get<0>(v[i]) - error) < minimo) &&
            (abs(get<0>(v[i]) - error) != 0) && (!esError(v[i], errores))) {
            minimo = abs(get<0>(v[i]) - error);
            puntoCercano1 = v[i];
        }
    }

    tiempo minimo = (tiempoMaximo(v) - tiempoMinimo(v));
    for (int i = 0; i < v.size(); i++) {
        if ((abs(get<0>(v[i]) - error) < minimo) &&
            (abs(get<0>(v[i]) - error) != 0) && (!esError(v[i], errores)) &&
            (v[i] != puntoCercano1)) {
            minimo = abs(get<0>(v[i]) - error);
            puntoCercano2 = v[i];
        }
    }
}

int getIndiceViaje(viaje v, tiempo t) {
    for (int i = 0; i < v.size(); i++) {
        if (get<0>(v[i]) == t) {
            return i;
        }
    }
    return -1;
}

double velocidadMedia(puntoViaje p1, puntoViaje p2) {
    return distanciaEntre(get<1>(p1), get<1>(p2)) / (get<0>(p2) - get<0>(p1));
}

puntoViaje puntoCorregido(puntoViaje error, puntoViaje puntoCercano1,
                          puntoViaje puntoCercano2) {
    double velocidadMediaPuntosCercanos =
        velocidadMedia(puntoCercano1, puntoCercano2);
    tiempo tiempoHastaError = get<0>(error) - get<0>(puntoCercano1);
    distancia distanciaHastaError =
        velocidadMediaPuntosCercanos * tiempoHastaError;
    double factorRecorrido =
        (distanciaHastaError /
         distanciaEntre(get<1>(puntoCercano1), get<1>(puntoCercano2)));

    distancia distanciaHorizontalRecorrida =
        (get<0>(get<1>(puntoCercano2)) - get<0>(get<1>(puntoCercano1))) *
        factorRecorrido;
    distancia distanciaVerticalRecorrida =
        (get<1>(get<1>(puntoCercano2)) - get<1>(get<1>(puntoCercano1))) *
        factorRecorrido;

    puntoViaje aux = error;

    get<0>(get<1>(aux)) =
        get<0>(get<1>(puntoCercano1)) + distanciaHorizontalRecorrida;

    get<1>(get<1>(aux)) =
        get<1>(get<1>(puntoCercano1)) + distanciaVerticalRecorrida;

    return aux;
}

void corregirViaje(viaje& v, vector<tiempo> errores) {
    for (int i = 0; i < errores.size(); i++) {
        puntoViaje puntoCercano1, puntoCercano2;
        v[i] = puntoCorregido(v[i], puntoCercano1, puntoCercano2);
    }

    return;
}
