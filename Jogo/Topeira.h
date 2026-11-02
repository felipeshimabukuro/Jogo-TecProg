#pragma once
#include "Inimigo.h"
#include "Jogador.h"

namespace Personagens
{
	class Topeira : public Inimigo
	{
	private:
		bool cavando;
		int tiro_cd;
		static const int dist_detec;
		static const int dist_atk;
		static const int tempo_tiro;

	public:
		Topeira(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j);
		~Topeira();
		void cavar();
		void atirar();
		bool detectarJogador();
		bool perto();
		void executar();
	};
}
