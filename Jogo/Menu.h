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
    std::vector<sf::Text> textosRanking;
    std::vector<sf::RectangleShape> botoes;

    int opcaoSelecionada;
    bool sairDoLoop;

    enum EstadoMenu { PRINCIPAL, SELECIONAR_FASE, SELECIONAR_JOGADOR, QTD_JOGADORES,PAUSE, RANKING };
    EstadoMenu estadoAtual;

    int faseMapeada;

    void atualizarOpcoesBotoes(const std::vector<std::string>& opcoes, float posYInicial = 250.0f);
    void carregarExibicaoRanking();
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
    void centralizarTexto();
    void continuarJogo();
    void registrarRanking(int pontos, int numJogadores);
};