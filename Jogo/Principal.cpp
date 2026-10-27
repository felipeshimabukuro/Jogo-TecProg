#include "Bibliotecas.h"
#include "Principal.h"
#include "Jogador.h"

using namespace Gerenciadores;

Principal::Principal() : pGG(Gerenciador_grafico::getGerenciadorGrafico()), jogador()
{
	executar();
}

Principal::~Principal()
{

}

void Principal::executar()
{
	while(pGG->verificaJanelaAberta())
	{
		sf::Event evento;
		if(pGG->getWindow()->pollEvent(evento))
		{
			if(evento.type == sf::Event::Closed)
			{
				pGG->fechaJanela();
			}
			else if(evento.type == sf::Event::KeyPressed)
			{
				if(evento.key.code == sf::Keyboard::Escape)
				{
					pGG->fechaJanela();
				}
			}
		}
		pGG->limpaJanela();
		jogador.mover();
		pGG->desenharQuadrado(jogador.getX(),jogador.getY());
		pGG->mostrarJanela();
	}
}