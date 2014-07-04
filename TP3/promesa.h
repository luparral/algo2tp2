#ifndef PROMESA_H
#define PROMESA_H

#include <string>
#include "Modulos-CPP/aed2.h"

typedef std::string Nombre;
enum TipoPromesa {COMPRA, VENTA};
typedef Nat Dinero;
typedef Nat Cant;

class Promesa {
	public:
		//Crea una promesa con la info pasada por parámetro-
		Promesa(Nombre titulo, TipoPromesa tipo, Dinero limite, Cant cantidad) : titulo_(titulo), tipo_(tipo), limite_(limite), cantidad_(cantidad){}
		const Nombre& titulo() const;
		TipoPromesa tipo() const;
		Dinero limite() const;
		Cant cantidad() const;
		bool operator!= (Promesa p) const;

	private:
		Nombre titulo_;
		TipoPromesa tipo_;
		Dinero limite_;
		Cant cantidad_;
};

#endif
