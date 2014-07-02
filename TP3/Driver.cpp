#include "Driver.h"
#include <assert.h>

using namespace aed2;

Driver::Driver(const Conj<Cliente>& clientes): wolfie_(Wolfie(clientes)) {}

Driver::~Driver()
{
	wolfie_.~Wolfie();
}

void Driver::AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones)
{
	wolfie_.AgregarTitulo(Titulo(nombre,cotizacion,max_acciones));
}

void Driver::ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion)
{
	wolfie_.ActualizarCotizacion(nombre, cotizacion);
}

void Driver::AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	wolfie_.AgregarPromesa(cliente, Promesa(titulo, COMPRA, limite, cantidad));
}

void Driver::AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	wolfie_.AgregarPromesa(cliente, Promesa(titulo, VENTA, limite, cantidad));
}

Nat Driver::CantidadDeClientes() const
{
	return wolfie_.CantClientes();
}

Cliente Driver::IesimoCliente(Nat i) const
{
	Wolfie::Iterador_clientes it = wolfie_.Clientes();
	while (i>0) {
		assert(it.HaySiguiente());
		it.Avanzar();
		i--;
	}
	return it.Siguiente();
}

Nat Driver::CantidadDeTitulos() const
{
	return wolfie_.CantTitulos();
}

NombreTitulo Driver::IesimoTitulo(Nat i) const
{
	Wolfie::Iterador_titulos it = wolfie_.Titulos();
	while (i>0) {
		assert(it.HaySiguiente());
		it.Avanzar();
		i--;
	}
	return it.Siguiente();
}

Nat Driver::MaxAccionesDe(const NombreTitulo& nombre_titulo) const
{
	return wolfie_.BuscarTitulo(nombre_titulo).maxAcciones();
}

Dinero Driver::CotizacionDe(const NombreTitulo& nombre_titulo) const
{
	return wolfie_.BuscarTitulo(nombre_titulo).cotizacion();
}

bool Driver::EnAlza(const NombreTitulo& nombre_titulo) const
{
	return wolfie_.BuscarTitulo(nombre_titulo).enAlza();
}

Nat Driver::AccionesTotalesDe(const Cliente& cliente) const
{
	return wolfie_.AccionesTotalesDe(cliente);
}

Nat Driver::AccionesPorCliente(const Cliente& cliente, const NombreTitulo& nombre_titulo) const
{
	return wolfie_.AccionesPorClienteW(cliente, nombre_titulo);
}

Nat Driver::AccionesDisponibles(const NombreTitulo& nombre_titulo) const
{
	return wolfie_.AccionesDisponibles(nombre_titulo);
}

bool Driver::PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return wolfie_.PrometeComprar(cliente, titulo);
}

Nat Driver::CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return wolfie_.PromesaDeCompra(cliente, titulo).cantidad();
}

Dinero Driver::ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return wolfie_.PromesaDeCompra(cliente, titulo).limite();
}

bool Driver::PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return wolfie_.PrometeVender(cliente, titulo);
}

Nat Driver::CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return wolfie_.PromesaDeVenta(cliente, titulo).cantidad();
}

Dinero Driver::ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return wolfie_.PromesaDeVenta(cliente, titulo).limite();
}
