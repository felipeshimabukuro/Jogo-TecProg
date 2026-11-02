#pragma once
#include "Elemento.h"
#include "Lista.h"
#include "Entidade.h"

using namespace Entidades;

namespace Listas
{
	class ListaEntidade
	{
	private:
		Lista<Entidade> LEs;

	public:
		ListaEntidade();
		~ListaEntidade();
		void incluir(Entidade* pElemento);
		void remover(Entidade* pElemento);
		int getTamanho();
		Entidade* operator[](int pos);
		//void percorrer(sf::RenderWindow* window);
		void executarTodas();
		void desenharTodas(sf::RenderWindow* window);
	};
}