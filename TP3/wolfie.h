#include "conjEstNat.h"
#include "promesa.h"
#include "diccString.h"
#include "titulo.h"

using namespace aed2;

typedef unsigned int Cliente;
/*
//typedef unsigned int Dinero;
//enum TipoPromesa{Compra,Venta};
typedef std::string Nombre;

class Promesa{};
class Titulo{};

template<typename T>
class DiccString
{
	public:
		class const_Iterador{};
};
*/
class Wolfie
{
	public:
		
		//esto donde va, public o private?*****************************************************************************
		struct TuplaPorCliente{
			public: 
				TuplaPorCliente();
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
				TuplaPorCantAcc(Cliente c, Nat ca, Promesa* pc, Promesa* pv): cliente(c), cantAcc(ca), promCompra(pc), promVenta(pv) {}
				Cliente cliente;
				Nat cantAcc;
				Promesa* promCompra;
				Promesa* promVenta;
				bool operator < (const typename Wolfie::TuplaPorCantAcc& otro) const {return(this->cantAcc < otro.cantAcc);}
				bool operator > (const typename Wolfie::TuplaPorCantAcc& otro) const {return(this->cantAcc > otro.cantAcc);}
		};
		
		struct InfoTitulo{
			public:
				//constructor:
				InfoTitulo();
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
		
		class const_Iterador
		{
			public:
				const Titulo& Actual() const;
				void Proximo() const;
				bool HayProximo() const;
			
			private:
				typename DiccString<InfoTitulo>::Iterador it;
				DiccString<typename Wolfie::InfoTitulo>* dicc;
				const_Iterador(typename DiccString<Wolfie::InfoTitulo>::Iterador& i, DiccString<Wolfie::InfoTitulo>* d): it(i), dicc(d){}
		};
		
		ConjEstNat::const_Iterador Clientes() const;
		Wolfie::const_Iterador Titulos() const;
		Conj<Promesa>::const_Iterador PromesasDe(Cliente c);
		Nat AccionesPorCliente(Cliente c, const Nombre& nt) const;
		Wolfie InaugurarWolfie(const Conj<Cliente> &c);
		void AgregarTitulo(const Titulo &t);
		void ActualizarCotizacion(const Nombre &nt, Dinero cot);
		void AgregarPromesa(Cliente c, const Promesa &p);
		bool EnAlza(const Nombre &nt) const;
		typename Wolfie::const_Iterador CrearIt(const Wolfie& w) const;
		
		Wolfie(const Conj<Nat> &c);
		
	private:
		
		
		DiccString<InfoTitulo> _titulos;
		ConjEstNat _clientes;
		ultLlamado _ultimoLlamado;



};
typename Wolfie::TuplaPorCliente BuscarCliente(Cliente c, Arreglo<Wolfie::TuplaPorCliente> a); //defino para que no crashee
Arreglo<typename Wolfie::TuplaPorCliente> CrearArrayClientes(typename ConjEstNat::const_Iterador it, Nat n);
//: _titulos(DiccString::DiccString()), _clientes(ConjEstNat::ConjEstNat(c), _ultimoLlamado()
Wolfie::Wolfie(const Conj<Nat> &c)
{
	DiccString<InfoTitulo> dicc = DiccString<InfoTitulo>();
	_titulos= dicc;
	ConjEstNat conj = ConjEstNat(c);
	_clientes= conj;
	_ultimoLlamado=ultLlamado();
}

typename ConjEstNat::const_Iterador Wolfie::Clientes() const
{
	return ConjEstNat::const_Iterador(_clientes);
}

Wolfie::const_Iterador Wolfie::Titulos() const
{
	return Wolfie::CrearIt(*(this));
}

Conj<Promesa>::const_Iterador Wolfie::PromesasDe(Cliente c)
{
	if (!(_ultimoLlamado.cliente == c && _ultimoLlamado.fueUltimo)) {
		typename DiccString<InfoTitulo>::Iterador it = _titulos.Claves(); ///---
		Conj<Promesa> proms = Conj<Promesa>();
		Wolfie::TuplaPorCliente tup;
		while (it.HaySiguiente()) {
			tup = BuscarCliente(c, _titulos.Obtener(Nombre(it.Siguiente())).ArrayClientes);
			if (tup.promVenta != NULL) proms.AgregarRapido(*(tup.promVenta));
			if (tup.promCompra != NULL) proms.AgregarRapido(*(tup.promCompra));
			it.Avanzar();
		}
		_ultimoLlamado.promesas = proms;
	}
	return _ultimoLlamado.promesas.CrearIt();
}

Nat Wolfie::AccionesPorCliente(Cliente c, const Nombre& nt) const {
	return (BuscarCliente(c, _titulos.Obtener(nt).ArrayClientes).cantAcc);
}

Wolfie Wolfie::InaugurarWolfie(const Conj<Cliente> &c) {return Wolfie(c);}

void Wolfie::AgregarTitulo(const Titulo &t) {
	Arreglo<Wolfie::TuplaPorCliente> arr = CrearArrayClientes(_clientes.CrearIt(), _clientes.Cardinal());
	_titulos.Definir(t.nombre(), Wolfie::InfoTitulo(arr, t, t.maxAcciones()));
}
/*void Wolfie::ActualizarCotizacion(const Nombre &nt, Dinero cot);
void Wolfie::AgregarPromesa(Cliente c, const Promesa &p);
bool Wolfie::EnAlza(const Nombre &nt) const;
*/
/*
cambios:
agregue la struct ultLlamado para no usar una tupla
agregue operadores entre tuplaPorCliente y Cliente para poder hacer busqueda binaria con el nombre de cliente 
*/
