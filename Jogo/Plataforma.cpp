#include "Plataforma.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Obstaculos {

			int Plataforma::ticks(0);

			Plataforma::Plataforma(int x, int y, int largura, int altura, int dano, bool danoso, bool quebravel) :
				Obstaculo(x, y, largura, altura, dano, danoso, quebravel),
				max_ticks(180)
			{
				inicializa();
			}

			Plataforma::~Plataforma() {

			}

			void Plataforma::executar()
			{
				aplicarGravidade();
				desGravitar();
				if (!rand() % 200) {
					danoso = true;
					dano = 5;
					sprite.setColor(sf::Color::Red);
					quebravel = false;
				}
			}

			void Plataforma::salvar() {
				buffer.str("");
				buffer.clear();
				salvarDataBuffer();
			}

			void Plataforma::salvarDataBuffer() {
				Obstaculo::salvarDataBuffer();
				buffer << ticks << " " << danoso;
			}

			void Plataforma::obstaculizar(Jogador* p) {
				ticks++;
				if (ticks == max_ticks) {
					ticks = 0;
					p->removerInventario();
					if (danoso)
					{
						p->receberDano(dano);
					}
				}
			}

			void Plataforma::inicializa() {
				corpo.setSize(sf::Vector2f(largura, altura));
				setTextura("terra", sf::Vector2f(largura, altura));
				corpo.setPosition(x, y);
				sprite.setPosition(x, y);
			}

			void Plataforma::setTicks(const int p)
			{
				ticks = p;
			}

			void Plataforma::setDanoso(const bool d)
			{
				danoso = d;
				if (danoso) {
					dano = 5;
					quebravel = false;
					sprite.setColor(sf::Color::Red);
				}
				else {
					dano = 0;
					quebravel = true;
					sprite.setColor(sf::Color::White);
				}
			}

			string Plataforma::getArquivoSave() const
			{
				return "saves/plataformaSave.txt";
			}
		}
	}
}