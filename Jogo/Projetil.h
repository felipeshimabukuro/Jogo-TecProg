#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"

namespace Entidades
{
	class Projetil : public Entidade
	{
	protected:
		int velX;
		int velY;
		static const int gravidade;
		short int direcao;
		sf::RectangleShape corpo;

	public:
		Projetil(int vX, int vY, short int direcao);
		~Projetil();
		virtual void trajetoria();
		virtual void salvar();
		void setPos(const sf::Vector2f pos);
		void executar();
	};
}