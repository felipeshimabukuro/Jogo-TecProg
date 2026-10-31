#include "Jogador.h"

using namespace Personagens;

int Jogador::pontos = 0;

Jogador::Jogador():Personagem(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)) {
    inicializa();
}

Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam, short int n) :Personagem(pos, tam),num(n){
    inicializa();
} 

Jogador::Jogador(const sf::RectangleShape corpo):Personagem(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)), corpo(corpo) {
    inicializa();
}

void Jogador::inicializa() { //tive q mudar pq tava dando mto b.o., nao rodava slk
    vel = sf::Vector2f(max_velx, max_vely);

    corpo.setSize(sf::Vector2f(50.0f, 50.0f)); 
    corpo.setFillColor(sf::Color::Green);      

    corpo.setPosition(x, y);
}

Jogador::~Jogador() {

}

sf::RectangleShape Jogador::getCorpo() {
    return corpo;
}

void Jogador::setPos(const sf::Vector2f pos) {
    x = pos.x;
    y = pos.y;
    corpo.setPosition(x, y);
}

/*void Jogador::colidir(Inimigo* pIn) {
	if (pIn) {
		if (pIn->getX() == x) {
			velx = -velx;
		}
		if (pIn->getY() == y) {
			vely = -vely;
		}
	}
}*/

void Jogador::executar() {
    
}

void Jogador::salvar() {

}

void Jogador::mover(int lado) {
    if (lado == -1)
    {
        x -= vel.x;
    }
    else if (lado == 1)
    {
        x += vel.x;
    }
    else if (lado == 3)
    {
		pular();
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

void Jogador::pular() 
{

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
