#include <iostream>
#include <queue>
#include "nodoavl.h"
#include "arbolbb.h"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#pragma once

/**
 * @brief Clase árbol AVL
 * Representa un árbol AVL.
 */
template <class Key>
class ArbolAVL : public ArbolBB<Key> {
 public:
  ArbolAVL();
  ~ArbolAVL();

  bool insertar(const Key&);
	bool buscar(const Key&) const;
	bool insertarBalanceado(NodoAVL<Key>**, NodoAVL<Key>*, bool&, int);
	void insertar_re_balancear_izquierda(NodoAVL<Key>**, bool&);
	void insertar_re_balancear_derecha(NodoAVL<Key>**, bool&);

  bool eliminar(const Key&);
	bool eliminarRama(NodoAVL<Key>**, const int&, bool&);
	void eliminar_re_balancear_izquierda(NodoAVL<Key>**, bool&);
	void eliminar_re_balancear_derecha(NodoAVL<Key>**, bool&);
	void sustituye(NodoAVL<Key>**, NodoAVL<Key>**, bool&);

	void rotacionII(NodoAVL<Key>**);
  void rotacionDD(NodoAVL<Key>**);
	void rotacionID(NodoAVL<Key>**);
	void rotacionDI(NodoAVL<Key>**);

	void recorrerInorden(NodoAVL<Key>*) const;
	void recorrerPreorden(NodoAVL<Key>*, std::vector<Key>&) const;
	void recorrerPostorden(NodoAVL<Key>*) const;
	std::ostream& recorrerNiveles(NodoAVL<Key>*, std::ostream&) const;

	NodoAVL<Key>* getRaiz() const;
	NodoAVL<Key>** getRaizPtr();

	template <class Key2>
	friend std::ostream& operator<<(std::ostream&, const ArbolAVL<Key>&);

 private:
  NodoAVL<Key>* raiz_ = nullptr;
};

/**
 * @brief Constructor de la clase árbol AVL
 */
template <class Key>
ArbolAVL<Key>::ArbolAVL() : ArbolBB<Key>() {}

/**
 * @brief Destructor de la clase árbol AVL
 */
template <class Key>
ArbolAVL<Key>::~ArbolAVL() {}

/**
 * @brief Método que busca un dato en el árbol
 * @param dat Dato a buscar
 */
template <class Key>
bool ArbolAVL<Key>::buscar(const Key& dat) const {
	// Recorremos el árbol hasta encontrar el dato o llegar a un nodo nulo.
	NodoAVL<Key>* aux = raiz_;
	while (aux != nullptr) {
		// Si encontramos el dato, devolvemos true.
		if (dat == aux->getClave()) return true;
		// Si el dato es menor que el dato del nodo actual, avanzamos por la rama izquierda.
		else if (dat < aux->getClave()) aux = aux->getIzdo();
		// Si el dato es mayor que el dato del nodo actual, avanzamos por la rama derecha.
		else aux = aux->getDcho();
	}
	return false;
}

/**
 * @brief Método que inserta un dato en el árbol
 * @param dat Dato a insertar
 */
template <class Key>
bool ArbolAVL<Key>::insertar(const Key& dat) {
	// Si el dato ya está en el árbol, devolvemos false.
	if (buscar(dat)) return false;
	bool crece = false;
	NodoAVL<Key>* nodo = new NodoAVL<Key>(dat, dat);
	int i = 0;
	// Si no se ha podido insertar el nodo, devolvemos false.
	if (!insertarBalanceado(getRaizPtr(), nodo, crece, i)) return false;
	std::cout << std::endl;
	// Mostramos el árbol.
	std::cout << *this;
	return true;
}

/**
 * @brief Método que inserta un dato en el árbol de forma balanceada
 * @param raiz Raíz del árbol
 * @param nodo Nodo a insertar
 * @param crece Indica si el árbol ha crecido
 */
