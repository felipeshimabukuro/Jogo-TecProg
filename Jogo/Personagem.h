#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"

using namespace Entidades;

namespace Personagens {
	class Personagem : public Entidade {
	protected:
		float velx;
		const float max_velx;
		bool chao;
		int dano;
		sf::Vector2f vel;

		int num_vidas;
		int max_vidas;
		sf::RectangleShape barraFundo;
		sf::RectangleShape barraVida;

		void inicializarVida(const int vidasMax);
		void desenharBarra(sf::RenderWindow* window, const float x, const float y, const float largura);

	public:
		Personagem(ID id, const sf::Vector2f pos, const sf::Vector2f tam);
		Personagem(const sf::Vector2f pos, const sf::Vector2f tam);
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

		void setNumVidas(const int vidas);
		const int getNumVidas() const;
		const int getMaxVidas() const;
	};
}