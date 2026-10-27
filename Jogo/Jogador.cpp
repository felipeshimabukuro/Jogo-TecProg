#include "Jogador.h"

int Jogador::pontos = 0;

Jogador::Jogador() {
    inicializa();
}

Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
    :Personagem(pos.x, pos.y),num(0){
    inicializa();
} 

Jogador::Jogador(const sf::RectangleShape corpo):corpo(corpo) {
    inicializa();
}

void Jogador::inicializa() {
    vel = sf::Vector2f(5.0f,5.0f);
}

Jogador::~Jogador() {

}

const sf::RectangleShape Jogador::getCorpo() {
    return corpo;
}

void Jogador::colidir(Inimigo* pIn) {
	if (pIn) {
		if (pIn->getX() == x) {
			velx = -velx;
		}
		if (pIn->getY() == y) {
			vely = -vely;
		}
	}
}

void Jogador::executar() {

}

void Jogador::salvar() {

}

void Jogador::mover() {
    if (!num)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            corpo.move(-vel.x, 0.0f);
            x -= vel.x;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            corpo.move(vel.x, 0.0f);
            x += vel.x;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            corpo.move(0.0f, vel.y);
            y += vel.y;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            corpo.move(0.0f, -vel.y);
            y -= vel.y;
        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            corpo.move(-vel.x, 0.0f);
            x -= vel.x;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            corpo.move(vel.x, 0.0f);
            x += vel.x;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            corpo.move(0.0f, vel.y);
            y += vel.y;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            corpo.move(0.0f, -vel.y);
            y -= vel.y;
        }
    }
    if (x < 0.0f) {
        x = 0.0f;
    }
   
    if (y < 0.0f) {
        y = 0.0f;
    }
   
    if (x > 800.0f - 50.0f) {
        x = 800.0f - 50.0f;
    }
    
    if (y > 600.0f - 50.0f) {
        y = 600.0f - 50.0f;
    }

    corpo.setPosition(x, y);
}

//void idle() {

//}

//void dig() {

//}

//void place() {

//}

void Jogador::receberDano(int dano) {
    num_vidas -= dano;
}