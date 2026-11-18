#pragma once
#include "Entidade.h"

namespace Entidades
{
    class Chao : public Entidade
    {
    public:
        Chao(const sf::Vector2f pos, const sf::Vector2f tam);
        ~Chao();

        void executar();
        void colisao(Entidade* ent, sf::Vector2f ds);
        void salvar();
        void desenhar(sf::RenderWindow* window);
    };
}