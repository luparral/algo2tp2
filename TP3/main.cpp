#include <iostream>
#include "conjEstNat.h"
#include "diccString.h"
#include "promesa.h"
#include "titulo.h"
#include "Modulos-CPP/mini_test.h"
#include "wolfie.h"
#include "algoritmos.h"

void conjEstNat_crear(){
	Conj<Nat> c = Conj<Nat>();
	c.Agregar(1);
	c.Agregar(3);
	c.Agregar(5);
	c.Agregar(6);
	ConjEstNat conj = ConjEstNat(c);
}

void conjEstNat_pertenece(){
	Conj<Nat> c = Conj<Nat>();
	c.Agregar(1);
	c.Agregar(3);
	c.Agregar(5);
	c.Agregar(6);
	ConjEstNat conj = ConjEstNat(c);
	ASSERT_EQ(conj.Pertenece(1), true);
	ASSERT_EQ(conj.Pertenece(2), false);
	ASSERT_EQ(conj.Pertenece(3), true);
	ASSERT_EQ(conj.Pertenece(6), true);
}

void conjEstNat_cardinal(){
	Conj<Nat> c = Conj<Nat>();
	c.Agregar(1);
	c.Agregar(5);
	c.Agregar(5);
	c.Agregar(6);
	ConjEstNat conj = ConjEstNat(c);
	ASSERT_EQ(conj.Cardinal(), 3);
}

void conjEstNat_const_Iterador(){
	Conj<Nat> c = Conj<Nat>();
	c.Agregar(6);
	c.Agregar(5);
	c.Agregar(3);
	c.Agregar(4);
	c.Agregar(10);
	c.Agregar(2);
	c.Agregar(0);
	ConjEstNat conj = ConjEstNat(c);
	typename ConjEstNat::const_Iterador it = conj.CrearIt();

	while (it.HayProx()){std::cout<<it.Actual()<<", ";it.Proximo();}
}

void Promesa_Titulo__test(){
}

void diccString_crear(){
	DiccString<Nat> d = DiccString<Nat>();
	d.Definir("test1",2);
	d.Definir("test2",67);
	d.Definir("test3",4);
	d.Definir("test4",22);
}

void diccString_definido(){
	DiccString<Nat> d = DiccString<Nat>();
	d.Definir("test1",22);
	d.Definir("tesa-test4",4);
	d.Definir("tesa-test5",5);
	d.Definir("tesa-test6",6);
	d.Definir("tesa-test8",8);
	ASSERT_EQ(d.Definido("test1"), true);
	ASSERT_EQ(d.Definido("test2"), false);
	ASSERT_EQ(d.Definido("test4"), false);
	ASSERT_EQ(d.Definido("tesa-test4"), true);
	ASSERT_EQ(d.Definido("tesa-test5"), true);
	ASSERT_EQ(d.Definido("tesa-test6"), true);
	ASSERT_EQ(d.Definido("tesa-test8"), true);
}

void diccString_obtener(){
	DiccString<Nat> d = DiccString<Nat>();
	d.Definir("test1",22);
	d.Definir("tesa-test4",4);
	d.Definir("tesa-test5",5);
	d.Definir("tesa-test6",6);
	d.Definir("tesa-test8",8);
	ASSERT_EQ(d.Obtener("test1"), 22);
	ASSERT_EQ(d.Obtener("tesa-test4"), 4);
	ASSERT_EQ(d.Obtener("tesa-test5"), 5);
	ASSERT_EQ(d.Obtener("tesa-test6"), 6);
	ASSERT_EQ(d.Obtener("tesa-test8"), 8);
}

void diccString_claves_vacias(){
	DiccString<Nat> d = DiccString<Nat>();
	typename DiccString<Nat>::Iterador it = d.Claves();
	ASSERT_EQ(it.HaySiguiente(), false);
}

void diccString_claves_noVacias(){
	DiccString<Nat> e = DiccString<Nat>();
	e.Definir("iterador_prueba_1",22);
	e.Definir("iterador_prueba_2",4);
	e.Definir("iterador_prueba_3",5);
	e.Definir("iterador_prueba_4",6);
	e.Definir("iterador_prueba_5",8);
	typename DiccString<Nat>::Iterador it = e.Claves();
	std::cout << "\n";
	while(it.HaySiguiente()){
		std::cout << it.Siguiente() << "\n";
		it.Avanzar();
	}

	DiccString<Nat> d = DiccString<Nat>();
	d.Definir("puto",22);
	d.Definir("el",4);
	d.Definir("que",5);
	d.Definir("lee",6);
	typename DiccString<Nat>::Iterador iter = d.Claves();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "puto");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "el");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "que");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "lee");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), false);
}

int main(){
	RUN_TEST(conjEstNat_crear);
	RUN_TEST(conjEstNat_pertenece);
	RUN_TEST(conjEstNat_cardinal);
	RUN_TEST(conjEstNat_const_Iterador);
	RUN_TEST(Promesa_Titulo__test);//Falta implementar
	RUN_TEST(diccString_crear);
	RUN_TEST(diccString_definido);
	RUN_TEST(diccString_obtener);
	RUN_TEST(diccString_claves_vacias);
	RUN_TEST(diccString_claves_noVacias);
}
