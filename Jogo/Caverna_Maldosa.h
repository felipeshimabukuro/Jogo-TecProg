#pragma once
#include "Fase.h"
#include "Plataforma.h"
#include "Magma.h"
#include "Topeira.h"
#include "Chao.h"

namespace Fases {
    class Caverna_Maldosa : public Fase {
    protected:
        void criarObstaculos();
        void criarInimigos();
        void criarFundo();
        

    public:
        Caverna_Maldosa();
        ~Caverna_Maldosa();

        void executar();
    };
}