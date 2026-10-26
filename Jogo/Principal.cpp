#include "Bibliotecas.h"
#include "Principal.h"

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
		pGG->desenharQuadrado();
		pGG->mostrarJanela();
	}
}