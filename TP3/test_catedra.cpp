#include "Driver.h"
#include "mini_test.h"

#include <iostream>

// macros para iterar sobre indices
#define forn(i, n) for(unsigned int i=0; (i)<(n); i++)
#define forsn(i, s, n) for(unsigned int i=(s); (i)<(n); i++)

// macro para iterar collecciones con nuestra interfaz de iterador
#define FORALL(it, c) for(typeof((c).CrearIt()) it = (c).CrearIt(); it.HaySiguiente(); it.Avanzar())

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

void asegurarDatosTitulo(Driver& wolfie, NombreTitulo nt, int cot, int maxAcc, bool alza, int disp )
{
	 ASSERT_EQ(wolfie.CotizacionDe(nt),cot);
	 ASSERT_EQ(wolfie.MaxAccionesDe(nt),maxAcc);
	 ASSERT_EQ(wolfie.EnAlza(nt),alza);
	 ASSERT_EQ(wolfie.AccionesDisponibles(nt),disp);
}

// ---------------------------------------------------------------------

void test_wolfie_vacio()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);

	Driver wolfie(clientes);

	ASSERT_EQ(wolfie.CantidadDeClientes(), 1);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 0);
}

void test_compra()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	// Titulo(nombre, cotizacion, maxAcciones)
	wolfie.AgregarTitulo("t4", 30, 10);
	wolfie.AgregarTitulo("t1", 10, 20);
	wolfie.AgregarTitulo("t3", 70, 30);

	wolfie.AgregarPromesaDeCompra(2, "t1", 40, 5);

	// asegurar que ningun cliente tenga acciones
	forn(iC, wolfie.CantidadDeClientes()) {
		forn(iT, wolfie.CantidadDeTitulos()) {
			ASSERT_EQ( wolfie.AccionesPorCliente(wolfie.IesimoCliente(iC), wolfie.IesimoTitulo(iT)), 0 );
		}
	}

	wolfie.ActualizarCotizacion("t1", 50);

	// asegurar que unicamente 2 tenga acciones en t1
	forn(iT, wolfie.CantidadDeTitulos()) {
		ASSERT_EQ( wolfie.AccionesPorCliente(1, wolfie.IesimoTitulo(iT)), 0 );
	}
	forn(iT, wolfie.CantidadDeTitulos()) {
		ASSERT_EQ( wolfie.AccionesPorCliente(3, wolfie.IesimoTitulo(iT)), 0 );
	}
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t4"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 5 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t3"), 0 );
}

void test_venta()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	wolfie.AgregarTitulo("t4", 30, 10);
	wolfie.AgregarTitulo("t1", 10, 20);
	wolfie.AgregarTitulo("t3", 70, 30);

	wolfie.AgregarPromesaDeCompra(1, "t1", 40, 5);
	wolfie.AgregarPromesaDeCompra(2, "t1", 40, 3);
	wolfie.AgregarPromesaDeCompra(3, "t1", 50, 2);
	wolfie.AgregarPromesaDeVenta(1, "t1", 40, 3);

	wolfie.ActualizarCotizacion("t1", 50);

	wolfie.ActualizarCotizacion("t1", 30);

	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t4"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 2 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t3"), 0 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t4"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 3 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t3"), 0 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t4"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t3"), 0 );
}

