#ifndef DICCTRIE_H
#define DICCTRIE_H

#include <iostream>
#include <assert.h>
#include "Modulos-CPP/aed2.h"

using namespace aed2;


template<typename T>
class DiccTrie {

  public:

	DiccTrie();
	//~DiccTrie();
	void definir(const String, const T&);
	bool definido(const String) const;
	const T& obtener(const String) const;

  private:
	
	struct Nodo {
        Nodo(const T& nuevoNodo):significado(nuevoNodo){}

		T significado;
		Arreglo< Nodo* > letras;
	};

	Nodo* _raiz;
	Nat _lenght;

};

template<class T>
DiccTrie<T>::DiccTrie(){
	_lenght = 0;
	_raiz = new Nodo();
	_raiz->letras = Arreglo< Nodo* >(256);
}

template<class T>
void DiccTrie<T>::definir(const String key, const T& value){
	_lenght++;
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	for(Nat i = 0;i < cantNodosNecesarios;i++){
		Nat posicionDelCarater = (Nat)key[i];
		if(actual->letras[posicionDelCarater] == NULL){
			actual->letras.Definir(posicionDelCarater,new Nodo());
		}
		actual = actual->letras[posicionDelCarater];
	}
	actual->significado = value;
}

template<class T>
bool DiccTrie<T>::definido(const String key) const{
	bool ret = true;
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	for(Nat i = 0;i < cantNodosNecesarios && ret;i++){
		Nat posicionDelCarater = (Nat)key[i];
		if(actual->letras[posicionDelCarater] == NULL){
			ret = false;
		}
		actual = actual->letras[posicionDelCarater];
	}
	return ret;
}

template<class T>
const T& DiccTrie<T>::obtener(const String key) const{
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	for(Nat i = 0;i < cantNodosNecesarios;i++){
		Nat posicionDelCarater = (Nat)key[i];
		actual = actual->letras[posicionDelCarater];
	}
	return actual->significado;
}



#endif //DICCTRIE_H
