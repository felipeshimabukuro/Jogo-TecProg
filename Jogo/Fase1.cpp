#include "Fase1.h"

using namespace Fases;

Fase1::Fase1() :Fase() {
	criarCenario();
	criarObstaculos();
	criarInimigos();
}

Fase1::~Fase1() {

}

void Fase1::criarCenario() {

}

void Fase1::criarObstaculos() {
    for (int i = 0; i < 16; i++) {
        Terra* terra1 = new Terra(50.0f * i, 450.0f, 50.0f, 50.0f, 0, false, true);
        pGC->adicionarObstaculo(terra1);
    }

    for (int i = 0; i < 16; i++) {
        Terra* terra2 = new Terra(50.0f * i, 300.0f, 50.0f, 50.0f, 0, false, true);
        pGC->adicionarObstaculo(terra2);
    }
}

void Fase1::criarInimigos() {
    criarTopeiras();
}

void Fase1::executar() {
	while (pGG->verificaJanelaAberta())
	{
		pEv->executar();
		list_ents.percorrer();
		pGC->executar();
		pGG->limpaJanela();
		list_ents.desenharTodas(pGG->getWindow());
		pGG->mostrarJanela();
	}
}