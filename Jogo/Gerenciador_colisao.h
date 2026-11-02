#pragma once
#include "Bibliotecas.h"
#include "Jogador.h"
#include "Obstaculo.h"
#include "Inimigo.h"
#include "Projetil.h"
#include "ListaEntidade.h"

using namespace Listas;
using namespace Entidades;
using namespace Personagens;

namespace Gerenciadores
{
	class Gerenciador_colisao
	{
	private:
		vector<Inimigo*> LIs;
		list<Obstaculo*> LOs;
		set<Projetil*> LPs;
		Jogador* pJog1;
		ListaEntidade* LE;

		// Singleton
		static Gerenciador_colisao* pColisao;
		Gerenciador_colisao();

	public:
		~Gerenciador_colisao();
		static Gerenciador_colisao* getGerenciadorColisao();
		void setJogador(Jogador* pJ);
		void setListaEntidade(ListaEntidade* pLE);
		void adicionarInimigo(Inimigo* pi);
		void removerInimigo(Inimigo* pi);
		void adicionarObstaculo(Obstaculo* po);
		void removerObstaculo(Obstaculo* po);
		void adicionarProjetil(Projetil* pj);
		void removerProjetil(Projetil* pj);
		const sf::Vector2f calcularColisao(Entidade* ent1, Entidade* ent2);
		//const bool verificaColisao(Entidade* pe1, Entidade* pe2) const;
		void executar();
	};
}
