#include "Personagem.h"

using namespace Personagens;

Personagem::Personagem(int xx, int yy):Entidade(xx,yy), chao(true),
vely(0),velx(0), pot_queda(10), max_velx(400),max_vely(400){

}

Personagem::~Personagem() {

}

void salvarDataBuffer();