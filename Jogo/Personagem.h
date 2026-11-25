#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Personagens {
			class Personagem : public Entidade, public BarraVida {
			protected:
				float velx;
				const float max_velx;
				bool chao;
				int dano;
				sf::Vector2f vel;

			public:
				Personagem(ID id, const sf::Vector2f pos, const sf::Vector2f tam);
				virtual ~Personagem();
				virtual void desenhar(sf::RenderWindow* window);
				void salvarDataBuffer();
				virtual void mover() = 0;
				virtual void salvar() = 0;
				virtual void executar() = 0;
				virtual void receberDano(int dano) = 0;
				const float getVely() const;
				const float getVelx() const;
				int getDano() const;
				void setVel(const sf::Vector2f v);
			};

		}
	}
}