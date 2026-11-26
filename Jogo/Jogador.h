#pragma once
#include "Personagem.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Obstaculos {
			class Obstaculo;
		}
		using namespace Obstaculos;
		namespace Personagens
		{
			class Inimigo;

			class Jogador : public Personagem {
			private:
				bool acaoPressionada;
				short int num;
				static int pontos;
				int inventario;
				int t_dano;
				static const int t_imune = 60;
				Entidade* chaoAtual;
				void inicializa();
				list<Obstaculo*> blocosPendentes;

			public:
				Jogador(const sf::Vector2f pos, const sf::Vector2f tam, short int n);
				Jogador(const sf::RectangleShape corpo);
				Jogador();
				~Jogador();
				void colisao(Entidade* ent, sf::Vector2f ds);
				void executar();
				void salvar();
				void mover();
				void pular();
				const int getNum() const;
				void cavar();
				void place();
				void receberDano(int dano);
				list<Obstaculo*>* getBlocosPendentes();
				void addInventario();
				void setChao(bool c);
				void operator++();
				void colidir(Inimigo* pIn);
				void removerInventario();
				void resetarChao();
				const bool getImune() const;
				void salvarDataBuffer();
				void setInventario(const int inv);
				void setTDano(const int td);
				static int getPontos();
				static void setPontos(int p);
				string getArquivoSave() const;
			};
		}
	}
}
