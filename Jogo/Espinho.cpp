#include "Espinho.h"

using namespace Entidades;

Espinho::Espinho(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel) :Obstaculo(x, y, largura, altura, dano, danoso, quebravel), max_ticks(60) {
	inicializa();
}

Espinho::~Espinho() {

}

void Espinho::executar() {
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Espinho::salvar() {

}

void Espinho::obstaculizar(Jogador* p) { // pensar em um obstaculizar melhor
	p->receberDano(15);
	p->pular();
}

void Espinho::inicializa() {
	corpo.setSize(sf::Vector2f(largura, altura));
	corpo.setPosition(x, y);
	corpo.setFillColor(sf::Color(128, 128, 128));
}

void Espinho::desenhar(sf::RenderWindow* window)
{
	window->draw(corpo);
}