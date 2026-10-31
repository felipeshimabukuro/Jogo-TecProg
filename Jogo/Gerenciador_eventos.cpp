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
	if(pJogador)
	{
		/*if (tecla == sf::Keyboard::A || tecla == sf::Keyboard::Left)
		{
			pJogador->mover(-1);
		}
		else if(tecla == sf::Keyboard::D || tecla == sf::Keyboard::Right)
		{
			pJogador->mover(1);
		}
		else if (tecla == sf::Keyboard::Space || tecla == sf::Keyboard::W || tecla == sf::Keyboard::Up)
		{
			pJogador->mover(3);
		}*/
		if (pJogador->getNum() == 0) {
			if (tecla == sf::Keyboard::A || tecla == sf::Keyboard::S || tecla == sf::Keyboard::D || tecla == sf::Keyboard::W) {
				pJogador->executar();
			}
		}
		else {
			if (tecla == sf::Keyboard::Up || tecla == sf::Keyboard::Right || tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Down) {
				pJogador->executar();
			}
		}
	}

	//interface
	if(tecla == sf::Keyboard::Escape)
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
