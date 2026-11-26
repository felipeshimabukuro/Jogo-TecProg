#pragma once
#include "Lista.h"
#include "Entidade.h"
#include "Gerenciador_grafico.h"

namespace Escavadores_intrepidos {
	namespace Listas
	{
		using namespace Entidades;
		using namespace Gerenciadores;
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
			void percorrer();
			void desenharTodas(Gerenciador_grafico* pGG);
			void limparDestruidos();
			void salvar();
		};
	}
}