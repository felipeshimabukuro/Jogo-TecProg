#pragma once
#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;

class Principal
{
private:
	Gerenciador_grafico* pGG;

public:
	Principal();
	~Principal();
	void executar();
};