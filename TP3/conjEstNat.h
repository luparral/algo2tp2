#ifndef CONJESTNAT_H
#define CONJESTNAT_H

#include <iostream>
#include <assert.h>
#include "Modulos-CPP/aed2.h"
#include "algoritmos.h"


using namespace aed2;

//void heapsort(Arreglo<Nat> a){}
class ConjEstNat
{
	public:
		ConjEstNat();
		//~ConjEstNat();
		class const_Iterador;
		ConjEstNat(const Conj<Nat> &c);
		bool Pertenece(Nat n);
		Nat Cardinal() const;
		const_Iterador CrearIt() const;
		
		class const_Iterador
		{
			public:
				const_Iterador(const ConjEstNat &c);
				void Proximo();
				Nat Actual() const;
				bool HayProx() const; 
			private:
				Arreglo<Nat> _lista;
				Nat _pos;
		};
		
	private:
		Arreglo<Nat> _array;
};
ConjEstNat::ConjEstNat(): _array(Arreglo<Nat>()){}

//ConjEstNat::~ConjEstNat() {delete _array;}

ConjEstNat::ConjEstNat(const Conj<Nat> &c){
	typename Conj<Nat>::const_Iterador it = c.CrearIt();
	Nat i=0;
	Arreglo<Nat> a = Arreglo<Nat>(c.Cardinal());
	while(it.HaySiguiente()){
		a.Definir(i,it.Siguiente());
		i++;
		it.Avanzar();
	}
	heapsort(a);
	_array = a;
}

bool ConjEstNat::Pertenece(Nat n)
{
	bool b=false;
	Nat i=0;
	while (i<_array.Tamanho()){
		b = (b || _array[i]==n);
		i++;
	}
	return b;
}

Nat ConjEstNat::Cardinal() const
{
	return _array.Tamanho();
}

typename ConjEstNat::const_Iterador ConjEstNat::CrearIt() const 
{
	return const_Iterador(*(this));
}

ConjEstNat::const_Iterador::const_Iterador(const ConjEstNat &c): _lista(c._array), _pos(0) {}

void ConjEstNat::const_Iterador::Proximo()
{
	assert(_pos < _lista.Tamanho());
	_pos++;
}

Nat ConjEstNat::const_Iterador::Actual() const
{
	return _lista[_pos];
}

bool ConjEstNat::const_Iterador::HayProx() const
{
	return (_pos < _lista.Tamanho());
}



/*
cambios:
ItConjEstNat ahora se llama const_Iterador, porque en todos los modulos basicos aparecia asi
Las estructuras ahora tienen un _card porque no puedo pedir longitud a un array

*/

#endif
