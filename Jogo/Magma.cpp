#include "Magma.h"

namespace Escavadores_intrepidos {
    namespace Entidades {
        namespace Obstaculos {
            using namespace Personagens;

            int Magma::ticks(0);

            Magma::Magma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel) :
                Obstaculo(x, y, largura, altura, dano, danoso, quebravel),
                max_ticks(60), dano(dano)
            {
                inicializa();
            }

            Magma::~Magma() {

            }

            void Magma::inicializa() {
                setTextura("magma", sf::Vector2f(largura, altura));
                corpo.setPosition(x, y);
                sprite.setPosition(x, y);
            }

            void Magma::obstaculizar(Jogador* p)
            {
                if (p != NULL)
                {
                    if (!danoso) return;
                    sf::Vector2f posJog = p->getPos();
                    if (p->getVelx() > 0)
                    {
                        p->setPos(sf::Vector2f(posJog.x - 3.0f, posJog.y));
                    }
                    else if (p->getVelx() < 0) {
                        p->setPos(sf::Vector2f(posJog.x + 3.0f, posJog.y));
                    }
                    else {
                        p->setPos(sf::Vector2f(posJog.x, posJog.y));
                    }
                    ticks++;
                    if (ticks >= max_ticks)
                    {
                        p->receberDano(dano);
                        ticks = 0;
                    }
                }
            }

            /*void Magma::colisao(Entidade* ent, sf::Vector2f ds)
            {
                if (ent == NULL || !ent->getAtivo())
                    return;

                Jogador* pJog = dynamic_cast<Jogador*>(ent);
                if (pJog != NULL)
                {
                    obstaculizar(pJog);
                }
            }*/

            void Magma::executar()
            {
                aplicarGravidade();
                desGravitar();
                if (!rand() % 200) {
                    danoso = false;
                    dano = 0;
                    sprite.setColor(sf::Color::Green);
                }
            }
            void Magma::salvar()
            {
                buffer.str("");
                buffer.clear();
                salvarDataBuffer();
            }

            void Magma::salvarDataBuffer()
            {
                Obstaculo::salvarDataBuffer();
            }

            void Magma::setTicks(const int t)
            {
                ticks = t;
            }

            string Magma::getArquivoSave() const
            {
                return "saves/magmaSave.txt";
            }
        }
    }
}