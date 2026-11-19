#pragma once
#include "Fase.h"
#include "Magma.h"
#include "Topeira.h"
#include "Chao.h"
#include "Espinho.h"

namespace Fases {
    class Caverna_Maldosa : public Fase {
    protected:

        //void criarObstaculos();
		void criarMagma(sf::Vector2f pos);

        //void criarInimigos();
        void criarFundo();
        void criarEntidade(char tipo, sf::Vector2f pos);

    public:
        Caverna_Maldosa();
        ~Caverna_Maldosa();

        void executar();
    };
}