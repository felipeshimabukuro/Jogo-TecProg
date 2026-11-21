#include "Bibliotecas.h"
#include "Jogo.h"

/*Jogo::Jogo() : faseAtual(new Fases::Caverna_Maldosa)
{
	executar();
}

Jogo::~Jogo()
{
	if (faseAtual) {
		delete faseAtual;
		faseAtual = NULL;
	}
}

void Jogo::executar()
{
	if (faseAtual) {
		faseAtual->executar();
	}
}*/
#include "Bibliotecas.h"
#include "Jogo.h"
#include "Menu.h"
#include "Caverna_Maldosa.h"
#include "Limbo_da_perdicao.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;

void Jogo::irParaMenu() { 
    voltarMenuFlag = true;
}

bool Jogo::deveVoltarMenu() {
    return voltarMenuFlag;
}

Jogo::Jogo() : faseAtual(NULL)
{
    pGG = Gerenciador_grafico::getGerenciadorGrafico();
    Gerenciadores::Gerenciador_eventos::getGerenciadorEventos()->setJogo(this);
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

void Jogo::carregarFase(int qualFase)
{
    if (faseAtual) {
        delete faseAtual;
        faseAtual = NULL;
    }

    if (qualFase == 1) {
        faseAtual = new Fases::Caverna_Maldosa();
    }
    else if (qualFase == 2) {
        faseAtual = new Fases::Limbo_da_perdicao();
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
        }
        else {
            Menu menuPrincipal(this);
            menuPrincipal.executar();
        }
    }
}