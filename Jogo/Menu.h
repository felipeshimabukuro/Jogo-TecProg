#pragma once
#include "Ente.h"
#include "Bibliotecas.h"

class Jogo;

class Menu : public Ente {
private:
    Jogo* pJogo;

    sf::Font fonte;
    sf::Text tituloMenu;

    std::vector<sf::Text> textosBotoes;
    std::vector<sf::RectangleShape> botoes;

    int opcaoSelecionada;
    bool sairDoLoop;

    enum EstadoMenu { PRINCIPAL, SELECIONAR_FASE, SELECIONAR_JOGADOR, QTD_JOGADORES,PAUSE };
    EstadoMenu estadoAtual;

    int faseMapeada;
public:
    Menu(Jogo* pJogo = nullptr);
    ~Menu();

    void executar();
    void setJogo(Jogo* p);
    void desenhar();
    void moverCima();
    void moverBaixo();
    void interagir();
    void executarTelaPause();
    void escolheAcao();
    void escolheJogador();
    void escolheFase();
    void escolhePause();
    void atualizarRanking(int pontos);
    void mostrarRanking();
    void centralizarTexto();
    void continuarJogo();
};