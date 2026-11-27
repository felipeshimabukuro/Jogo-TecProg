#include "Gerenciador_colisao.h"
#include "Ratao.h"
#include "Topeira.h"

namespace Escavadores_intrepidos {
	namespace Gerenciadores {

		Gerenciador_colisao* Gerenciador_colisao::pColisao = NULL;

		Gerenciador_colisao::Gerenciador_colisao() :
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
			pJog1 = NULL;
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
			if (pi)
			{
				Entidade* pE = static_cast<Entidade*>(pi);
				LIs.push_back(pi);
				LE->incluir(pE);
			}
		}

		void Gerenciador_colisao::removerInimigo(Inimigo* pi)
		{
			if (pi)
			{
				Entidade* pE = static_cast<Entidade*>(pi);
				LIs.erase(remove(LIs.begin(), LIs.end(), pi), LIs.end());
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

		const sf::Vector2f Gerenciador_colisao::calcularColisao(Entidade* ent1, Entidade* ent2) const
		{
			if (!ent1 || !ent2) return sf::Vector2f(0.0f, 0.0f);
			return calcularColisao(ent1->getPos(), ent1->getTam(), ent2->getPos(), ent2->getTam());
		}

		const sf::Vector2f Gerenciador_colisao::calcularColisao(const sf::Vector2f pos1, const sf::Vector2f tam1, const sf::Vector2f pos2, const sf::Vector2f tam2) const
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

		const bool Gerenciador_colisao::verificaColisao(Entidade* pe1, Entidade* pe2, sf::Vector2f& ds) const
		{
			if (!pe1 || !pe2) return false;
			ds = calcularColisao(pe1, pe2);
			return (ds.x < 0.0f && ds.y < 0.0f);
		}

		const bool Gerenciador_colisao::verificaColisao(const sf::Vector2f pos1, const sf::Vector2f tam1, const sf::Vector2f pos2, const sf::Vector2f tam2) const
		{
			sf::Vector2f ds = calcularColisao(pos1, tam1, pos2, tam2);
			return (ds.x < 0.0f && ds.y < 0.0f);
		}

		void Gerenciador_colisao::tratarColisaoJogsInimigs()
		{
			if (pJog1 && pJog1->getAtivo())
			{
				vector<Inimigo*>::iterator itIni;
				for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni)
				{
					Inimigo* inim = *itIni;
					if (inim && inim->getAtivo())
					{
						sf::Vector2f ds;
						if (verificaColisao(pJog1, inim, ds))
						{
							pJog1->colisao(inim, ds);
							inim->colisao(pJog1, ds);
						}

						if (inim->getBoss())
						{
							Ratao* boss = static_cast<Ratao*>(inim);
							if (boss && boss->getBatendo())
							{
								sf::FloatRect areaHit = boss->getHitboxBatida();
								sf::Vector2f posHit(areaHit.left, areaHit.top);
								sf::Vector2f tamHit(areaHit.width, areaHit.height);

								if (verificaColisao(pJog1->getPos(), pJog1->getTam(), posHit, tamHit))
								{
									boss->danificar(pJog1);
								}
							}
						}
					}
				}
			}

			if (pJog2 && pJog2->getAtivo())
			{
				vector<Inimigo*>::iterator itIni;
				for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni)
				{
					Inimigo* inim = *itIni;
					if (inim && inim->getAtivo())
					{
						sf::Vector2f ds;
						if (verificaColisao(pJog2, inim, ds))
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

								if (verificaColisao(pJog2->getPos(), pJog2->getTam(), posHit, tamHit))
								{
									boss->danificar(pJog2);
								}
							}
						}
					}
				}
			}
		}

		void Gerenciador_colisao::tratarColisaoJogsObstacs()
		{
			if (pJog1 && pJog1->getAtivo())
			{
				list<Obstaculo*>::iterator itObs;
				for (itObs = LOs.begin(); itObs != LOs.end(); ++itObs)
				{
					Obstaculo* obs = *itObs;
					if (obs && obs->getAtivo())
					{
						sf::Vector2f ds;
						if (verificaColisao(pJog1, obs, ds))
						{
							pJog1->colisao(obs, ds);
							obs->obstaculizar(pJog1);
						}
					}
				}
			}

			if (pJog2 && pJog2->getAtivo())
			{
				list<Obstaculo*>::iterator itObs;
				for (itObs = LOs.begin(); itObs != LOs.end(); ++itObs)
				{
					Obstaculo* obs = *itObs;
					if (obs && obs->getAtivo())
					{
						sf::Vector2f ds;
						if (verificaColisao(pJog2, obs, ds))
						{
							pJog2->colisao(obs, ds);
							obs->obstaculizar(pJog2);
						}
					}
				}
			}
		}

		void Gerenciador_colisao::tratarColisaoJogsProjeteis()
		{
			vector<Projetil*> projeteisParaRemover;

			if (pJog1 && pJog1->getAtivo())
			{
				vector<Projetil*> projeteisAtuais(LPs.begin(), LPs.end());
				vector<Projetil*>::iterator itProj;
				for (itProj = projeteisAtuais.begin(); itProj != projeteisAtuais.end(); ++itProj)
				{
					Projetil* proj = *itProj;
					if (proj && LPs.find(proj) != LPs.end())
					{
						sf::Vector2f ds;
						if (verificaColisao(proj, pJog1, ds))
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
				vector<Projetil*> projeteisAtuais(LPs.begin(), LPs.end());
				vector<Projetil*>::iterator itProj;
				for (itProj = projeteisAtuais.begin(); itProj != projeteisAtuais.end(); ++itProj)
				{
					Projetil* proj = *itProj;
					if (proj && LPs.find(proj) != LPs.end())
					{
						sf::Vector2f ds;
						if (verificaColisao(proj, pJog2, ds))
						{
							proj->colisao(pJog2, ds);
							projeteisParaRemover.push_back(proj);
							continue;
						}
					}
				}
			}

			vector<Projetil*>::iterator itRem;
			for (itRem = projeteisParaRemover.begin(); itRem != projeteisParaRemover.end(); ++itRem)
			{
				Projetil* proj = *itRem;
				removerProjetil(proj);
			}
		}

		void Gerenciador_colisao::tratarColisaoInimigsObstacs()
		{
			vector<Inimigo*>::iterator itIni;
			for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni)
			{
				Inimigo* inim = *itIni;
				if (inim && inim->getAtivo())
				{
					list<Obstaculo*>::iterator itObs;
					for (itObs = LOs.begin(); itObs != LOs.end(); ++itObs)
					{
						Obstaculo* obs = *itObs;
						if (obs && obs->getAtivo())
						{
							sf::Vector2f ds;
							if (verificaColisao(inim, obs, ds))
							{
								inim->colisao(obs, ds);
							}
						}
					}
				}
			}
		}

		void Gerenciador_colisao::tratarColisaoProjeteisObstacs()
		{
			vector<Projetil*> projeteisParaRemover;

			vector<Projetil*> projeteisAtuais(LPs.begin(), LPs.end());
			vector<Projetil*>::iterator itProj;
			for (itProj = projeteisAtuais.begin(); itProj != projeteisAtuais.end(); ++itProj)
			{
				Projetil* proj = *itProj;
				if (proj && LPs.find(proj) != LPs.end())
				{
					list<Obstaculo*>::iterator itObs;
					for (itObs = LOs.begin(); itObs != LOs.end(); ++itObs)
					{
						Obstaculo* obs = *itObs;
						if (obs && obs->getAtivo())
						{
							sf::Vector2f ds;
							if (verificaColisao(proj, obs, ds))
							{
								proj->colisao(obs, ds);
								projeteisParaRemover.push_back(proj);
								break;
							}
						}
					}
				}
			}

			vector<Projetil*>::iterator itRem;
			for (itRem = projeteisParaRemover.begin(); itRem != projeteisParaRemover.end(); ++itRem)
			{
				Projetil* proj = *itRem;
				removerProjetil(proj);
			}
		}

		bool Gerenciador_colisao::posicaoLivre(sf::Vector2f pos, sf::Vector2f tam) {
			list<Obstaculo*>::const_iterator itObs;
			for (itObs = LOs.begin(); itObs != LOs.end(); ++itObs) {
				Obstaculo* obs = *itObs;
				if (obs && obs->getAtivo()) {
					if (verificaColisao(pos, tam, obs->getPos(), obs->getTam())) {
						return false;
					}
				}
			}

			vector<Inimigo*>::const_iterator itIni;
			for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni) {
				Inimigo* ini = *itIni;
				if (ini && ini->getAtivo()) {
					if (verificaColisao(pos, tam, ini->getPos(), ini->getTam())) {
						return false;
					}
				}
			}

			if (pChao) {
				if (verificaColisao(pos, tam, pChao->getPos(), pChao->getTam())) {
					return false;
				}
			}

			return true;
		}

		void Gerenciador_colisao::executar()
		{
			if (pJog1) pJog1->resetarChao();
			if (pJog2) pJog2->resetarChao();
			tratarTiro();
			tratarColisaoJogsInimigs();
			tratarColisaoJogsObstacs();
			tratarColisaoJogsProjeteis();
			tratarColisaoInimigsObstacs();
			tratarColisaoProjeteisObstacs();
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
			list<Obstaculo*>::iterator itObs = LOs.begin();
			while (itObs != LOs.end())
			{
				Obstaculo* obs = *itObs;
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
			vector<Inimigo*>::iterator itIni = LIs.begin();
			while (itIni != LIs.end())
			{
				Inimigo* ini = *itIni;
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
			set<Projetil*>::iterator itProj = LPs.begin();
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
					if (Topeira* top = dynamic_cast<Topeira*>(inim))
					{
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
					else if (Ratao* rat = dynamic_cast<Ratao*>(inim))
					{
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

		void Gerenciador_colisao::setChao(Chao* chao) {
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
					if (pChao->getCurar()) pChao->ajudar(pJog1);
				}
			}

			if (pJog2 && pJog2->getAtivo())
			{
				float peJogador2 = pJog2->getPos().y + pJog2->getTam().y;
				if (peJogador2 >= topoChao)
				{
					pJog2->setPos(sf::Vector2f(pJog2->getPos().x, topoChao - pJog2->getTam().y));
					pJog2->setChao(true);
					if (pChao->getCurar()) pChao->ajudar(pJog2);
				}
			}

			vector<Inimigo*>::iterator itIni;
			for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni)
			{
				Inimigo* inim = *itIni;

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
	}
}