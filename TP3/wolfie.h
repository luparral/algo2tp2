#include "conjEstNat.h"
#include "promesa.h"
#include "diccString.h"
#include "titulo.h"
#include <assert.h>

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
				bool operator < (const typename Wolfie::TuplaPorCantAcc& otro) const {return(this->cantAcc < otro.cantAcc);}
				bool operator > (const typename Wolfie::TuplaPorCantAcc& otro) const {return(this->cantAcc > otro.cantAcc);}
		};
		
		struct InfoTitulo{
			public:
				//constructor:
				InfoTitulo():ArrayClientes(Arreglo<TuplaPorCliente>()), titulo(Titulo(/*"",0, 0*/)), AccionesDisponibles(){}
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
				void Proximo();
				bool HayProximo() const;
				const_Iterador(typename DiccString<Wolfie::InfoTitulo>::Iterador i, const DiccString<Wolfie::InfoTitulo>* d): it(i), dicc(d){}
				//typename Wolfie::const_Iterador CrearIt(const DiccString<Wolfie::InfoTitulo>& t) const;
			
			private:
				typename DiccString<Wolfie::InfoTitulo>::Iterador it;
				const DiccString<typename Wolfie::InfoTitulo>* dicc;
		};
		
		/*
		 *Constructores y destructor
		 */
		// Wolfie();
		Wolfie(const Conj<Nat> &c);
		~Wolfie();
		// Wolfie InaugurarWolfie(const Conj<Cliente> &c);
		/*
		 *Funciones con iterador
		 */
		ConjEstNat::const_Iterador Clientes() const;
		Wolfie::const_Iterador Titulos() const;
		Conj<Promesa>::const_Iterador PromesasDe(Cliente c);

		/*
		 *Métodos normales
		 */
		Nat AccionesPorCliente(const Cliente c, const Nombre& nt) const;
		void AgregarTitulo(const Titulo &t);
		void ActualizarCotizacion(const Nombre &nt, Dinero cot);
		void AgregarPromesa(Cliente c, const Promesa &p);
		bool EnAlza(const Nombre &nt) const;
		//funciones adicionales para el driver
		Nat CantClientes();
		Nat CantTitulos();
		Titulo BuscarTitulo(const Nombre& nombre_titulo) const;
		Nat AccionesTotalesDe(const Cliente& cliente) const;
		Nat AccionesPorCliente(const Cliente& cliente, const Nombre& nombre_titulo) const;
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
/*
Wolfie::const_Iterador Wolfie::const_Iterador::CrearIt(const DiccString<Wolfie::InfoTitulo>& t) const{
	const_Iterador i(t.Claves(), &t);
	//i.it=t.Claves();
	//i.dicc= &t;
	return i;
	//return Wolfie::const_Iterador::const_Iterador(t.Claves(), &t);
}
*/
Wolfie::Wolfie(const Conj<Nat> &c)
{
	_titulos= DiccString<InfoTitulo>();
	_clientes= ConjEstNat(c);;
	_ultimoLlamado=ultLlamado();
}

// Wolfie::Wolfie() {
// 	DiccString<InfoTitulo> dicc = DiccString<InfoTitulo>();
// 	_titulos= dicc;
// 	_clientes= ConjEstNat(Conj<Nat>());
// 	_ultimoLlamado=ultLlamado();
// }

Wolfie::~Wolfie() {
	DiccString<InfoTitulo>::Iterador it = _titulos.Claves();
	while (it.HaySiguiente()) {
		Wolfie::InfoTitulo info = _titulos.Significado(it.Siguiente());
		Nat i=0;
		while (i<info.ArrayClientes.Tamanho()) {
			if (info.ArrayClientes[i].promVenta != NULL) {
				delete info.ArrayClientes[i].promVenta;
				info.ArrayClientes[i].promVenta=NULL;
			}
			if (info.ArrayClientes[i].promCompra != NULL) {
				delete info.ArrayClientes[i].promCompra;
				info.ArrayClientes[i].promCompra=NULL;
			}
			i++;
		}
	}
}


const Titulo& Wolfie::const_Iterador::Actual() const {
	return (dicc->Significado(it.Siguiente()).titulo);
}

