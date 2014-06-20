#include <iostream>
#include "conjEstNat.h"
#include "diccTrie.h"
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
int main(){
	RUN_TEST(conjEstNat_crear);
	RUN_TEST(conjEstNat_pertenece);
	RUN_TEST(conjEstNat_cardinal);
	RUN_TEST(conjEstNat_iterador);
	
}