void test_venta_dispara_compra()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);

	Driver wolfie(clientes);

	// Titulo(nombre, cotizacion, maxAcciones)
	wolfie.AgregarTitulo("t1", 30, 10);

	// Cliente 1 quiere comprar todas las acciones de t1
	// luego se hace efectiva la compra
	wolfie.AgregarPromesaDeCompra(1, "t1", 40, 10);
	wolfie.ActualizarCotizacion("t1", 50);

	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 10 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesDisponibles("t1"), 0 );

	// cliente 2 pide comprar, puede por el precio,
	// pero no hay acciones disponibles
	wolfie.AgregarPromesaDeCompra(2, "t1", 5, 1);

	wolfie.ActualizarCotizacion("t1", 15);

	ASSERT_EQ( wolfie.AccionesDisponibles("t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 10 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 0 );

	// cliente 1 pide vender un par, y a continuacion se dispara la venta
	// cliente 2 deberia comprar automaticamente
	wolfie.AgregarPromesaDeVenta(1, "t1", 20, 6);
	wolfie.ActualizarCotizacion("t1", 10);

	ASSERT_EQ( wolfie.AccionesDisponibles("t1"), 5 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 4 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 1 );
}

void iesimo_titulo()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	Driver wolfie(clientes);

	Conj<NombreTitulo> titulos;
	titulos.Agregar("t1");
	titulos.Agregar("t2");
	titulos.Agregar("t3");
	titulos.Agregar("t4");

	FORALL(it, titulos) {
		wolfie.AgregarTitulo(it.Siguiente(), 1, 1);
	}

	{
		ASSERT_EQ(wolfie.CantidadDeTitulos(), 4);

		Conj<NombreTitulo> titulos_i;
		forn(i, wolfie.CantidadDeTitulos()) {
			titulos_i.Agregar( wolfie.IesimoTitulo(i) );
		}

		ASSERT( titulos == titulos_i );
	}

	NombreTitulo t_0 = wolfie.IesimoTitulo(0);
	NombreTitulo t_1 = wolfie.IesimoTitulo(1);
	NombreTitulo t_2 = wolfie.IesimoTitulo(2);
	NombreTitulo t_3 = wolfie.IesimoTitulo(3);

	Conj<NombreTitulo> titulos_nuevos;
	titulos_nuevos.Agregar("t5");
	titulos_nuevos.Agregar("t6");

	FORALL(it, titulos_nuevos) {
		wolfie.AgregarTitulo(it.Siguiente(), 1, 1);
	}

	{
		ASSERT_EQ(wolfie.CantidadDeTitulos(), 6);

		ASSERT(t_0 == wolfie.IesimoTitulo(0));
		ASSERT(t_1 == wolfie.IesimoTitulo(1));
		ASSERT(t_2 == wolfie.IesimoTitulo(2));
		ASSERT(t_3 == wolfie.IesimoTitulo(3));
	}

	{
		Conj<NombreTitulo> titulos_i;
		forsn(i, 4, 6) {
			titulos_i.Agregar( wolfie.IesimoTitulo(i) );
		}

		ASSERT( titulos_nuevos == titulos_i );
	}
}

void iesimo_cliente()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	ASSERT_EQ(wolfie.CantidadDeClientes(), 3);

	Conj<Cliente> clientes_i;
	forn(i, wolfie.CantidadDeClientes()) {
		clientes_i.Agregar( wolfie.IesimoCliente(i) );
	}

	ASSERT( clientes == clientes_i );
}

void test_promesas_no_se_ejecutan_porque_no_son_ejecutables()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);

	Driver wolfie(clientes);

	//Agrego titulo
	wolfie.AgregarTitulo("t1", 30, 10);

	//Agrego promesas de compras NO ejecutables (una por que no hay tantas
	//acciones y otra porque no alcanzó la cotización que pedía)
	wolfie.AgregarPromesaDeCompra(1, "t1", 40, 20);
	wolfie.AgregarPromesaDeCompra(2, "t1", 50, 10);

	//Actualizo cotización
	wolfie.ActualizarCotizacion("t1", 50);

	//Nadie compra nada!
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 0 );
}

