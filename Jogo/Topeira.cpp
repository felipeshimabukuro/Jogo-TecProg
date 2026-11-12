#include "Topeira.h"
#include "Proj_top.h"
#define MINUTOS *60

using namespace Entidades;
using namespace Personagens;

const int Topeira::dist_detec = 360;
const int Topeira::dist_atk = 180;
const int Topeira::tempo_tiro = 5 MINUTOS;

Topeira::Topeira(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j) :
	Inimigo(pos, tam, j),
	cavando(false),
	tiro_cd(0)
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
}

Topeira::~Topeira()
{
}

void Topeira::cavar()
{
	cavando = !cavando;
}

void Topeira::atirar()
{
	if (cavando) { cavar(); }

	atualizaLado();

	if (tiro_cd <= 0)
	{
		if (!cavando)
		{
			Projetil* novoProjetil = new Proj_top(lado, x + GRID / 2, y + GRID / 2);
			projeteisPendentes.push_back(novoProjetil);
		}
		tiro_cd = tempo_tiro;
	}
}

bool Topeira::detectarJogador()
{
	if (jogador == NULL) return false;

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
	return (distancia.x < dist_detec && distancia.y < dist_detec);
}

void Topeira::seguir()
{
	atualizaLado();

	if (!cavando) { cavar(); }

	if (jogador)
	{
		persegueJogador(jogador->getCorpo().getPosition(), corpo.getPosition(), jogador);
	}
}

bool Topeira::perto()
{
	if(jogador == NULL) return false;

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
	return (distancia.x < dist_atk && distancia.y < dist_atk);
}

void Topeira::atualizaLado()
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

void Topeira::executar()
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
		atirar();
	}

	else if (estado == "SEGUIR")
	{
		seguir();
	}

    mover(); 

    if (tiro_cd > 0)
    {
        tiro_cd--;
    }
}

void Topeira::colisao(Entidade* ent, sf::Vector2f ds)
{
	if (!ent || !ent->getAtivo())
		return;

	Jogador* pJog = dynamic_cast<Jogador*>(ent);
	if (pJog)
	{
		float pesJogador = pJog->getY() + pJog->getTam().y;

		if (ds.x <= ds.y && pesJogador <= y + 15.0f && pJog->getVely() >= 0.0f)
		{
			pJog->setPos(sf::Vector2f(pJog->getX(), y - pJog->getTam().y - 8.0f));
			pJog->setChao(true);
			pJog->pular();
			setAtivo(false);
		}
		return;
	}
	Inimigo::colisao(ent, ds);
	
}