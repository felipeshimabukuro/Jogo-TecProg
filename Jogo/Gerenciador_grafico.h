#pragma once
#include "Bibliotecas.h"
#include "Ente.h"

namespace Escavadores_intrepidos {
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
			void desenharEnte(Ente* pE);
			void mostrarJanela();

			bool carregarTextura(const string& id, const string& caminho);
			sf::Texture* getTextura(const string& id);
			//verificar se dá p remover getTextura
		};
	}
}