#pragma once
#include "Fase.h"
#include "Espinho.h"
#include "Ratao.h"

namespace Fases {
    class Limbo_da_perdicao : public Fase {
    private:
        const int maxRatao;
        int contRatao;
    
    protected:

        //void criarObstaculos();
		void criarEspinho(sf::Vector2f pos);

        //void criarInimigos();
        void criarRatao(sf::Vector2f pos);

        void criarFundo();
        void criarEntidade(char tipo, sf::Vector2f pos);

    public:
        Limbo_da_perdicao(bool save = 0);
        ~Limbo_da_perdicao();

        void executar();
        void carregar();
    };
}