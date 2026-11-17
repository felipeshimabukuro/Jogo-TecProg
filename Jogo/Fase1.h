#pragma once
#include "Fase.h"
#include "Terra.h"
#include "Magma.h"
#include "Topeira.h"

namespace Fases {
    class Fase1 : public Fase {
    protected:
        void criarObstaculos();
        void criarInimigos();
        void criarFundo();
        

    public:
        Fase1();
        ~Fase1();

        void executar();
    };
}