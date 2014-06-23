#ifndef TITULO_H
#define TITULO_H
//#include "aed2.h"
#include <string>

typedef std::string Name;
typedef int Dinero;

class Titulo {
	private:
		Name nombre_;
		int maxAcciones_;
		Dinero cotizacion_;
		bool enAlza_;

	public:
		
		//Crea un titulo con la info pasada por parámetro
		//Es el equivalente a crearTitulo!
		Titulo(Name nombre, int maxAcciones, Dinero cotizacion, bool enAlza) : nombre_(nombre), maxAcciones_(maxAcciones), cotizacion_(cotizacion), enAlza_(enAlza){}

		Name nombre() const;
		int maxAcciones() const;
		Dinero cotizacion() const;
		bool enAlza() const;
		void recotizar(Dinero d);
};

//pasar a titulo.cpp
Name Titulo::nombre() const {
	return nombre_;
}

int Titulo::maxAcciones() const {
	return maxAcciones_;
}

Dinero Titulo::cotizacion() const {
	return cotizacion_;
}

bool Titulo::enAlza() const {
	return enAlza_;
}

void Titulo::recotizar(Dinero d){
	enAlza_ = d > cotizacion_;
	cotizacion_ = d;
}

#endif