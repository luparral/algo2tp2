#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <iostream>
#include "Modulos-CPP/aed2.h"
#include <assert.h>

template<class T>
void bajar(Arreglo<T> &a, Nat n, Nat i){
	Nat indice=i;
	while (indice<=n)
	{
		Nat maximo=indice; //tomo el minimo de los hijos
		if ((n % 2 == 0 && indice == n) || a[indice]<a[indice-1]) maximo--;

		if (a[maximo]>a[(indice-2)/2]) //compara con el padre
		{ 
			a.Swap((indice-2)/2, maximo);
			indice=maximo*2+2; //si cambio, baja
		} else 
		{
			indice=a.Tamanho()+1; //si no, sale
		}
	}

}


template<class T>
void heapify(Arreglo<T> &a){
	Nat n=a.Tamanho();
	Nat i=n - 1;

	if (i % 2==1)i++;

	while (i>1)
	{
		bajar(a, n, i);
		i-=2;

	}
}

template<class T>
void heapsort(Arreglo<T> &a){
	for(int i=0;i<a.Tamanho();i++) assert(a.Definido(i));
	Nat n=a.Tamanho();
	heapify(a);
	while (n>1){
		n--;
		a.Swap(0,n);
		bajar(a, n, 2);
	}
}

template<class T, class U>
U& BusquedaBinaria(const T& t, Arreglo<U>& a) {
	Nat arriba = a.Tamanho();
	Nat abajo = 0;
	Nat centro;
	while (abajo <= arriba) {
		centro=(abajo+arriba)/2;
		if (a[centro]==t) {
			return a[centro];
		}else{
			if (a[centro]>t) {
				arriba=centro-1;
			}else{
				abajo=centro+1;
			}
		}
	}
}

#endif
