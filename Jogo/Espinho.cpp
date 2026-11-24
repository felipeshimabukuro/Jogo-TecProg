#include "Espinho.h"

using namespace Entidades;

Espinho::Espinho(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel, Jogador* j1, Jogador* j2):
	Obstaculo(ID::espinho, x, y, largura, altura, dano, danoso, quebravel),
	distJogador(0),
	pJogador1(j1),
	pJogador2(j2)
{
	inicializa();
}

Espinho::~Espinho() {

}

void Espinho::executar()
{
	calculaDistancia();

	if (distJogador <= 510)
	{
		sprite.setColor(sf::Color(255, 255, 255, 255 - distJogador/2));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 0));
	}
}

void Espinho::obstaculizar(Jogador* p) { // pensar em um obstaculizar melhor
	p->receberDano(15);
	p->pular();
}

void Espinho::inicializa() {
	corpo.setSize(sf::Vector2f(largura, altura));
	setTextura("espinho", sf::Vector2f(largura, altura));
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
	calculaDistancia();
}

void Espinho::salvarDataBuffer()
{
	Obstaculo::salvarDataBuffer();
}

void Espinho::salvar() {
	buffer.str("");
	buffer.clear();
	salvarDataBuffer();
}

void Espinho::setJogadores(Jogador* j1, Jogador* j2)
{
	pJogador1 = j1;
	pJogador2 = j2;
}

void Espinho::calculaDistancia()
{
	if ((!pJogador1 || !pJogador1->getAtivo()) && (!pJogador2 || !pJogador2->getAtivo())) {
		sprite.setColor(sf::Color(255, 255, 255, 255));
		return;
	}

	float centroEspX = x + largura / 2.0f;
	float centroEspY = y + altura / 2.0f;

	float menorDist = -1.0f;

	if (pJogador1 && pJogador1->getAtivo()) {
		float dx = (pJogador1->getX() + pJogador1->getTam().x / 2.0f) - centroEspX;
		float dy = (pJogador1->getY() + pJogador1->getTam().y / 2.0f) - centroEspY;
		menorDist = std::sqrt(dx * dx + dy * dy);
	}

	if (pJogador2 && pJogador2->getAtivo()) {
		float dx = (pJogador2->getX() + pJogador2->getTam().x / 2.0f) - centroEspX;
		float dy = (pJogador2->getY() + pJogador2->getTam().y / 2.0f) - centroEspY;
		float dist2 = std::sqrt(dx * dx + dy * dy);

		if (menorDist < 0.0f || dist2 < menorDist) {
			menorDist = dist2;
		}
	}

	distJogador = static_cast<int>(menorDist);
}

std::string Espinho::getArquivoSave() const
{
	return "saves/espinhoSave.txt";
}