template <class Key>
bool ArbolAVL<Key>::insertarBalanceado(NodoAVL<Key>** nodo, NodoAVL<Key>* nuevo, bool& crece, int i) {
	// Si el nodo es nulo, insertamos el nuevo nodo.
	if ((*nodo) == nullptr) {
		*nodo = nuevo;
		crece = true;
		return true;
	} else if (nuevo->getClave() < (*nodo)->getClave()) { // Si el dato es menor que el dato del nodo actual.
		// Si no se ha podido insertar el nodo, devolvemos false.
		if (!insertarBalanceado((*nodo)->getIzdoPtr(), nuevo, crece, ++i)) return false;
		// Si el árbol ha crecido, rebalanceamos a la izquierda.
		if (crece) insertar_re_balancear_izquierda(nodo, crece);
	} else { // Si el dato es mayor que el dato del nodo actual.
		// Si no se ha podido insertar el nodo, devolvemos false.
		if (!insertarBalanceado((*nodo)->getDchoPtr(), nuevo, crece, ++i)) return false;
		// Si el árbol ha crecido, rebalanceamos a la derecha.
		if (crece) insertar_re_balancear_derecha(nodo, crece);
	}
	return true;
}

/**
 * @brief Método que inserta un dato en el árbol de forma balanceada
 * @param nodo Nodo a insertar
 */
template <class Key>
void ArbolAVL<Key>::insertar_re_balancear_izquierda(NodoAVL<Key>** nodo, bool& crece) {
	// Dependiendo del balance del nodo, realizamos una rotación.
	switch ((*nodo)->getBal()) {
		case -1: // Si el balance es -1, rotamos a la derecha.
			(*nodo)->setBal(0);
			crece = false;
			break;
		case 0: // Si el balance es 0, rotamos a la derecha.
			(*nodo)->setBal(1);
			break;
		case 1: // Si el balance es 1, rotamos a la izquierda o a la derecha.
			if ((*nodo)->getIzdo()->getBal() == 1) this->rotacionII(nodo); 
			else this->rotacionID(nodo);
			crece = false;
			break;
	}
}

/**
 * @brief Método que inserta un dato en el árbol de forma balanceada
 * @param nodo Nodo a insertar
 */
template <class Key>
void ArbolAVL<Key>::insertar_re_balancear_derecha(NodoAVL<Key>** nodo, bool& crece) {
	// Dependiendo del balance del nodo, realizamos una rotación.
	switch ((*nodo)->getBal()) {
		case -1: // Si el balance es -1, rotamos a la izquierda o a la derecha.
			if ((*nodo)->getDcho()->getBal() == -1) this->rotacionDD(nodo);
			else this->rotacionDI(nodo);
			crece = false;
			break;
		case 0: // Si el balance es 0, rotamos a la izquierda.
			(*nodo)->setBal(-1);
			break;
		case 1: // Si el balance es 1, rotamos a la izquierda.
			(*nodo)->setBal(0);
			crece = false;
			break;
	}
}

/**
 * @brief Método que elimina un dato del árbol
 * @param dat Dato a eliminar
 */
template <class Key>
bool ArbolAVL<Key>::eliminar(const Key& dat) {
	// Si el dato no está en el árbol, devolvemos false.
	if (!buscar(dat)) return false;
	bool decrece = false;
	// Si no se ha podido eliminar el nodo, devolvemos false.
	eliminarRama(new NodoAVL<Key>*(&raiz_), dat, decrece);
}

/**
 * @brief Método que elimina un dato del árbol
 * @param nodo Nodo a eliminar
 * @param clavedada Dato a eliminar
 * @param decrece Indica si el árbol ha decrecido
 */
