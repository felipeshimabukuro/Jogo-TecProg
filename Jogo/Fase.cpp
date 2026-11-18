#include "Fase.h"
#include "Topeira.h"
#include "Ratao.h"

using namespace Fases;

Fase::Fase():Ente(), list_ents(),
pGC(Gerenciadores::Gerenciador_colisao::getGerenciadorColisao()),
pEv(Gerenciadores::Gerenciador_eventos::getGerenciadorEventos()),
pGG(Gerenciadores::Gerenciador_grafico::getGerenciadorGrafico()),
pJogador1(NULL)
{
	if (pGC) {
		pGC->setListaEntidade(&list_ents);
	}

	pJogador1 = new Jogador(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(GRID, GRID), 0);

	if (pGC && pJogador1) {
		pGC->setJogador(pJogador1);
	}

	if (pEv && pJogador1) {
		pEv->setJogador(pJogador1);
	}
}

Fase::~Fase() {
	pJogador1 = NULL;
	pGC = NULL;
}

void Fase::blocosColocados() {
	if (pJogador1 != NULL) {
		std::list<Entidades::Obstaculo*>* pendentes = pJogador1->getBlocosPendentes();

		std::list<Entidades::Obstaculo*>::iterator it = pendentes->begin();
		while (it != pendentes->end()) {
			Entidades::Obstaculo* bloco = *it;

			if (bloco != NULL) {
				if (pGC->posicaoLivre(bloco->getPos(), bloco->getTam())) {
					pGC->adicionarObstaculo(bloco);
				}
				else {
					pJogador1->addInventario();
					delete bloco;
					bloco = NULL;
				}
			}
			it = pendentes->erase(it);
		}
	}
} 

void Fase::criarCenario() {

}

void Fase::criarTopeiras() {
	Topeira* topeira = new Topeira(sf::Vector2f(300.0f, 200.0f), sf::Vector2f(GRID * 2, GRID * 2), pJogador1);
	pGC->adicionarInimigo(topeira);
}