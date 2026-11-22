#pragma once
#include "Fase.h"
#include "Magma.h"
#include "Rato.h"

namespace Fases {
    class Caverna_Maldosa : public Fase {
    private:
        const int maxRato;
        int contRato;

    protected:

        //void criarObstaculos();
		void criarMagma(sf::Vector2f pos);

        //void criarInimigos();
        void criarRato(sf::Vector2f pos);

        void criarFundo();
        void criarEntidade(char tipo, sf::Vector2f pos);

    public:
        Caverna_Maldosa(bool save = 0);
        ~Caverna_Maldosa();

        void executar();
        void carregar();
    };
}