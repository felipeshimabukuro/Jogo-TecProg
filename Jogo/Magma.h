#pragma once
#include "Obstaculo.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Obstaculos {
			using namespace Personagens;
			class Magma :public Obstaculo {
			private:
				static int ticks;
				const int max_ticks;
				int dano;

			public:
				Magma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel);
				~Magma();

				void obstaculizar(Jogador* p);
				void executar();
				void inicializa();
				void salvar();
				void salvarDataBuffer();
				static void setTicks(const int t);
				string getArquivoSave() const;
			};
		}
	}
}