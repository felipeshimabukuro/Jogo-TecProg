#pragma once
#include "Bibliotecas.h"
#include "Jogador.h"
#include "Obstaculo.h"
#include "Inimigo.h"
#include "Projetil.h"
#include "ListaEntidade.h"
#include "Chao.h"


namespace Escavadores_intrepidos {
	namespace Gerenciadores
	{
		using namespace Listas;
		using namespace Entidades;
		using namespace Personagens;
		using namespace Obstaculos;

		class Gerenciador_colisao
		{
		private:
			vector<Inimigo*> LIs;
			list<Obstaculo*> LOs;
			set<Projetil*> LPs;
			Jogador* pJog1;
			Jogador* pJog2;
			ListaEntidade* LE;
			Chao* pChao;

			// Singleton
			static Gerenciador_colisao* pColisao;
			Gerenciador_colisao();

			//Jogador = Jogs
			//Verificar UML e mudar nome funções
			//Tirar autos
			//Usar verificarColisao

			void tratarColisaoJogadorInimigo();
			void tratarColisaoJogadorObstaculo();
			void tratarColisaoJogadorProjetil();
			void tratarColisaoInimigoObstaculo();
			void tratarColisaoProjetilObstaculo();
			void tratarColisaoChao();
			const sf::Vector2f calcularColisao(Entidade* ent1, Entidade* ent2);
			const sf::Vector2f calcularColisao(const sf::Vector2f pos1, const sf::Vector2f tam1, const sf::Vector2f pos2, const sf::Vector2f tam2);

		public:
			~Gerenciador_colisao();
			static Gerenciador_colisao* getGerenciadorColisao();
			void setJogador1(Jogador* pJ1);
			void setJogador2(Jogador* pJ2);
			void setListaEntidade(ListaEntidade* pLE);
			void adicionarInimigo(Inimigo* pi);
			void removerInimigo(Inimigo* pi);
			void adicionarObstaculo(Obstaculo* po);
			void removerObstaculo(Obstaculo* po);
			void adicionarProjetil(Projetil* pj);
			void removerProjetil(Projetil* pj);
			bool posicaoLivre(sf::Vector2f pos, sf::Vector2f tam);
			//const bool verificaColisao(Entidade* pe1, Entidade* pe2) const;
			void executar();
			void limparDestruidos();
			void tratarTiro();
			void setChao(Chao* chao);
			void limpar();
		};
	}
}
