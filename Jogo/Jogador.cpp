#include "Jogador.h"
#include "Obstaculo.h"
#include "Terra.h"

using namespace Personagens;

int Jogador::pontos = 0;

Jogador::Jogador() :Personagem(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)), inventario(0) {
    inicializa();
}

Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam, short int n) :Personagem(pos, tam), num(n), inventario(0) {
    inicializa();
}

Jogador::Jogador(const sf::RectangleShape corpo) :Personagem(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)), inventario(0) {
    inicializa();
}

void Jogador::inicializa() { //tive q mudar pq tava dando mto b.o., nao rodava slk
    chaoAtual = NULL;
    acaoPressionada = false;
	num_vidas = 100;

    vel = sf::Vector2f(max_velx, max_vely);

    corpo.setSize(sf::Vector2f(50.0f, 50.0f)); 
    corpo.setFillColor(sf::Color::Green);      

    corpo.setPosition(x, y);
}

Jogador::~Jogador() {

}

void Jogador::setPos(const sf::Vector2f pos) {
    x = pos.x;
    y = pos.y;
    corpo.setPosition(x, y);
}

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

void Jogador::cavar() {
    if (chaoAtual == NULL) {
        return;
    }
    Entidades::Obstaculo* chaoAt = dynamic_cast<Entidades::Obstaculo*>(chaoAtual);
    if (chao == true && chaoAt != NULL && chaoAt->getQuebravel() == true) {
        chaoAt->setAtivo(false);

        chaoAtual = NULL;
        chao = false;
        inventario++;
    }
}

void Jogador::receberDano(int dano) {
    num_vidas -= dano;
	cout << "Jogador tomou " << dano << " de dano. Vidas restantes: " << num_vidas << endl;
}

void Jogador::colisao(Entidade* ent, sf::Vector2f ds) {
    if (ent == NULL || !ent->getAtivo()) {
        return;
    }

    Entidades::Entidade::colisao(ent, ds);
    
    if (ds.x <= ds.y) {

        if (getY() < ent->getY()) {
            vely = 0.0f;
            chao = true;

            Entidades::Obstaculo* bloco = dynamic_cast<Entidades::Obstaculo*>(ent);

            if (bloco && bloco->getAtivo()) {
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

/*void Jogador::colisao(Entidade* ent, sf::Vector2f ds) {
    if (ent == NULL || !ent->getAtivo()) {
        return;
    }

    Entidades::Obstaculo* bloco = dynamic_cast<Entidades::Obstaculo*>(ent);

    if (bloco != NULL) {
        Entidades::Entidade::colisao(ent, ds);

        if (ds.x <= ds.y) {
            if (getY() < ent->getY()) {
                vely = 0.0f;
                chao = true;
                chaoAtual = bloco;
            }
            else {
                vely = -vely;
            }
        }
    }
    else {
        Entidades::Entidade::colisao(ent, ds);
    }
}*/

void Jogador::place() {
    if (inventario > 0) {
        /*float posX = x;
        float posY = y + getTam().y + 2.0f;
        */
        Entidades::Obstaculo* novoBloco = new Entidades::Terra(
            x,
            y + getTam().y,
            50.0f, 50.0f,
            0, false, true);

        blocosPendentes.push_back(novoBloco);

        inventario--;
    }
}

std::list<Entidades::Obstaculo*>* Jogador::getBlocosPendentes() {
    return &blocosPendentes;
}

void Jogador::addInventario() {
    inventario++;
}