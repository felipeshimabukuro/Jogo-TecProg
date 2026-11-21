#pragma once
#include "Entidade.h"

namespace Personagens {
    class Jogador;
}

namespace Entidades
{
    class Chao : public Entidade
    {
    private:
        int ticks;
        const int max_ticks;
    public:
        Chao(const sf::Vector2f pos, const sf::Vector2f tam);
        ~Chao();

        void executar();
        void colisao(Entidade* ent, sf::Vector2f ds);
        void salvarDataBuffer();
        void salvar();
        void desenhar(sf::RenderWindow* window);
        void ajudar(Personagens::Jogador* p);
    };
}