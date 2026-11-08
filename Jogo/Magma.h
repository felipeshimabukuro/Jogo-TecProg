#pragma once
#include "Obstaculo.h"

using namespace Personagens;

namespace Entidades {
	class Magma :public Obstaculo {
	private:
		int ticks;
		int max_ticks;
		int dano;
	public:
		Magma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel);
		~Magma();

		void obstaculizar(Jogador* p);
		void colisao(Entidade* ent, sf::Vector2f ds);
		void executar();
		void inicializa();
		void salvar();
	};
}