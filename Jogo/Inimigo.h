#pragma once
#include "Bibliotecas.h"
#include "Personagem.h"

namespace Personagens {
	class Jogador;

	class Inimigo : public Personagem {
	protected:
		bool boss;
		int nivel_maldade;
		int walk_cd;
		int walk_tm;
		int x_alvo;
		short int lado;
		Jogador* jogador;
		sf::Clock relogio;
		//short moveAleatorio;
		void inicializa();

	public:
		Inimigo(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j);
		~Inimigo();
		virtual void executar() = 0;
		//virtual void danificar() = 0;
		//virtual void salvar() = 0;
		//virtual void selecionarAlvo() = 0;
		void mover();
		sf::Vector2f distanciaAlvo(sf::Vector2f posJogador, sf::Vector2f posInimigo);
		void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo, Jogador* j);
		void movimentoAleatorio();
		void salvar();
		void receberDano(int dano);
		sf::RectangleShape getCorpo();
		void setPos(const sf::Vector2f pos);
		void colisao(Entidade* ent, sf::Vector2f ds);
		const bool getBoss() const;
	};
}
