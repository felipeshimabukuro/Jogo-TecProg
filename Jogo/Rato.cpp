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
	num_vidas = 15;
	lado = 1;                        // Olhando para a direita
	x = pos.x;
	y = pos.y;
	x_alvo = static_cast<int>(x);
	velx = 0.0f;
	vely = 0.0f;
	estado = "IDLE";

	corpo.setSize(tam);
	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
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

		const sf::Texture* tex = sprite.getTexture();
		if (tex) {
			int w = tex->getSize().x;
			int h = tex->getSize().y;
			if (lado == 1) {
				sprite.setTextureRect(sf::IntRect(w, 0, -w, h));
				sprite.setOrigin(0.0f, 0.0f);
			}
			else {
				sprite.setTextureRect(sf::IntRect(0, 0, w, h));
				sprite.setOrigin(0.0f, 0.0f);
			}
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

	velx = 0.0f;

	if (estado == "ATAQUE")
	{
		atualizaLado();
		if (jogador) {
			if (jogador->getX() > x) {
				velx = 1.5f * nivel_maldade; 
			}
			else if(jogador->getX() < x){
				velx = -1.5f * nivel_maldade; 
			}
			else {
				velx = 0.0f;
			}
		}
	}
	else if (estado == "SEGUIR")
	{
		persegueJogador(jogador); 
	}
	else
	{
		movimentoAleatorio();
	}

	mover();

	corpo.setPosition(x, y);
	sprite.setPosition(x, y);
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
	p->receberDano(dano);
	p->setChao(true);
	p->pular();
}

void Rato::inicializa() {
	setTextura("rato", getTam());
}