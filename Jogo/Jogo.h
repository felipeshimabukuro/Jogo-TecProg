#pragma once
/*#include "Bibliotecas.h"
#include "Gerenciador_grafico.h"
#include "Gerenciador_eventos.h" 
#include "Gerenciador_colisao.h"
#include "Jogador.h"
#include "ListaEntidade.h"

using namespace Gerenciadores;
using namespace Listas;
*/

#include "limbo_da_perdicao.h"
#include "Caverna_Maldosa.h"
#include "Gerenciador_grafico.h"

class Jogo
{
private:
	Fases::Fase* faseAtual;
	Gerenciadores::Gerenciador_grafico* pGG;
	bool voltarMenuFlag;
	int faseID;
	bool carregarSaveFlag;
	Jogador* pJogador1;
	Jogador* pJogador2;
public:
	Jogo();
	~Jogo();
	void executar();

	sf::RenderWindow* getWindow();
	void carregarFase(int qualFase, int numJogadores = 1, bool resetarPontos = true);
	void salvar();
	void carregar();
	void solicitarCarregamento();
	bool deveCarregarSave();

	void irParaMenu();  
	bool deveVoltarMenu();
	void criarJogadores(int numJogadores);
};