#include "Bibliotecas.h"
#include "Obstaculo.h"

using namespace Entidades;

Obstaculo::Obstaculo(int x, int y, int larg, int alt, int dano, bool danoso, bool queb): 
    Entidade(x, y), 
    largura(larg), 
    altura(alt), 
    dano(dano), 
    danoso(danoso), 
    quebravel(queb)
{
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