#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;

Gerenciador_grafico* Gerenciador_grafico::pGrafico = NULL;

Gerenciador_grafico::Gerenciador_grafico() : 
	window(new sf::RenderWindow(sf::VideoMode(800, 600), "Jogo"))
{
	if (window == NULL) {
		cout << "ERROR::Gerenciador_grafico nao foi possivel criar uma janela grafica" << endl;
		exit(1);
	}
	window->setFramerateLimit(60);

	window->setKeyRepeatEnabled(false);
}

Gerenciador_grafico::~Gerenciador_grafico()
{
	if(window)
	{
		delete window;
		window = NULL;
	}
}
	
Gerenciador_grafico* Gerenciador_grafico::getGerenciadorGrafico()
{
	if (pGrafico == NULL)
	{
		pGrafico = new Gerenciador_grafico();
	}
	return pGrafico;
}

sf::RenderWindow* Gerenciador_grafico::getWindow()
{
	return window;
}

void Gerenciador_grafico::limpaJanela()
{
	window->clear();
}

void Gerenciador_grafico::fechaJanela()
{
	if (window)
	{
		window->close();
	}
}

const bool Gerenciador_grafico::verificaJanelaAberta()
{
	return window && window->isOpen();
}

/*void Gerenciador_grafico::desenharEnte(Ente* pE)
{
	if (window && pE)
	{
		pE->desenhar();
	}
}*/

void Gerenciador_grafico::mostrarJanela()
{
	if (window)
	{
		window->display();
	}
}

void Gerenciador_grafico::desenharQuadrado(int x, int y)
{
	if (window)
	{
		sf::RectangleShape quadrado(sf::Vector2f(100.0f, 100.0f));
		quadrado.setFillColor(sf::Color::Green);
		quadrado.setPosition(x, y);
		window->draw(quadrado);
	}
}