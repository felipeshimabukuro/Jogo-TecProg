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

        if (pJogador1 != NULL) {
            std::list<Entidades::Obstaculo*>* pendentes = pJogador1->getBlocosPendentes();

            std::list<Entidades::Obstaculo*>::iterator it = pendentes->begin();
            while (it != pendentes->end()) {
                Entidades::Obstaculo* bloco = *it;

                if (bloco != NULL) {
                    // A Fase é quem valida com o gerenciador de colisões
                    if (pGC->posicaoLivre(bloco->getPos(), bloco->getTam())) {
                        pGC->adicionarObstaculo(bloco); // Adiciona ao GC e à ListaEntidade
                    }
                    else {
                        // Se a posição estiver ocupada, devolve ao inventário e elimina a memória
                        delete bloco;
                        bloco = NULL;
                        // Opcional: devolver 1 ao inventario do jogador aqui
                    }
                }
                it = pendentes->erase(it); // Remove da lista temporária do jogador
            }
        }

        pGG->limpaJanela();
        list_ents.desenharTodas(pGG->getWindow());
        pGG->mostrarJanela();
        pGC->limparDestruidos();
        list_ents.limparDestruidos();
    }
}