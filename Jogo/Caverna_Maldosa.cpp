#include "Caverna_Maldosa.h"

using namespace Fases;

Caverna_Maldosa::Caverna_Maldosa() :Fase() {
	criarFundo();
    criarCenario();
    criarObstaculos();
    criarInimigos();
}

Caverna_Maldosa::~Caverna_Maldosa() {

}


void Caverna_Maldosa::criarObstaculos() {
    for (int i = 0; i < 8; i++) {
        Plataforma* terra1 = new Plataforma(GRID * i, 450.0f, GRID, GRID, 0, false, true);
        pGC->adicionarObstaculo(terra1);
    }

    for (int i = 8; i < WIDTH/GRID; i++) {
        Magma* magma = new Magma(GRID * i, 450.0f, GRID, GRID, 5, true, false);
        pGC->adicionarObstaculo(magma);
    }

    for (int i = 0; i < WIDTH/GRID; i++) {
        Plataforma* terra2 = new Plataforma(GRID * i, 300.0f, GRID, GRID, 0, false, true);
        pGC->adicionarObstaculo(terra2);
    }

    //Chao* chao = new Chao(sf::Vector2f(0.0f, 600.0f - 50.0f), sf::Vector2f(800.0f, 50.0f));
    //pGC->adicionarChao(chao);
    Chao* chao = new Chao(sf::Vector2f(0.0f, 780.0f), sf::Vector2f(WIDTH, 300.0f));
    pGC->setChao(chao);
}

void Caverna_Maldosa::criarInimigos() {
    criarTopeiras();
}

void Caverna_Maldosa::criarFundo() 
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

void Caverna_Maldosa::executar() {
    while (pGG->verificaJanelaAberta())
    {
        pEv->executar();
        list_ents.percorrer();
        pGC->executar();
        blocosColocados();
        pGG->limpaJanela();
        pGG->getWindow()->draw(fundo);
        list_ents.desenharTodas(pGG);
        pGG->mostrarJanela();
        pGC->limparDestruidos();
        list_ents.limparDestruidos();
    }
}

