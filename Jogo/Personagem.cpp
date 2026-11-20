#include "Personagem.h"

using namespace Personagens;

const float Personagem::gravidade = 0.9;

Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam):Entidade(pos.x,pos.y), chao(true),
vely(0),velx(0), max_velx(5.0f),max_vely(15.0f), pot_queda(10), dano(dano){

}

Personagem::~Personagem() {

}

void Personagem::salvarDataBuffer() {

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
