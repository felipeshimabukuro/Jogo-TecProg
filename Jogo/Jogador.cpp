#include "Jogador.h"
#include "Obstaculo.h"

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
    chaoAtual = NULL;
    acaoPressionada = false;

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
    mover();
}

void Jogador::salvar() {

}

int Jogador::getNum(){
    return num;
}
void Jogador::mover() {
    vely += gravidade;
    y += vely;
    if (num == 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            x -= max_velx;

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            x += max_velx;

       
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            pular();
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (!acaoPressionada) {
                if (chao) {
                    cavar();
                }
                else {
                    place();
                }
                acaoPressionada = true;
            }
        }
        else {
            acaoPressionada = false;
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            x -= max_velx;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            x -= max_velx;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pular();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (!acaoPressionada) {
                if (chao) {
                    cavar();
                }
                else {
                    place();
                }
                acaoPressionada = true;
            }
        }
        else {
            acaoPressionada = false;
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
    
    /*if (y > 600.0f - 50.0f) {
        y = 600.0f - 50.0f;
    }*/

    corpo.setPosition(x, y);
}

void Jogador::pular() 
{
    if (chao == true) {
        vely = -20*gravidade;
        chao = false;  
    }
}

//void idle() {

//}

void Jogador::cavar() {
    if (chaoAtual == NULL) {
        return;
    }
    Entidades::Obstaculo* chaoAt = dynamic_cast<Entidades::Obstaculo*>(chaoAtual);
    if (chao == true && chaoAt != NULL && chaoAt->getQuebravel() == true) {
        inventario.push_back(chaoAt);
        chaoAtual->setPos(sf::Vector2f(-10000.0f, 10000.0f));

        chao = false; 
        chaoAtual = NULL; 
    }
}

void Jogador::place() {
    if (!inventario.empty()) {
        Entidades::Obstaculo* novoBloco = inventario.back();
        inventario.pop_back();

        novoBloco->setPos(sf::Vector2f(x, y + 50.0f));

        vely = 0.0f;
        chao = true;

        chaoAtual = novoBloco;
    }
}

void Jogador::receberDano(int dano) {
    num_vidas -= dano;
}

void Jogador::colisao(Entidade* ent, sf::Vector2f ds) {
    
    Entidades::Entidade::colisao(ent, ds);

    
    if (ds.x <= ds.y) {

        if (getY() < ent->getY()) {
            vely = 0.0f;
            chao = true;

            Entidades::Obstaculo* bloco = dynamic_cast<Entidades::Obstaculo*>(ent);

            if (bloco) {
                chaoAtual = bloco;
            }
            else {
                chaoAtual = NULL;
            }
        }
        else {
            vely = -vely;
        }
    }
}