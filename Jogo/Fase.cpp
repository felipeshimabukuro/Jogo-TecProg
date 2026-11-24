#include "Fase.h"

using namespace Fases;

Fase::Fase(int numJogadores, Jogador* pJ1, Jogador* pJ2):Ente(ID::fase), 
    maxTopeiras(5),
    contTopeiras(0),
	maxPlataformas(900),
	contPlataformas(0),
    lista_ents(),
    pGC(Gerenciador_colisao::getGerenciadorColisao()),
    pEv(Gerenciador_eventos::getGerenciadorEventos()),
    pJogador1(pJ1),
	pJogador2(pJ2),
	numJogadores(numJogadores),
	venceu(false)
{
	if (pGC) {
		pGC->setListaEntidade(&lista_ents);
	}

	if (pGC) {
		pGC->setJogador1(pJogador1);
		pGC->setJogador2(pJogador2);
	}

	if (pEv) {
		pEv->setJogador1(pJogador1);
		pEv->setJogador2(pJogador2);
	}
}

Fase::~Fase()
{
	if (pEv) {
		pEv->setJogador1(NULL);
		pEv->setJogador2(NULL); // <--
	}
	if (pGC) {
		pGC->limpar();
	}
	pJogador1 = NULL;
	pJogador2 = NULL; // <--
	pGC = NULL;
	pEv = NULL;
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
	if (pJogador2 != NULL) {
		std::list<Entidades::Obstaculo*>* pendentes2 = pJogador2->getBlocosPendentes();
		std::list<Entidades::Obstaculo*>::iterator it2 = pendentes2->begin();
		while (it2 != pendentes2->end()) {
			Entidades::Obstaculo* bloco = *it2;
			if (bloco != NULL) {
				if (pGC->posicaoLivre(bloco->getPos(), bloco->getTam())) {
					pGC->adicionarObstaculo(bloco);
				}
				else {
					pJogador2->addInventario();
					delete bloco;
				}
			}
			it2 = pendentes2->erase(it2);
		}
	}
} 

void Fase::criarTopeira(sf::Vector2f pos) {
	Topeira* topeira = new Topeira(pos, sf::Vector2f(GRID * 2, GRID * 2), pJogador1,pJogador2);
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
	if (pJogador2) {
		pJogador2->setPos(sf::Vector2f(pos.x + GRID, pos.y));
	}
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

const bool Fase::getVenceu() const
{
	return venceu;
}

const int Fase::getNumJogadores() const
{
	return numJogadores;
}

void Fase::setJogador1(Jogador* pJ1) {
	pJogador1 = pJ1;
	if (pGC) pGC->setJogador1(pJogador1);
	if (pEv) pEv->setJogador1(pJogador1);
}

void Fase::setJogador2(Jogador* pJ2) {
	pJogador2 = pJ2;
	if (pGC) pGC->setJogador2(pJogador2);
	if (pEv) pEv->setJogador2(pJogador2);
}