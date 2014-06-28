#ifndef DICCSTRING_H
#define DICCSTRING_H

#include <iostream>
#include <assert.h>
#include "Modulos-CPP/aed2.h"

using namespace aed2;


template<typename T>
class DiccString {

	public:
	  	class ItClaves;

		DiccString();
		~DiccString();
		void Definir(const String, const T&);
		bool Definido(const String) const;
		T& Significado(const String) const;
		ItClaves Claves() const;

		class ItClaves{
	    	public:
	        	ItClaves(const DiccString<T> &d);
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
	    	T* significado;
			Arreglo< Nodo* > letras;
		};

		Nodo* _raiz;
		Lista<String> _claves;
};

template<class T>
DiccString<T>::Nodo::Nodo(){
	letras = Arreglo< Nodo* >(256);
	significado = NULL;
}

template<class T>
DiccString<T>::Nodo::~Nodo() {
	if(significado != NULL){
		delete significado;
	}

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
	_claves = Lista<String>();
	_raiz = new Nodo();
}

template<class T>
DiccString<T>::~DiccString(){
	delete _raiz;
}

template<class T>
void DiccString<T>::Definir(const String key, const T& value){
	Nodo* actual = _raiz;
	Nat i = 0;
	while(i < key.length()){
		Nat posicionDelCarater = (Nat)key[i];
		if(!(actual->letras.Definido(posicionDelCarater))){
			Nodo* newNode = new Nodo();
			actual->letras.Definir(posicionDelCarater,newNode);
		}
		actual = actual->letras[posicionDelCarater];
		i++;
	}
	actual->significado = new T(value);
	_claves.AgregarAtras(key);
}

template<class T>
bool DiccString<T>::Definido(const String key) const{
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	Nat i = 0;
	while(i < cantNodosNecesarios){
		Nat posicionDelCarater = (Nat)key[i];
		if(actual->letras.Definido(posicionDelCarater)){
			actual = actual->letras[posicionDelCarater];
			i++;
		}else{
			return false;
		}
	}
	return actual->significado != NULL;
}

template<class T>
T& DiccString<T>::Significado(const String key) const{
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	Nat i = 0;
	while(i < cantNodosNecesarios){
		Nat posicionDelCarater = (Nat)key[i];
		actual = actual->letras[posicionDelCarater];
		i++;
	}
	return *actual->significado;
}

template<class T>
typename DiccString<T>::ItClaves DiccString<T>::Claves() const {
	return ItClaves(*(this));
}


/*
 *Implementación del iterador de claves
 */
template<class T>
DiccString<T>::ItClaves::ItClaves(const DiccString<T> &d): it(d._claves.CrearIt()) {}

template<class T>
void DiccString<T>::ItClaves::Avanzar(){
	it.Avanzar();;
}

template<class T>
const String& DiccString<T>::ItClaves::Siguiente() const{
	return it.Siguiente();
}

template<class T>
bool DiccString<T>::ItClaves::HaySiguiente() const{
	return it.HaySiguiente();
}


#endif //DICCSTRING_H