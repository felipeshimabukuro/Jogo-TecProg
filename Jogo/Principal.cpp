#include "Bibliotecas.h"
#include "Principal.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Topeira.h"
#include "Obstaculo.h"
#include "Terra.h"

using namespace Gerenciadores;
using namespace Personagens;

Principal::Principal() : 
	pGG(Gerenciador_grafico::getGerenciadorGrafico()), 
	pEvento(Gerenciador_eventos::getGerenciadorEventos()),
	pColisao(Gerenciador_colisao::getGerenciadorColisao()),
	LEs()
{
	pColisao->setListaEntidade(&LEs);
	instanciarEntidades();
	executar();
}

Principal::~Principal()
{
	if (pColisao)
	{
		delete pColisao;
		pColisao = NULL;
	}
	if (pEvento)
	{
		delete pEvento;
		pEvento = NULL;
	}
	if (pGG)
	{
		delete pGG;
		pGG = NULL;
	}
}

void Principal::executar()
{
	//Cada coisa tem sua funcao agora
	while(pGG->verificaJanelaAberta())
	{
		pEvento->executar();
		LEs.executarTodas();
		pColisao->executar();
		pGG->limpaJanela();
		LEs.desenharTodas(pGG->getWindow());
		pGG->mostrarJanela();
	}
}

void Principal::instanciarEntidades()
{
	//So adicionar na colisao que ja adiciona na lista de entidades

	//Jogador
	Jogador* jogador = new Jogador(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), 0);
	pEvento->setJogador(jogador);
	pColisao->setJogador(jogador);


	//Inimigos
	Topeira* inimigo = new Topeira(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), jogador);
	pColisao->adicionarInimigo(inimigo);


	//Obstaculos
	for (int i = 0; i < 16; i++) {
		Terra* terra = new Terra(50.0f * i, 450.0f, 50.0f, 50.0f, 0, false, true);
		pColisao->adicionarObstaculo(terra);
	}

	for (int i = 0; i < 16; i++) {
		Terra* terra = new Terra(50.0f * i, 300.0f, 50.0f, 50.0f, 0, false, true);
		pColisao->adicionarObstaculo(terra);
	}
}
