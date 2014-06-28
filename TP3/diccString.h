#ifndef DICCSTRING_H
#define DICCSTRING_H

#include <iostream>
#include <assert.h>
#include "Modulos-CPP/aed2.h"

using namespace aed2;


template<typename T>
class DiccString {

	public:
	  	class Iterador;

		DiccString();
		~DiccString();
		void Definir(const String, const T&);
		bool Definido(const String) const;
		const T& Obtener(const String) const;
		Iterador Claves() const;

		class Iterador{
	    	public:
	        	Iterador(const DiccString<T> &d);
        		void Avanzar();
	        	const String& Siguiente() const;
	        	bool HaySiguiente() const;

	    	private:
	      		Lista<String>::const_Iterador it;
		};

	private:
		struct Nodo {
			Nodo();
			~Nodo();
	    	T significado;
			Arreglo< Nodo* > letras;
		};

		Nodo* _raiz;
		Lista<String> _claves;
		Nat _cantClaves;
};

template<class T>
DiccString<T>::Nodo::Nodo(){
	Arreglo< Nodo* > leters = Arreglo< Nodo* >(256);
	letras = leters;
}

template<class T>
DiccString<T>::Nodo::~Nodo() {
	Nat i = 256;
	while(i > 0){
		if(letras.Definido(i-1)){
			delete letras[i-1];
		}
		i--;
	}
}

template<class T>
DiccString<T>::DiccString(){
	_cantClaves = 0;
	_claves = Lista<String>();
	_raiz = new Nodo();
}

template<class T>
DiccString<T>::~DiccString(){
	delete _raiz;
}

template<class T>
void DiccString<T>::Definir(const String key, const T& value){
	_claves.AgregarAtras(key);
	_cantClaves++;
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	for(Nat i = 0;i < cantNodosNecesarios;i++){
		Nat posicionDelCarater = (Nat)key[i];
		if(!(actual->letras.Definido(posicionDelCarater))){
			Nodo* newNode = new Nodo();
			actual->letras.Definir(posicionDelCarater,newNode);
		}
		actual = actual->letras[posicionDelCarater];
	}
	actual->significado = value;
}

template<class T>
bool DiccString<T>::Definido(const String key) const{
	bool ret = true;
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	for(Nat i = 0;i < cantNodosNecesarios && ret;i++){
		Nat posicionDelCarater = (Nat)key[i];
		ret = actual->letras.Definido(posicionDelCarater);
		if(ret)
			actual = actual->letras[posicionDelCarater];
	}
	return ret;
}

template<class T>
const T& DiccString<T>::Obtener(const String key) const{
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	for(Nat i = 0;i < cantNodosNecesarios;i++){
		Nat posicionDelCarater = (Nat)key[i];
		actual = actual->letras[posicionDelCarater];
	}
	return actual->significado;
}

template<class T>
typename DiccString<T>::Iterador DiccString<T>::Claves() const {
	return Iterador(*(this));
}


/*
 *Implementación del iterador de claves
 */
template<class T>
DiccString<T>::Iterador::Iterador(const DiccString<T> &d): it(d._claves.CrearIt()) {}

template<class T>
void DiccString<T>::Iterador::Avanzar(){
	it.Avanzar();;
}

template<class T>
const String& DiccString<T>::Iterador::Siguiente() const{
	return it.Siguiente();
}

template<class T>
bool DiccString<T>::Iterador::HaySiguiente() const{
	return it.HaySiguiente();
}


#endif //DICCSTRING_H