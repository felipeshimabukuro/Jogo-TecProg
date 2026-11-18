#pragma once
#include "Obstaculo.h"

using namespace Personagens;

namespace Entidades {
	class Terra :public Obstaculo {
	private:

	public:
		Terra(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel);
		~Terra();
		void executar();
		void salvar();
		void obstaculizar(Jogador* p);
		void inicializa();
	};
}