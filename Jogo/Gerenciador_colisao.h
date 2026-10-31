#pragma once
#include "Bibliotecas.h"
#include "Jogador.h"
#include "Obstaculo.h"
#include "Inimigo.h"

using namespace Entidades;
using namespace Personagens;

namespace Gerenciadores
{
	class Gerenciador_colisao
	{
	private:
		vector<Inimigo*> LIs;
		list<Obstaculo*> LOs;
		//set<Projetil*> LPs;
		Jogador* pJog1;

	public:
		Gerenciador_colisao(Jogador* pJ = nullptr, vector<Inimigo*> LIn = vector<Inimigo*>(), list<Obstaculo*> LOb = list<Obstaculo*>());
		~Gerenciador_colisao();
		void setJogador(Jogador* pJ);
		void adicionarInimigo(Inimigo* pIn);
		void removerInimigo(Inimigo* pIn);
		void adicionarObstaculo(Obstaculo* pOb);
		void removerObstaculo(Obstaculo* pOb);
		const sf::Vector2f calcularColisao(Entidade* ent1, Entidade* ent2);
		void executar();
	};
}
