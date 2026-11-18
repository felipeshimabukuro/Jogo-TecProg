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

#include "Fase1.h"

class Principal
{
private:
	Fases::Fase* faseAtual;
public:
	Principal();
	~Principal();
	void executar();
};