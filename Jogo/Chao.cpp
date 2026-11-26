#include "Chao.h"
#include "Jogador.h"

namespace Escavadores_intrepidos {
    namespace Entidades {
        using namespace Personagens;

        Chao::Chao(const sf::Vector2f pos, const sf::Vector2f tam) :
            Entidade(pos.x, pos.y), max_ticks(45), ticks(0), curar(false)
        {
            x = pos.x;
            y = pos.y;

            corpo.setSize(tam);
            corpo.setPosition(pos);

            setTextura("chao", getTam());
            sprite.setPosition(x, y);
        }

        Chao::~Chao()
        {
        }

        void Chao::executar()
        {
            aplicarGravidade();
            desGravitar();
            
            if (!curar)
            {
                if (ticks < max_ticks)
                {
                    ticks++;
                }
                else if (ticks == max_ticks)
                {
                    curar = true;
                }
            }
        }

        void Chao::ajudar(Jogador* p) 
        {
            if(p) p->operator++();
            curar = false;
            ticks = 0;
        }

        void Chao::salvarDataBuffer()
        {
            Entidade::salvarDataBuffer();
            buffer << ticks;
        }

        void Chao::salvar()
        {
            buffer.str("");
            buffer.clear();

            salvarDataBuffer();
        }

        void Chao::setTicks(const int t)
        {
            ticks = t;
        }

        string Chao::getArquivoSave() const
        {
            return "saves/chaoSave.txt";
        }

        void Chao::desGravitar()
        {
            y -= vely;
            vely = 0.0f;
            setPos(sf::Vector2f(x, y));
        }

        const bool Chao::getCurar() const
        {
            return curar;
        }
    }
}