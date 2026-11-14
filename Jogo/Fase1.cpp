#include "Fase1.h"

using namespace Fases;

Fase1::Fase1() :Fase() {
	criarFundo();
    criarCenario();
    criarObstaculos();
    criarInimigos();
}

Fase1::~Fase1() {

}

void Fase1::criarCenario() {

}

void Fase1::criarObstaculos() {
    for (int i = 0; i < 8; i++) {
        Terra* terra1 = new Terra(GRID * i, 450.0f, GRID, GRID, 0, false, true);
        pGC->adicionarObstaculo(terra1);
    }

    for (int i = 8; i < WIDTH/GRID; i++) {
        Magma* magma = new Magma(GRID * i, 450.0f, GRID, GRID, 5, true, false);
        pGC->adicionarObstaculo(magma);
    }

    for (int i = 0; i < WIDTH/GRID; i++) {
        Terra* terra2 = new Terra(GRID * i, 300.0f, GRID, GRID, 0, false, true);
        pGC->adicionarObstaculo(terra2);
    }
}

void Fase1::criarInimigos() {
    criarTopeiras();
}

void Fase1::criarFundo() 
{
    if (pGG) 
    {
        sf::Texture* tex = pGG->getTextura("fundo");
        if (tex) 
        {
            tex->setRepeated(true);
            fundo.setTexture(*tex);

			fundo.setScale(3.0f, 3.0f); //relacao grid com o tamanho da textura

            int larguraRepeticao = static_cast<int>(WIDTH / 3.0f);
            int alturaRepeticao = static_cast<int>(HEIGHT / 3.0f);
            fundo.setTextureRect(sf::IntRect(0, 0, larguraRepeticao, alturaRepeticao));
            fundo.setPosition(0.0f, 0.0f);
        }
    }
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
        pGG->getWindow()->draw(fundo);
        list_ents.desenharTodas(pGG->getWindow());
        pGG->mostrarJanela();
        pGC->limparDestruidos();
        list_ents.limparDestruidos();
    }
}