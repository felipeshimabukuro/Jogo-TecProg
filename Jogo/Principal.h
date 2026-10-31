#pragma once
#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Gerenciador_eventos.h"
#include "Gerenciador_colisao.h"
#include "Jogador.h"
#include "ListaEntidade.h"

using namespace Gerenciadores;
using namespace Listas;

class Principal
{
private:
	Gerenciador_grafico* pGG;
	Gerenciador_eventos* pEvento;
	Gerenciador_colisao* pColisao;
	ListaEntidade LEs;

public:
	Principal();
	~Principal();
	void executar();
	void instanciarEntidades();
};