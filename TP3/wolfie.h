#ifndef H_WOLFIE
#define H_WOLFIE

#include "conjEstNat.h"
#include "promesa.h"
#include "diccString.h"
#include "titulo.h"
#include <assert.h>

using namespace aed2;

typedef unsigned int Cliente;

class Wolfie
{
		
	public:
		//esto VA en private*****************************************************************************
		struct TuplaPorCliente{
			public: 
				TuplaPorCliente(): cliente(0), cantAcc(0), promCompra(NULL), promVenta(NULL){}
				TuplaPorCliente(Cliente c, Nat ca, Promesa* pc, Promesa* pv): cliente(c), cantAcc(ca), promCompra(pc), promVenta(pv) {}
				Cliente cliente;
				Nat cantAcc;
				Promesa* promCompra;
				Promesa* promVenta;
				bool operator < (const typename Wolfie::TuplaPorCliente& otro) const {return(this->cliente < otro.cliente);}
				bool operator > (const typename Wolfie::TuplaPorCliente& otro) const {return(this->cliente > otro.cliente);}
				
				bool operator == (Cliente c) const {return(this->cliente == c);} //ver notas
				bool operator < (Cliente c) const {return(this->cliente < c);}
				bool operator > (Cliente c) const {return(this->cliente > c);}
		};
		
		struct TuplaPorCantAcc{
			public: 
				TuplaPorCantAcc(): cliente(0), cantAcc(0), promCompra(NULL), promVenta(NULL){}
				TuplaPorCantAcc(Cliente c, Nat ca, Promesa* pc, Promesa* pv): cliente(c), cantAcc(ca), promCompra(pc), promVenta(pv) {}
				Cliente cliente;
				Nat cantAcc;
				Promesa* promCompra;
				Promesa* promVenta;
				bool operator < (const typename Wolfie::TuplaPorCantAcc& otro) const {return(this->cantAcc > otro.cantAcc);}
				bool operator > (const typename Wolfie::TuplaPorCantAcc& otro) const {return(this->cantAcc < otro.cantAcc);}
		};
		
		struct InfoTitulo{
			public:
				InfoTitulo():ArrayClientes(Arreglo<TuplaPorCliente>()), titulo(Titulo(/*"",0, 0*/)), AccionesDisponibles(){}
				InfoTitulo(const InfoTitulo& otro): ArrayClientes(otro.ArrayClientes), titulo(otro.titulo), AccionesDisponibles(otro.AccionesDisponibles) {}
				InfoTitulo(Arreglo<TuplaPorCliente> &ac, const Titulo &t, Nat ad): ArrayClientes(ac), titulo(t), AccionesDisponibles(ad){}
				Arreglo<TuplaPorCliente> ArrayClientes;
				Titulo titulo;
				Nat AccionesDisponibles;
		};

		struct ultLlamado{
			Cliente cliente;
			Conj<Promesa> promesas;
			bool fueUltimo;
			ultLlamado() {
				cliente=0;
				Conj<Promesa> c = Conj<Promesa>();
				promesas=c;
				fueUltimo=false;
			}
		};
		//*******************************************************************************************************************************
		
		class Iterador_titulos{
			public:
				Iterador_titulos(const Wolfie &w);
				void Avanzar();
				const String& Siguiente() const;
				bool HaySiguiente() const;

			private:
				DiccString<InfoTitulo>::Iterador it;
		};

		class Iterador_clientes{
			public:
				Iterador_clientes(const Wolfie &w);
				void Avanzar();
				Nat Siguiente() const;
				bool HaySiguiente() const;

			private:
				ConjEstNat::const_Iterador it;
		};


		
		/*
		 *Constructor y destructor
		 */
		Wolfie(const Conj<Nat> &c);
		~Wolfie();
		
		/*
		 *Funciones con iterador
		 */
		Conj<Promesa>::const_Iterador PromesasDe(Cliente c);
		Iterador_clientes Clientes() const;
		Iterador_titulos Titulos() const;

		/*
		 *Métodos normales
		 */
		void AgregarTitulo(const Titulo &t);
		Nat AccionesPorCliente(const Cliente c, const Nombre& nt) const;
		void ActualizarCotizacion(const Nombre &nt, Dinero cot);
		void AgregarPromesa(Cliente c, const Promesa &p);
		bool EnAlza(const Nombre &nt) const;

		/*
		 *Funciones adicionales para el driver
		 */
		Nat CantClientes() const;
		Nat CantTitulos() const;
		Titulo BuscarTitulo(const Nombre& nombre_titulo) const;
		Nat AccionesTotalesDe(const Cliente& cliente) const;
		Nat AccionesPorClienteW(const Cliente& cliente, const Nombre& nombre_titulo) const;
		Nat AccionesDisponibles(const Nombre& nombre_titulo) const;
		bool PrometeComprar(const Cliente& cliente, const Nombre& titulo) const;
		Promesa PromesaDeCompra(const Cliente& cliente, const Nombre& titulo) const;
		bool PrometeVender(const Cliente& cliente, const Nombre& titulo) const;
		Promesa PromesaDeVenta(const Cliente& cliente, const Nombre& titulo) const;

	private:		
		DiccString<InfoTitulo> _titulos;
		ConjEstNat _clientes;
		ultLlamado _ultimoLlamado;

};
	
#endif //WOLFIE_H