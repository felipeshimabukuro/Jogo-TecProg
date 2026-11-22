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

void ListaEntidade::salvar()
{
	int tam = 10;
	vector<ostringstream> classes (tam);

	for (int i = 0; i < LEs.getTamanho(); i++)
	{
		Entidade* ent = LEs[i];
		ent->salvar();
		classes[ static_cast<int>(ent->getID()) - 1 ] << ent->getBuffer() << '\n';
	}

	map<int, string> arquivosSave = 
	{
		{0, "saves/jogadorSave.txt"},
		{1, "saves/plataformaSave.txt"},
		{2, "saves/magmaSave.txt"},
		{3, "saves/espinhoSave.txt"},
		{4, "saves/topeiraSave.txt"},
		{5, "saves/ratoSave.txt"},
		{6, "saves/rataoSave.txt"},
		{7, "saves/projTopSave.txt"},
		{8, "saves/projBossSave.txt"},
		{9, "saves/chaoSave.txt"}
	};

	for (int i = 0; i < tam; i++)
	{
		ofstream arquivo(arquivosSave[i]);
		if (arquivo.is_open())
		{
			arquivo << classes[i].str();
		}
	}
}