#pragma once
#include "Bibliotecas.h"
#include "Personagem.h"
#include "Projetil.h"

namespace Personagens {
	class Jogador;

	class Inimigo : public Personagem {
	protected:
		bool boss;
		int nivel_maldade;
		int walk_cd;
		static const int walk_tm;
		int x_alvo;
		short int lado;
		Jogador* pJogador1;
		Jogador* pJogador2;
		sf::Clock relogio;
		//short moveAleatorio;
		void inicializa();
		std::list<Entidades::Projetil*> projeteisPendentes;
		float dist_detec;

	public:
		Inimigo(ID id, const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j1, Jogador* j2);
		~Inimigo();
		virtual void executar() = 0;
		//virtual void danificar() = 0;
		virtual void salvar() = 0;
		//virtual void selecionarAlvo() = 0;
		void mover();
		sf::Vector2f distanciaAlvo(sf::Vector2f posJogador, sf::Vector2f posInimigo);
		void persegueJogador(Jogador* j);
		void movimentoAleatorio();
		virtual void atualizaLado();
		void salvarDataBuffer();
		void receberDano(int dano);
		sf::RectangleShape getCorpo();
		void setPos(const sf::Vector2f pos);
		void colisao(Entidade* ent, sf::Vector2f ds);
		const bool getBoss() const;
		std::list<Entidades::Projetil*>* getProjeteisPendentes();
		virtual void danificar(Jogador* p) = 0;
		bool detectarJogador();
		void setNivelMaldade(const int nm);
		void setWalkCd(const int cd);
		void setLado(const int l);
		void setXAlvo(const int xa);
		Jogador* getJogadorAlvo();
	};
}
