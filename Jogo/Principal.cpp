#include "Bibliotecas.h"
#include "Principal.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Topeira.h"
#include "Obstaculo.h"
#include "Terra.h"

using namespace Gerenciadores;
using namespace Personagens;

Principal::Principal() : faseAtual(new Fases::Fase1)
{
	executar();
}

Principal::~Principal()
{
	if (faseAtual) {
		delete faseAtual;
		faseAtual = NULL;
	}
}

void Principal::executar()
{
	if (faseAtual) {
		faseAtual->executar();
	}
}