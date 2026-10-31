#pragma once
#include "Personagem.h"

namespace Personagens
{
	class Inimigo;

	class Jogador : public Personagens::Personagem {
	private:
		sf::RectangleShape corpo;
		//sf::Vector2f vel;
		short int num;
		static int pontos;
		int pulo_coyote;
		//const int t_coyote;
		int invent;
		int t_dano;
		static const int t_imune = 10;
		Entidade* chaoAtual;
		void inicializa();
	public:
		Jogador(const sf::Vector2f pos, const sf::Vector2f tam, short int n);
		Jogador(const sf::RectangleShape corpo);
		Jogador();
		~Jogador();
		void colisao(Entidade* ent, sf::Vector2f ds);
		void executar();
		void salvar();
		void mover();
		void pular();
		int getNum();
		//void idle();
		void cavar();
		//void place();
		void receberDano(int dano);
		sf::RectangleShape getCorpo();
		void setPos(const sf::Vector2f pos);
	};
}
