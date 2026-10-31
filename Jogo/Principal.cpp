#include "Bibliotecas.h"
#include "Principal.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "Terra.h"

using namespace Gerenciadores;
using namespace Personagens;

Principal::Principal() : 
	pGG(Gerenciador_grafico::getGerenciadorGrafico()), 
	pEvento(Gerenciador_eventos::getGerenciadorEventos()),
	pColisao(new Gerenciador_colisao()),
	LEs()
{
	instanciarEntidades();
	executar();
}

Principal::~Principal()
{
	if (pColisao)
	{
		delete pColisao;
		pColisao = nullptr;
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
	//Tudo que for adicionar de entidade deve fazer essa sequencia de passos
	Jogador* jogador = new Jogador(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), 0);
	Entidade* e1 = static_cast<Entidade*>(jogador);
	LEs.incluir(e1);

	pEvento->setJogador(jogador);
	pColisao->setJogador(jogador);

	Inimigo* inimigo = new Inimigo(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), jogador);
	Entidade* e2 = static_cast<Entidade*>(inimigo);
	LEs.incluir(e2);

	pColisao->adicionarInimigo(inimigo);
	for (int i = 0; i < 16; i++) {
		Terra* terra = new Terra(50.0f * i, 450.0f, 50.0f, 50.0f, 0, false, true);
		Entidade* e3 = static_cast<Entidade*>(terra);
		LEs.incluir(e3);

		pColisao->adicionarObstaculo(terra);
	}
}
