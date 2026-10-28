#include "Bibliotecas.h"
#include "Principal.h"
#include "Jogador.h"

using namespace Gerenciadores;

Principal::Principal() : 
	pGG(Gerenciador_grafico::getGerenciadorGrafico()), 
	pEvento(Gerenciador_eventos::getGerenciadorEventos()),
	LEs()
{
	instanciarEntidades();
	executar();
}

Principal::~Principal()
{

}

void Principal::executar()
{
	//Cada coisa tem sua funcao agora
	while(pGG->verificaJanelaAberta())
	{
		pEvento->executar();
		pGG->limpaJanela();
		LEs.percorrer(pGG->getWindow());
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

	Inimigo* inimigo = new Inimigo(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f),jogador);
	Entidade* e2 = static_cast<Entidade*>(inimigo);
	LEs.incluir(e2);

}