template <class Key>
bool ArbolAVL<Key>::eliminarRama(NodoAVL<Key>** nodo, const int& clavedada, bool& decrece) {
	// Si el nodo es nulo, devolvemos false.
	if ((*nodo) == nullptr) return false;
	bool encontrado = false;
	if (clavedada < (*nodo)->getClave()) { // Si el dato es menor que el dato del nodo actual, eliminamos por la rama izquierda.
		// Llamamos recursivamente a eliminarRama con el hijo izquierdo del nodo actual para eliminar el dato.
		encontrado = eliminarRama((*nodo)->getIzdoPtr(), clavedada, decrece);
		// Si el árbol ha decrecido, rebalanceamos a la izquierda.
		if (decrece) eliminar_re_balancear_izquierda(nodo, decrece);
	} else if (clavedada > (*nodo)->getClave()) { // Si el dato es mayor que el dato del nodo actual, eliminamos por la rama derecha.
		// Llamamos recursivamente a eliminarRama con el hijo derecho del nodo actual para eliminar el dato.
		encontrado = eliminarRama((*nodo)->getDchoPtr(), clavedada, decrece);
		// Si el árbol ha decrecido, rebalanceamos a la derecha.
		if (decrece) eliminar_re_balancear_derecha(nodo, decrece);
	} else { // Si el dato es igual al dato del nodo actual, eliminamos el nodo actual.
		encontrado = true;
		NodoAVL<Key>** eliminado = nodo;
		if ((*nodo)->getIzdoPtr() == nullptr) { // Si el nodo no tiene hijos o solo tiene hijo derecho, lo eliminamos.
			nodo = (*nodo)->getDchoPtr();
			decrece = true;
		} else if ((*nodo)->getDchoPtr() == nullptr) { // Si el nodo no tiene hijos o solo tiene hijo izquierdo, lo eliminamos.
			nodo = (*nodo)->getIzdoPtr();
			decrece = true;
		} else { // Si el nodo tiene dos hijos.
			// Sustituimos el nodo por su sucesor en el orden in-order.
			sustituye(eliminado, (*nodo)->getIzdoPtr(), decrece);
			// Si el árbol ha decrecido, rebalanceamos a la izquierda.
			if (decrece) eliminar_re_balancear_izquierda(nodo, decrece);
		}
		// Eliminamos el nodo.
		delete *eliminado;
	}
	return encontrado;
}

/**
 * @brief Método que elimina un dato del árbol
 * @param nodo Nodo a eliminar
 */
template <class Key>
void ArbolAVL<Key>::eliminar_re_balancear_izquierda(NodoAVL<Key>** nodo, bool& decrece) {
	// Dependiendo del balance del nodo, realizamos una rotación.
	switch ((*nodo)->getBal()) {
		case -1: // Si el balance es -1, rotamos a la izquierda.
			// Si el balance del hijo derecho del nodo es mayor que 0, rotamos a la derecha-izquierda.
			if (*((*nodo)->getDchoPtr())->getBal() > 0) this->rotacionDI(nodo);
			else { // Si el balance del hijo derecho del nodo es 0, rotamos a la derecha-derecha.
				if (*((*nodo)->getDchoPtr())->getBal() == 0) decrece = false;
				this->rotacionDD(nodo);
			}
			break;
		case 0: // Si el balance es 0, rotamos a la derecha.
			(*nodo)->setBal(-1);
			decrece = false;
			break;
		case 1: // Si el balance es 1, rotamos a la derecha.
			(*nodo)->setBal(0);
			break;
	}
}

/**
 * @brief Método que elimina un dato del árbol
 * @param nodo Nodo a eliminar
 */
template <class Key>
void ArbolAVL<Key>::eliminar_re_balancear_derecha(NodoAVL<Key>** nodo, bool& decrece) {
	// Dependiendo del balance del nodo, realizamos una rotación.
	switch ((*nodo)->getBal()) {
		case -1: // Si el balance es -1, rotamos a la izquierda.
			(*nodo)->setBal(0);
			break;
		case 0: // Si el balance es 0, rotamos a la izquierda.
			(*nodo)->setBal(1);
			decrece = false;
			break;
		case 1: // Si el balance es 1, rotamos a la izquierda o a la derecha.
			if ((*nodo)->getIzdoPtr()->getBal() < 0) this->rotacionID(nodo);
			else {
				if ((*nodo)->getIzdoPtr()->getBal() == 0) decrece = false;
				this->rotacionII(nodo);
			}
			break;
	}
}