void Wolfie::const_Iterador::Proximo() {
	it.Avanzar();
}

bool Wolfie::const_Iterador::HayProximo() const{
	return it.HaySiguiente();
}

void CambiarPorCantAcc(Arreglo<Wolfie::TuplaPorCliente> a1, Arreglo<Wolfie::TuplaPorCantAcc> a2) {
	Nat i=0;
	while (i<a1.Tamanho()){
		a2[i].cliente=a1[i].cliente;
		a2[i].cantAcc=a1[i].cantAcc;
		a2[i].promCompra=a1[i].promCompra;
		a2[i].promVenta=a1[i].promVenta;
		i++;
	}
} 

void CambiarPorCliente(Arreglo<Wolfie::TuplaPorCantAcc> a1, Arreglo<Wolfie::TuplaPorCliente> a2) {
	Nat i=0;
	while (i<a1.Tamanho()) {
		a2[i].cliente=a1[i].cliente;
		a2[i].cantAcc=a1[i].cantAcc;
		a2[i].promCompra=a1[i].promCompra;
		a2[i].promVenta=a1[i].promVenta;
		i++;
	}
} 

Arreglo<typename Wolfie::TuplaPorCliente> CrearArrayClientes(typename ConjEstNat::const_Iterador it, Nat n){
	Arreglo<typename Wolfie::TuplaPorCliente> arr =Arreglo<typename Wolfie::TuplaPorCliente>(n);
	Nat i=0;
	do{
		arr[i] = Wolfie::TuplaPorCliente(it.Actual(), 0, NULL, NULL);
		i++;
		it.Proximo();
	} while(it.HayProx());
	return arr;
}


typename ConjEstNat::const_Iterador Wolfie::Clientes() const
{
	return ConjEstNat::const_Iterador(_clientes);
}

Wolfie::const_Iterador Wolfie::Titulos() const
{
	Wolfie::const_Iterador i(_titulos.Claves(), &_titulos);
	return i;
}

Conj<Promesa>::const_Iterador Wolfie::PromesasDe(Cliente c)
{
	if (!(_ultimoLlamado.cliente == c && _ultimoLlamado.fueUltimo)) {
		typename DiccString<InfoTitulo>::Iterador it = _titulos.Claves(); ///---
		Conj<Promesa> proms = Conj<Promesa>();
		Wolfie::TuplaPorCliente tup;
		while (it.HaySiguiente()) {
			tup = BusquedaBinaria(c, _titulos.Significado(it.Siguiente()).ArrayClientes);//saque Nombre(---) a ir.Siguiente()
			if (tup.promVenta != NULL) proms.AgregarRapido(*(tup.promVenta));
			if (tup.promCompra != NULL) proms.AgregarRapido(*(tup.promCompra));
			it.Avanzar();
		}
		_ultimoLlamado.promesas = proms;
	}
	return _ultimoLlamado.promesas.CrearIt();
}

Nat Wolfie::AccionesPorCliente(const Cliente c, const Nombre& nt) const {
	return (BusquedaBinaria(c, _titulos.Significado(nt).ArrayClientes).cantAcc);
}

// Wolfie Wolfie::InaugurarWolfie(const Conj<Cliente> &c) {return Wolfie(c);}

