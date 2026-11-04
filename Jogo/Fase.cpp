#include "Fase.h"
#include "Topeira.h"


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

	pJogador1 = new Jogador(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), 0);

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

void Fase::criarTopeiras() {
	Topeira* topeira = new Topeira(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), pJogador1);
	pGC->adicionarInimigo(topeira);
}
