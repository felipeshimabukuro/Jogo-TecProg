#include "Plataforma.h"

using namespace Entidades;

int Plataforma::ticks(0);

Plataforma::Plataforma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel):
	Obstaculo(ID::plataforma, x, y, largura, altura, dano, danoso, quebravel),
	max_ticks(180)
{
	inicializa();
}

Plataforma::~Plataforma() {

}

void Plataforma::executar() {
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Plataforma::salvar() {
	buffer.str("");
	buffer.clear();
	salvarDataBuffer();
}

void Plataforma::obstaculizar(Jogador* p) { // pensar em um obstaculizar melhor
	ticks++;
	if (ticks == max_ticks) {
		ticks = 0;
		p->removerInventario();
	}
}

void Plataforma::inicializa() {
	corpo.setSize(sf::Vector2f(largura, altura));
	setTextura("terra", sf::Vector2f(largura, altura));
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Plataforma::setTicks(const int p)
{ 
	ticks = p;
}