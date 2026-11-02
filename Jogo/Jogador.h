#pragma once
#include "Personagem.h"

namespace Entidades {
	class Obstaculo;
}

namespace Personagens
{
	class Inimigo;

	class Jogador : public Personagens::Personagem {
	private:
		sf::RectangleShape corpo;
		bool acaoPressionada;
		short int num;
		static int pontos;
		int pulo_coyote;
		//const int t_coyote;
		int invent;
		//std::vector<Entidades::Obstaculo*> inventario;
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
		void cavar();
		void place();
		void receberDano(int dano);
		sf::RectangleShape getCorpo();
		void setPos(const sf::Vector2f pos);
	};
}
