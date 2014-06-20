#include "Driver.h"

Driver::Driver(const Conj<Cliente>& clientes)
{
	//TODO
}

Driver::~Driver()
{
	//TODO
}

void Driver::AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones)
{
	//TODO
}

void Driver::ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion)
{
	//TODO
}

void Driver::AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	//TODO
}

void Driver::AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	//TODO
}

Nat Driver::CantidadDeClientes() const
{
	//TODO
}

Cliente Driver::IesimoCliente(Nat i) const
{
	//TODO
}

Nat Driver::CantidadDeTitulos() const
{
	//TODO
}

NombreTitulo Driver::IesimoTitulo(Nat i) const
{
	//TODO
}

Nat Driver::MaxAccionesDe(const NombreTitulo& nombre_titulo) const
{
	//TODO
}

Dinero Driver::CotizacionDe(const NombreTitulo& nombre_titulo) const
{
	//TODO
}

bool Driver::EnAlza(const NombreTitulo& nombre_titulo) const
{
	//TODO
}

Nat Driver::AccionesTotalesDe(const Cliente& cliente) const
{
	//TODO
}

Nat Driver::AccionesPorCliente(const Cliente& cliente, const NombreTitulo& nombre_titulo) const
{
	//TODO
}

Nat Driver::AccionesDisponibles(const NombreTitulo& nombre_titulo) const
{
	//TODO
}

bool Driver::PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}

const NombreTitulo& Driver::TituloAComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}

Nat Driver::CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}

Dinero Driver::ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}

bool Driver::PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}

const NombreTitulo& Driver::TituloAVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}

Nat Driver::CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}

Dinero Driver::ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	//TODO
}
