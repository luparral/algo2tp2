#include "Driver.h"
#include "Modulos-CPP/mini_test.h"

#include <string>
#include <iostream>

using namespace aed2;

/** 
 * Imprime un elemento a un string, en vez de a una pantalla, 
 * a través del operador << 
 */
template <typename T>
std::string to_str(const T& t)
{
	std::stringstream ss;
	ss << t;

	return ss.str();
}

/**
 * Esta función se puede utilizar para comparar dos colecciones
 * iterables que representen conjuntos, es decir, que no tengan 
 * elementos repetidos.
 */
template<typename T, typename S>
bool Comparar(const T& t, const S& s)
{
  typename T::const_Iterador it1 = t.CrearIt();
  typename T::const_Iterador it2 = s.CrearIt();

	// me fijo si tienen el mismo tamanho

	Nat len1 = 0;
	while( it1.HaySiguiente() ) {
		len1++;
		it1.Avanzar();
	}

	Nat len2 = 0;
	while( it2.HaySiguiente() ) {
		len2++;
		it2.Avanzar();
	}

	if ( len1 != len2 )
		return false;

	it1 = t.CrearIt();
  it2 = s.CrearIt();

	// me fijo que tengan los mismos elementos

  while( it1.HaySiguiente() )
  {
    bool esta = false;

    while( it2.HaySiguiente() ) {
      if ( it1.Siguiente() == it2.Siguiente() ) {
        esta = true;
				break;
      }
      it2.Avanzar();
    }

    if ( !esta ) {
			return false;
		}
		
		it1.Avanzar();
  }
  
  return true;
}

// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */
void test_wolfie_simple()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);

	ASSERT(wolfie.CantidadDeClientes() == clientes.Cardinal());

	for(Nat i=0; i<wolfie.CantidadDeClientes(); i++) {
		ASSERT( clientes.Pertenece( wolfie.IesimoCliente(i) ) );
	}

	ASSERT_EQ(wolfie.CantidadDeTitulos(), 0);
}

void test_agregar_titulo() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("YPF",25,4);//nombre:YPF, maxAcciones:25, cotizacion 4
}

void test_actualizar_cotizacion() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("YPF",25,4);
	wolfie.ActualizarCotizacion("YPF", 5);
	
}

void test_agregar_promesa_compra() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("YPF",25,4);	

	wolfie.AgregarPromesaDeCompra(1, "YPF", 5, 10);//promesa del cliente 1 para comprar a YPF 10 acciones cuando suban de 5
	
}

void test_agregar_promesa_venta() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("YPF",25,4);	

	wolfie.AgregarPromesaDeVenta(1, "YPF", 3, 10);//promesa del cliente 1 para vender a YPF 10 acciones cuando suban de 5
	//IMPORTANTE: la promesa no se deberia agregar porque no se puede cumplir!!!
	
}





void test_promete_comprar() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("YPF",25,4);	//agrego titulo YPF con 25 acciones maximas y cotizacion 4
	
	ASSERT_EQ(wolfie.PrometeComprar(1,"YPF"), false);
	
	wolfie.AgregarPromesaDeCompra(1, "YPF", 5, 10);//promesa del cliente 1 para comprar a YPF 10 acciones cuando suban de 5
	ASSERT_EQ(wolfie.PrometeComprar(1,"YPF"), true);
	
	wolfie.ActualizarCotizacion("YPF", 6);
	ASSERT_EQ(wolfie.PrometeComprar(1,"YPF"), false);
}

void test_promete_comprar() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("YPF",25,4);	//agrego titulo YPF con 25 acciones maximas y cotizacion 4
	
	ASSERT_EQ(wolfie.PrometeComprar(1,"YPF"), false);
	
	wolfie.AgregarPromesaDeCompra(1, "YPF", 5, 10);//promesa del cliente 1 para comprar a YPF 10 acciones cuando suban de 5
	ASSERT_EQ(wolfie.PrometeComprar(1,"YPF"), true);
	
	wolfie.ActualizarCotizacion("YPF", 6);
	ASSERT_EQ(wolfie.PrometeComprar(1,"YPF"), false);
}

int main(/*int argc, char **argv*/)
{
	RUN_TEST(test_wolfie_simple);
	RUN_TEST(test_agregar_titulo);
	RUN_TEST(test_actualizar_cotizacion);
	RUN_TEST(test_agregar_promesa_compra);
	RUN_TEST(test_agregar_promesa_venta);
	
	
	RUN_TEST(test_promete_comprar);
	
	
	RUN_TEST(test_promete_comprar);
	
	/******************************************************************
	 * TODO: escribir casos de test exhaustivos para todas            *
	 * las funcionalidades del módulo.                                *
	 * La interacción con el TAD Wolfie se debe hacer exclusivamente  *
	 * a través de la interfaz del driver.                            *
	 ******************************************************************/

	return 0;
}