void test_valores_de_los_titulos_se_modifican_correctamente()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);

	Driver wolfie(clientes);

	//Agrego titulo
	wolfie.AgregarTitulo("t1", 10, 100);
	wolfie.AgregarTitulo("t2", 20, 200);
	wolfie.AgregarTitulo("t3", 30, 300);
	wolfie.AgregarTitulo("t4", 40, 400);

	//Chequeo:
	asegurarDatosTitulo(wolfie,"t1",10,100,true,100);
	asegurarDatosTitulo(wolfie,"t2",20,200,true,200);
	asegurarDatosTitulo(wolfie,"t3",30,300,true,300);
	asegurarDatosTitulo(wolfie,"t4",40,400,true,400);

	//Actualizo cotizacion para que cambien alza y cotizaciones
	wolfie.ActualizarCotizacion("t1",15);
	wolfie.ActualizarCotizacion("t2",15);
	wolfie.ActualizarCotizacion("t3",30);
	wolfie.ActualizarCotizacion("t4",80);

	//Chequeo:
	asegurarDatosTitulo(wolfie,"t1",15,100,true,100);
	asegurarDatosTitulo(wolfie,"t2",15,200,false,200);
	asegurarDatosTitulo(wolfie,"t3",30,300,false,300);
	asegurarDatosTitulo(wolfie,"t4",80,400,true,400);

	//Hacemos unas compras así se modifican los disponibles
	wolfie.AgregarPromesaDeCompra(1,"t1",1,50);
	wolfie.AgregarPromesaDeCompra(2,"t2",1,100);
	wolfie.AgregarPromesaDeCompra(1,"t3",1,150);
	wolfie.AgregarPromesaDeCompra(2,"t4",1,200);

	//Actualizo cotizaciones
	wolfie.ActualizarCotizacion("t1",15);
	wolfie.ActualizarCotizacion("t2",15);
	wolfie.ActualizarCotizacion("t3",30);
	wolfie.ActualizarCotizacion("t4",80);

	//Chequeo:
	asegurarDatosTitulo(wolfie,"t1",15,100,false,50);
	asegurarDatosTitulo(wolfie,"t2",15,200,false,100);
	asegurarDatosTitulo(wolfie,"t3",30,300,false,150);
	asegurarDatosTitulo(wolfie,"t4",80,400,false,200);
}

void test_no_se_venden_mas_acciones_que_el_limite_del_titulo()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	//Agrego títulos
	wolfie.AgregarTitulo("t1", 30, 10);
	wolfie.AgregarTitulo("t2", 10, 20);

	//Agrego promesas
	wolfie.AgregarPromesaDeCompra(1,"t1",40,10);
	wolfie.AgregarPromesaDeCompra(2,"t2",40,20);

	//Hago que suban hasta 50 para comprar todo lo que haya
	wolfie.ActualizarCotizacion("t1",50);
	wolfie.ActualizarCotizacion("t2",50);

	//Corrobamos que hayan comprado
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 10 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t2"), 0 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t2"), 20 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t2"), 0 );

	//Nuevas promesas de compra
	wolfie.AgregarPromesaDeCompra(1,"t1",70,5);
	wolfie.AgregarPromesaDeCompra(2,"t2",70,5);

	//Actualizo la cotización para que llegue a ese valor
	wolfie.ActualizarCotizacion("t1",80);
	wolfie.ActualizarCotizacion("t2",80);

	//Corroboro que siga igual que antes ya que no hay títulos
	//para que los clientes compren.
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 10 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t2"), 0 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t2"), 20 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t2"), 0 );
}

void test_cliente_con_mas_acciones_compra_primero()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	//Agrego títulos
	wolfie.AgregarTitulo("t1", 10, 250);
	wolfie.AgregarTitulo("t2", 10, 200);

	//Chequeo valores de titulos
	asegurarDatosTitulo(wolfie,"t1",10,250,true,250);
	asegurarDatosTitulo(wolfie,"t2",10,200,true,200);

	//Agrego promesas de Compra
	wolfie.AgregarPromesaDeCompra(1,"t1",15,10);
	wolfie.AgregarPromesaDeCompra(1,"t2",15,25);
	wolfie.AgregarPromesaDeCompra(2,"t1",15,7);
	wolfie.AgregarPromesaDeCompra(2,"t2",15,15);

	//Actualizo el valor de los títulos
	wolfie.ActualizarCotizacion("t1",16);
	wolfie.ActualizarCotizacion("t2",16);

	//Chequeo valores de titulos
	asegurarDatosTitulo(wolfie,"t1",16,250,true,233);
	asegurarDatosTitulo(wolfie,"t2",16,200,true,160);

	//Chequeo que se hayan comprado bien
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 10 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t2"), 25 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 7 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t2"), 15 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t2"), 0 );

	//Chequeo que la cant de promesas totales sea la correcta
	ASSERT_EQ( wolfie.AccionesTotalesDe(1), 35 );
	ASSERT_EQ( wolfie.AccionesTotalesDe(2), 22 );
	ASSERT_EQ( wolfie.AccionesTotalesDe(3), 0 );

	//Nuevas promesas todos quieren comprar cuando suba de 20.
	wolfie.AgregarPromesaDeCompra(1,"t1",20,200);
	wolfie.AgregarPromesaDeCompra(2,"t1",20,200);
	wolfie.AgregarPromesaDeCompra(3,"t1",20,200);

	wolfie.ActualizarCotizacion("t1",22);

	// Chequeo que haya comprado sólo el cliente 1 dado que es el que
	//más acciones totales tiene.
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 210 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t2"), 25 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 7 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t2"), 15 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t2"), 0 );
}

