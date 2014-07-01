#include <iostream>
#include "conjEstNat.h"
#include "diccString.h"
#include "promesa.h"
#include "titulo.h"
#include "Modulos-CPP/mini_test.h"
#include "algoritmos.h"
#include "wolfie.h"
#include "base/Driver.h"

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

void diccString_Significado(){
	DiccString<Nat> d = DiccString<Nat>();
	d.Definir("test1",22);
	d.Definir("tesa-test4",4);
	d.Definir("tesa-test5",5);
	d.Definir("tesa-test6",6);
	d.Definir("tesa-test8",8);
	ASSERT_EQ(d.Significado("test1"), 22);
	ASSERT_EQ(d.Significado("tesa-test4"), 4);
	ASSERT_EQ(d.Significado("tesa-test5"), 5);
	ASSERT_EQ(d.Significado("tesa-test6"), 6);
	ASSERT_EQ(d.Significado("tesa-test8"), 8);
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
	d.Definir("test",22);
	d.Definir("usando",4);
	d.Definir("los",5);
	d.Definir("assert",6);
	typename DiccString<Nat>::Iterador iter = d.Claves();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "test");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "usando");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "los");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), true);
	ASSERT_EQ(iter.Siguiente(), "assert");
	iter.Avanzar();
	ASSERT_EQ(iter.HaySiguiente(), false);
}

void diccString_cambio_de_valor_por_referencia(){
	DiccString<Nat> d = DiccString<Nat>();
	d.Definir("test",22);
	d.Definir("de",4);
	d.Definir("cambio",5);
	d.Definir("de valor",6);
	d.Definir("por referencia",7);
	ASSERT_EQ(d.Significado("test"),22);
	ASSERT_EQ(d.Significado("de"),4);
	ASSERT_EQ(d.Significado("cambio"),5);
	ASSERT_EQ(d.Significado("de valor"),6);
	ASSERT_EQ(d.Significado("por referencia"),7);
	
	d.Significado("de valor") = 44;
	d.Significado("cambio") = 101;

	ASSERT_EQ(d.Significado("test"),22);
	ASSERT_EQ(d.Significado("de"),4);
	ASSERT_EQ(d.Significado("cambio"),101);
	ASSERT_EQ(d.Significado("de valor"),44);
	ASSERT_EQ(d.Significado("por referencia"),7);
}

void diccString_cantClaves(){
	DiccString<Nat> d = DiccString<Nat>();
	ASSERT_EQ(d.CantClaves(),0);
	d.Definir("test",22);
	ASSERT_EQ(d.CantClaves(),1);
	d.Definir("de",4);
	ASSERT_EQ(d.CantClaves(),2);
	d.Definir("cantidad",5);
	d.Definir("de claves",6);
	ASSERT_EQ(d.CantClaves(),4);
	d.Definir("definidas",7);
	ASSERT_EQ(d.CantClaves(),5);

	//Redefinicion de clave no deberia sumar una clave
	d.Definir("test",25);
	d.Definir("de",45);
	d.Definir("cantidad",55);
	d.Definir("de claves",65);
	d.Definir("definidas",75);
	ASSERT_EQ(d.CantClaves(),5);

	d.Definir("agregado Extra De Clave",8);
	ASSERT_EQ(d.CantClaves(),6);

	d.Definir("test",226);
	d.Definir("de",46);
	d.Definir("cantidad",56);
	d.Definir("de claves",66);
	d.Definir("definidas",76);
	ASSERT_EQ(d.CantClaves(),6);
}

int main(){
	RUN_TEST(conjEstNat_crear);
	RUN_TEST(conjEstNat_pertenece);
	RUN_TEST(conjEstNat_cardinal);
	RUN_TEST(conjEstNat_const_Iterador);
	RUN_TEST(Promesa_Titulo__test);//Falta implementar
	RUN_TEST(diccString_crear);
	RUN_TEST(diccString_definido);
	RUN_TEST(diccString_Significado);
	RUN_TEST(diccString_claves_vacias);
	RUN_TEST(diccString_claves_noVacias);
	RUN_TEST(diccString_cambio_de_valor_por_referencia);
	RUN_TEST(diccString_cantClaves);
}
