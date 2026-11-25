#include "Jogador.h"
#include "Obstaculo.h"
#include "Plataforma.h"
#include "Inimigo.h"

using namespace Personagens;

int Jogador::pontos = 0;

Jogador::Jogador() :Personagem(ID::jogador, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)), inventario(0){
    inicializa();
}

Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam, short int n) :Personagem(ID::jogador, pos, tam), num(n), inventario(0) {
    inicializa();
}

Jogador::Jogador(const sf::RectangleShape corpo) :Personagem(ID::jogador, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)), inventario(0) {
    inicializa();
}

void Jogador::inicializa() { //tive q mudar pq tava dando mto b.o., nao rodava slk
    chaoAtual = NULL;
    acaoPressionada = false;
    inicializarVida(100);
    dano = 5;

    vel = sf::Vector2f(max_velx, max_vely);

    corpo.setSize(sf::Vector2f(GRID, GRID));
    corpo.setPosition(x, y);

    if(num == 0) setTextura("jogador1", sf::Vector2f(GRID, GRID));
    else setTextura("jogador2", sf::Vector2f(GRID, GRID));
}

Jogador::~Jogador() {

}

void Jogador::executar() 
{
    mover();

    if (t_dano >= 0)
    {
        t_dano--;
        sprite.setColor(sf::Color(255, 255, 255, 179));
    }
    else
    {
        sprite.setColor(sf::Color(255, 255, 255, 255));
    }
        
}

const int Jogador::getNum()const{
    return num;
}
void Jogador::mover() 
{
    aplicarGravidade();
    velx = 0;
    if (num == 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velx = -max_velx;
            x += velx;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velx = max_velx;
            x += velx;
        }
       
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velx = -max_velx;
            x += velx;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velx = max_velx;
            x += velx;
        }

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
   
    if (x > WIDTH - corpo.getSize().x) {
        x = WIDTH - 50.0f;
    }
    
    /*if (y > 600.0f - 50.0f) {
        y = 600.0f - 50.0f;
    }*/

    corpo.setPosition(x, y);
    sprite.setPosition(x, y);
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
    if (num_vidas > 0 && !getImune()) {
        num_vidas -= dano;
        cout << "Jogador tomou " << dano << " de dano. Vidas restantes: " << num_vidas << endl;

        if (num_vidas <= 0) {
            cout << "Jogador morreu!" << endl;
            setAtivo(false); 
        }
        else {
            t_dano = t_imune; 
        }
    }
}

void Jogador::colisao(Entidade* ent, sf::Vector2f ds) {
    if (ent == NULL || !ent->getAtivo()) {
        return;
    }

    Entidades::Obstaculo* bloco = dynamic_cast<Entidades::Obstaculo*>(ent);

    if (bloco != NULL) {
        if (ds.x <= ds.y) {
            if (getY() < ent->getY()) {
                if (vely >= 0.0f) {
                    Entidades::Entidade::colisao(ent, ds);
                    vely = 0.0f;
                    chao = true;
                    chaoAtual = bloco;
                }
            }
            else {
                if (vely < 0.0f) {
                    Entidades::Entidade::colisao(ent, ds);
                    vely = 0.0f; 
                }
            }
        }
        else {
            Entidades::Entidade::colisao(ent, ds);
        }
    }
    else {
        Personagens::Inimigo* inimigo = dynamic_cast<Personagens::Inimigo*>(ent);

        if (inimigo != NULL) {
            colidir(inimigo); 
        }
        else {
            Entidades::Entidade::colisao(ent, ds);
        }
    }
}
void Jogador::place() {
    if (inventario > 0) {
        /*float posX = x;
        float posY = y + getTam().y + 2.0f;
        */
        Entidades::Obstaculo* novoBloco = new Entidades::Plataforma(
            x,
            y + getTam().y,
            GRID, GRID,
            0, false, true);

        blocosPendentes.push_back(novoBloco);

        inventario--;
    }
}

std::list<Entidades::Obstaculo*>* Jogador::getBlocosPendentes(){
    return &blocosPendentes;
}

void Jogador::addInventario() {
    inventario++;
}

void Jogador::setChao(bool c) {
    chao = c;
}

void Jogador::operator++() {
    num_vidas++;
}

void Jogador::colidir(Inimigo* pIn) {
    if (pIn == NULL || !pIn->getAtivo()) {
        return;
    }

    if (vely >= 0.0f && getY() <= (pIn->getY() - GRID / 2.0f)) {
        setPos(sf::Vector2f(x, pIn->getY() - getTam().y));
        setChao(true);
        pular();
        pIn->receberDano(dano);
    }
    else {
        pIn->danificar(this);
    }
}

/*void Jogador::setVelx(float vel) {
    velx = vel;
}*/

void Jogador::removerInventario() {
    if (inventario > 0) {
        inventario--;
    }
}

void Jogador::resetarChao() {
    chao = false;
    chaoAtual = NULL;
}

const bool Jogador::getImune() const
{
    return t_dano > 0;
}
void Jogador::salvarDataBuffer()
{
    Personagem::salvarDataBuffer();
    buffer << pontos << " ";
    buffer << inventario << " ";
    buffer << t_dano;
    //blocos pendentes
}

void Jogador::salvar() 
{
    buffer.str(""); // Limpa dados de saves anteriores no buffer
    buffer.clear();

    salvarDataBuffer();
}

void Jogador::setInventario(const int inv) {
    inventario = inv;
}

void Jogador::setTDano(const int td) {
    t_dano = td;
}

void Jogador::setPontos(int p) {
    pontos = p;
}

int Jogador::getPontos(){
    return pontos;
}

string Jogador::getArquivoSave() const
{
    return "saves/jogadorSave.txt";
}