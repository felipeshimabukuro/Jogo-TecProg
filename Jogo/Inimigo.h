#pragma once
#include "Bibliotecas.h"
#include "Personagem.h"
class Jogador;

class Inimigo :public Personagens::Personagem {
protected:
	int nivel_maldade;
	int walk_cd;
	int walk_tm;
	int x_alvo;
	short int lado;
	Jogador* jogador;
	sf::Clock relogio;
	//short moveAleatorio;
	void inicializa();
	sf::RectangleShape corpo;
public:
	Inimigo(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j);
	~Inimigo();
	//virtual void executar() = 0;
	//virtual void danificar() = 0;
	//virtual void salvar() = 0;
	//virtual void selecionarAlvo() = 0;
	void mover();
	void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo, Jogador* j);
	void movimentoAleatorio();
	void salvar();
	void receberDano(int dano);
	void executar();
	sf::RectangleShape getCorpo();
};
