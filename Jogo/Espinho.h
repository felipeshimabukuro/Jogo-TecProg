#pragma once
#include "Obstaculo.h"

using namespace Personagens;

namespace Entidades {
	class Espinho :public Obstaculo {
	private:
		static int ticks;
		int max_ticks;
	public:
		Espinho(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel);
		~Espinho();
		void executar();
		void salvar();
		void obstaculizar(Jogador* p);
		void inicializa();
	};
}