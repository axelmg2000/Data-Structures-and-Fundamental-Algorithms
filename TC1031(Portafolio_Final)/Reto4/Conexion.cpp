// Developed by: Axel Mercado Gasque
// Start Date: October 15th 2020
// End date: October 15th 2020

/* ******************** 
    This file contains the implementation of the methods of the class "Conexion"
   ******************** */


#include "Conexion.hpp"

// Constructor with no parameters
Conexion::Conexion() {
    fecha = "-";
    hora = "-";
    IpOrigen = "-";
    conexion1 = "-";
    nomOrigen = "-";
    IpDestino = "-";
    conexion2 = "-";
    nomDestino = "-";
}

// Constructor with parameters
Conexion::Conexion(string fech, string hor, string IpOri, string trans1, string nomOri, string IpDes, string trans2, string nomDes) {
    fecha = fech;
    hora = hor;
    IpOrigen = IpOri;
    conexion1 = trans1;
    nomOrigen = nomOri;
    IpDestino = IpDes;
    conexion2 = trans2;
    nomDestino = nomDes;
}


// Set methods
void Conexion::setFecha(string fech) {
  fecha = fech;
}

void Conexion::setHora(string hor) {
  hora = hor;
}

void Conexion::setIpOrigen(string IpOri) {
  IpOrigen = IpOri;
}

void Conexion::setConexion1(string con1) {
  conexion1 = con1;
}

void Conexion::setNomOrigen(string nomOri) {
  nomOrigen = nomOri;
}

void Conexion::setIpDestino(string IpDes) {
  IpDestino = IpDes;
}

void Conexion::setConexion2(string con2) {
  conexion2 = con2;
}

void Conexion::setNomDestino(string nomDes) {
  nomDestino = nomDes;
}

// Get methods
string Conexion::getFecha() {
  return fecha;
}

string Conexion::getHora() {
  return hora;
}

string Conexion::getIpOrigen() {
  return IpOrigen;
}

string Conexion::getConexion1() {
  return conexion1;
}

string Conexion::getNomOrigen() {
  return nomOrigen;
}

string Conexion::getIpDestino() {
  return IpDestino;
}

string Conexion::getConexion2() {
  return conexion2;
}

string Conexion::getNomDestino() {
  return nomDestino;
}

// Str method
// Returns a string with all attribues seperated by a white space
string Conexion::str() {
  return fecha + " " + hora + " " + IpOrigen + " " + conexion1 + " " + nomOrigen + " " + IpDestino + " " + conexion2 + " " + nomDestino;
}