void test_primero_todas_las_de_venta()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	//Agrego títulos
	wolfie.AgregarTitulo("t1", 10, 250);
	wolfie.AgregarTitulo("t2", 10, 200);

	//Cliente 1 y 2 primero van a comprar para después venderlas
	wolfie.AgregarPromesaDeCompra(1,"t1",20,120);
	wolfie.AgregarPromesaDeCompra(2,"t1",20,100);
	wolfie.AgregarPromesaDeCompra(1,"t2",20,12);
	wolfie.AgregarPromesaDeCompra(2,"t2",20,18);

	//Actualizo cotizaciones para que se ejecuten las promesas
	wolfie.ActualizarCotizacion("t1",22);
	wolfie.ActualizarCotizacion("t2",22);

	//Chequeo que cliente 1 y 2 hayan comprado, y 3 tenga todo en 0
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 120 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t2"), 12 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 100 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t2"), 18 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t2"), 0 );

	//Clientes 1 y 2 quieren vender todo lo que tienen, 3 quiere comprar
	//pero necesita que primero se vendan para comprar la cantidad que él quiere.
	wolfie.AgregarPromesaDeVenta(1,"t1",20,120);
	wolfie.AgregarPromesaDeVenta(2,"t1",20,100);
	wolfie.AgregarPromesaDeVenta(1,"t2",20,12);
	wolfie.AgregarPromesaDeVenta(2,"t2",20,18);
	wolfie.AgregarPromesaDeCompra(3,"t1",15,220);
	wolfie.AgregarPromesaDeCompra(3,"t2",15,190);

	//La promesa de compra no debería ejecutarse autoḿaticamente porque no hay
	//suficientes títulos.
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 120 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t2"), 12 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 100 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t2"), 18 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t2"), 0 );

	//Actulizo cotización para que se ejecuten las ventas y las compras.
	wolfie.ActualizarCotizacion("t1",18);
	wolfie.ActualizarCotizacion("t2",18);

	//Chequeo acciones disponibles de cada titulo
	ASSERT_EQ(wolfie.AccionesDisponibles("t1"), 30  );
	ASSERT_EQ(wolfie.AccionesDisponibles("t2"), 10  );

	//Chequeo que se haya comprado y vendido como se debe.
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "t2"), 0 );

	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t1"), 0 );
	ASSERT_EQ( wolfie.AccionesPorCliente(2, "t2"), 0 );

	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t1"), 220 );
	ASSERT_EQ( wolfie.AccionesPorCliente(3, "t2"), 190 );
}

