//verificar os "executar" dos obstaculos

#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"
#include "Jogador.h"

namespace Escavadores_intrepidos {
    namespace Entidades {
        namespace Obstaculos {
            using namespace Personagens;
            class Obstaculo : public Entidade
            {
            protected:
                int largura;
                int altura;
                int dano;
                bool danoso;
                bool quebravel;

            public:
                Obstaculo(ID id, int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel);
                ~Obstaculo();
                virtual void executar() = 0;
                virtual void salvar() = 0;
                virtual void obstaculizar(Jogador* p) = 0;
                const int getLargura() const;
                const int getAltura() const;
                void darDano(Jogador* p);
                const bool getQuebravel() const;
                void salvarDataBuffer();
                void desGravitar();
            };
        }
    }
}
