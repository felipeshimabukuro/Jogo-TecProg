#include "Ente.h"
#include "Gerenciador_grafico.h"

namespace Escavadores_intrepidos {

    using namespace Gerenciadores;

    Gerenciador_grafico* Ente::pGG = Gerenciador_grafico::getGerenciadorGrafico();

    Ente::Ente()
    {
    }

    Ente::~Ente()
    {
    }

    void Ente::desenhar(sf::RenderWindow* window) {
        if (sprite.getTexture() != NULL) {
            window->draw(sprite);
        }
        else {
            sf::RectangleShape falha(sf::Vector2f(30.0f, 30.0f));
            falha.setFillColor(sf::Color::Red);
            window->draw(falha);
        }
    }

    void Ente::setTextura(const string& idTextura, const sf::Vector2f& tam) {
        if (pGG) {
            sf::Texture* tex = pGG->getTextura(idTextura);
            if (tex) {
                sprite.setTexture(*tex);
                if (tam.x > 0.0f && tam.y > 0.0f) {
                    sf::Vector2u tamTex = tex->getSize();
                    sprite.setScale(
                        tam.x / (float)tamTex.x,
                        tam.y / (float)tamTex.y
                    );
                }
            }
        }
    }

    const void Ente::setGG(Gerenciador_grafico* GG) const
    {
        pGG = GG;
    }
}