#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"
namespace Personagens {
	class Personagem: public Entidades::Entidade {
	protected:
		int num_vidas;
		float velx;
		float vely;
		const float max_velx;
		const float max_vely;
		const float pot_queda;
		bool chao;
		static const int gravidade = 10;
	public:
		Personagem(int xx = 0, int yy = 0);
		~Personagem();
		void salvarDataBuffer();
		virtual void executar() = 0;
		virtual void salvar() = 0;
		virtual void mover(int lado) = 0;
		virtual void receberDano(int dano) = 0;
	};
	
}