#include "Bibliotecas.h"
#include "Jogo.h"

Jogo::Jogo() : faseAtual(new Fases::Caverna_Maldosa)
{
	executar();
}

Jogo::~Jogo()
{
	if (faseAtual) {
		delete faseAtual;
		faseAtual = NULL;
	}
}

void Jogo::executar()
{
	if (faseAtual) {
		faseAtual->executar();
	}
}