#ifndef TITULO_H
#define TITULO_H
//#include "aed2.h"
#include <string>
#include "Modulos-CPP/aed2.h"

typedef std::string Name;
typedef Nat Dinero;

class Titulo {
	private:
		Name nombre_;
		Nat maxAcciones_;
		Dinero cotizacion_;
		bool enAlza_;

	public:
		//Crea un titulo con la info pasada por parámetro
		//Es el equivalente a crearTitulo!
		Titulo(Name nombre, Nat maxAcciones, Dinero cotizacion) : nombre_(nombre), maxAcciones_(maxAcciones), cotizacion_(cotizacion), enAlza_(true){}
		Titulo(const Titulo& otro): nombre_(otro.nombre()), maxAcciones_(otro.maxAcciones()), cotizacion_(otro.cotizacion()), enAlza_(otro.enAlza()){}

		Name nombre() const;
		Nat maxAcciones() const;
		Dinero cotizacion() const;
		bool enAlza() const;
		void recotizar(Dinero d);

		Titulo(): nombre_(""), maxAcciones_(0), cotizacion_(0), enAlza_(true){}

};

//pasar a titulo.cpp


#endif
