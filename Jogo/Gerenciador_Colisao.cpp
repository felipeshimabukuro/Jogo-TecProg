#include "Gerenciador_colisao.h"
#include "Ratao.h"
#include "Topeira.h"


using namespace Gerenciadores;

Gerenciador_colisao* Gerenciador_colisao::pColisao = NULL;

Gerenciador_colisao::Gerenciador_colisao():
	LIs(),
	LOs(),
	LPs(),
	pJog1(NULL),
	pJog2(NULL),
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

void Gerenciador_colisao::setJogador1(Jogador* pJ1)
{
	if (pJ1)
	{
		pJog1 = pJ1;
		Entidade* pE = static_cast<Entidade*>(pJ1);
		LE->incluir(pE);
	}
}

void Gerenciador_colisao::setJogador2(Jogador* pJ2)
{
	if (pJ2)
	{
		pJog2 = pJ2;
		Entidade* pE = static_cast<Entidade*>(pJ2);
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
	return calcularColisao(ent1->getPos(), ent1->getTam(), ent2->getPos(), ent2->getTam());
}

const sf::Vector2f Gerenciador_colisao::calcularColisao(const sf::Vector2f pos1, const sf::Vector2f tam1, const sf::Vector2f pos2, const sf::Vector2f tam2)
{
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
	if (pJog1 && pJog1->getAtivo())
	{
		for (auto* inim : LIs)
		{
			if (inim && inim->getAtivo())
			{
				sf::Vector2f ds = calcularColisao(pJog1, inim);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					pJog1->colisao(inim, ds);
					inim->colisao(pJog1, ds);
				}

				if(inim->getBoss())
				{
					Ratao* boss = static_cast<Ratao*>(inim);
					if (boss && boss->getBatendo())
					{
						sf::FloatRect areaHit = boss->getHitboxBatida();
						sf::Vector2f posHit(areaHit.left, areaHit.top);
						sf::Vector2f tamHit(areaHit.width, areaHit.height);

						sf::Vector2f dsHit = calcularColisao(pJog1->getPos(), pJog1->getTam(), posHit, tamHit);
						if (dsHit.x < 0.0f && dsHit.y < 0.0f)
						{
							pJog1->receberDano(boss->getForca());
						}
					}
				}
			}
		}
	}
	if (pJog2 && pJog2->getAtivo())
	{
		for (auto* inim : LIs)
		{
			if (inim && inim->getAtivo())
			{
				sf::Vector2f ds = calcularColisao(pJog2, inim);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					pJog2->colisao(inim, ds);
					inim->colisao(pJog2, ds);
				}

				if (inim->getBoss())
				{
					Ratao* boss = static_cast<Ratao*>(inim);
					if (boss && boss->getBatendo())
					{
						sf::FloatRect areaHit = boss->getHitboxBatida();
						sf::Vector2f posHit(areaHit.left, areaHit.top);
						sf::Vector2f tamHit(areaHit.width, areaHit.height);

						sf::Vector2f dsHit = calcularColisao(pJog2->getPos(), pJog2->getTam(), posHit, tamHit);
						if (dsHit.x < 0.0f && dsHit.y < 0.0f)
						{
							pJog2->receberDano(boss->getForca());
						}
					}
				}
			}
		}
	}
}

void Gerenciador_colisao::tratarColisaoJogadorObstaculo()
{
	if (pJog1 && pJog1->getAtivo())
	{
		for (auto* obs : LOs) 
		{
			if (obs && obs->getAtivo())
			{
				sf::Vector2f ds = calcularColisao(pJog1, obs);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					pJog1->colisao(obs, ds);
					obs->obstaculizar(pJog1);
				}
			}
		}
	}

	if (pJog2 && pJog2->getAtivo())
	{
		for (auto* obs : LOs)
		{
			if (obs && obs->getAtivo())
			{
				sf::Vector2f ds = calcularColisao(pJog2, obs);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					pJog2->colisao(obs, ds);
					obs->obstaculizar(pJog2);
				}
			}
		}
	}
}

