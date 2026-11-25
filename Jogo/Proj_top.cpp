#include "Proj_top.h"
#include "Jogador.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		using namespace Personagens;

		Proj_top::Proj_top(short int direcao, float x, float y) :
			Projetil(ID::projTop, direcao, x, y),
			dano(10)
		{
			srand(time(NULL));
			setDano(rand() % 10 + 10);
			sf::Vector2f tam(GRID, GRID);
			setTextura("p_topeira", tam);
		}

		Proj_top::~Proj_top()
		{
		}

		void Proj_top::setDano(int d)
		{
			dano = d;
		}

		const int Proj_top::getDano() const
		{
			return dano;
		}

		void Proj_top::colisao(Entidade* ent, sf::Vector2f ds)
		{
			if (ent)
			{
				Jogador* jogador = dynamic_cast<Jogador*>(ent);
				if (jogador)
				{
					jogador->receberDano(getDano());
				}
			}
		}

		void Proj_top::salvarDataBuffer()
		{
			Projetil::salvarDataBuffer();
			buffer << dano;
		}

		void Proj_top::salvar()
		{
			buffer.str(""); // Limpa dados de saves anteriores no buffer
			buffer.clear();

			salvarDataBuffer();
		}

		string Proj_top::getArquivoSave() const
		{
			return "saves/projTopSave.txt";
		}
	}
}