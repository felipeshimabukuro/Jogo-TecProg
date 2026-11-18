#include "Plataforma.h"

using namespace Entidades;

int Plataforma::ticks(0);

Plataforma::Plataforma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel):Obstaculo(x,y,largura,altura,dano,danoso,quebravel) , max_ticks(60){
	inicializa();
}

Plataforma::~Plataforma() {

}

void Plataforma::executar() {
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Plataforma::salvar() {

}

void Plataforma::obstaculizar(Jogador* p) { // pensar em um obstaculizar melhor
	ticks++;
	if (ticks == max_ticks) {
		ticks = 0;
		p->operator++();
	}
}

void Plataforma::inicializa() {
	corpo.setSize(sf::Vector2f(largura, altura));
	setTextura("terra", sf::Vector2f(largura, altura));
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}