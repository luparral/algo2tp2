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

void diccTrie_crear(){
	DiccTrie<Nat> d = DiccTrie<Nat>();
	d.definir("test1",2);
	d.definir("test2",67);
	d.definir("test3",4);
	d.definir("test4",22);
}

void diccTrie_definido(){
	DiccTrie<Nat> d = DiccTrie<Nat>();
	d.definir("test1",22);
	d.definir("tesa-test4",4);
	d.definir("tesa-test5",5);
	d.definir("tesa-test6",6);
	d.definir("tesa-test8",8);
	ASSERT_EQ(d.definido("test1"), true);
	ASSERT_EQ(d.definido("test2"), false);
	ASSERT_EQ(d.definido("test4"), false);
	ASSERT_EQ(d.definido("tesa-test4"), true);
	ASSERT_EQ(d.definido("tesa-test5"), true);
	ASSERT_EQ(d.definido("tesa-test6"), true);
	ASSERT_EQ(d.definido("tesa-test8"), true);
}

void diccTrie_obtener(){
	DiccTrie<Nat> d = DiccTrie<Nat>();
	d.definir("test1",22);
	d.definir("tesa-test4",4);
	d.definir("tesa-test5",5);
	d.definir("tesa-test6",6);
	d.definir("tesa-test8",8);
	ASSERT_EQ(d.obtener("test1"), 22);
	ASSERT_EQ(d.obtener("tesa-test4"), 4);
	ASSERT_EQ(d.obtener("tesa-test5"), 5);
	ASSERT_EQ(d.obtener("tesa-test6"), 6);
	ASSERT_EQ(d.obtener("tesa-test8"), 8);
}

int main(){
	RUN_TEST(conjEstNat_crear);
	RUN_TEST(conjEstNat_pertenece);
	RUN_TEST(conjEstNat_cardinal);
	RUN_TEST(conjEstNat_iterador);
	RUN_TEST(diccTrie_crear);
	RUN_TEST(diccTrie_definido);
	RUN_TEST(diccTrie_obtener);
}
