#include "Topeira.h"
#include "Proj_top.h"
#include "Gerenciador_colisao.h"
#define MINUTOS *60

using namespace Gerenciadores;
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
	if(!cavando)
	{
		Projetil* novoProjetil = new Proj_top(lado, x + getTam().x / 2, y + getTam().y / 2);
		Gerenciador_colisao* pGC = Gerenciador_colisao::getGerenciadorColisao();
		pGC->adicionarProjetil(novoProjetil);
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

bool Topeira::perto()
{
	if(jogador == NULL) return false;

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
	return (distancia.x < dist_atk && distancia.y < dist_atk);
}

void Topeira::executar()
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

    if (perto())
    {
        if (cavando) { cavar(); }

        if (tiro_cd <= 0) 
        {
            atirar();
            tiro_cd = tempo_tiro;
        }
    }
    else if (detectarJogador())
    {
        if (!cavando) { cavar(); }

        if (jogador) 
        {
            persegueJogador(jogador->getCorpo().getPosition(), corpo.getPosition(), jogador);
        }
    }
    mover(); 

    if (tiro_cd > 0)
    {
        tiro_cd--;
    }
}
