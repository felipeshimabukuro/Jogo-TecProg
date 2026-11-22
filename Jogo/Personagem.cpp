#include "Personagem.h"

using namespace Personagens;

const float Personagem::gravidade = 0.9;

Personagem::Personagem(ID id, const sf::Vector2f pos, const sf::Vector2f tam):
	Entidade(id, pos.x,pos.y), 
	chao(true),
	vely(0),
	velx(0), 
	max_velx(5.0f),
	max_vely(15.0f), 
	pot_queda(10), 
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

void Personagem::setNumVidas(const int vidas) {
	num_vidas = vidas;
}