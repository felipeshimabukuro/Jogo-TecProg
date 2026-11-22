#pragma once
#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Jogador.h"

class Menu;
class Jogo;
using namespace Personagens;

namespace Gerenciadores 
{
	class Gerenciador_eventos 
	{
	private:
		static Gerenciador_grafico* pGG;
		Jogador* pJogador1;
		Jogador* pJogador2;
		Jogo* pJogo;
		Menu* pMenu;
		//Singleton (ex-monitor Gege++)
		static Gerenciador_eventos* pEventos;
		Gerenciador_eventos();

	public:
		~Gerenciador_eventos();
		static Gerenciador_eventos* getGerenciadorEventos();
		void setJogador1(Jogador* pJ1);
		void setJogador2(Jogador* pJ2);
		void verificarTeclaPressionada(sf::Keyboard::Key tecla);
		void verificaTeclaSolta(sf::Keyboard::Key tecla);
		void executar();
		void setJogo(Jogo* p);
		bool getVoltarMenu();
		bool deveSairDaFase();
		void setMenu(Menu* pM);
	};
}