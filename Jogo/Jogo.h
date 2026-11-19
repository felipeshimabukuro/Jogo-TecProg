#pragma once
/*#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Gerenciador_eventos.h" 
#include "Gerenciador_colisao.h"
#include "Jogador.h"
#include "ListaEntidade.h"

using namespace Gerenciadores;
using namespace Listas;
*/

#include "limbo_da_perdicao.h"
#include "Caverna_Maldosa.h"

class Jogo
{
private:
	Fases::Fase* faseAtual;

public:
	Jogo();
	~Jogo();
	void executar();
};