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
	Jogador* jogador = new Jogador();
	Entidade* e1 = static_cast<Entidade*>(jogador);
	LEs.incluir(e1);

	pEvento->setJogador(jogador);
}
