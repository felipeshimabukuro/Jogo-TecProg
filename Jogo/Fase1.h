#pragma once
#include "Fase.h"
#include "Terra.h"

namespace Fases {
    class Fase1 : public Fase {
    protected:
        void criarCenario();
        void criarObstaculos();
        void criarInimigos();

    public:
        Fase1();
        ~Fase1();

        void executar();
    };
}