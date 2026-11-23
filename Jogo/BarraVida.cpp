#include "BarraVida.h"

using namespace Personagens;

BarraVida::BarraVida(const int vidasMax) :
    num_vidas(vidasMax),
    max_vidas(vidasMax > 0 ? vidasMax : 1)
{
    barraFundo.setFillColor(sf::Color(40, 40, 40, 200));
    barraFundo.setOutlineThickness(1.0f);
    barraFundo.setOutlineColor(sf::Color::Black);

    barraVida.setFillColor(sf::Color(50, 205, 50));
}

BarraVida::~BarraVida()
{
}

void BarraVida::inicializarVida(const int vidasMax)
{
    max_vidas = (vidasMax > 0) ? vidasMax : 1;
    num_vidas = max_vidas;
}

void BarraVida::desenharBarra(sf::RenderWindow* window, const float x, const float y, const float largura)
{
    if (!window) return;

    float larguraBarra = (largura > 0.0f) ? largura : 50.0f;
    float alturaBarra = 6.0f;
    float offsetY = 10.0f; // Distância acima da cabeça da entidade

    float proporcao = static_cast<float>(num_vidas) / static_cast<float>(max_vidas);
    if (proporcao < 0.0f) proporcao = 0.0f;
    if (proporcao > 1.0f) proporcao = 1.0f;

    barraFundo.setSize(sf::Vector2f(larguraBarra, alturaBarra));
    barraVida.setSize(sf::Vector2f(larguraBarra * proporcao, alturaBarra));

    barraFundo.setPosition(x, y - offsetY);
    barraVida.setPosition(x, y - offsetY);

    // Muda a cor conforme a porcentagem de vida restante
    if (proporcao > 0.5f) {
        barraVida.setFillColor(sf::Color(50, 205, 50));   // Verde
    }
    else if (proporcao > 0.25f) {
        barraVida.setFillColor(sf::Color(255, 200, 0));   // Amarelo
    }
    else {
        barraVida.setFillColor(sf::Color(220, 40, 40));   // Vermelho
    }

    window->draw(barraFundo);
    window->draw(barraVida);
}

void BarraVida::setNumVidas(const int vidas)
{
    num_vidas = vidas;
}

const int BarraVida::getNumVidas() const
{
    return num_vidas;
}

const int BarraVida::getMaxVidas() const
{
    return max_vidas;
}