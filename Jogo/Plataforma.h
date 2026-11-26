#pragma once
#include "Obstaculo.h"


namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Obstaculos {
			using namespace Personagens;
			class Plataforma :public Obstaculo {
			private:
				static int ticks;
				const int max_ticks;
				void inicializa();
			public:
				Plataforma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel);
				~Plataforma();
				void executar();
				void salvar();
				void salvarDataBuffer();
				void obstaculizar(Jogador* p);
				static void setTicks(const int t);
				string getArquivoSave() const;
			};
		}
	}
}