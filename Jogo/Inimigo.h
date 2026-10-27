#pragma once
#include "Personagem.h"

class Inimigo :public Personagens::Personagem {
protected:
	int nivel_maldade;
	int walk_cd;
	int walk_tm;
	int x_alvo;
	short int lado;
public:
	Inimigo();
	~Inimigo();
	virtual void executar() = 0;
	virtual void danificar() = 0;
	virtual void salvar() = 0;
	virtual void selecionarAlvo() = 0;
};
