#include "Terra.h"

using namespace Entidades;

int Terra::ticks(0);

Terra::Terra(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel):Obstaculo(x,y,largura,altura,dano,danoso,quebravel) , max_ticks(60){
	inicializa();
}

Terra::~Terra() {

}

void Terra::executar() {
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Terra::salvar() {

}

void Terra::obstaculizar(Jogador* p) {
	ticks++;
	if (ticks == max_ticks) {
		ticks = 0;
		p->operator++();
	}
}

void Terra::inicializa() {
	corpo.setSize(sf::Vector2f(largura, altura));
	setTextura("terra", sf::Vector2f(largura, altura));
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}