/**
 * @brief Método que sustituye un nodo por su sucesor en el orden in-order cuando tiene dos hijos.
 * @param eliminado Nodo a eliminar, que será reemplazado por el sucesor.
 * @param sust Nodo sustituto, inicialmente el hijo derecho del nodo a eliminar.
 * @param decrece Indica si el árbol ha decrecido, esencial para el rebalanceo posterior.
 *
 * Este método recursivamente busca el sucesor in-order más pequeño (el nodo más a la izquierda del subárbol derecho),
 * lo mueve al lugar del nodo eliminado y ajusta los apuntadores para mantener las propiedades del árbol AVL.
 * El parámetro decrece se ajusta para indicar si la altura del subárbol ha disminuido, necesitando rebalanceo.
 */

template <class Key>
void ArbolAVL<Key>::sustituye(NodoAVL<Key>** eliminado, NodoAVL<Key>** sust, bool& decrece) {
	// Si el nodo sustituto tiene hijo derecho
	if ((*sust)->getDchoPtr() != nullptr) {
		// Llamamos recursivamente a sustituye con el hijo derecho del nodo sustituto.
		sustituye(eliminado, (*sust)->getDchoPtr(), decrece);
		// Si el árbol ha decrecido, rebalanceamos a la derecha.
		if (decrece) eliminar_re_balancear_derecha(sust, decrece);
	} else { // Si el nodo sustituto no tiene hijo derecho.
		// Copiamos los datos del nodo sustituto al nodo eliminado.
		(*eliminado)->setDato((*sust)->getDato());
		(*eliminado)->setClave((*sust)->getClave());
		eliminado = sust;
		sust = (*sust)->getIzdoPtr();
		decrece = true;
	}
}

/**
 * @brief Método que realiza una rotación a la izquierda
 * @param nodo Nodo a rotar
 */
template <class Key>
void ArbolAVL<Key>::rotacionII(NodoAVL<Key>** nodo) {
  if (!nodo || !*nodo) return; // Verificamos que nodo no sea nulo.
	// Muestra la traza si está activada.
	if (this->getTraza()) {
		std::cout << std::endl;
    std::cout << BOLD << YELLOW << "Desbalanceo:" << RESET << std::endl;
		std::cout << *this;
    std::cout << ITALIC << "Rotación II en [" << (*nodo)->getClave() << " (" << (*nodo)->getBal() + 1 << ")]" << RESET;
  }
	// Obtenemos el hijo izquierdo de nodo.
  NodoAVL<Key>* nodo1 = (*nodo)->getIzdo();
  if (!nodo1) return; // Verificamos que nodo1 no sea nulo.
  // Actualizamos los enlaces entre los nodos.
  (*nodo)->setIzdo(nodo1->getDcho());
  nodo1->setDcho(*nodo);
  // Actualizamos los factores de balance si es necesario.
  if (nodo1->getBal() == 1) {
    (*nodo)->setBal(0);
    nodo1->setBal(0);
  } else {
    (*nodo)->setBal(1);
    nodo1->setBal(-1);
  }
  // Actualizamos el puntero del nodo padre para apuntar al nuevo subárbol raíz.
  *nodo = nodo1;
}


/**
 * @brief Método que realiza una rotación a la derecha
 * @param nodo Nodo a rotar
 */
template <class Key>
void ArbolAVL<Key>::rotacionDD(NodoAVL<Key>** nodo) {
	if (!nodo || !*nodo) return; // Verificamos que nodo no sea nulo.
	if (this->getTraza()) {
		std::cout << std::endl;
		std::cout << BOLD << YELLOW << "Desbalanceo:" << RESET << std::endl;
		std::cout << *this;
		std::cout << ITALIC << "Rotación DD en [" << (*nodo)->getClave() << " (" << (*nodo)->getBal() - 1 << ")]" << RESET;
	}
	// Obtenemos el hijo derecho de nodo.
	NodoAVL<Key>* aux = (*nodo)->getDcho();
	if (!aux) return; // Verificamos que aux no sea nulo.
	// Actualizamos los enlaces entre los nodos.
	(*nodo)->SetDcho(aux->getIzdo());
	aux->SetIzdo(*nodo);
	// Actualizamos los factores de balance si es necesario.
	if (aux->getBal() == -1) {
		(*nodo)->setBal(0);
		aux->setBal(0);
	} else {
		(*nodo)->setBal(-1);
		aux->setBal(1);
	}
	// Actualizamos el puntero del nodo padre para apuntar al nuevo subárbol raíz.
	*nodo = aux;
}

