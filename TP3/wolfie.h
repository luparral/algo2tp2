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
				InfoTitulo():ArrayClientes(Arreglo<TuplaPorCliente>()), titulo(Titulo("",0, 0, true)), AccionesDisponibles(){}
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
				const_Iterador(typename DiccString<Wolfie::InfoTitulo>::Iterador i, const DiccString<Wolfie::InfoTitulo>* d): it(i), dicc(d){}
				typename Wolfie::const_Iterador CrearIt(const DiccString<Wolfie::InfoTitulo>& t) const;
			
			private:
				typename DiccString<Wolfie::InfoTitulo>::Iterador it;
				const DiccString<typename Wolfie::InfoTitulo>* dicc;
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
		
		Wolfie(const Conj<Nat> &c);
		
	private:
		
		
		DiccString<InfoTitulo> _titulos;
		ConjEstNat _clientes;
		ultLlamado _ultimoLlamado;
	


};
Wolfie::const_Iterador Wolfie::const_Iterador::CrearIt(const DiccString<Wolfie::InfoTitulo>& t) const{
	const_Iterador i(t.Claves(), &t);
	//i.it=t.Claves();
	//i.dicc= &t;
	return i;
	//return Wolfie::const_Iterador::const_Iterador(t.Claves(), &t);
}

const Titulo& Wolfie::const_Iterador::Actual() const {
	return (dicc->Significado(it.Siguiente()).titulo);
}




template<class T, class U>
U& BusquedaBinaria(const T& t, Arreglo<U>& a) {
	Nat arriba = a.Tamanho();
	Nat abajo = 0;
	Nat centro;
	while (abajo <= arriba) {
		centro=(abajo+arriba)/2;
		if (a[centro]==t) {
			return a[centro];
		}else{
			if (a[centro]>t) {
				arriba=centro-1;
			}else{
				abajo=centro+1;
			}
		}
	}
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
	//const_Iterador i(t.Claves(), &t);
	return Wolfie::const_Iterador::CrearIt(_titulos);
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

Nat Wolfie::AccionesPorCliente(Cliente c, const Nombre& nt) const {
	return (BusquedaBinaria(c, _titulos.Significado(nt).ArrayClientes).cantAcc);
}

Wolfie Wolfie::InaugurarWolfie(const Conj<Cliente> &c) {return Wolfie(c);}

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
		BusquedaBinaria(c, _titulos.Significado(prom->titulo()).ArrayClientes).promCompra=prom;
	} else {
		BusquedaBinaria(c, _titulos.Significado(prom->titulo()).ArrayClientes).promVenta=prom;
	}
}

bool Wolfie::EnAlza(const Nombre &nt) const {
	return (_titulos.Significado(nt).titulo.enAlza());
}



/*
cambios:
agregue la struct ultLlamado para no usar una tupla
agregue operadores entre tuplaPorCliente y Cliente para poder hacer busqueda binaria con el nombre de cliente 
*/
