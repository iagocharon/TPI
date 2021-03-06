#include "auxiliares.h"

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) { return get<0>(posicion); }

double obtenerLongitud(gps posicion) { return get<1>(posicion); }

gps obtenerPosicion(tuple<tiempo, gps> medicion) { return get<1>(medicion); }

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) { return get<0>(medicion); }
gps obtenerEsq1(celda celda) { return get<0>(celda); }
gps obtenerEsq2(celda celda) { return get<1>(celda); }
nombre obtenerNombre(celda celda) { return get<2>(celda); }
int obtenerFila(nombre nombre) { return get<0>(nombre); }
int obtenerColumna(nombre nombre) { return get<1>(nombre); }
tiempo obtenerTiempoMaximo(tuple<tiempo, tiempo> tiemposMaximoYMinimo) {
    return get<0>(tiemposMaximoYMinimo);
}
tiempo obtenerTiempoMinimo(tuple<tiempo, tiempo> tiemposMaximoYMinimo) {
    return get<1>(tiemposMaximoYMinimo);
}
puntoViaje obtenerPrimerPuntoCercano(tuple<puntoViaje, puntoViaje> puntosCercanos) {
    return get<0>(puntosCercanos);
}
puntoViaje obtenerSegundoPuntoCercano(tuple<puntoViaje, puntoViaje> puntosCercanos) {
    return get<1>(puntosCercanos);
}

double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1)*pi / 180.0;
    latitud2 = (latitud2)*pi / 180.0;

    // aplico la formula
    double a =
        pow(sin(distanciaLatitud / 2), 2) +
        pow(sin(distanciaLongitud / 2), 2) * cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

double velocidadMedia(puntoViaje p1, puntoViaje p2) {
    return (distEnKM(obtenerPosicion(p1), obtenerPosicion(p2))) /
           (obtenerTiempo(p2) - obtenerTiempo(p1));
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud) {
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude =
        lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);
}

bool sonGrillasIguales(grilla g1, grilla g2) {
    if (g1.size() != g2.size()) {
        return false;
    }

    for (int i = 0; i < g1.size(); i++) {
        bool existe = false;
        for (int j = 0; j < g2.size(); j++) {
            if (obtenerNombre(g1[i]) == obtenerNombre(g2[j])) {
                existe = true;
                if (g1[i] != g2[j]) {
                    return false;
                }
            }
        }
        if (!existe) {
            return false;
        }
    }

    return true;
}

gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) { return make_tuple(t, g); }

void guardarGrillaEnArchivo(grilla g, string nombreArchivo) {
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for (int i = 0; i < g.size(); i++) {
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t" << esq1_lng << "\t" << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")" << endl;
    }
    myfile.close();
}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos,
                                string nombreArchivo) {
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for (int i = 0; i < recorridos.size(); i++) {
        for (int k = 0; k < recorridos[i].size(); k++) {
            lat = get<0>(recorridos[i][k]);
            lng = get<1>(recorridos[i][k]);

            myfile << i << "\t" << lat << "\t" << lng << endl;
        }
    }
    myfile.close();
}
