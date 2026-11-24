#pragma once
#include "Obstaculo.h"

using namespace Personagens;

namespace Entidades {
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
		void obstaculizar(Jogador* p);
		static void setTicks(const int t);
		string getArquivoSave() const;
	};
}