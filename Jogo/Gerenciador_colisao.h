#pragma once
#include "Bibliotecas.h"
#include "Jogador.h"
#include "Obstaculo.h"
#include "Inimigo.h"
#include "Projetil.h"

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

	public:
		Gerenciador_colisao(Jogador* pJ = NULL, vector<Inimigo*> LIn = vector<Inimigo*>(), list<Obstaculo*> LOb = list<Obstaculo*>());
		~Gerenciador_colisao();
		void setJogador(Jogador* pJ);
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
