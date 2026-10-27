#include "Bibliotecas.h"
#include "Principal.h"
#include "Jogador.h"

using namespace Gerenciadores;

Principal::Principal() : pGG(pGG->getGerenciadorGrafico())
{
	executar();
}

Principal::~Principal()
{

}

void Principal::executar()
{
	Jogador jogador(350, 250, 0);

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
		jogador.executar();
		pGG->limpaJanela();
		pGG->desenharQuadrado(jogador.getX(),jogador.getY());
		pGG->mostrarJanela();
	}
}