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

void Gerenciador_colisao::adicionarInimigo(Inimigo* pi)
{
	if(pi)
	{
		LIs.push_back(pi);
	}
}

void Gerenciador_colisao::removerInimigo(Inimigo* pi)
{
	if(pi)
	{
		LIs.erase(std::remove(LIs.begin(), LIs.end(), pi), LIs.end());
	}
}

void Gerenciador_colisao::adicionarObstaculo(Obstaculo* po)
{
	if (po)
	{
		LOs.push_back(po);
	}
}

void Gerenciador_colisao::removerObstaculo(Obstaculo* po)
{
	if (po)
	{
		LOs.remove(po);
	}
}

void Gerenciador_colisao::adicionarProjetil(Projetil* pj) {
	if (pj)
	{
		LPs.insert(pj);

	}
}

void Gerenciador_colisao::removerProjetil(Projetil* pj) {
	if (pj)
	{
		LPs.erase(pj);
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

//const bool verificaColisao(Entidade* pe1, Entidade* pe2) const;

void Gerenciador_colisao::executar()
{
	// os fors com auto percorrem a estrutura inteira (acho que ja expliquei isso mas n lembro onde kk)

	// JOGADOR
	if (pJog1)
	{
		for (auto* inim : LIs) // Inimigos
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
		
		for (auto* obs : LOs) // Obstaculos
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
			for (auto* obs : LOs) // Obstaculos
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

	// PROJETEIS
	for (auto proj : LPs)
	{
		if (proj)
		{
			// Jogador
			if (pJog1)
			{
				sf::Vector2f ds = calcularColisao(proj, pJog1);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					proj->colisao(pJog1, ds);
				}
			}

			// Obstaculos
			for (auto obs : LOs)
			{
				if (obs)
				{
					sf::Vector2f ds = calcularColisao(proj, obs);
					if (ds.x < 0.0f && ds.y < 0.0f)
					{
						proj->colisao(obs, ds);
					}
				}
			}
		}
	}

}
