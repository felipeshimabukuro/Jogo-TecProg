#include "Jogador.h"

int Jogador::pontos = 0;

Jogador::Jogador(int xx, int yy, short int n):Personagem(xx, yy),t_coyote(10), num(n)
,pulo_coyote(10),invent(0),t_dano(10){

} 
Jogador::~Jogador() {

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
    velx = 0;
    vely = 0;

    if (!num)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velx = -max_velx;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velx = max_velx;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            vely = -max_vely;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            vely = max_vely;
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velx = -max_velx;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velx = max_velx;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            vely = max_vely;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            vely = -max_vely;
    }

    mover();
}

void Jogador::salvar() {

}

void Jogador::mover() {
    x += velx * 0.016f;
    y += vely * 0.016f;
}

void idle() {

}

void dig() {

}

void place() {

}

void Jogador::receberDano(int dano) {
    num_vidas -= dano;
}