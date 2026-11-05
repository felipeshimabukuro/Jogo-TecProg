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
		static const float gravidade;
		sf::Vector2f vel;
	public:
		Personagem(const sf::Vector2f pos, const sf::Vector2f tam);
		~Personagem();
		void salvarDataBuffer();
		//virtual void mover() = 0;
		virtual void salvar() = 0;
		//virtual void mover(int lado) = 0;
		virtual void receberDano(int dano) = 0;
		const float getVely() const;
	};

}