#include "Chao.h"
#include "Jogador.h"

namespace Escavadores_intrepidos {
    namespace Entidades {
        using namespace Personagens;

        Chao::Chao(const sf::Vector2f pos, const sf::Vector2f tam) :
            Entidade(pos.x, pos.y), max_ticks(60), ticks(0)
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
        }

        void Chao::colisao(Entidade* ent, sf::Vector2f ds)
        {
        }

        void Chao::ajudar(Jogador* p) {
            ticks++;
            if (ticks == max_ticks) {
                ticks = 0;
                p->operator++();
            }
        }

        void Chao::salvarDataBuffer()
        {
            Entidade::salvarDataBuffer();
            buffer << ticks;
        }

        void Chao::salvar()
        {
            buffer.str(""); // Limpa dados de saves anteriores no buffer
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
    }
}