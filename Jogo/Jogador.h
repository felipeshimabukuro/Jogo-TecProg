#pragma once
#include "Personagem.h"
#include "Inimigo.h"

class Jogador:public Personagens::Personagem {
private:
	short int num;
	static int pontos;
	int pulo_coyote;
	const int t_coyote;
	int invent;
	int t_dano;
	static const int t_imune = 10;
public:
	Jogador(int xx, int yy, short int n);
	~Jogador();
	void colidir(Inimigo* pIn);
	void executar();
	void salvar();
	void mover();
	void idle();
	void dig();
	void place();
	void receberDano(int dano);
};