void Wolfie::AgregarTitulo(const Titulo &t) {
	Arreglo<Wolfie::TuplaPorCliente> arr = CrearArrayClientes(_clientes.CrearIt(), _clientes.Cardinal());
	_titulos.Definir(t.nombre(), Wolfie::InfoTitulo(arr, t, t.maxAcciones()));
}
void Wolfie::ActualizarCotizacion(const Nombre &nt, Dinero cot){
	Wolfie::InfoTitulo s = _titulos.Significado(nt);
	s.titulo.recotizar(cot); //aca quizas hay problema si titulo devuelve una copia, no deberia
	Nat i=0;
	while (i<s.ArrayClientes.Tamanho()){
		if (s.ArrayClientes[i].promVenta != NULL && (s.ArrayClientes[i].promVenta->limite() > s.titulo.cotizacion())) {
			s.ArrayClientes[i].cantAcc -= s.ArrayClientes[i].promVenta->cantidad();
			s.AccionesDisponibles += s.ArrayClientes[i].promVenta->cantidad();
			delete s.ArrayClientes[i].promVenta;
			s.ArrayClientes[i].promVenta = NULL;
		}
	}
	Arreglo<TuplaPorCantAcc> arr = 	Arreglo<TuplaPorCantAcc>(s.ArrayClientes.Tamanho());
	CambiarPorCantAcc(s.ArrayClientes, arr);
	heapsort(arr);
	i=0;
	while (i<s.ArrayClientes.Tamanho()){
		if (arr[i].promCompra != NULL && (arr[i].promCompra->limite() < s.titulo.cotizacion()) && (arr[i].promCompra->cantidad() <= s.AccionesDisponibles)) {
			arr[i].cantAcc += arr[i].promCompra->cantidad();
			s.AccionesDisponibles -= arr[i].promCompra->cantidad();
			delete s.ArrayClientes[i].promCompra;
			arr[i].promCompra = NULL;
		}
	}
	CambiarPorCliente(arr, s.ArrayClientes);
	heapsort(s.ArrayClientes);
}

void Wolfie::AgregarPromesa(Cliente c, const Promesa &p) {
	Promesa* prom= new Promesa(p.titulo(), p.tipo(), p.limite(), p.cantidad());
	if (prom->tipo()==COMPRA) {
		Promesa*& ptr = BusquedaBinaria(c, _titulos.Significado(prom->titulo()).ArrayClientes).promCompra;
		assert(ptr==NULL);
		ptr=prom;
	} else {
		Promesa*& ptr = BusquedaBinaria(c, _titulos.Significado(prom->titulo()).ArrayClientes).promVenta;
		assert(ptr==NULL);
		ptr=prom;
	}
}

bool Wolfie::EnAlza(const Nombre &nt) const {
	return (_titulos.Significado(nt).titulo.enAlza());
}

Nat Wolfie::CantClientes() {return _clientes.Cardinal();}

Nat Wolfie::CantTitulos() {return _titulos.CantClaves();}

Titulo Wolfie::BuscarTitulo(const Nombre& nombre_titulo) const {
	return _titulos.Significado(nombre_titulo).titulo;
}

Nat Wolfie::AccionesTotalesDe(const Cliente& cliente) const {
	Nat cant=0;
	DiccString<InfoTitulo>::Iterador it = _titulos.Claves();
	while (it.HaySiguiente()) {
		cant += BusquedaBinaria(cliente, _titulos.Significado(it.Siguiente()).ArrayClientes).cantAcc;
		it.Siguiente();
	}
	return cant;
}

Nat Wolfie::AccionesPorCliente(const Cliente& cliente, const Nombre& nombre_titulo) const {
	return BusquedaBinaria(cliente, _titulos.Significado(nombre_titulo).ArrayClientes).cantAcc;
}

Nat Wolfie::AccionesDisponibles(const Nombre& nombre_titulo) const {
	return _titulos.Significado(nombre_titulo).AccionesDisponibles;
}

bool Wolfie::PrometeComprar(const Cliente& cliente, const Nombre& titulo) const {
	return (BusquedaBinaria(cliente, _titulos.Significado(titulo).ArrayClientes).promCompra != NULL);
}

Promesa Wolfie::PromesaDeCompra(const Cliente& cliente, const Nombre& titulo) const{
	assert(this->Wolfie::PrometeComprar(cliente, titulo));
	return *(BusquedaBinaria(cliente, _titulos.Significado(titulo).ArrayClientes).promCompra);
}

bool Wolfie::PrometeVender(const Cliente& cliente, const Nombre& titulo) const {
	return (BusquedaBinaria(cliente, _titulos.Significado(titulo).ArrayClientes).promVenta != NULL);
}

Promesa Wolfie::PromesaDeVenta(const Cliente& cliente, const Nombre& titulo) const{
	assert(this->Wolfie::PrometeVender(cliente, titulo));
	return *(BusquedaBinaria(cliente, _titulos.Significado(titulo).ArrayClientes).promVenta);
}

/*
cambios:
agregue la struct ultLlamado para no usar una tupla
agregue operadores entre tuplaPorCliente y Cliente para poder hacer busqueda binaria con el nombre de cliente 
*/
