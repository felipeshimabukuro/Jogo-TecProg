#pragma once
#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Jogador.h"

namespace Escavadores_intrepidos {
	class Menu;
	class Jogo;

	namespace Gerenciadores
	{
		using namespace Entidades;
		using namespace Personagens;
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
			void executar();
			void setJogo(Jogo* p);
			bool deveSairDaFase();
			void setMenu(Menu* pM);
		};
	}
}