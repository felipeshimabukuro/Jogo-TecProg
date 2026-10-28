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

void ListaEntidade::removerElemento(Entidade* pElemento)
{
	LEs.removerElemento(pElemento);
}

int ListaEntidade::getTamanho()
{
	return LEs.getTamanho();
}

Entidade* ListaEntidade::operator[](int pos)
{
	return LEs.operator[](pos);
}

void ListaEntidade::percorrer(sf::RenderWindow* window)
{
	int tamanho = LEs.getTamanho();

	Entidade* pEntidade = NULL;
	for (int i = 0; i < tamanho; i++)
	{
		pEntidade = LEs.operator[](i);
		pEntidade->executar();
		window->draw(pEntidade->getCorpo());
	}
}