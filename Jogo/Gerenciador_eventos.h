#pragma once
#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Jogador.h"

class Jogo;
using namespace Personagens;

namespace Gerenciadores 
{
	class Gerenciador_eventos 
	{
	private:
		static Gerenciador_grafico* pGG;
		Jogador* pJogador;
		Jogo* pJogo;

		//Singleton (ex-monitor Gege++)
		static Gerenciador_eventos* pEventos;
		Gerenciador_eventos();

	public:
		~Gerenciador_eventos();
		static Gerenciador_eventos* getGerenciadorEventos();
		void setJogador(Jogador* pJogador);
		void verificarTeclaPressionada(sf::Keyboard::Key tecla);
		void verificaTeclaSolta(sf::Keyboard::Key tecla);
		void executar();
		void setJogo(Jogo* p);
		bool getVoltarMenu();
		bool deveSairDaFase();
	};
}