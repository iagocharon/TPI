#ifndef TRANSPORTEURBANO_DEFINICIONES_H
#define TRANSPORTEURBANO_DEFINICIONES_H

#include <cmath>
#include <tuple>
#include <vector>

using namespace std;

#define T0 1651596890.0

// DEFINICIONES DE TIPO
typedef double tiempo;
typedef double distancia;
typedef tuple<double, double> gps;
typedef vector<gps> recorrido;
typedef tuple<tiempo, gps> puntoViaje;
typedef vector<tuple<tiempo, gps> > viaje;
typedef tuple<int, int> nombre;
typedef tuple<gps, gps, nombre> celda;
typedef vector<celda> grilla;

#endif  // TRANSPORTEURBANO_DEFINICIONES_H