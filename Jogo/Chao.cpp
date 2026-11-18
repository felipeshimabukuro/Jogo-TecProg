#include "Chao.h"

using namespace Entidades;

Chao::Chao(const sf::Vector2f pos, const sf::Vector2f tam) :
    Entidade(pos.x, pos.y)
{
    x = pos.x;
    y = pos.y;

    corpo.setSize(tam);
    corpo.setPosition(pos);
    corpo.setFillColor(sf::Color(34, 139, 34));
}

Chao::~Chao()
{
}

void Chao::executar()
{
    corpo.setPosition(x, y);
}

void Chao::colisao(Entidade* ent, sf::Vector2f ds)
{
}

void Chao::salvar()
{
}

void Chao::desenhar(sf::RenderWindow* window)
{
    window->draw(corpo);
}