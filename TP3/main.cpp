#include <iostream>
#include "conjEstNat.h"
#include "diccString.h"
#include "Modulos-CPP/mini_test.h"

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

void conjEstNat_iterador(){
	Conj<Nat> c = Conj<Nat>();
	c.Agregar(6);
	c.Agregar(5);
	c.Agregar(4);
	c.Agregar(3);
	ConjEstNat conj = ConjEstNat(c);
	typename ConjEstNat::Iterador it = conj.CrearIt();
	ASSERT_EQ(it.HayProx(), true);
	ASSERT_EQ(it.Actual(), 3);
	it.Proximo();
	ASSERT_EQ(it.HayProx(), true);
	ASSERT_EQ(it.Actual(), 4);
	
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

void diccString_claves(){
}

int main(){
	RUN_TEST(conjEstNat_crear);
	RUN_TEST(conjEstNat_pertenece);
	RUN_TEST(conjEstNat_cardinal);
	RUN_TEST(conjEstNat_iterador);
	RUN_TEST(diccString_crear);
	RUN_TEST(diccString_definido);
	RUN_TEST(diccString_obtener);
	RUN_TEST(diccString_claves);//Falta ver porque no compila
}
