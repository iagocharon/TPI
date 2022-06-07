#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include <fstream>
#include <iomanip>
#include <iostream>

#include "definiciones.h"
#include "string"

double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
gps obtenerEsq1(celda celda);
gps obtenerEsq2(celda celda);
nombre obtenerNombre(celda celda);
int obtenerFila(nombre nombre);
int obtenerColumna(nombre nombre);
double distEnKM(gps posicion1, gps posicion2);
double velocidadMedia(puntoViaje p1, puntoViaje p2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);
bool sonGrillasIguales(grilla g1, grilla g2);
void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos,
                                string nombreArchivo);

#endif  // TRANSPORTEURBANO_AUXILIARES_H
