#pragma once
#include "Entidade.h"

namespace Escavadores_intrepidos
{
    namespace Entidades {

        namespace Personagens {
            class Jogador;
        }
        using namespace Personagens;
        class Chao : public Entidade
        {
        private:
            int ticks;
            const int max_ticks;
            bool curar;

        public:
            Chao(const sf::Vector2f pos, const sf::Vector2f tam);
            ~Chao();

            void executar();
            void salvarDataBuffer();
            void salvar();
            void ajudar(Jogador* p);
            void setTicks(const int t);
            string getArquivoSave() const;
            void desGravitar();
            const bool getCurar() const;
        };
    }
}