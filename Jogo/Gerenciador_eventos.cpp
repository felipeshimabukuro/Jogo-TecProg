#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Gerenciador_eventos.h"
#include "Jogador.h"
#include "Jogo.h"
#include "Menu.h"

using namespace Gerenciadores;

Gerenciador_eventos* Gerenciador_eventos::pEventos = NULL;
Gerenciador_grafico* Gerenciador_eventos::pGG = Gerenciador_grafico::getGerenciadorGrafico();

Gerenciador_eventos::Gerenciador_eventos():
	pJogador(NULL),	
	pJogo(NULL)
{
}

Gerenciador_eventos::~Gerenciador_eventos()
{
	pGG = NULL;
	pEventos = NULL;
	pJogador = NULL;
	pJogo = NULL;
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
	if (tecla == sf::Keyboard::P)
	{
		if (pJogo) 
		{
			pJogo->salvar();
		}
	}
	if (tecla == sf::Keyboard::L) {
		if (pJogo) {
			pJogo->solicitarCarregamento();
		}
	}
	if(tecla == sf::Keyboard::Escape)
	{
		if (pJogo) {
			Menu menuPause(pJogo);
			menuPause.executarTelaPause();
		}
		else {
			pGG->fechaJanela();
		}
	}
}

void Gerenciador_eventos::verificaTeclaSolta(sf::Keyboard::Key tecla)
{
	
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

void Gerenciador_eventos::setJogo(Jogo* p)
{
	this->pJogo = p;
}

bool Gerenciador_eventos::deveSairDaFase() 
{
	if (pJogo) 
	{
		return pJogo->deveVoltarMenu() || pJogo->deveCarregarSave();
	}
	return false;
}