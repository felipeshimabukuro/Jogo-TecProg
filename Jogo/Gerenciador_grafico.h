#pragma once
#include "Bibliotecas.h"
#include "Ente.h"

namespace Gerenciadores
{
	class Gerenciador_grafico
	{
	private:
		sf::RenderWindow* window;

		//Padrão Singleton (canal ex-monitor Gege++)
		static Gerenciador_grafico* pGrafico;
		Gerenciador_grafico();

	public:
		~Gerenciador_grafico();
		static Gerenciador_grafico* getGerenciadorGrafico();
		sf::RenderWindow* getWindow();
		void limpaJanela();
		void fechaJanela();
		const bool verificaJanelaAberta();
		//void desenharEnte(Ente* pE);
		void desenharQuadrado();
		void mostrarJanela();

	};
}