#include "ejercicios.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "auxiliares.h"

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal
 * ***********+++***********************/

tuple<tiempo, tiempo> tiemposMaximoYMinimo(viaje v) {
    tiempo max = obtenerTiempo(v[0]);     // O(1)
    tiempo min = obtenerTiempo(v[0]);     // O(1)
    for (int i = 1; i < v.size(); i++) {  // 0(n)
        if (obtenerTiempo(v[i]) > max) {  // O(1)
            max = obtenerTiempo(v[i]);
        }
        if (obtenerTiempo(v[i]) < min) {  // O(1)
            min = obtenerTiempo(v[i]);
        }
    }
    return {max, min};
}

tiempo tiempoTotal(viaje v) {
    return get<0>(tiemposMaximoYMinimo(v)) -
           get<1>(tiemposMaximoYMinimo(v));  // 0(n) no se como justificar bien
                                             // este, es 0(n)-0(n) => O(n)??
}

/************++*********************** EJERCICIO distanciaTotal
 * ************++*********************/

viaje viajeOrdenado(viaje v) {  // n=|v|
    viaje auxViaje = v;
    sort(auxViaje.begin(), auxViaje.end());
    return auxViaje;
}

distancia distanciaTotal(viaje v) {  // n=|v|
    distancia d = 0;
    viaje aux = viajeOrdenado(v);  // O(n^2)

    for (int i = 0; i < aux.size() - 1; i++) {  // O(n)
        d += distEnKM(obtenerPosicion(aux[i]), obtenerPosicion(aux[i + 1]));
    }
    return d;
}  // O(n^2) + O(n) = O(n^2)

/*****************************+***** EJERCICIO excesoDeVelocidad
 * **********************************/
bool excesoDeVelocidad(viaje v) {
    viaje aux = viajeOrdenado(v);
    for (int i = 0; i < aux.size() - 1; i++) {
        if (velocidadMedia(aux[i], aux[i + 1]) * 3600 > 80) {
            return true;
        }
    }
    return false;
}

/***************************************** EJERCICIO flota
 * ***************************************/
