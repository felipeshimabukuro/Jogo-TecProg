#pragma once

#include "Ente.h"

#include "Gerenciador_colisao.h"
#include "Gerenciador_eventos.h"
#include "ListaEntidade.h"

#include "Chao.h"
#include "Plataforma.h"
#include "Topeira.h"

using namespace Gerenciadores;

namespace Fases {
	class Fase : public Ente {
	protected:
		const int maxTopeiras;
		int contTopeiras;

		ListaEntidade lista_ents;
		Gerenciador_colisao* pGC;
		Gerenciador_eventos* pEv;
		Gerenciador_grafico* pGG;
		Jogador* pJogador1;
		ifstream tilemap;
		
		void blocosColocados();
		void criarCenario();
		virtual void criarEntidade(char tipo, sf::Vector2f pos) = 0;

		virtual void criarFundo() = 0;
		//virtual void criarObstaculos(sf::Vector2f pos) = 0;
		//virtual void criarInimigos(sf::Vector2f pos) = 0;

		void criarChao(sf::Vector2f pos);
		void criarTopeira(sf::Vector2f pos);
		void posJogador(sf::Vector2f pos);
		void criarPlataforma(sf::Vector2f pos);

	public:
		Fase();
		~Fase();

		void salvar();
		virtual void executar() = 0;
	};
}
