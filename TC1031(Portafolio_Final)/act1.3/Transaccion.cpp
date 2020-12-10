#include "Transaccion.hpp"

// Constructor sin parámetros
Transaccion::Transaccion() {
    fecha = "-";
    hora = "-";
    IpOrigen = "-";
    transaccion1 = "-";
    nomOrigen = "-";
    IpDestino = "-";
    transaccion2 = "-";
    nomDestino = "-";
}

// Constructor con parámetros
Transaccion::Transaccion(string fech, string hor, string IpOri, string trans1, string nomOri, string IpDes, string trans2, string nomDes) {
    fecha = fech;
    hora = hor;
    IpOrigen = IpOri;
    transaccion1 = trans1;
    nomOrigen = nomOri;
    IpDestino = IpDes;
    transaccion2 = trans2;
    nomDestino = nomDes;
}

// Destructor
Transaccion::~Transaccion(){

}
// Métdos set
void Transaccion::setFecha(string fech) {
  fecha = fech;
}

void Transaccion::setHora(string hor) {
  hora = hor;
}

void Transaccion::setIpOrigen(string IpOri) {
  IpOrigen = IpOri;
}

void Transaccion::setTransaccion1(string trans1) {
  transaccion1 = trans1;
}

void Transaccion::setNomOrigen(string nomOri) {
  nomOrigen = nomOri;
}

void Transaccion::setIpDestino(string IpDes) {
  IpDestino = IpDes;
}

void Transaccion::setTransaccion2(string trans2) {
  transaccion2 = trans2;
}

void Transaccion::setNomDestino(string nomDes) {
  nomDestino = nomDes;
}

// Métodos get
string Transaccion::getFecha() {
  return fecha;
}

string Transaccion::getHora() {
  return hora;
}

string Transaccion::getIpOrigen() {
  return IpOrigen;
}

string Transaccion::getTransaccion1() {
  return transaccion1;
}

string Transaccion::getNomOrigen() {
  return nomOrigen;
}

string Transaccion::getIpDestino() {
  return IpDestino;
}

string Transaccion::getTransaccion2() {
  return transaccion2;
}

string Transaccion::getNomDestino() {
  return nomDestino;
}

// Método str
// Devuelve todos los atributos separados por un espacio
string Transaccion::str() {
  return fecha + " " + hora + " " + IpOrigen + " " + transaccion1 + " " + nomOrigen + " " + IpDestino + " " + transaccion2 + " " + nomDestino;
}