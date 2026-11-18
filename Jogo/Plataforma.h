#pragma once
#include "Obstaculo.h"

using namespace Personagens;

namespace Entidades {
	class Plataforma :public Obstaculo {
	private:
		static int ticks;
		int max_ticks;
	public:
		Plataforma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel);
		~Plataforma();
		void executar();
		void salvar();
		void obstaculizar(Jogador* p);
		void inicializa();
	};
}