#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"
#include "BarraVida.h"

using namespace Entidades;

namespace Personagens {
	class Personagem: public Entidade, public BarraVida {
	protected:
		float velx;
		float vely;
		const float max_velx;
		const float max_vely;
		const int pot_queda;
		bool chao;
		int dano;
		static const float gravidade;
		sf::Vector2f vel;

	public:
		Personagem(ID id, const sf::Vector2f pos, const sf::Vector2f tam);
		virtual ~Personagem();
		virtual void desenhar(sf::RenderWindow* window);
		void salvarDataBuffer();
		virtual void mover() = 0;
		virtual void salvar() = 0;
		virtual void executar() = 0;
		virtual void receberDano(int dano) = 0;
		const float getVely() const;
		const float getVelx() const;
		int getDano() const;
		void setVel(const sf::Vector2f v);
	};

}