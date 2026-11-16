#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;

Gerenciador_grafico* Gerenciador_grafico::pGrafico = NULL;

Gerenciador_grafico::Gerenciador_grafico() : 
	window(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Jogo"))
{
	if (window == NULL) {
		cout << "ERROR::Gerenciador_grafico nao foi possivel criar uma janela grafica" << endl;
		exit(1);
	}
	window->setFramerateLimit(60);

	window->setKeyRepeatEnabled(false);

	// ==================== CARREGAR TEXTURAS AQUI ====================
	carregarTextura("jogador1", "assets/jogador1.png");
	carregarTextura("topeira", "assets/topeira.png");
	carregarTextura("p_topeira", "assets/p_topeira.png");
	carregarTextura("terra", "assets/terra.png");
	carregarTextura("magma", "assets/magma.png");
	carregarTextura("fundo", "assets/fundo.png");
	// ================================================================
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

bool Gerenciador_grafico::carregarTextura(const std::string& id, const std::string& caminho)
{
	// Se já foi carregada anteriormente
	if (mapaTexturas.find(id) != mapaTexturas.end())
	{
		return true;
	}

	sf::Texture textura;
	if (!textura.loadFromFile(caminho))
	{
		cout << "Sem caminho: " << caminho << endl;
		return false;
	}

	mapaTexturas[id] = textura;
	return true;
}

sf::Texture* Gerenciador_grafico::getTextura(const string& id)
{
	map<string, sf::Texture>::iterator it = mapaTexturas.find(id);
	if (it != mapaTexturas.end())
	{
		return &(it->second);
	}

	cout << "Textura '" << id << "' nao encontrada." << std::endl;
	return NULL;
}

void Gerenciador_grafico::desenharEnte(Ente* pE) {
	pE->desenhar(window);
}