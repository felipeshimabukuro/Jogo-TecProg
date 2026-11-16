#include "ListaEntidade.h"

using namespace Listas;

ListaEntidade::ListaEntidade()
{
}

ListaEntidade::~ListaEntidade()
{
}

void ListaEntidade::incluir(Entidade* pElemento)
{
	LEs.incluir(pElemento);
}

void ListaEntidade::remover(Entidade* pElemento)
{
	LEs.removerElemento(pElemento);
}

const int ListaEntidade::getTamanho() const
{
	return LEs.getTamanho();
}

Entidade* ListaEntidade::operator[](int pos)
{
	return LEs.operator[](pos);
}

/*void ListaEntidade::percorrer(sf::RenderWindow* window)
{
	int tamanho = LEs.getTamanho();

	Entidade* pEntidade = NULL;
	for (int i = 0; i < tamanho; i++)
	{
		pEntidade = LEs.operator[](i);
		pEntidade->executar();
		window->draw(pEntidade->getCorpo());
	}
}*/

void ListaEntidade::percorrer()
{
	for (int i = 0; i < LEs.getTamanho(); i++) {
		LEs.operator[](i)->executar(); 
	}
}

void ListaEntidade::desenharTodas(Gerenciador_grafico* pGG)
{
	for (int i = 0; i < LEs.getTamanho(); i++) {
		pGG->desenharEnte(LEs.operator[](i));
	}
}

void ListaEntidade::limparDestruidos()
{
	for (int i = 0; i < LEs.getTamanho(); i++)
	{
		Entidade* pEnt = LEs[i];

		if (pEnt != NULL && !pEnt->getAtivo())
		{
			remover(pEnt);
			i--;
		}
	}
}