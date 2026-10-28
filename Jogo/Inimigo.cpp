#include "Inimigo.h"
#include "Jogador.h"

Inimigo::Inimigo(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j):
Personagem(pos,tam),relogio(),jogador(j){
	inicializa();
	srand(time(NULL));
	moveAleatorio = rand() % 1;
}

Inimigo::~Inimigo() {

}

void Inimigo::inicializa() {
	vel = sf::Vector2f(max_velx/5.0, max_vely/5.0);

	corpo.setSize(sf::Vector2f(50.0f, 50.0f));
	corpo.setFillColor(sf::Color::Red);

	corpo.setPosition(x + 100.0f, y);
}

void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo, Jogador* j) {
	if (posJogador.x - posInimigo.x > 0.0f) {
		corpo.move(vel.x, 0.0f);
	}
	else {
		corpo.move(-vel.x, 0.0f);
	}

	/*if (posJogador.y - posInimigo.y > 0.0f) {
		corpo.move(0.0f, vel.y);
	}
	else {
		corpo.move(0.0f, -vel.y);
	}*/
}

void Inimigo::mover() {
	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();

	if (fabs(posJogador.x - posInimigo.x) <= 200.0f && fabs(posJogador.y - posInimigo.y) <= 200.0f) {
		persegueJogador(posJogador,posInimigo,jogador);
	}
}

void Inimigo::salvar() {

}

void Inimigo::receberDano(int dano) {
	num_vidas -= dano;
}
sf::RectangleShape Inimigo::getCorpo() {
	return corpo;
}

void Inimigo::executar() {
	mover();
}