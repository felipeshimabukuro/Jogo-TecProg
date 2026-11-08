#include "Magma.h"

using namespace Entidades;
using namespace Personagens;

Magma::Magma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel):
	Obstaculo(x, y, largura, altura, dano, danoso, quebravel),
    ticks(0),max_ticks(60),dano(dano)
{
	inicializa();
}

Magma::~Magma() {

}

void Magma::inicializa() {
	corpo.setSize(sf::Vector2f(largura, altura));
	corpo.setFillColor(sf::Color::Yellow);

	corpo.setPosition(x, y);
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

void Magma::colisao(Entidade* ent, sf::Vector2f ds)
{
    if (ent == NULL || !ent->getAtivo())
        return;

    Personagens::Jogador* pJog = dynamic_cast<Personagens::Jogador*>(ent);
    if (pJog != NULL)
    {
        obstaculizar(pJog);
    }
}

void Magma::executar()
{

}
void Magma::salvar()
{
}