#pragma once
#include "Obstaculo.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Obstaculos {
			using namespace Personagens;
			class Espinho :public Obstaculo {
			private:
				int distJogador;
				Jogador* pJogador1;
				Jogador* pJogador2;
				void inicializa();

			public:
				Espinho(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel, Jogador* j1 = NULL, Jogador* j2 = NULL);
				~Espinho();
				void executar();
				void salvar();
				void salvarDataBuffer();
				void obstaculizar(Jogador* p);
				void calculaDistancia();
				void setJogadores(Jogador* j1, Jogador* j2 = NULL);
				string getArquivoSave() const;
			};
		}
	}
}