#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"

namespace Entidades
{
	class Projetil : public Entidade
	{
	protected:
		float velX;
		float velY;
		static const float gravidade;
		short int direcao;

	public:
		Projetil(ID id, short int dir, float ix, float iy);
		~Projetil();
		sf::RectangleShape getCorpo();
		virtual void trajetoria();
		virtual void salvar() = 0;
		void salvarDataBuffer();
		void setPos(const sf::Vector2f pos);
		void executar();
		virtual void colisao(Entidade* ent, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) = 0;
		void setVelX(const float vx);
		void setVelY(const float vy);
	};
}