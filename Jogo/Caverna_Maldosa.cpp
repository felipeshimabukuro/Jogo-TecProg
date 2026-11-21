#include "Caverna_Maldosa.h"

using namespace Fases;

Caverna_Maldosa::Caverna_Maldosa() :Fase(), maxRato(5), contRato(0)
{
    tilemap.open("fases/caverna_maldosa.txt");
    criarCenario();
    //criarObstaculos();
    //criarInimigos();
	
}

Caverna_Maldosa::~Caverna_Maldosa() {

}


/*void Caverna_Maldosa::criarObstaculos() {

}*/

void Caverna_Maldosa::criarMagma(sf::Vector2f pos)
{
    Magma* magma = new Magma(pos.x, pos.y, GRID, GRID, 5, true, false);
    pGC->adicionarObstaculo(magma);
}

void Caverna_Maldosa::criarRato(sf::Vector2f pos)
{
    Rato* rato = new Rato(pos, sf::Vector2f(GRID, GRID), pJogador1);
    pGC->adicionarInimigo(rato);
}

/* void Caverna_Maldosa::criarInimigos() {
    
}*/

void Caverna_Maldosa::criarFundo() 
{
    if (pGG) 
    {
        sf::Texture* tex = pGG->getTextura("fundo");
        if (tex) 
        {
            tex->setRepeated(true);
            sprite.setTexture(*tex);

            sprite.setScale(3.0f, 3.0f); //relacao grid com o tamanho da textura

            int larguraRepeticao = static_cast<int>(WIDTH / 3.0f);
            int alturaRepeticao = static_cast<int>(HEIGHT / 3.0f);
            sprite.setTextureRect(sf::IntRect(0, 0, larguraRepeticao, alturaRepeticao));
            sprite.setPosition(0.0f, 0.0f);
        }
    }
}

void Caverna_Maldosa::executar() {
    while (pGG->verificaJanelaAberta())
    {
        pEv->executar();
        lista_ents.percorrer();
        pGC->executar();
        blocosColocados();
        pGG->limpaJanela();
        pGG->getWindow()->draw(sprite);
        lista_ents.desenharTodas(pGG);
        pGG->mostrarJanela();
        pGC->limparDestruidos();
        lista_ents.limparDestruidos();

        bool pPressionado = false;

        // Dentro do método executar():
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            if (!pPressionado)
            {
                salvar();
                pPressionado = true;
            }
        }
        else
        {
            pPressionado = false;
        }
    }
}

void Caverna_Maldosa::criarEntidade(char tipo, sf::Vector2f pos) {
    switch (tipo)
    {
        case('#'):
            criarChao(pos);
            break;

        case('@'):
            criarPlataforma(pos);
            break;

        case('j'):
            posJogador(pos);
            break;

        case('T'):
            criarTopeira(pos);
            break;

		case('t'):
        {
            if(contTopeiras < maxTopeiras && rand()%3 != 0)
            {
                criarTopeira(pos);
                contTopeiras++;
            }
        }
            break;

        case('R'):
            criarRato(pos);
            break;

        case('r'):
        {
            if(contRato < maxRato && rand() % 3 != 0)
            {
                criarRato(pos);
                contRato++;
            }
        }
            break;

        case('m'):
            criarMagma(pos);
            break;
    }
}