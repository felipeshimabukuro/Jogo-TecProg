#pragma once
#include "Personagem.h"
#include "Inimigo.h"

class Jogador:public Personagens::Personagem {
private:
	sf::RectangleShape corpo;
	sf::Vector2f vel;
	short int num;
	static int pontos;
	int pulo_coyote;
	//const int t_coyote;
	int invent;
	int t_dano;
	static const int t_imune = 10;
	void inicializa();
public:
	Jogador(const sf::Vector2f pos, const sf::Vector2f tam);
	Jogador(const sf::RectangleShape corpo);
	Jogador();
	~Jogador();
	void colidir(Inimigo* pIn);
	void executar();
	void salvar();
	void mover();
	//void idle();
	//void dig();
	//void place();
	void receberDano(int dano);
	const sf::RectangleShape getCorpo();
};