#include "Ente.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;

Gerenciador_grafico* Ente::pGG = Gerenciador_grafico::getGerenciadorGrafico();

int Ente::cont = 0;

Ente::Ente() : id(cont++)
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

const int Ente::getID() const
{
	return id;
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