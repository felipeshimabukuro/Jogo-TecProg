#pragma once
#include "Elemento.h"
#include "Lista.h"
#include "Entidade.h"
#include "Gerenciador_grafico.h"

using namespace Entidades;
using namespace Gerenciadores;

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
		const int getTamanho() const;
		Entidade* operator[](int pos);
		//void percorrer(sf::RenderWindow* window);
		void percorrer();
		void desenharTodas(Gerenciador_grafico *pGG);
		void limparDestruidos();
		void salvar();
	};
}