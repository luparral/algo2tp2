#include "titulo.h"

const Name& Titulo::nombre() const {
	return nombre_;
}


Nat Titulo::maxAcciones() const {
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
