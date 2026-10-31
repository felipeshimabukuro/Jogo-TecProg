#include "Personagem.h"

using namespace Personagens;

Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam):Entidade(pos.x,pos.y), chao(true),
vely(0),velx(0), pot_queda(10), max_velx(5.0f),max_vely(5.0f){

}

Personagem::~Personagem() {

}

void Personagem::salvarDataBuffer() {

}
