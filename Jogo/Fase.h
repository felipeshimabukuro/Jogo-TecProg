#pragma once

#include "Ente.h"

#include "Gerenciador_colisao.h"
#include "Gerenciador_eventos.h"
#include "ListaEntidade.h"

#include "Chao.h"
#include "Plataforma.h"
#include "Topeira.h"


namespace Escavadores_intrepidos {
	namespace Fases {

		using namespace Gerenciadores;
		using namespace Listas;
		using namespace Entidades;
		using namespace Obstaculos;
		using namespace Personagens;

		class Fase : public Ente {
		protected:
			const int maxTopeiras;
			int contTopeiras;
			const int maxPlataformas;
			int contPlataformas;

			ListaEntidade lista_ents;
			Gerenciador_colisao* pGC;
			Gerenciador_eventos* pEv;
			Jogador* pJogador1;
			Jogador* pJogador2;
			ifstream tilemap;

			bool faseConcluida;
			bool venceu;
			int numJogadores;
			sf::Text textoFimDeFase;
			sf::Font fonteTexto;

			void blocosColocados();
			void criarCenario();
			virtual void criarEntidade(char tipo, sf::Vector2f pos) = 0;

			virtual void criarFundo() = 0;

			void criarChao(sf::Vector2f pos);
			void criarTopeira(sf::Vector2f pos);
			void posJogador(sf::Vector2f pos);
			void criarPlataforma(sf::Vector2f pos);

		public:
			Fase(int numJogadores, Jogador* pJ1, Jogador* pJ2);
			~Fase();

			const bool getVenceu() const;
			const int getNumJogadores() const;
			void salvar();
			virtual void carregar() = 0;
			virtual void executar();
		};
	}
}
