#pragma once

#include "Ente.h"
#include "Gerenciador_colisao.h"
#include "ListaEntidade.h"
#include "Gerenciador_eventos.h"

namespace Fases {
	class Fase : public Ente {
	protected:
		ListaEntidade list_ents;
		Gerenciadores::Gerenciador_colisao* pGC;
		Gerenciadores::Gerenciador_eventos* pEv;
		Gerenciadores::Gerenciador_grafico* pGG;
		Jogador* pJogador1;

		void criarTopeiras();
		virtual void criarCenario() = 0;
		virtual void criarObstaculos() = 0;
		virtual void criarInimigos() = 0;
	public:
		Fase();
		virtual ~Fase();

		virtual void executar() = 0;
	};
}
