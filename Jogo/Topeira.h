#pragma once
#include "Inimigo.h"
#include "Jogador.h"

namespace Personagens
{
	class Topeira : public Inimigo
	{
	private:
		string estado;
		bool cavando;
		int tiro_cd;
		static const int dist_atk;
		static const int tempo_tiro;
		int ticks;
		const int max_ticks;

	public:
		Topeira(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j);
		~Topeira();
		void cavar();
		void atirar();
		bool perto();
		void seguir();
		void executar();
		void colisao(Entidade* ent, sf::Vector2f ds);
		void danificar(Jogador* p);
	};
}
