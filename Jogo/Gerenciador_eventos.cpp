#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Gerenciador_eventos.h"
#include "Jogador.h"
#include "Principal.h"

using namespace Gerenciadores;

Gerenciador_eventos* Gerenciador_eventos::pEventos = NULL;
Gerenciador_grafico* Gerenciador_eventos::pGG = Gerenciador_grafico::getGerenciadorGrafico();

Gerenciador_eventos::Gerenciador_eventos():
	pJogador(NULL)	
{
}

Gerenciador_eventos::~Gerenciador_eventos()
{
	pGG = NULL;
	pEventos = NULL;
	pJogador = NULL;
}

Gerenciador_eventos* Gerenciador_eventos::getGerenciadorEventos()
{
	if(!pEventos)
	{
		pEventos = new Gerenciador_eventos();
	}
	return pEventos;
}

void Gerenciador_eventos::setJogador(Jogador* pJogador)
{
	this->pJogador = pJogador;
}

void Gerenciador_eventos::verificarTeclaPressionada(sf::Keyboard::Key tecla)
{
	//jogador
	if(tecla == sf::Keyboard::A)
	{
		pJogador->mover(-1);
	}
	else if(tecla == sf::Keyboard::D)
	{
		pJogador->mover(1);
	}
	else if (tecla == sf::Keyboard::Space)
	{
		pJogador->mover(0);
	}

	//interface
	else if(tecla == sf::Keyboard::Escape)
	{
		pGG->fechaJanela();
	}
}

void Gerenciador_eventos::verificaTeclaSolta(sf::Keyboard::Key tecla)
{
	// Implementation for handling key release events
}

void Gerenciador_eventos::executar()
{
	sf::Event evento;
	while(pGG->getWindow()->pollEvent(evento))
	{
		if(evento.type == sf::Event::KeyPressed)
		{
			verificarTeclaPressionada(evento.key.code);
		}
		else if (evento.type == sf::Event::KeyReleased)
		{
			verificaTeclaSolta(evento.key.code);
		}
		else if (evento.type == sf::Event::Closed)
		{
			pGG->fechaJanela();
		}
	}
}