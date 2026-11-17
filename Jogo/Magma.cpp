#include "Magma.h"

using namespace Entidades;
using namespace Personagens;

int Magma::ticks(0);

Magma::Magma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel):
	Obstaculo(x, y, largura, altura, dano, danoso, quebravel),
    max_ticks(60),dano(dano)
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
        sf::Vector2f posJog = p->getPos();
        if(p->getVelx() > 0)
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

    Personagens::Jogador* pJog = dynamic_cast<Personagens::Jogador*>(ent);
    if (pJog != NULL)
    {
        obstaculizar(pJog);
    }
}*/

void Magma::executar()
{
    corpo.setPosition(x, y);
    sprite.setPosition(x, y);
}
void Magma::salvar()
{
}