#include "wolfie.h"
#include <iostream>
/*
Wolfie::const_Iterador Wolfie::const_Iterador::CrearIt(const DiccString<Wolfie::InfoTitulo>& t) const{
	const_Iterador i(t.Claves(), &t);
	//i.it=t.Claves();
	//i.dicc= &t;
	return i;
	//return Wolfie::const_Iterador::const_Iterador(t.Claves(), &t);
}
*/
Wolfie::Wolfie(const Conj<Nat> &c):	_titulos(DiccString<InfoTitulo>()),_clientes(ConjEstNat(c)),_ultimoLlamado(ultLlamado()){}

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
		it.Avanzar();
	}
}


/*const Titulo& Wolfie::const_Iterador::Actual() const {
	return (dicc->Significado(it.Siguiente()).titulo);
}

void Wolfie::const_Iterador::Proximo() {
	it.Avanzar();
}

bool Wolfie::const_Iterador::HayProximo() const{
	return it.HaySiguiente();
}*/

void CambiarPorCantAcc(Arreglo<Wolfie::TuplaPorCliente>& a1, Arreglo<Wolfie::TuplaPorCantAcc>& a2) {
	Nat i=0;
	while (i<a1.Tamanho()){
		a2.Definir(i, Wolfie::TuplaPorCantAcc(a1[i].cliente,a1[i].cantAcc,a1[i].promCompra,a1[i].promVenta));
		/*
		a2[i].cliente=a1[i].cliente;
		a2[i].cantAcc=a1[i].cantAcc;
		a2[i].promCompra=a1[i].promCompra;
		a2[i].promVenta=a1[i].promVenta;
		*/
		i++;
	}
} 

void CambiarPorCliente(Arreglo<Wolfie::TuplaPorCantAcc>& a1, Arreglo<Wolfie::TuplaPorCliente>& a2) {
	Nat i=0;
	while (i<a1.Tamanho()) {
		a2.Definir(i, Wolfie::TuplaPorCliente(a1[i].cliente,a1[i].cantAcc,a1[i].promCompra,a1[i].promVenta));
		/*
		a2[i].cliente=a1[i].cliente;
		a2[i].cantAcc=a1[i].cantAcc;
		a2[i].promCompra=a1[i].promCompra;
		a2[i].promVenta=a1[i].promVenta;
		*/
		i++;
	}
} 

Arreglo<typename Wolfie::TuplaPorCliente> CrearArrayClientes(typename ConjEstNat::const_Iterador it, Nat n){
	Arreglo<typename Wolfie::TuplaPorCliente> arr =Arreglo<typename Wolfie::TuplaPorCliente>(n);
	Nat i=0;
	do{
		
		arr.Definir(i, Wolfie::TuplaPorCliente(it.Actual(), 0, NULL, NULL));
		i++;
		it.Proximo();
		
	} while(it.HayProx());
	return arr;
}

/*
typename ConjEstNat::const_Iterador Wolfie::Clientes() const
{
	return ConjEstNat::const_Iterador(_clientes);
}

Wolfie::const_Iterador Wolfie::Titulos() const
{
	Wolfie::const_Iterador i(_titulos.Claves(), &_titulos);
	return i;
}
*/

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

void Wolfie::AgregarTitulo(const Titulo &t) {
	
	Arreglo<Wolfie::TuplaPorCliente> arr = CrearArrayClientes(_clientes.CrearIt(), _clientes.Cardinal());
	typename Wolfie::InfoTitulo info(arr, t, t.maxAcciones());
	_titulos.Definir(t.nombre(), info);
}

Nat Wolfie::AccionesPorCliente(const Cliente c, const Nombre& nt) const {
	return (BusquedaBinaria(c, _titulos.Significado(nt).ArrayClientes).cantAcc);
}

// Wolfie Wolfie::InaugurarWolfie(const Conj<Cliente> &c) {return Wolfie(c);}

void Wolfie::ActualizarCotizacion(const Nombre &nt, Dinero cot){
	Wolfie::InfoTitulo& s = _titulos.Significado(nt);
	s.titulo.recotizar(cot); //aca quizas hay problema si titulo devuelve una copia, no deberia
	Nat i=0;
	while (i<s.ArrayClientes.Tamanho()){
		if (s.ArrayClientes[i].promVenta != NULL && (s.ArrayClientes[i].promVenta->limite() > s.titulo.cotizacion())) {
			s.ArrayClientes[i].cantAcc -= s.ArrayClientes[i].promVenta->cantidad();
			s.AccionesDisponibles += s.ArrayClientes[i].promVenta->cantidad();
			delete s.ArrayClientes[i].promVenta;
			s.ArrayClientes[i].promVenta = NULL;
		}
		i++;
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
		i++;
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

Nat Wolfie::CantClientes() const {return _clientes.Cardinal();}

Nat Wolfie::CantTitulos() const {return _titulos.CantClaves();}

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

Nat Wolfie::AccionesPorClienteW(const Cliente& cliente, const Nombre& nombre_titulo) const {
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
 *Implementación del iterador de titulos
 */

 	//Funcion Clientes
 	typename Wolfie::Iterador_titulos Wolfie::Titulos() const{
 		return Iterador_titulos(*(this));
  	}

  	//Traslate del iterador de clientes de conjEstNat
	Wolfie::Iterador_titulos::Iterador_titulos(const Wolfie &w): it(w._titulos.Claves()) {}

	void Wolfie::Iterador_titulos::Avanzar(){
		it.Avanzar();
	}

	const String& Wolfie::Iterador_titulos::Siguiente() const{
		return it.Siguiente();
	}

	bool Wolfie::Iterador_titulos::HaySiguiente() const{
		return it.HaySiguiente();
	}
	

/*
 *Implementación del iterador de clientes
 */

 	//Funcion Clientes
 	typename Wolfie::Iterador_clientes Wolfie::Clientes() const{
 		return Iterador_clientes(*(this));
  	}

  	//Traslate del iterador de clientes de conjEstNat
	Wolfie::Iterador_clientes::Iterador_clientes(const Wolfie &w): it(w._clientes.CrearIt()) {}

	void Wolfie::Iterador_clientes::Avanzar(){
		it.Proximo();
	}

	Nat Wolfie::Iterador_clientes::Siguiente() const{
		return it.Actual();
	}

	bool Wolfie::Iterador_clientes::HaySiguiente() const{
		return it.HayProx();
	}
