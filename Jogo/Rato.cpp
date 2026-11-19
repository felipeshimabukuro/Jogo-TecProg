#include "Rato.h"

using namespace Entidades;
using namespace Personagens;

const int Rato::dist_detec = 360;
const int Rato::dist_atk = 180;

Rato::Rato(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j) :
	Inimigo(pos, tam, j),
	ticks(0),
	max_ticks(60)
{
	boss = false;
	num_vidas = 3;
	lado = 1;                        // Olhando para a direita
	x = pos.x;
	y = pos.y;
	x_alvo = static_cast<int>(x);
	velx = 0.0f;
	vely = 0.0f;
	estado = "IDLE";

	inicializa();
}

Rato::~Rato()
{
}

bool Rato::detectarJogador()
{
	if (jogador == NULL) return false;

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
	return (distancia.x < dist_detec && distancia.y < dist_detec);
}

void Rato::seguir()
{
	atualizaLado();

	if (jogador)
	{
		if (jogador->getX() > x) {
			velx = 2.5f;
		}
		else {
			velx = -2.5f;
		}
	}
}

bool Rato::perto()
{
	if (jogador == NULL) return false;

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
	return (distancia.x < dist_atk && distancia.y < dist_atk);
}

void Rato::atualizaLado()
{
	if (jogador)
	{
		if (jogador->getCorpo().getPosition().x > x)
		{
			lado = 1;
		}
		else
		{
			lado = -1;
		}
	}
}

void Rato::executar()
{
	if (perto())
	{
		estado = "ATAQUE";
	}
	else if (detectarJogador())
	{
		estado = "SEGUIR";
	}
	else
	{
		estado = "IDLE";
	}

	if (estado == "ATAQUE")
	{
		atualizaLado();
		if (jogador) {
			if (jogador->getX() > x) {
				velx = 8.0f; 
			}
			else {
				velx = -8.0f; 
			}
		}
	}
	else if (estado == "SEGUIR")
	{
		seguir(); 
	}
	else
	{
		velx = 0.0f; 
	}

	mover();

	corpo.setPosition(x, y);
}

void Rato::colisao(Entidade* ent, sf::Vector2f ds)
{
	if (!ent || !ent->getAtivo())
		return;

	Jogador* pJog = dynamic_cast<Jogador*>(ent);
	if (pJog)
	{
		sf::FloatRect hitboxRato = corpo.getGlobalBounds();
		sf::FloatRect hitboxJog = pJog->getCorpo().getGlobalBounds();

		if (hitboxRato.intersects(hitboxJog))
		{
			float pesJogador = pJog->getY() + pJog->getTam().y;

			if (ds.x <= ds.y && pesJogador <= y + 15.0f && pJog->getVely() >= 0.0f)
			{
				pJog->setPos(sf::Vector2f(pJog->getX(), y - pJog->getTam().y - 8.0f));
				pJog->setChao(true);
				pJog->pular();
				setAtivo(false); 
			}
			else
			{
				danificar(pJog);
			}
		}
		return;
	}
	Inimigo::colisao(ent, ds);
}

void Rato::danificar(Jogador* p) {
	p->receberDano(5);
	p->setChao(true);
	p->pular();
}

void Rato::desenhar(sf::RenderWindow* window)
{
	window->draw(corpo);
}

void Rato::inicializa() {
	corpo.setFillColor(sf::Color(80, 80, 80));
}