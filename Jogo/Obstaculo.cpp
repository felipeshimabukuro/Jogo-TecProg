#include "Bibliotecas.h"
#include "Obstaculo.h"

using namespace Entidades;
using namespace Personagens;

Obstaculo::Obstaculo(int x, int y, int larg, int alt, int dano, bool danoso, bool queb): 
    Entidade(x, y), 
    largura(larg), 
    altura(alt), 
    dano(dano), 
    danoso(danoso), 
    quebravel(queb)
{
    corpo.setSize(sf::Vector2f((float)largura, (float)altura));
    corpo.setPosition((float)x, (float)y);
}

Obstaculo::~Obstaculo()
{
}

const int Obstaculo::getLargura() const
{
    return largura;
}

const int Obstaculo::getAltura() const
{
    return altura;
}

void Obstaculo::darDano(Jogador* p)
{
    if(p && danoso)
    {
        p->receberDano(dano);
    }
}

const bool Obstaculo::getQuebravel() const
{
	return quebravel;
}

void Obstaculo::colisao(Entidade* ent, sf::Vector2f ds) {

}