void test_promete_comprar_y_promete_vender()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	//Agrego títulos
	wolfie.AgregarTitulo("t1", 10, 500);
	wolfie.AgregarTitulo("t2", 10, 500);

	//Nadie prometio comprar ni vender
	ASSERT(!wolfie.PrometeComprar(1,"t1"));
	ASSERT(!wolfie.PrometeComprar(2,"t1"));
	ASSERT(!wolfie.PrometeComprar(3,"t1"));
	ASSERT(!wolfie.PrometeComprar(1,"t2"));
	ASSERT(!wolfie.PrometeComprar(2,"t2"));
	ASSERT(!wolfie.PrometeComprar(3,"t2"));

	ASSERT(!wolfie.PrometeVender(1,"t1"));
	ASSERT(!wolfie.PrometeVender(2,"t1"));
	ASSERT(!wolfie.PrometeVender(3,"t1"));
	ASSERT(!wolfie.PrometeVender(1,"t2"));
	ASSERT(!wolfie.PrometeVender(2,"t2"));
	ASSERT(!wolfie.PrometeVender(3,"t2"));

	//Hago promesas de compra
	wolfie.AgregarPromesaDeCompra(1,"t1", 20, 100);
	wolfie.AgregarPromesaDeCompra(2,"t1", 20, 100);
	wolfie.AgregarPromesaDeCompra(3,"t1", 20, 100);
	wolfie.AgregarPromesaDeCompra(1,"t2", 20, 100);
	wolfie.AgregarPromesaDeCompra(2,"t2", 20, 100);
	wolfie.AgregarPromesaDeCompra(3,"t2", 20, 100);

	//Todos prometieron comprar nadie vender
	ASSERT(wolfie.PrometeComprar(1,"t1"));
	ASSERT(wolfie.PrometeComprar(2,"t1"));
	ASSERT(wolfie.PrometeComprar(3,"t1"));
	ASSERT(wolfie.PrometeComprar(1,"t2"));
	ASSERT(wolfie.PrometeComprar(2,"t2"));
	ASSERT(wolfie.PrometeComprar(3,"t2"));

	ASSERT(!wolfie.PrometeVender(1,"t1"));
	ASSERT(!wolfie.PrometeVender(2,"t1"));
	ASSERT(!wolfie.PrometeVender(3,"t1"));
	ASSERT(!wolfie.PrometeVender(1,"t2"));
	ASSERT(!wolfie.PrometeVender(2,"t2"));
	ASSERT(!wolfie.PrometeVender(3,"t2"));

	//Actualizo para que se ejecuten las compras
	wolfie.ActualizarCotizacion("t1",25);
	wolfie.ActualizarCotizacion("t2",25);

	//Nadie promete  comprar ni vender
	ASSERT(!wolfie.PrometeComprar(1,"t1"));
	ASSERT(!wolfie.PrometeComprar(2,"t1"));
	ASSERT(!wolfie.PrometeComprar(3,"t1"));
	ASSERT(!wolfie.PrometeComprar(1,"t2"));
	ASSERT(!wolfie.PrometeComprar(2,"t2"));
	ASSERT(!wolfie.PrometeComprar(3,"t2"));

	ASSERT(!wolfie.PrometeVender(1,"t1"));
	ASSERT(!wolfie.PrometeVender(2,"t1"));
	ASSERT(!wolfie.PrometeVender(3,"t1"));
	ASSERT(!wolfie.PrometeVender(1,"t2"));
	ASSERT(!wolfie.PrometeVender(2,"t2"));
	ASSERT(!wolfie.PrometeVender(3,"t2"));

	//Hago Promesas de Venta
	wolfie.AgregarPromesaDeVenta(1,"t1", 30, 100);
	wolfie.AgregarPromesaDeVenta(2,"t1", 30, 100);
	wolfie.AgregarPromesaDeVenta(3,"t1", 30, 100);
	wolfie.AgregarPromesaDeVenta(1,"t2", 30, 100);
	wolfie.AgregarPromesaDeVenta(2,"t2", 30, 100);
	wolfie.AgregarPromesaDeVenta(3,"t2", 30, 100);

	ASSERT(!wolfie.PrometeComprar(1,"t1"));
	ASSERT(!wolfie.PrometeComprar(2,"t1"));
	ASSERT(!wolfie.PrometeComprar(3,"t1"));
	ASSERT(!wolfie.PrometeComprar(1,"t2"));
	ASSERT(!wolfie.PrometeComprar(2,"t2"));
	ASSERT(!wolfie.PrometeComprar(3,"t2"));

	ASSERT(wolfie.PrometeVender(1,"t1"));
	ASSERT(wolfie.PrometeVender(2,"t1"));
	ASSERT(wolfie.PrometeVender(3,"t1"));
	ASSERT(wolfie.PrometeVender(1,"t2"));
	ASSERT(wolfie.PrometeVender(2,"t2"));
	ASSERT(wolfie.PrometeVender(3,"t2"));
}

