#include "ListaEntidade.h"

namespace Escavadores_intrepidos {
	namespace Listas {

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
			map<string, ostringstream> arquivos;

			arquivos["saves/jogadorSave.txt"];
			arquivos["saves/plataformaSave.txt"];
			arquivos["saves/magmaSave.txt"];
			arquivos["saves/topeiraSave.txt"];
			arquivos["saves/ratoSave.txt"];
			arquivos["saves/projTopSave.txt"];
			arquivos["saves/chaoSave.txt"];

			for (int i = 0; i < LEs.getTamanho(); i++)
			{
				Entidade* ent = LEs[i];
				ent->salvar();
				arquivos[ent->getArquivoSave()] << ent->getBuffer() << '\n';
			}

			map<string, ostringstream>::const_iterator it;
			for (it = arquivos.begin(); it != arquivos.end(); ++it)
			{
				ofstream arquivo(it->first);
				if (arquivo.is_open())
				{
					arquivo << it->second.str();
				}
			}
		}
	}
}