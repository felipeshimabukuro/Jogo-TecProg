#include "Bibliotecas.h"
#include "Jogo.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Topeira.h"
#include "Obstaculo.h"
#include "Plataforma.h"

using namespace Gerenciadores;
using namespace Personagens;

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