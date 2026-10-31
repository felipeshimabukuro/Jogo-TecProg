#include "Gerenciador_colisao.h"
#include <algorithm>

using namespace Gerenciadores;

Gerenciador_colisao::Gerenciador_colisao(Jogador* pJ, vector<Inimigo*> LIn, list<Obstaculo*> LOb):
	pJog1(pJ),
	LIs(LIn),
	LOs(LOb)
{
}

Gerenciador_colisao::~Gerenciador_colisao()
{
	pJog1 = nullptr;
	LIs.clear();
	LOs.clear();
}

void Gerenciador_colisao::setJogador(Jogador* pJ)
{
	pJog1 = pJ;
}

void Gerenciador_colisao::adicionarInimigo(Inimigo* pIn)
{
	if(pIn)
	{
		LIs.push_back(pIn);
	}
}

void Gerenciador_colisao::removerInimigo(Inimigo* pIn)
{
	if(pIn)
	{
		LIs.erase(std::remove(LIs.begin(), LIs.end(), pIn), LIs.end());
	}
}

void Gerenciador_colisao::adicionarObstaculo(Obstaculo* pOb)
{
	if (pOb)
	{
		LOs.push_back(pOb);
	}
}

void Gerenciador_colisao::removerObstaculo(Obstaculo* pOb)
{
	if (pOb)
	{
		LOs.remove(pOb);
	}
}

const sf::Vector2f Gerenciador_colisao::calcularColisao(Entidade* ent1, Entidade* ent2)
{
	if (!ent1 || !ent2) return sf::Vector2f(0.0f, 0.0f);

	sf::Vector2f pos1 = ent1->getPos();
	sf::Vector2f tam1 = ent1->getTam();
	sf::Vector2f pos2 = ent2->getPos();
	sf::Vector2f tam2 = ent2->getTam();

	sf::Vector2f distanciaPos
		(
			fabs((pos1.x + tam1.x / 2.0f) - (pos2.x + tam2.x / 2.0f)),
			fabs((pos1.y + tam1.y / 2.0f) - (pos2.y + tam2.y / 2.0f))
		);

	sf::Vector2f SomaMetade
	(
		(tam1.x / 2.0f) + (tam2.x / 2.0f),
		(tam1.y / 2.0f) + (tam2.y / 2.0f)
	);

	return sf::Vector2f(distanciaPos.x - SomaMetade.x, distanciaPos.y - SomaMetade.y);
}

void Gerenciador_colisao::executar()
{
	// JOGADOR
	if (pJog1)
	{
		for (auto* inim : LIs) // inimigos
		{
			if (inim)
			{
				sf::Vector2f ds = calcularColisao(pJog1, inim);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					pJog1->colisao(inim, ds);
				}
			}
		}
		
		for (auto* obs : LOs) // obstaculos
		{
			if (obs)
			{
				sf::Vector2f ds = calcularColisao(pJog1, obs);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					pJog1->colisao(obs, ds);
				}
			}
		}
	}

	// INIMIGOS
	for (auto* inim : LIs)
	{
		if (inim)
		{
			for (auto* obs : LOs)
			{
				if (obs)
				{
					sf::Vector2f ds = calcularColisao(inim, obs);
					if (ds.x < 0.0f && ds.y < 0.0f)
					{
						inim->colisao(obs, ds);
					}
				}
			}
		}
	}
}