void test_cantidad_a_comprar_y_cantidad_a_vender()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	//Agrego títulos
	wolfie.AgregarTitulo("t1", 10, 500);
	wolfie.AgregarTitulo("t2", 10, 500);

	//Agrego promesas de venta y compra
	wolfie.AgregarPromesaDeCompra(1,"t1", 20, 10);
	wolfie.AgregarPromesaDeCompra(2,"t1", 25, 20);
	wolfie.AgregarPromesaDeCompra(3,"t1", 40, 30);

	wolfie.AgregarPromesaDeCompra(1,"t2", 40, 110);
	wolfie.AgregarPromesaDeCompra(2,"t2", 50, 120);
	wolfie.AgregarPromesaDeCompra(3,"t2", 80, 130);

	//Corroboro cantidades
	ASSERT_EQ(wolfie.CantidadAComprar(1,"t1"),10 );
	ASSERT_EQ(wolfie.CantidadAComprar(2,"t1"),20 );
	ASSERT_EQ(wolfie.CantidadAComprar(3,"t1"),30 );

	ASSERT_EQ(wolfie.CantidadAComprar(1,"t2"),110 );
	ASSERT_EQ(wolfie.CantidadAComprar(2,"t2"),120 );
	ASSERT_EQ(wolfie.CantidadAComprar(3,"t2"),130 );

	//Actualizo cot para que se ejecuten las ventas
	wolfie.ActualizarCotizacion("t1",100);
	wolfie.ActualizarCotizacion("t2",100);

	// Agrego promesas de venta
	wolfie.AgregarPromesaDeVenta(1,"t1", 20, 10);
	wolfie.AgregarPromesaDeVenta(2,"t1", 25, 20);
	wolfie.AgregarPromesaDeVenta(3,"t1", 40, 30);

	wolfie.AgregarPromesaDeVenta(1,"t2", 40, 110);
	wolfie.AgregarPromesaDeVenta(2,"t2", 50, 120);
	wolfie.AgregarPromesaDeVenta(3,"t2", 80, 130);

	// // Corroboro cantidades
	ASSERT_EQ(wolfie.CantidadAVender(1,"t1"),10 );
	ASSERT_EQ(wolfie.CantidadAVender(2,"t1"),20 );
	ASSERT_EQ(wolfie.CantidadAVender(3,"t1"),30 );

	ASSERT_EQ(wolfie.CantidadAVender(1,"t2"),110 );
	ASSERT_EQ(wolfie.CantidadAVender(2,"t2"),120 );
	ASSERT_EQ(wolfie.CantidadAVender(3,"t2"),130 );
}

void test_valorEsperadoVender_y_valorEsperadoComprar()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);

	Driver wolfie(clientes);

	//Agrego títulos
	wolfie.AgregarTitulo("t1", 10, 500);
	wolfie.AgregarTitulo("t2", 10, 500);

	//Agrego promesas de venta y compra
	wolfie.AgregarPromesaDeCompra(1,"t1", 20, 10);
	wolfie.AgregarPromesaDeCompra(2,"t1", 25, 20);
	wolfie.AgregarPromesaDeCompra(3,"t1", 40, 30);

	wolfie.AgregarPromesaDeCompra(1,"t2", 40, 110);
	wolfie.AgregarPromesaDeCompra(2,"t2", 50, 120);
	wolfie.AgregarPromesaDeCompra(3,"t2", 80, 130);

	//Corroboro cantidades
	ASSERT_EQ(wolfie.ValorEsperadoParaComprar(1,"t1"),20 );
	ASSERT_EQ(wolfie.ValorEsperadoParaComprar(2,"t1"),25 );
	ASSERT_EQ(wolfie.ValorEsperadoParaComprar(3,"t1"),40 );

	ASSERT_EQ(wolfie.ValorEsperadoParaComprar(1,"t2"),40 );
	ASSERT_EQ(wolfie.ValorEsperadoParaComprar(2,"t2"),50 );
	ASSERT_EQ(wolfie.ValorEsperadoParaComprar(3,"t2"),80 );

	// Agrego promesas de venta
	wolfie.AgregarPromesaDeVenta(1,"t1", 20, 10);
	wolfie.AgregarPromesaDeVenta(2,"t1", 25, 20);
	wolfie.AgregarPromesaDeVenta(3,"t1", 40, 30);

	wolfie.AgregarPromesaDeVenta(1,"t2", 40, 110);
	wolfie.AgregarPromesaDeVenta(2,"t2", 50, 120);
	wolfie.AgregarPromesaDeVenta(3,"t2", 80, 130);

	// Corroboro cantidades
	ASSERT_EQ(wolfie.ValorEsperadoParaVender(1,"t1"),20 );
	ASSERT_EQ(wolfie.ValorEsperadoParaVender(2,"t1"),25 );
	ASSERT_EQ(wolfie.ValorEsperadoParaVender(3,"t1"),40 );

	ASSERT_EQ(wolfie.ValorEsperadoParaVender(1,"t2"),40 );
	ASSERT_EQ(wolfie.ValorEsperadoParaVender(2,"t2"),50 );
	ASSERT_EQ(wolfie.ValorEsperadoParaVender(3,"t2"),80 );
}

