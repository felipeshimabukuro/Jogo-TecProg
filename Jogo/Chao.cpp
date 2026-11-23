#include "Chao.h"
#include "Jogador.h"

using namespace Entidades;

Chao::Chao(const sf::Vector2f pos, const sf::Vector2f tam) :
    Entidade(ID::chao, pos.x, pos.y), max_ticks(60), ticks(0)
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
    corpo.setPosition(x, y);
    sprite.setPosition(x, y);
}

void Chao::colisao(Entidade* ent, sf::Vector2f ds)
{
}

void Chao::ajudar(Personagens::Jogador* p) {
    ticks++;
    if (ticks == 60) {
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