/**
 * @brief Método que realiza una rotación a la izquierda y luego a la derecha
 * @param nodo Nodo a rotar
 */
template <class Key>
void ArbolAVL<Key>::rotacionID(NodoAVL<Key>** nodo) {
	if (!nodo || !*nodo) return; // Verificamos que nodo no sea nulo.
	if (this->getTraza()) {
		std::cout << std::endl;
		std::cout << BOLD << YELLOW << "Desbalanceo:" << RESET << std::endl;
		std::cout << *this;
		std::cout << ITALIC << "Rotación ID en [" << (*nodo)->getClave() << " (" << (*nodo)->getBal() + 1 << ")]" << RESET;
	}
	// Obtenemos el hijo izquierdo y derecho de nodo.
	NodoAVL<Key>* nodo1 = (*nodo)->getIzdo();
	NodoAVL<Key>* nodo2 = nodo1->getDcho();
	// Actualizamos los enlaces entre los nodos.
	(*nodo)->SetIzdo(nodo2->getDcho());
	nodo2->SetDcho(*nodo);
	nodo1->SetDcho(nodo2->getIzdo());
	nodo2->SetIzdo(nodo1);
	// Actualizamos los factores de balance si es necesario.
	if (nodo2->getBal() == -1) nodo1->setBal(1);
	else nodo1->setBal(0);
	if (nodo2->getBal() == 1) (*nodo)->setBal(-1);
	else (*nodo)->setBal(0);
	nodo2->setBal(0);
	// Actualizamos el puntero del nodo padre para apuntar al nuevo subárbol raíz.
	*nodo = nodo2;
}

/**
 * @brief Método que realiza una rotación a la derecha y luego a la izquierda
 * @param nodo Nodo a rotar
 */
template <class Key>
void ArbolAVL<Key>::rotacionDI(NodoAVL<Key>** nodo) {
	if (!nodo || !*nodo) return; // Verificamos que nodo no sea nulo.
	if (this->getTraza()) {
		std::cout << std::endl;
		std::cout << BOLD << YELLOW << "Desbalanceo:" << RESET << std::endl;
		std::cout << *this;
		std::cout << ITALIC << "Rotación DI en [" << (*nodo)->getClave() << " (" << (*nodo)->getBal() - 1 << ")]" << RESET;
	}
	// Obtenemos el hijo izquierdo y derecho de nodo.
	NodoAVL<Key>* nodo1 = (*nodo)->getDcho();
	NodoAVL<Key>* nodo2 = nodo1->getIzdo();
	// Actualizamos los enlaces entre los nodos.
	(*nodo)->SetDcho(nodo2->getIzdo());
	nodo2->SetIzdo(*nodo);
	nodo1->SetIzdo(nodo2->getDcho());
	nodo2->SetDcho(nodo1);
	// Actualizamos los factores de balance si es necesario.
	if (nodo2->getBal() == 1) nodo1->setBal(-1);
	else nodo1->setBal(0);
	if (nodo2->getBal() == -1) (*nodo)->setBal(1);
	else (*nodo)->setBal(0);
	nodo2->setBal(0);
	// Actualizamos el puntero del nodo padre para apuntar al nuevo subárbol raíz.
	*nodo = nodo2;
}

/**
 * @brief Método que recorre el árbol en inorden
 * @param nodo Nodo a recorrer
 */
template <class Key>
void ArbolAVL<Key>::recorrerInorden(NodoAVL<Key>* nodo) const {
	// Si el nodo es nulo.
	if (nodo != nullptr) {
		// Recorremos el árbol en inorden por la rama izquierda.
		recorrerInorden(nodo->getIzdo());
		// Mostramos el dato del nodo.
		std::cout << nodo->getClave() << " ";
		// Recorremos el árbol en inorden por la rama derecha.
		recorrerInorden(nodo->getDcho());
	}
}

/**
 * @brief Método que recorre el árbol en preorden
 * @param nodo Nodo a recorrer
 */
