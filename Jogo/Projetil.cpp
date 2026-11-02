#include "Projetil.h"

using namespace Entidades;

const float Projetil::gravidade = 0.3;

Projetil::Projetil(short int dir, float ix, float iy):
	direcao(dir)
{
	velY = -10;
	velX = 2.5 * direcao;
	x = ix;
	y = iy;
	corpo = sf::RectangleShape(sf::Vector2f(20.0f, 20.0f));
	corpo.setFillColor(sf::Color::Magenta);
	corpo.setPosition(x, y);
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