void test_cache()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);

	Driver wolfie(clientes);

	//Agrego títulos
	wolfie.AgregarTitulo("t1", 10, 500);
	wolfie.AgregarTitulo("t2", 20, 500);
	wolfie.AgregarTitulo("t3", 30, 500);
	wolfie.AgregarTitulo("t4", 40, 500);

	//Agrego promesas de venta y compra
	wolfie.AgregarPromesaDeCompra(1,"t1", 20, 100);
	wolfie.AgregarPromesaDeCompra(1,"t2", 20, 100);
	wolfie.AgregarPromesaDeCompra(1,"t3", 20, 10);
	wolfie.AgregarPromesaDeCompra(1,"t4", 20, 10);

	wolfie.AgregarPromesaDeCompra(2,"t1", 20, 100);
	wolfie.AgregarPromesaDeCompra(2,"t2", 20, 100);
	wolfie.AgregarPromesaDeCompra(2,"t3", 20, 10);
	wolfie.AgregarPromesaDeCompra(2,"t4", 20, 10);

	//Actualizo para que se ejecute la compra
	wolfie.ActualizarCotizacion("t1",30);
	wolfie.ActualizarCotizacion("t2",30);

	//Hago promesas de venta
	wolfie.AgregarPromesaDeVenta(1,"t1", 10, 100);
	wolfie.AgregarPromesaDeVenta(1,"t2", 10, 100);
	wolfie.AgregarPromesaDeVenta(2,"t1", 10, 100);
	wolfie.AgregarPromesaDeVenta(2,"t2", 10, 100);

	forn(iC, wolfie.CantidadDeClientes()) {
		forn(iT, wolfie.CantidadDeTitulos()) {

			NombreTitulo titulo = wolfie.IesimoTitulo(iT);
			Cliente cliente = wolfie.IesimoCliente(iC);

			if (wolfie.PrometeComprar(cliente, titulo)) {
				Nat cantidad = wolfie.CantidadAComprar(cliente, titulo);
				Dinero limite = wolfie.ValorEsperadoParaComprar(cliente, titulo);

				ASSERT(cantidad == wolfie.CantidadAComprar(cliente, titulo))
				ASSERT(limite == wolfie.ValorEsperadoParaComprar(cliente, titulo))
				ASSERT( wolfie.PrometeComprar(cliente, titulo) );
			}
			else if (wolfie.PrometeVender(cliente, titulo)) {
				Nat cant = wolfie.CantidadAVender(cliente, titulo);
				Dinero din = wolfie.ValorEsperadoParaVender(cliente, titulo);

				ASSERT(cant == wolfie.CantidadAVender(cliente, titulo));
				ASSERT(din == wolfie.ValorEsperadoParaVender(cliente, titulo));
				ASSERT( wolfie.PrometeVender(cliente, titulo) );
			}
		}
	}
}

int main(int argc, char **argv)
{
	RUN_TEST(test_wolfie_vacio);
	RUN_TEST(test_valores_de_los_titulos_se_modifican_correctamente);
	RUN_TEST(test_compra);
	RUN_TEST(test_venta);
	RUN_TEST(test_venta_dispara_compra);
	RUN_TEST(iesimo_titulo);
	RUN_TEST(iesimo_cliente);
	RUN_TEST(test_promesas_no_se_ejecutan_porque_no_son_ejecutables);
	RUN_TEST(test_no_se_venden_mas_acciones_que_el_limite_del_titulo);
	RUN_TEST(test_cliente_con_mas_acciones_compra_primero);
	RUN_TEST(test_primero_todas_las_de_venta);
	RUN_TEST(test_promete_comprar_y_promete_vender);
	RUN_TEST(test_cantidad_a_comprar_y_cantidad_a_vender);
	RUN_TEST(test_valorEsperadoVender_y_valorEsperadoComprar);
	RUN_TEST(test_cache);

	return 0;
}