template <class Key>
void ArbolAVL<Key>::recorrerPreorden(NodoAVL<Key>* nodo, std::vector<Key>& v) const {
	// Si el nodo es nulo.
	if (nodo != nullptr) {
		// Mostramos el dato del nodo.
		v.push_back(nodo->getClave());
		// Recorremos el árbol en preorden por la rama izquierda.
		recorrerPreorden(nodo->getIzdo(), v);
		// Recorremos el árbol en preorden por la rama derecha.
		recorrerPreorden(nodo->getDcho(), v);
	}
}

/**
 * @brief Método que recorre el árbol en postorden
 * @param nodo Nodo a recorrer
 */
template <class Key>
void ArbolAVL<Key>::recorrerPostorden(NodoAVL<Key>* nodo) const {
	// Si el nodo es nulo.
	if (nodo != nullptr) {
		// Recorremos el árbol en postorden por la rama izquierda.
		recorrerPostorden(nodo->getIzdo());
		// Recorremos el árbol en postorden por la rama derecha.
		recorrerPostorden(nodo->getDcho());
		// Mostramos el dato del nodo.
		std::cout << nodo->getClave() << " ";
	}
}

/**
 * @brief Método que recorre el árbol por niveles
 * @param nodo Nodo a recorrer
 */
template <class Key>
std::ostream& ArbolAVL<Key>::recorrerNiveles(NodoAVL<Key>* nodo, std::ostream& os) const {
	// Manejo explícito del árbol vacío.
	if (nodo == nullptr) {
		os << std::endl;
		os << "Nivel " << BOLD << MAGENTA << "0" << RESET << ": [.] " << std::endl;
		return os;
	}

	// Cola de nodos.
	std::queue<std::pair<NodoAVL<Key>*, int>> Q;

	int nivelActual = 0;
	os << "Nivel " << BOLD << MAGENTA << nivelActual << RESET << ": ";

	// Insertamos la raíz del árbol en la cola con nivel 0.
	Q.push({nodo, nivelActual});

	// Mientras la cola no esté vacía, procesamos los nodos.
	while (!Q.empty()) {
		// Extraemos y eliminamos el nodo de la cola.
		std::pair<NodoAVL<Key>*, int> nodoInfo = Q.front();
		Q.pop();

		// Extraemos el nodo y el nivel del nodo.
		NodoAVL<Key>* nodo_aux = nodoInfo.first;
		int nivel = nodoInfo.second;

		// Si estamos en un nuevo nivel, actualizamos nivelActual.
		if (nivel > nivelActual) {
			os << "\nNivel " << BOLD << MAGENTA << nivel << RESET << ": ";
			nivelActual = nivel;
		}

		// Si el nodo no es nullptr, lo procesamos.
		if (nodo_aux != nullptr) {
			if (this->getTraza()) os << "[" << nodo_aux->getClave() << " (" << nodo_aux->getBal() << ")] ";
			else os << "[" <<  nodo_aux->getDato() << "] ";
			// Insertar hijo izquierdo y derecho en la cola, incluso si son nullptr.
			Q.push({nodo_aux->getIzdo(), nivel + 1});
			Q.push({nodo_aux->getDcho(), nivel + 1});
		} else {
			os << "[.] ";
		}
	}
	os << std::endl;
	return os;
}

/**
 * @brief Función que devuelve la raíz del árbol
 * 
 * @tparam Key Dato a procesar
 * @return NodoAVL<Key>* Raíz del árbol
 */
template <class Key>
NodoAVL<Key>* ArbolAVL<Key>::getRaiz() const { return raiz_; }

/**
 * @brief Función que devuelve un puntero a la raíz del árbol
 * 
 * @tparam Key Dato a procesar
 * @return NodoAVL<Key>** Puntero a la raíz del árbol
 */
template <class Key>
NodoAVL<Key>** ArbolAVL<Key>::getRaizPtr() { return &raiz_; }

/**
 * @brief Sobrecarga del operador de inserción para mostrar el árbol
 * 
 */
template <class Key>
std::ostream& operator<<(std::ostream& os, const ArbolAVL<Key>& arbol) {
	return arbol.recorrerNiveles(arbol.getRaiz(), os);
}