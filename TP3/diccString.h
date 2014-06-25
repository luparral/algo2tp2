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
		//~DiccString();
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
	      		Nat _pos;
	      		Lista<String> _lista;
	      		Nat _tam;
		};

	private:
		struct Nodo {
	    	T significado;
			Arreglo< Nodo* > letras;
		};

		Nodo* _raiz;
		Lista<String> _claves;
		Nat _cantClaves;
};

template<class T>
DiccString<T>::DiccString(){
	_cantClaves = 0;
	_claves = Lista<String>();
	_raiz = new Nodo();
	_raiz->letras = Arreglo<Nodo*>(256);
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
			Nodo* minodo = new Nodo();
			minodo->letras = Arreglo<Nodo*>(256);
			actual->letras.Definir(posicionDelCarater,minodo);
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
DiccString<T>::Iterador::Iterador(const DiccString<T> &d): _lista(d._claves), _pos(0), _tam(d._cantClaves) {}

template<class T>
void DiccString<T>::Iterador::Avanzar(){
	_pos++;
}

template<class T>
const String& DiccString<T>::Iterador::Siguiente() const{
	return _lista[_pos];
}

template<class T>
bool DiccString<T>::Iterador::HaySiguiente() const{
	return (_pos < _tam);
}


#endif //DICCSTRING_H