void Gerenciador_colisao::tratarColisaoJogadorProjetil()
{
	std::vector<Projetil*> projeteisParaRemover;

	if (pJog1 && pJog1->getAtivo())
	{
		std::vector<Projetil*> projeteisAtuais(LPs.begin(), LPs.end());
		for (auto proj : projeteisAtuais)
		{
			if (proj && LPs.find(proj) != LPs.end())
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
	if (pJog2 && pJog2->getAtivo())
	{
		std::vector<Projetil*> projeteisAtuais(LPs.begin(), LPs.end());
		for (auto proj : projeteisAtuais)
		{
			if (proj && LPs.find(proj) != LPs.end())
			{
				sf::Vector2f ds = calcularColisao(proj, pJog2);
				if (ds.x < 0.0f && ds.y < 0.0f)
				{
					proj->colisao(pJog2, ds);
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
		if (inim && inim->getAtivo())
		{
			for (auto* obs : LOs)
			{
				if (obs && obs->getAtivo())
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

	std::vector<Projetil*> projeteisAtuais(LPs.begin(), LPs.end());
	for (auto proj : projeteisAtuais)
	{
		if (proj && LPs.find(proj) != LPs.end())
		{
			for (auto obs : LOs)
			{
				if (obs && obs->getAtivo())
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
	}
	for (auto proj : projeteisParaRemover)
	{
		removerProjetil(proj);
	}
}

bool Gerenciadores::Gerenciador_colisao::posicaoLivre(sf::Vector2f pos, sf::Vector2f tam) {
	std::list<Entidades::Obstaculo*>::const_iterator itObs;
	for (itObs = LOs.begin(); itObs != LOs.end(); ++itObs) {
		Entidades::Obstaculo* obs = *itObs;
		if (obs && obs->getAtivo()) {
			sf::Vector2f ds = calcularColisao(pos, tam, obs->getPos(), obs->getTam());
			if (ds.x < 0.0f && ds.y < 0.0f) {
				return false;
			}
		}
	}

	std::vector<Personagens::Inimigo*>::const_iterator itIni;
	for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni) {
		Personagens::Inimigo* ini = *itIni;
		if (ini && ini->getAtivo()) {
			sf::Vector2f ds = calcularColisao(pos, tam, ini->getPos(), ini->getTam());
			if (ds.x < 0.0f && ds.y < 0.0f) {
				return false;
			}
		}
	}

	if (pChao) {
		sf::Vector2f ds = calcularColisao(pos, tam, pChao->getPos(), pChao->getTam());
		if (ds.x < 0.0f && ds.y < 0.0f) {
			return false;
		}
	}

	return true;
}

//const bool verificaColisao(Entidade* pe1, Entidade* pe2) const;

void Gerenciador_colisao::executar()
{
	if (pJog1) pJog1->resetarChao();
	if (pJog2) pJog2->resetarChao();
	tratarTiro();
	tratarColisaoJogadorInimigo();
	tratarColisaoJogadorObstaculo();
	tratarColisaoJogadorProjetil();
	tratarColisaoInimigoObstaculo();
	tratarColisaoProjetilObstaculo();
	tratarColisaoChao();
}


void Gerenciador_colisao::limparDestruidos()
{
	if (pJog1 != NULL && !pJog1->getAtivo())
	{
		pJog1 = NULL;
	}
	if (pJog2 != NULL && !pJog2->getAtivo())
	{
		pJog2 = NULL;
	}

	// 1. Limpar Obstáculos inativos
	std::list<Entidades::Obstaculo*>::iterator itObs = LOs.begin();
	while (itObs != LOs.end())
	{
		Entidades::Obstaculo* obs = *itObs;
		if (obs != NULL && !obs->getAtivo())
		{
			itObs = LOs.erase(itObs);
		}
		else
		{
			++itObs;
		}
	}

	// 2. Limpar Inimigos inativos
	std::vector<Personagens::Inimigo*>::iterator itIni = LIs.begin();
	while (itIni != LIs.end())
	{
		Personagens::Inimigo* ini = *itIni;
		if (ini != NULL && !ini->getAtivo())
		{
			itIni = LIs.erase(itIni);
		}
		else
		{
			++itIni;
		}
	}

	// 3. Limpar Projéteis inativos
	std::set<Projetil*>::iterator itProj = LPs.begin();
	while (itProj != LPs.end())
	{
		Projetil* proj = *itProj;
		if (proj != NULL && !proj->getAtivo())
		{
			itProj = LPs.erase(itProj);
		}
		else
		{
			++itProj;
		}
	}
}

void Gerenciador_colisao::tratarTiro() {
	vector<Inimigo*>::iterator itIni;
	for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni)
	{
		Inimigo* inim = *itIni;
		if (inim && inim->getAtivo())
		{
			if(inim->getID() == ID::topeira)
			{
				Topeira* top = dynamic_cast<Topeira*>(inim);
				list<Projetil*>* pendentes = top->getProjeteisPendentes();
				list<Projetil*>::iterator itProj = pendentes->begin();
				while (itProj != pendentes->end())
				{
					Projetil* proj = *itProj;
					if (proj != NULL)
					{
						adicionarProjetil(proj);
					}
					itProj = pendentes->erase(itProj);
				}
			}
			else if(inim->getID() == ID::ratao)
			{
				Ratao* rat = dynamic_cast<Ratao*>(inim);
				list<Projetil*>* pendentes = rat->getProjeteisPendentes();
				list<Projetil*>::iterator itProj = pendentes->begin();
				while (itProj != pendentes->end())
				{
					Projetil* proj = *itProj;
					if (proj != NULL)
					{
						adicionarProjetil(proj);
					}
					itProj = pendentes->erase(itProj);
				}
			}
			
		}
	}
}

void Gerenciador_colisao::setChao(Entidades::Chao* chao) {
	pChao = chao;
	Entidade* pE = static_cast<Entidade*>(chao);
	LE->incluir(pE);
}

void Gerenciador_colisao::tratarColisaoChao()
{
	if (!pChao) return;

	// Pega a altura do topo do chão (coordenada Y)
	float topoChao = pChao->getPos().y;

	if (pJog1 && pJog1->getAtivo())
	{
		float peJogador = pJog1->getPos().y + pJog1->getTam().y;

		if (peJogador >= topoChao)
		{
			pJog1->setPos(sf::Vector2f(pJog1->getPos().x, topoChao - pJog1->getTam().y));
			pJog1->setChao(true);
		}
	}

	if (pJog2 && pJog2->getAtivo())
	{
		float peJogador2 = pJog2->getPos().y + pJog2->getTam().y;
		if (peJogador2 >= topoChao)
		{
			pJog2->setPos(sf::Vector2f(pJog2->getPos().x, topoChao - pJog2->getTam().y));
			pJog2->setChao(true);
		}
	}

	std::vector<Personagens::Inimigo*>::iterator itIni;
	for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni)
	{
		Personagens::Inimigo* inim = *itIni;

		if (inim && inim->getAtivo())
		{
			float peInimigo = inim->getPos().y + inim->getTam().y;

			if (peInimigo >= topoChao)
			{
				inim->setPos(sf::Vector2f(inim->getPos().x, topoChao - inim->getTam().y));
			}
		}
	}
}

void Gerenciador_colisao::limpar()
{
	LIs.clear();
	LOs.clear();
	LPs.clear();
	pJog1 = NULL;
	pJog2 = NULL;
	pChao = NULL;
	LE = NULL;
}