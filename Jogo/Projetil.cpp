#include "Projetil.h"

using namespace Entidades;

const float Projetil::gravidade = 0.3;

Projetil::Projetil(ID id, short int dir, float ix, float iy):
	Entidade(id, ix, iy),
	direcao(dir)
{
	velY = -10;
	velX = 2.5 * direcao;
	corpo = sf::RectangleShape(sf::Vector2f(GRID/2, GRID/2));
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

Projetil::~Projetil()
{
}

void Projetil::trajetoria()
{
	velY += gravidade;
	x += velX;
	y += velY;

	sf::Vector2f ds(x, y);
	setPos(ds);
}

void Projetil::setPos(const sf::Vector2f pos) {
	x = pos.x;
	y = pos.y;
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Projetil::executar()
{
	trajetoria();
}

void Projetil::salvarDataBuffer()
{
	Entidade::salvarDataBuffer();
	buffer << velX << " ";
	buffer << velY << " ";
	buffer << direcao << " ";
}