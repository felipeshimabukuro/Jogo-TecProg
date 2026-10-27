#pragma once
#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Jogador.h"

using namespace Gerenciadores;

class Principal
{
private:
	Gerenciador_grafico* pGG;
	Jogador jogador;
public:
	Principal();
	~Principal();
	void executar();
};