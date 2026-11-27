#include "Bibliotecas.h"
#include "Jogo.h"
#include "Menu.h"
#include "Caverna_Maldosa.h"
#include "Limbo_da_perdicao.h"
#include "Gerenciador_grafico.h"

namespace Escavadores_intrepidos {

    using namespace Entidades;
    using namespace Gerenciadores;
    using namespace Fases;
    using namespace Personagens;


    Jogo::Jogo() :
        faseAtual(NULL),
        pMenu(NULL),
        voltarMenuFlag(false),
        carregarSaveFlag(false),
        faseID(0),
        pJogador1(NULL),
        pJogador2(NULL)
    {
        pGG = Gerenciador_grafico::getGerenciadorGrafico();
        pMenu = new Menu(this);
        Gerenciador_eventos::getGerenciadorEventos()->setJogo(this);
        executar();
    }

    Jogo::~Jogo()
    {
        if (faseAtual) {
            delete faseAtual;
            faseAtual = NULL;
            pJogador1 = NULL;
            pJogador2 = NULL;
        }
        if (pMenu) {
            delete pMenu;
            pMenu = NULL;
        }
    }

    sf::RenderWindow* Jogo::getWindow()
    {
        return pGG->getWindow();
    }

    void Jogo::carregarFase(int qualFase, int numJogadores, bool resetarPontos)
    {
        if (faseAtual) {
            delete faseAtual;
            faseAtual = NULL;
            pJogador1 = NULL;
            pJogador2 = NULL;
        }

        carregarSaveFlag = false;
        voltarMenuFlag = false;
        criarJogadores(numJogadores);
        if (resetarPontos) {
            Jogador::setPontos(0);
        }
        faseID = qualFase;

        if (qualFase == 1) {
            faseAtual = new Caverna_Maldosa(false, numJogadores, pJogador1, pJogador2);
        }
        else if (qualFase == 2) {
            faseAtual = new Limbo_da_perdicao(false, numJogadores, pJogador1, pJogador2);
        }
    }

    void Jogo::executar()
    {
        while (pGG->verificaJanelaAberta()) {
            if (faseAtual) {
                faseAtual->executar();

                if (voltarMenuFlag == true) {
                    delete faseAtual;
                    faseAtual = NULL;
                    voltarMenuFlag = false;
                    pJogador1 = NULL;
                    pJogador2 = NULL;
                }

                else if (carregarSaveFlag == true)
                {
                    carregarSaveFlag = false;
                    carregar();
                }
                else if (faseAtual->getVenceu())
                {
                    if (faseID == 1)
                    {
                        int qtdJog = faseAtual->getNumJogadores();
                        carregarFase(2, qtdJog, false);
                    }
                    else if (faseID == 2)
                    {
                        int pontosFinais = Jogador::getPontos();
                        int qtdJog = faseAtual->getNumJogadores();

                        delete faseAtual;
                        faseAtual = NULL;
                        pJogador1 = NULL;
                        pJogador2 = NULL;

                        pMenu->registrarRanking(pontosFinais, qtdJog);
                    }
                }
            }
            else {
                pMenu->executar();

                if (carregarSaveFlag == true) {
                    carregarSaveFlag = false;
                    carregar();
                }
            }
        }
    }

    void Jogo::salvar()
    {
        if (faseAtual != NULL)
        {
            faseAtual->salvar();

            ofstream arqFase("saves/faseSave.txt");
            if (arqFase.is_open()) {
                arqFase << faseID;
            }
        }
    }

    void Jogo::carregar()
    {
        ifstream arqFase("saves/faseSave.txt");
        int qualFase = 0;

        if (arqFase.is_open()) {
            arqFase >> qualFase;
            arqFase.close();
        }

        if (qualFase == 0) {
            cout << "Nenhum save encontrado!" << endl;
            return;
        }

        int numJogadores = 0;
        ifstream arqJog("saves/jogadorSave.txt");
        string linha;
        while (getline(arqJog, linha)) {
            if (!linha.empty()) {
                numJogadores++;
            }
        }
        arqJog.close();
        if (numJogadores < 1) numJogadores = 1;

        if (faseAtual) {
            delete faseAtual;
            faseAtual = NULL;
            pJogador1 = NULL;
            pJogador2 = NULL;
        }

        faseID = qualFase;

        criarJogadores(numJogadores);

        if (qualFase == 1) {
            faseAtual = new Caverna_Maldosa(true, numJogadores, pJogador1, pJogador2);
        }
        else if (qualFase == 2) {
            faseAtual = new Limbo_da_perdicao(true, numJogadores, pJogador1, pJogador2);
        }
    }

    void Jogo::solicitarCarregamento() {
        carregarSaveFlag = true;
    }

    bool Jogo::deveCarregarSave() {
        return carregarSaveFlag;
    }

    void Jogo::irParaMenu() {
        voltarMenuFlag = true;
    }

    bool Jogo::deveVoltarMenu() {
        return voltarMenuFlag;
    }

    void Jogo::criarJogadores(int numJogadores) {
        pJogador1 = new Jogador(sf::Vector2f(0, 0), sf::Vector2f(GRID, GRID), 0);
        if (numJogadores == 2) {
            pJogador2 = new Jogador(sf::Vector2f(0, 0), sf::Vector2f(GRID, GRID), 1);
        }
        else {
            pJogador2 = NULL;
        }
    }

    void Jogo::pausar()
    {
        if (pMenu) {
            pMenu->executarTelaPause();
        }
    }

}