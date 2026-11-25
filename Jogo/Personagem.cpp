#include "Personagem.h"

using namespace Personagens;

Personagem::Personagem(ID id, const sf::Vector2f pos, const sf::Vector2f tam):
	Entidade(id, pos.x,pos.y), 
	BarraVida(),
	chao(true),
	velx(0), 
	max_velx(5.0f),	
	dano(dano)
{

}

Personagem::~Personagem() {

}

void Personagem::salvarDataBuffer() 
{
	Entidade::salvarDataBuffer();
	buffer << velx << " ";
	buffer << vely << " ";
	buffer << num_vidas << " ";
}

const float Personagem::getVely() const {
	return vely;
}

const float Personagem::getVelx() const {
	return velx;
}

int Personagem::getDano() const {
	return dano;
}

void Personagem::setVel(const sf::Vector2f v) {
	velx = v.x;
	vely = v.y;
}

void Personagem::desenhar(sf::RenderWindow* window)
{
	Ente::desenhar(window);

	if (ativo) 
	{
		desenharBarra(window, x, y, getTam().x);
	}
}