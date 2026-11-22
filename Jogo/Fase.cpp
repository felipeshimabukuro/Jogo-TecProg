#include "Fase.h"

using namespace Fases;

Fase::Fase():Ente(ID::fase), 
    maxTopeiras(5),
    contTopeiras(0),
    lista_ents(),
    pGC(Gerenciador_colisao::getGerenciadorColisao()),
    pEv(Gerenciador_eventos::getGerenciadorEventos()),
    pGG(Gerenciador_grafico::getGerenciadorGrafico()),
    pJogador1(NULL)
{
	if (pGC) {
		pGC->setListaEntidade(&lista_ents);
	}

	pJogador1 = new Jogador(sf::Vector2f(0, 0), sf::Vector2f(GRID, GRID), 0);

	if (pGC && pJogador1) {
		pGC->setJogador(pJogador1);
	}

	if (pEv && pJogador1) {
		pEv->setJogador(pJogador1);
	}
}

Fase::~Fase()
{
    if (pEv) 
    {
        pEv->setJogador(NULL);
    }

    if (pGC) 
    {
        pGC->limpar();
    }

    pJogador1 = NULL;
    pGC = NULL;
    pEv = NULL;
    pGG = NULL;
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

void Fase::criarTopeira(sf::Vector2f pos) {
	Topeira* topeira = new Topeira(pos, sf::Vector2f(GRID * 2, GRID * 2), pJogador1);
	pGC->adicionarInimigo(topeira);
}

void Fase::criarChao(sf::Vector2f pos)
{
	Chao* chao = new Chao(pos, sf::Vector2f(WIDTH, 300.0f));
	pGC->setChao(chao);
}

void Fase::criarPlataforma(sf::Vector2f pos)
{
	Plataforma* terra = new Plataforma(pos.x, pos.y, GRID, GRID, 0, false, true);
	pGC->adicionarObstaculo(terra);
	terra->setAtivo(1);
}

void Fase::posJogador(sf::Vector2f pos)
{
	pJogador1->setPos(pos);
}

void Fase::criarCenario() 
{
	criarFundo();

	string linha;
	if (!tilemap.is_open())
	{
		cout << "Erro ao abrir o arquivo de tilemap!" << endl;
		return;
	}

	int i = 0;
	while(getline(tilemap, linha))
	{
		for(int j = 0; j < linha.length(); j++)
		{
			if(linha[j] != ' ')
			{
				sf::Vector2f pos(j * GRID, i * GRID);
				criarEntidade(linha[j], pos);
			}
		}
		i++;
	}
	tilemap.close();
}

void Fase::salvar()
{
	lista_ents.salvar();
}