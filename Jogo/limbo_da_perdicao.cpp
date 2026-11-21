#include "Limbo_da_perdicao.h"

using namespace Fases;

Limbo_da_perdicao::Limbo_da_perdicao() :Fase(), maxRatao(5), contRatao(0)
{
    tilemap.open("fases/limbo_da_perdicao.txt");
    criarCenario();
    //criarObstaculos();
    //criarInimigos();
	
}

Limbo_da_perdicao::~Limbo_da_perdicao() {
    Gerenciadores::Gerenciador_eventos::getGerenciadorEventos()->setJogador(NULL);
    if (pGC) {
        delete pGC;
        pGC = NULL;
    }
}


/*void Caverna_Maldosa::criarObstaculos() {

}*/

void Limbo_da_perdicao::criarEspinho(sf::Vector2f pos)
{
    Espinho* espinho = new Espinho(pos.x, pos.y, GRID, GRID, 5, true, false);
    pGC->adicionarObstaculo(espinho);
}

void Limbo_da_perdicao::criarRatao(sf::Vector2f pos)
{
    Ratao* ratao = new Ratao(pos, sf::Vector2f(GRID * 2, GRID * 2), pJogador1);
    pGC->adicionarInimigo(ratao);
}

/* void Caverna_Maldosa::criarInimigos() {
    
}*/

void Limbo_da_perdicao::criarFundo()
{
    if (pGG) 
    {
        sf::Texture* tex = pGG->getTextura("fundo2");
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

void Limbo_da_perdicao::executar() {
    while (pGG->verificaJanelaAberta())
    {
        if (Gerenciadores::Gerenciador_eventos::getGerenciadorEventos()->getVoltarMenu()) {
            return; 
        }
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
    }
}

void Limbo_da_perdicao::criarEntidade(char tipo, sf::Vector2f pos) {
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
            }
        }
            break;

        case('B'):
        {
            criarRatao(pos);
            contRatao++;
        }
            break;

        case('b'):
        {
            if(contRatao < maxRatao && rand() % 3 != 0)
            {
                criarRatao(pos);
                contRatao++;
            }
        }
            break;

        case('e'):
            criarEspinho(pos);
            break;
    }
}