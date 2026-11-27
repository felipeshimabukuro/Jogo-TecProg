#pragma once
#include "Ente.h"
#include "Bibliotecas.h"

namespace Escavadores_intrepidos {

    class Jogo;

    class Menu : public Ente {
    private:
        Jogo* pJogo;

        sf::Font fonte;
        sf::Text tituloMenu;

        vector<sf::Text> textosBotoes;
        vector<sf::Text> textosRanking;
        sf::RectangleShape fundoMenu;

        int opcaoSelecionada;
        bool sairDoLoop;

        enum EstadoMenu { PRINCIPAL, SELECIONAR_FASE, QTD_JOGADORES, PAUSE, RANKING };
        EstadoMenu estadoAtual;

        int faseMapeada;

        void atualizarOpcoesBotoes(const vector<string>& opcoes, float posYInicial = 250.0f);
        void carregarExibicaoRanking();

    public:
        Menu(Jogo* pJogo = NULL);
        ~Menu();

        void executar();
        void setJogo(Jogo* p);
        void desenhar();
        void moverCima();
        void moverBaixo();
        void interagir();
        void executarTelaPause();
        void registrarRanking(int pontos, int numJogadores);
    };
}