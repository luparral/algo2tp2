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
#endif
