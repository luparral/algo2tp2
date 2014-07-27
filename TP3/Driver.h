#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"
//#include "../aed2/TiposBasicos.h"ddd
#include "wolfie.h"


namespace aed2 {

class Driver
{
	public:

		Driver(const Conj<Cliente>& clientes);

		~Driver();

		// PRE: nombre() \notin Titulos()
		void AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones);

		// PRE: nombre \in Titulos()
		void ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion);

		// PRE: no PrometeComprar(cliente)
		void AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad);

		// PRE: no PrometeVender(cliente) y cantidad < AccionesPorCliente(cliente, titulo)
		void AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad);

		Nat CantidadDeClientes() const;
		// PRE: 0 <= i < CantidadDeClientes()
		Cliente IesimoCliente(Nat i) const;

		Nat CantidadDeTitulos() const;
		// PRE: 0 <= i < CantidadDeTitulos()
		NombreTitulo IesimoTitulo(Nat i) const;

		// PRE: nombre_titulo \in Titulos()
		Nat MaxAccionesDe(const NombreTitulo& nombre_titulo) const;

		// PRE: nombre_titulo \in Titulos()
		Dinero CotizacionDe(const NombreTitulo& nombre_titulo) const;

		// PRE: nombre_titulo \in Titulos()
		bool EnAlza(const NombreTitulo& nombre_titulo) const;

		// PRE: c \in Clientes()
		Nat AccionesTotalesDe(const Cliente& cliente) const;

		// PRE: c \in Clientes(), nombre_titulo \in Titulos()
		Nat AccionesPorCliente(const Cliente& cliente, const NombreTitulo& nombre_titulo) const;

		// PRE: nombre_titulo \in Titulos()
		Nat AccionesDisponibles(const NombreTitulo& nombre_titulo) const;

		// PRE: c \in Clientes()
		bool PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) /*const*/ ;
		// PRE: c \in Clientes(), PrometeComprar(c, titulo)
		Nat CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) /*const*/ ;
		// PRE: c \in Clientes(), PrometeComprar(c, titulo)
		Dinero ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) /*const*/ ;

		// PRE: c \in Clientes()
		bool PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) /*const*/ ;
		// PRE: c \in Clientes(), PrometeVender(c, titulo)
		Nat CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) /*const*/ ;
		// PRE: c \in Clientes(), PrometeVender(c, titulo)
		Dinero ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) /*const*/ ;

	private:

	/******************************************************************
	 * TODO: Va a ser necesario instanciar privadamente un TAD Wolfie *
	 * con el cuál interactuar. Además, pueden declarar todas las     *
	 * funciones auxiliares que les hagan falta.                      *
	 ******************************************************************/

		Wolfie wolfie_;
		/*estas para que son?
		const Titulo& getTitulo(const NombreTitulo& nombre_titulo) const {
			//return wolfie_._titulos.Significado(nombre_titulo);
		}

		const Promesa& promesaDeCompra(const Cliente& cliente) const {
			//return
		}

		const Promesa& promesaDeVenta(const Cliente& cliente) const {}
		*/
}; // class Driver

} // namespace aed2






























#endif // DRIVER_H_
