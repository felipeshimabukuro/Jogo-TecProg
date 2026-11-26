#pragma once
#include "Inimigo.h"
#include "Jogador.h"

namespace Escavadores_intrepidos {
    namespace Entidades {
        namespace Personagens
        {
            class Rato : public Inimigo
            {
            private:
                static const int dist_detec;
                static const int dist_atk;
                string estado;

            public:
                Rato(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j1, Jogador* j2);
                ~Rato();

                bool detectarJogador();
                void seguir();
                bool perto();
                void atualizaLado();
                void inicializa();
                void executar();
                void colisao(Entidade* ent, sf::Vector2f ds) override;
                void danificar(Jogador* p);
                //void mover();
                void salvarDataBuffer();
                void salvar();
                void setEstado(const string& est);
                string getArquivoSave() const;
            };
        }
    }
}