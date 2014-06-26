#ifndef PROMESA_H
#define PROMESA_H
//#include "aed2.h"
#include <string>

typedef std::string Nombre;
enum TipoPromesa {COMPRA, VENTA};
typedef Nat Dinero;
typedef Nat Cant;

class Promesa {
	private:
		Nombre titulo_;
		TipoPromesa tipo_;
		Dinero limite_;
		Cant cantidad_;

	public:
		
		//Crea una promesa con la info pasada por parámetro
		//Es el equivalente a crearPromesa!
		Promesa(Nombre titulo, TipoPromesa tipo, Dinero limite, Cant cantidad) : titulo_(titulo), tipo_(tipo), limite_(limite), cantidad_(cantidad){}

		Nombre titulo() const;
		TipoPromesa tipo() const;
		Dinero limite() const;
		Cant cantidad() const;
		bool operator!= (Promesa p) const;
};

//pasar a promesa.cpp
Nombre Promesa::titulo() const {
	return titulo_;
}

TipoPromesa Promesa::tipo() const {
	return tipo_;
}

Dinero Promesa::limite() const {
	return limite_;
}

Cant Promesa::cantidad() const {
	return cantidad_;
}

bool Promesa::operator!=(Promesa p) const{
	return (!(titulo_ == p.titulo() && tipo_ == p.tipo() && limite_ == p.limite() && cantidad_ == p.cantidad()));
}

#endif
