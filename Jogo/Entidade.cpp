#include "Entidade.h"
#include "Bibliotecas.h"

using namespace Entidades;

Entidade::Entidade(ID id, float xx, float yy): Ente(id),  x(xx), y(yy), ativo(true)
{
}

Entidade::~Entidade()
{
}

void Entidade::salvarDataBuffer()
{
	buffer << static_cast<int>(id) << " ";
	buffer << x << " ";
	buffer << y << " ";
	buffer << ativo << " ";
}

const float Entidade::getX() const {
	return x;
}

const float Entidade::getY() const {
	return y;
}

const sf::Vector2f Entidade::getPos() const {
	return sf::Vector2f(x, y);
}

void Entidade::setPos(const sf::Vector2f pos) {
	x = pos.x;
	y = pos.y;

	if (x < 0.0f) {
		x = 0.0f;
	}
	else if (x > WIDTH - corpo.getSize().x) {
		x = WIDTH - corpo.getSize().x;
	}

	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

const sf::Vector2f Entidade::getTam() {
	return getCorpo().getSize();
}

const sf::RectangleShape Entidade::getCorpo() const
{
	return corpo;
}

void Entidade::colisao(Entidade* ent, sf::Vector2f ds) 
{
	if (!ent) return;

	sf::Vector2f pos1 = getPos();
	sf::Vector2f tam1 = getTam();
	sf::Vector2f pos2 = ent->getPos();
	sf::Vector2f tam2 = ent->getTam();

	float centro1X = pos1.x + tam1.x / 2.0f;
	float centro1Y = pos1.y + tam1.y / 2.0f;
	float centro2X = pos2.x + tam2.x / 2.0f;
	float centro2Y = pos2.y + tam2.y / 2.0f;

	float dx = centro1X - centro2X;
	float dy = centro1Y - centro2Y;

	if (ds.x == 0.0f && ds.y == 0.0f)
	{
		ds.x = fabs(dx) - (tam1.x / 2.0f + tam2.x / 2.0f);
		ds.y = fabs(dy) - (tam1.y / 2.0f + tam2.y / 2.0f);
	}

	if (ds.x < 0.0f && ds.y < 0.0f)
	{
		if (ds.x > ds.y) // Eixo X tem menor penetração -> colisão horizontal
		{
			if (dx > 0.0f)
			{
				pos1.x -= ds.x; // ent1 está à direita de ent2, empurra para a direita
			}
			else
			{
				pos1.x += ds.x; // ent1 está à esquerda de ent2, empurra para a esquerda
			}
		}
		else // Eixo Y tem menor penetração -> colisão vertical
		{
			if (dy > 0.0f)
			{
				pos1.y -= ds.y; // ent1 está abaixo de ent2, empurra para baixo
			}
			else
			{
				pos1.y += ds.y; // ent1 está acima de ent2, empurra para cima
			}
		}
		setPos(pos1);
	}
}

void Entidade::setAtivo(bool a) {
	ativo = a;
}

const bool Entidade::getAtivo() const {
	return ativo;
}

const string Entidade::getBuffer() const
{
	return buffer.str();
}