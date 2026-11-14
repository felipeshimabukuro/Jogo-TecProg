#pragma once
#include "Bibliotecas.h"
#include "Ente.h"

namespace Gerenciadores
{
	class Gerenciador_grafico
	{
	private:
		sf::RenderWindow* window;
		map<string, sf::Texture> mapaTexturas;

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
		void desenharQuadrado(int x, int y);
		void mostrarJanela();

		bool carregarTextura(const std::string& id, const std::string& caminho);
		sf::Texture* getTextura(const std::string& id);

	};
}