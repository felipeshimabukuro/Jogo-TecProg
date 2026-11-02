#include "Gerenciador_colisao.h"
#include <algorithm>

using namespace Gerenciadores;

Gerenciador_colisao* Gerenciador_colisao::pColisao = NULL;

Gerenciador_colisao::Gerenciador_colisao():
	LIs(),
	LOs(),
	LPs(),
	pJog1(NULL),
	LE(NULL)
{
}

Gerenciador_colisao::~Gerenciador_colisao()
{
	pJog1 = nullptr;
	LIs.clear();
	LOs.clear();
	pColisao = NULL;
}

Gerenciador_colisao* Gerenciador_colisao::getGerenciadorColisao()
{
	if (!pColisao)
	{
		pColisao = new Gerenciador_colisao();
	}
	return pColisao;
}

void Gerenciador_colisao::setListaEntidade(ListaEntidade* pLE)
{
	if (pLE)
	{
		LE = pLE;
	}
}

void Gerenciador_colisao::setJogador(Jogador* pJ)
{
	if(pJ)
	{
		pJog1 = pJ;
		Entidade* pE = static_cast<Entidade*>(pJ);
		LE->incluir(pE);
	}
}

void Gerenciador_colisao::adicionarInimigo(Inimigo* pi)
{
	if(pi)
	{
		Entidade* pE = static_cast<Entidade*>(pi);
		LIs.push_back(pi);
		LE->incluir(pE);
	}
}

void Gerenciador_colisao::removerInimigo(Inimigo* pi)
{
	if(pi)
	{
		Entidade* pE = static_cast<Entidade*>(pi);
		LIs.erase(std::remove(LIs.begin(), LIs.end(), pi), LIs.end());
		LE->remover(pE);
	}
}

void Gerenciador_colisao::adicionarObstaculo(Obstaculo* po)
{
	if (po)
	{
		Entidade* pE = static_cast<Entidade*>(po);
		LOs.push_back(po);
		LE->incluir(pE);
	}
}

void Gerenciador_colisao::removerObstaculo(Obstaculo* po)
{
	if (po)
	{
		Entidade* pE = static_cast<Entidade*>(po);
		LOs.remove(po);
		LE->remover(pE);
	}
}

void Gerenciador_colisao::adicionarProjetil(Projetil* pj) {
	if (pj)
	{
		Entidade* pE = static_cast<Entidade*>(pj);
		LPs.insert(pj);
		LE->incluir(pE);
	}
}

void Gerenciador_colisao::removerProjetil(Projetil* pj) {
	if (pj)
	{
		Entidade* pE = static_cast<Entidade*>(pj);
		LPs.erase(pj);
		LE->remover(pE);
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

void Gerenciador_colisao::tratarColisaoJogadorInimigo()
{
	if (pJog1)
	{
		for (auto* inim : LIs)
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
	}
}
void Gerenciador_colisao::tratarColisaoJogadorObstaculo()
{
	if (pJog1)
	{
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
}

void Gerenciador_colisao::tratarColisaoJogadorProjetil()
{
	std::vector<Projetil*> projeteisParaRemover;

	if (pJog1)
	{
		for (auto proj : LPs)
		{
			if (proj)
			{
				sf::Vector2f ds = calcularColisao(proj, pJog1);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					proj->colisao(pJog1, ds);
					projeteisParaRemover.push_back(proj);
					continue;
				}
			}
		}
	}
	for (auto proj : projeteisParaRemover)
	{
		removerProjetil(proj);
	}
}
void Gerenciador_colisao::tratarColisaoInimigoObstaculo()
{
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

void Gerenciador_colisao::tratarColisaoProjetilObstaculo()
{
	std::vector<Projetil*> projeteisParaRemover;

	for (auto proj : LPs)
	{
		for (auto obs : LOs)
		{
			if (obs)
			{
				sf::Vector2f ds = calcularColisao(proj, obs);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					proj->colisao(obs, ds);
					projeteisParaRemover.push_back(proj);
					break;
				}
			}
		}
	}
	for (auto proj : projeteisParaRemover)
	{
		removerProjetil(proj);
	}
}

bool Gerenciadores::Gerenciador_colisao::posicaoLivre(sf::Vector2f pos, sf::Vector2f tam) {
	sf::FloatRect rectNovo(pos.x, pos.y, tam.x, tam.y);

	std::list<Entidades::Obstaculo*>::const_iterator itObs;
	for (itObs = LOs.begin(); itObs != LOs.end(); ++itObs) {
		Entidades::Obstaculo* obs = *itObs;
		if (obs) {
			sf::FloatRect rectObs(obs->getX(), obs->getY(), obs->getTam().x, obs->getTam().y);
			if (rectNovo.intersects(rectObs)) {
				return false;
			}
		}
	}

	std::vector<Personagens::Inimigo*>::const_iterator itIni;
	for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni) {
		Personagens::Inimigo* ini = *itIni;
		if (ini) {
			sf::FloatRect rectIni(ini->getX(), ini->getY(), ini->getTam().x, ini->getTam().y);
			if (rectNovo.intersects(rectIni)) {
				return false;
			}
		}
	}

	if (pJog1) {
		sf::FloatRect rectJog(pJog1->getX(), pJog1->getY(), pJog1->getTam().x, pJog1->getTam().y);
		if (rectNovo.intersects(rectJog)) {
			return false;
		}
	}

	return true;
}

//const bool verificaColisao(Entidade* pe1, Entidade* pe2) const;

void Gerenciador_colisao::executar()
{
	tratarColisaoJogadorInimigo();
	tratarColisaoJogadorObstaculo();
	tratarColisaoJogadorProjetil();
	tratarColisaoInimigoObstaculo();
	tratarColisaoProjetilObstaculo();
}
