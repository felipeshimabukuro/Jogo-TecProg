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
		sf::RectangleShape corpo;

	public:
		Projetil(short int dir, float ix, float iy);
		~Projetil();
		sf::RectangleShape getCorpo();
		virtual void trajetoria();
		void salvar();
		void setPos(const sf::Vector2f pos);
		void executar();
		virtual void colisao(Entidade* ent, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) = 0;
	};
}