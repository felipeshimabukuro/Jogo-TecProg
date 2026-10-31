#include "Inimigo.h"
#include "Jogador.h"

using namespace Personagens;

Inimigo::Inimigo(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j):
Personagem(pos,tam),relogio(),jogador(j){
	inicializa();
	srand(time(NULL));
	//moveAleatorio = rand() % 1;
}

Inimigo::~Inimigo() {

}

void Inimigo::inicializa() {
	vel = sf::Vector2f(max_velx/5.0f, max_vely/5.0f);

	corpo.setSize(sf::Vector2f(50.0f, 50.0f));
	corpo.setFillColor(sf::Color::Red);

	x = x + 500.0f;
	corpo.setPosition(x, y);
}

void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo, Jogador* j) {
	if (!j) return;

	float tamJogadorX = j->getTam().x;
	float tamInimigoX = corpo.getSize().x;
	float deltaX = 0.0f;

	if (posJogador.x > posInimigo.x) {
		// Inimigo à esquerda do jogador: persegue para a direita (+X)
		float gap = posJogador.x - (posInimigo.x + tamInimigoX);
		if (gap > 0.0f) {
			deltaX = (gap < vel.x) ? gap : vel.x;
			x += deltaX;
		}
	}
	else {
		// Inimigo à direita do jogador: persegue para a esquerda (-X)
		float gap = posInimigo.x - (posJogador.x + tamJogadorX);
		if (gap > 0.0f) {
			deltaX = (gap < vel.x) ? gap : vel.x;
			x -= deltaX;
		}
	}
}

void Inimigo::mover() {
	vely += gravidade;
	y += vely;
	if (!jogador) return;
	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f tamJogador = jogador->getTam();
	sf::Vector2f tamInimigo = getTam();

	float distCentroX = fabs((posJogador.x + tamJogador.x / 2.0f) - (posInimigo.x + tamInimigo.x / 2.0f));
	float distCentroY = fabs((posJogador.y + tamJogador.y / 2.0f) - (posInimigo.y + tamInimigo.y / 2.0f));
	float minDistX = (tamJogador.x + tamInimigo.x) / 2.0f;
	float minDistY = (tamJogador.y + tamInimigo.y) / 2.0f;

	// Se estiver colidindo com o jogador, o inimigo fica parado e nao empurra
	if (distCentroX <= minDistX && distCentroY < minDistY) {
		return;
	}

	if (distCentroX <= 200.0f && distCentroY <= 200.0f) {
		persegueJogador(posJogador, posInimigo, jogador);
	}

	corpo.setPosition(x, y);
}

void Inimigo::salvar() {

}

void Inimigo::receberDano(int dano) {
	num_vidas -= dano;
}

sf::RectangleShape Inimigo::getCorpo() {
	return corpo;
}

void Inimigo::setPos(const sf::Vector2f pos) {
	x = pos.x;
	y = pos.y;
	corpo.setPosition(x, y);
}

void Inimigo::executar() {
	mover();
}

void Inimigo::colisao(Entidade* ent, sf::Vector2f ds) {
	
	Entidades::Entidade::colisao(ent, ds);

	
	if (ds.x <= ds.y) {
		vely = 0.0f; 
		if (getY() < ent->getY()) {
			chao = true;
		}
	}
}
