#include "Topeira.h"
#include "Proj_top.h"
#define MINUTOS *60

using namespace Entidades;
using namespace Personagens;

const int Topeira::dist_atk = 180;
const int Topeira::tempo_tiro = 5 MINUTOS;

Topeira::Topeira(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j) :
	Inimigo(pos, tam, j),
	cavando(false),
	tiro_cd(0),
	ticks(0),
	max_ticks(60)
{
	dist_detec = 350;
	boss = false;
	num_vidas = 5;
	lado = 1;                        // Olhando para a direita
	x = pos.x;
	y = pos.y;
	x_alvo = static_cast<int>(x);
	velx = 0.0f;
	vely = 0.0f;
	estado = "IDLE";

	setTextura("topeira", getTam());
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

void Topeira::seguir()
{
	if (!cavando) { cavar(); }

	if (jogador)
	{
		persegueJogador(jogador);
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
		estado = "LIVRE";
	}

	if (estado == "ATAQUE")
	{
		atirar();
	}

	else if (estado == "SEGUIR")
	{
		seguir();
	}

	else if (estado == "LIVRE")
	{
		movimentoAleatorio();
	}

    mover(); 

	sf::Vector2f pos(x, y);
	setPos(pos);

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
		}
		return;
	}
	Inimigo::colisao(ent, ds);
	
}

void Topeira::danificar(Jogador* p) {
	ticks++;
	if (ticks == max_ticks) {
		p->receberDano(dano);
		ticks = 0;
	}
}