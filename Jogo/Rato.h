#pragma once
#include "Inimigo.h"
#include "Jogador.h"

namespace Personagens
{
    class Rato : public Inimigo
    {
    private:
        static const int dist_detec;
        static const int dist_atk;
        string estado;
    public:
        Rato(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j);
        ~Rato();

        bool detectarJogador();
        void seguir();
        bool perto();
        void atualizaLado();
        void inicializa();
        void executar();
        void colisao(Entidades::Entidade* ent, sf::Vector2f ds) override;
        void danificar(Jogador* p);
       //void mover();
    };
}