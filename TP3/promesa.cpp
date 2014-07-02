#include "promesa.h"
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

