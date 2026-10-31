#include "Projetil.h"

using namespace Entidades;

const int Projetil::gravidade = 0.3;

Projetil::Projetil(int vX, int vY, short int dir):
	velX(vX),
	velY(vY),
	direcao(dir)
{
}

Projetil::~Projetil()
{
}

void Projetil::trajetoria()
{
	if (velX == 0 && direcao != 0)
	{
		velX *= direcao;
		//image_xscale = direcao;     //quando tiver imagem
	}

	velY += gravidade;
	x += velX;
	y += velY;

	sf::Vector2f ds(x, y);
	setPos(ds);
}

void Projetil::salvar()
{
}

void Projetil::setPos(const sf::Vector2f pos) {
	x = pos.x;
	y = pos.y;
	corpo.setPosition(x, y);
}

void Projetil::executar()
{
	trajetoria();
}