bool estabaEnViaje(viaje v, tiempo t0, tiempo tf) {
    for (int i = 0; i < v.size(); i++) {
        if (obtenerTiempo(v[i]) >= t0 && obtenerTiempo(v[i]) <= tf) {
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
bool estaCubierto(gps p, viaje v, distancia u) {  // n=|v|
    for (int i = 0; i < v.size(); i++) {          // O(n)
        if (distEnKM(p, obtenerPosicion(v[i])) < u) {
            return true;
        }
    }
    return false;
}

vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {  // m=|r|
    vector<gps> resp;
    for (int i = 0; i < r.size(); i++) {  // O(m) * O(n)= O(n x m)
        if (!estaCubierto(r[i], v, u)) {  // O(n)
            resp.push_back(r[i]);
        }
    }
    return resp;  // O(n x m)
}

/************************************** EJERCICIO construirGrilla
 * *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    distancia ladoHorizontal =
        (obtenerLongitud(esq2) - obtenerLongitud(esq1)) / n;
    distancia ladoVertical = (obtenerLatitud(esq2) - obtenerLatitud(esq1)) / m;
    grilla resp = {};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            gps auxEsq1 = {obtenerLongitud(esq1) + i * ladoHorizontal,
                           obtenerLatitud(esq1) + j * ladoVertical};
            gps auxEsq2 = {obtenerLongitud(esq1) + (i + 1) * ladoHorizontal,
                           obtenerLatitud(esq1) + (j + 1) * ladoVertical};
            resp.push_back({auxEsq1, auxEsq2, {i + 1, j + 1}});
        }
    }
    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos
 * ******************************/
nombre getNombreCelda(gps p, grilla g) {
    for (int i = 0; i < g.size(); i++) {
        if ((obtenerLatitud(p) >= obtenerLatitud(obtenerEsq1(g[i]))) &&
            (obtenerLatitud(p) <= obtenerLatitud(obtenerEsq2(g[i]))) &&
            (obtenerLongitud(p) >= obtenerLongitud(obtenerEsq1(g[i]))) &&
            (obtenerLongitud(p) <= obtenerLongitud(obtenerEsq2(g[i])))) {
            return obtenerNombre(g[i]);
        }
    }
    return {-1, -1};
}

int distanciaEnCeldas(gps p1, gps p2, grilla g) {
    nombre n1 = getNombreCelda(p1, g);
    nombre n2 = getNombreCelda(p2, g);
    return abs(obtenerFila(n1) - obtenerFila(n2)) +
           abs(obtenerColumna(n1) - obtenerColumna(n2));
}

int siguienteEnGrilla(grilla g, viaje v, int index) {
    nombre noExiste = {-1, -1};
    int posSiguiente = -1;
    for (int i = index + 1; i < v.size(); i++) {
        if (getNombreCelda(obtenerPosicion(v[i]), g) != noExiste) {
            return i;
        }
    }
    return -1;
}

int cantidadDeSaltos(grilla g, viaje v) {
    int resp = 0;
    for (int i = 0; i < v.size(); i++) {
        if (siguienteEnGrilla(g, v, i) != -1) {
            if (distanciaEnCeldas(
                    obtenerPosicion(v[i]),
                    obtenerPosicion(v[siguienteEnGrilla(g, v, i)]), g) >= 2) {
                resp++;
            }
        }
    }
    return resp;
}

/************************************* EJERCICIO corregirViaje
 * ******************************/

bool esError(puntoViaje p, vector<tiempo> errores) {
    for (int i = 0; i < errores.size(); i++) {
        if (obtenerTiempo(p) == errores[i]) {
            return true;
        }
    }
    return false;
}

tuple<puntoViaje, puntoViaje> puntosCercanos(tiempo error, viaje v,
                                             vector<tiempo> errores) {
    puntoViaje puntoCercano1;
    puntoViaje puntoCercano2;
    tiempo minimo =
        (get<0>(tiemposMaximoYMinimo(v)) - get<1>(tiemposMaximoYMinimo(v)));
    for (int i = 0; i < v.size(); i++) {
        if ((abs(obtenerTiempo(v[i]) - error) < minimo) &&
            (!esError(v[i], errores))) {
            minimo = abs(obtenerTiempo(v[i]) - error);
            puntoCercano1 = v[i];
        }
    }

    minimo =
        (get<0>(tiemposMaximoYMinimo(v)) - get<1>(tiemposMaximoYMinimo(v)));
    for (int i = 0; i < v.size(); i++) {
        if ((abs(obtenerTiempo(v[i]) - error) < minimo) &&
            (!esError(v[i], errores)) && (v[i] != puntoCercano1)) {
            minimo = abs(obtenerTiempo(v[i]) - error);
            puntoCercano2 = v[i];
        }
    }

    if (obtenerTiempo(puntoCercano1) > obtenerTiempo(puntoCercano2)) {
        puntoViaje aux = puntoCercano1;
        puntoCercano1 = puntoCercano2;
        puntoCercano2 = aux;
    }
    return {puntoCercano1, puntoCercano2};
}

int getIndiceViaje(viaje v, tiempo t) {
    for (int i = 0; i < v.size(); i++) {
        if (obtenerTiempo(v[i]) == t) {
            return i;
        }
    }
}

puntoViaje puntoCorregido(puntoViaje error, puntoViaje puntoCercano1,
                          puntoViaje puntoCercano2) {
    double velocidadMediaPuntosCercanos =
        velocidadMedia(puntoCercano1, puntoCercano2);
    tiempo tiempoHastaError =
        obtenerTiempo(error) - obtenerTiempo(puntoCercano1);
    distancia distanciaHastaError =
        velocidadMediaPuntosCercanos * tiempoHastaError;
    double factorRecorrido =
        (distanciaHastaError / distEnKM(obtenerPosicion(puntoCercano1),
                                        obtenerPosicion(puntoCercano2)));

    distancia distanciaHorizontalRecorrida =
        (obtenerLatitud(obtenerPosicion(puntoCercano2)) -
         obtenerLatitud(obtenerPosicion(puntoCercano1))) *
        factorRecorrido;
    distancia distanciaVerticalRecorrida =
        (obtenerLongitud(obtenerPosicion(puntoCercano2)) -
         obtenerLongitud(obtenerPosicion(puntoCercano1))) *
        factorRecorrido;

    double auxLatitud = obtenerLatitud(obtenerPosicion(puntoCercano1)) +
                        distanciaHorizontalRecorrida;

    double auxLongitud = obtenerLongitud(obtenerPosicion(puntoCercano1)) +
                         distanciaVerticalRecorrida;

    return {obtenerTiempo(error), {auxLatitud, auxLongitud}};
}

void corregirViaje(viaje &v, vector<tiempo> errores) {
    for (int i = 0; i < errores.size(); i++) {
        puntoViaje puntoCercano1 =
            get<0>(puntosCercanos(errores[i], v, errores));
        puntoViaje puntoCercano2 =
            get<1>(puntosCercanos(errores[i], v, errores));
        int indiceError = getIndiceViaje(v, errores[i]);
        v[indiceError] =
            puntoCorregido(v[indiceError], puntoCercano1, puntoCercano2);
    }
}
