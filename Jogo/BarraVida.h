#pragma once
#include "Bibliotecas.h"

namespace Escavadores_intrepidos {
    namespace Entidades {
        namespace Personagens {

            class BarraVida {
            protected:
                int num_vidas;
                int max_vidas;

                sf::RectangleShape barraFundo;
                sf::RectangleShape barraVida;

                void inicializarVida(const int vidasMax);
                void desenharBarra(sf::RenderWindow* window, const float x, const float y, const float largura);

            public:
                BarraVida(const int vidasMax = 100);
                virtual ~BarraVida();

                void setNumVidas(const int vidas);
                const int getNumVidas() const;
                const int getMaxVidas() const;
            };

        }
    }
}