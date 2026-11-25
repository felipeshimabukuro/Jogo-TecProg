#include "Projetil.h"

using namespace Entidades;

Projetil::Projetil(short int dir, float ix, float iy) :
	Entidade(ix, iy),
	direcao(dir)
{
	vely = -16.0f;     
	velX = 5.0f * direcao;
	corpo = sf::RectangleShape(sf::Vector2f(GRID / 2, GRID / 2));
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

Projetil::~Projetil()
{
}

void Projetil::trajetoria()
{
	aplicarGravidade();
	x += velX;

	sf::Vector2f ds(x, y);
	setPos(ds);
}

void Projetil::executar()
{
	trajetoria();
}

void Projetil::salvarDataBuffer()
{
	Entidade::salvarDataBuffer();
	buffer << velX << " ";
	buffer << vely << " ";
	buffer << direcao << " ";
}

void Projetil::setVelX(const float vx) {
	velX = vx;
}

void Projetil::setVelY(const float vy) {
	vely = vy;
}