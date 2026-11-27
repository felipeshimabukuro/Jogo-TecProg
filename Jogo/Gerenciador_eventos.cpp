#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Gerenciador_eventos.h"
#include "Jogador.h"
#include "Jogo.h"
#include "Menu.h"

namespace Escavadores_intrepidos {
	namespace Gerenciadores {

		Gerenciador_eventos* Gerenciador_eventos::pEventos = NULL;
		Gerenciador_grafico* Gerenciador_eventos::pGG = Gerenciador_grafico::getGerenciadorGrafico();

		Gerenciador_eventos::Gerenciador_eventos() :
			pJogador1(NULL),
			pJogador2(NULL),
			pJogo(NULL),
			pMenu(NULL)
		{
		}

		Gerenciador_eventos::~Gerenciador_eventos()
		{
			pGG = NULL;
			pEventos = NULL;
			pJogador1 = NULL;
			pJogador2 = NULL;
			pJogo = NULL;
			pMenu = NULL;
		}

		Gerenciador_eventos* Gerenciador_eventos::getGerenciadorEventos()
		{
			if (!pEventos)
			{
				pEventos = new Gerenciador_eventos();
			}
			return pEventos;
		}

		void Gerenciador_eventos::setJogador1(Jogador* pJ1)
		{
			pJogador1 = pJ1;
		}

		void Gerenciador_eventos::setJogador2(Jogador* pJ2)
		{
			pJogador2 = pJ2;
		}

		void Gerenciador_eventos::verificarTeclaPressionada(sf::Keyboard::Key tecla)
		{
			//Menu
			if (pMenu) {
				if (tecla == sf::Keyboard::Up) {
					pMenu->moverCima();
				}
				else if (tecla == sf::Keyboard::Down) {
					pMenu->moverBaixo();
				}
				else if (tecla == sf::Keyboard::Enter) {
					pMenu->interagir();
				}
				return;
			}

			//jogador
			if (pJogador1) {
				if (tecla == sf::Keyboard::A || tecla == sf::Keyboard::S || tecla == sf::Keyboard::D || tecla == sf::Keyboard::W) {
					pJogador1->executar();
				}
			}

			//jogador 2
			if (pJogador2) {
				if (tecla == sf::Keyboard::Up || tecla == sf::Keyboard::Right || tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Down) {
					pJogador2->executar();
				}
			}

			if (tecla == sf::Keyboard::L) {
				if (pJogo) {
					pJogo->solicitarCarregamento();
				}
			}

			if (tecla == sf::Keyboard::Escape)
			{
				if (pJogo) {
					pJogo->pausar();
				}
				else {
					pGG->fechaJanela();
				}
			}
		}

		void Gerenciador_eventos::executar()
		{
			sf::Event evento;
			while (pGG->getWindow()->pollEvent(evento))
			{
				if (evento.type == sf::Event::KeyPressed)
				{
					verificarTeclaPressionada(evento.key.code);
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

		void Gerenciador_eventos::setMenu(Menu* pM) {
			pMenu = pM;
		}
	}
}