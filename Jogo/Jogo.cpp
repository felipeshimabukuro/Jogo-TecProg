#include "Bibliotecas.h"
#include "Jogo.h"
#include "Menu.h"
#include "Caverna_Maldosa.h"
#include "Limbo_da_perdicao.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;
using namespace Fases;

void Jogo::irParaMenu() { 
    voltarMenuFlag = true;
}

bool Jogo::deveVoltarMenu() {
    return voltarMenuFlag;
}

Jogo::Jogo() :
    faseAtual(NULL),
    voltarMenuFlag(false),
    carregarSaveFlag(false),
    faseID(0)
{
    pGG = Gerenciador_grafico::getGerenciadorGrafico();
    Gerenciador_eventos::getGerenciadorEventos()->setJogo(this);
    executar();
}

Jogo::~Jogo()
{
    if (faseAtual) {
        delete faseAtual;
        faseAtual = NULL;
    }
}

sf::RenderWindow* Jogo::getWindow()
{
    return pGG->getWindow();
}

void Jogo::carregarFase(int qualFase, int numJogadores)
{
    if (faseAtual) {
        delete faseAtual;
        faseAtual = NULL;
    }

    faseID = qualFase;

    if (qualFase == 1) {
        faseAtual = new Caverna_Maldosa(false,numJogadores);
    }
    else if (qualFase == 2) {
        faseAtual = new Limbo_da_perdicao(false,numJogadores);
    }
}

void Jogo::executar()
{
    while (pGG->verificaJanelaAberta()) {
        if (faseAtual) {
            faseAtual->executar();

            if (voltarMenuFlag == true) {
                faseAtual->salvar();

                delete faseAtual; 
                faseAtual = NULL;
                voltarMenuFlag = false;
            }

            else if (carregarSaveFlag == true) 
            {
                carregarSaveFlag = false;
                carregar(); 
            }
        }
        else {
            Menu menuPrincipal(this);
            menuPrincipal.executar();
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
        cout << "Nenhum save encontrado!" << std::endl;
        return;
    }

    if (faseAtual) {
        delete faseAtual;
        faseAtual = NULL;
    }

    faseID = qualFase;

    if (qualFase == 1) {
        faseAtual = new Caverna_Maldosa(true);
    }
    else if (qualFase == 2) {
        faseAtual = new Limbo_da_perdicao(true);
    }
}

void Jogo::solicitarCarregamento() {
    carregarSaveFlag = true;
}

bool Jogo::deveCarregarSave() {
    return carregarSaveFlag;
}