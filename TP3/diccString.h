#ifndef DICCSTRING_H
#define DICCSTRING_H

#include <iostream>
#include <assert.h>
#include "Modulos-CPP/aed2.h"

using namespace aed2;


template<typename T>
class DiccString {

  public:
  	class const_Iterador;

	DiccString();
	//~DiccString();
	void definir(const String, const T&);
	bool definido(const String) const;
	const T& obtener(const String) const;

	const_Iterador claves() const;

	class const_Iterador{
      public:

        const_Iterador();

        const_Iterador(const typename DiccString<T>::const_Iterador& otra);

        bool HaySiguiente()const;
        bool HayAnterior()const;

        const T& Siguiente()const;
        const T& Anterior()const;

        void Avanzar();
        void Retroceder();

      private:
      
      	typename Conj<String>::const_Iterador it_dicc_;

        const_Iterador(const DiccString<T>& c);

		friend typename DiccString<T>::const_Iterador DiccString<T>::claves() const;
	};

  private:
	
	struct Nodo {
        T significado;
		Arreglo< Nodo* > letras;
	};

	Nodo* _raiz;
	Conj<String> _claves;

};

template<class T>
DiccString<T>::DiccString(){
	_raiz = new Nodo();
	_raiz->letras = Arreglo<Nodo*>(256);
}

template<class T>
void DiccString<T>::definir(const String key, const T& value){
	_claves.Agregar(key);
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
bool DiccString<T>::definido(const String key) const{
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
const T& DiccString<T>::obtener(const String key) const{
	Nat cantNodosNecesarios = key.length();
	Nodo* actual = _raiz;
	for(Nat i = 0;i < cantNodosNecesarios;i++){
		Nat posicionDelCarater = (Nat)key[i];
		actual = actual->letras[posicionDelCarater];
	}
	return actual->significado;
}

template<class T>
typename DiccString<T>::const_Iterador DiccString<T>::claves() const{
    return const_Iterador(_claves);
}

//Implementación del iterador

template<class T>
DiccString<T>::const_Iterador::const_Iterador()
{}

template<class T>
DiccString<T>::const_Iterador::const_Iterador(const typename DiccString<T>::const_Iterador& otra)
  : it_dicc_( otra.it_dicc_ )
{}

template<class T>
bool DiccString<T>::const_Iterador::HaySiguiente() const{
  return it_dicc_.HaySiguiente();
}

template<class T>
bool DiccString<T>::const_Iterador::HayAnterior() const{
  return it_dicc_.HayAnterior();
}

template<class T>
const T& DiccString<T>::const_Iterador::Siguiente() const{
  return it_dicc_.Siguiente();
}

template<class T>
const T& DiccString<T>::const_Iterador::Anterior() const{
  return it_dicc_.Anterior();
}

template<class T>
void DiccString<T>::const_Iterador::Avanzar(){
  it_dicc_.Avanzar();
}

template<class T>
void DiccString<T>::const_Iterador::Retroceder(){
  it_dicc_.Retroceder();
}

template<class T>
DiccString<T>::const_Iterador::const_Iterador(const DiccString<T>& c)
  : it_dicc_( c.dicc_.CrearIt() )
{}


#endif //DICCSTRING_H