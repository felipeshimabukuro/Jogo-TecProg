#include "Topeira.h"
#include "Proj_top.h"
#define MINUTOS *60

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Personagens {

			const int Topeira::dist_atk = 180;
			const int Topeira::tempo_tiro = 5 MINUTOS;

			Topeira::Topeira(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j1, Jogador* j2) :
				Inimigo(ID::topeira, pos, tam, j1, j2),
				cavando(false),
				tiro_cd(0)
			{
				nivel_maldade = rand() % 3 + 1;
				dist_detec = 350;
				boss = false;
				inicializarVida(10);
				lado = 1;                        // Olhando para a direita
				x = pos.x;
				y = pos.y;
				x_alvo = static_cast<int>(x);
				velx = 0.0f;
				vely = 0.0f;
				estado = "IDLE";

				setTextura("topeira", getTam());
			}

			Topeira::~Topeira()
			{
			}

			void Topeira::cavar()
			{
				cavando = !cavando;
			}

			void Topeira::atirar()
			{
				if (cavando) { cavar(); }

				if (tiro_cd <= 0)
				{
					if (!cavando)
					{
						Projetil* novoProjetil = new Proj_top(lado, x + GRID / 2, y + GRID / 2);
						projeteisPendentes.push_back(novoProjetil);
					}
					tiro_cd = tempo_tiro / nivel_maldade;
				}
			}

			void Topeira::seguir()
			{
				if (!cavando) { cavar(); }

				Jogador* jogador = getJogadorAlvo();
				if (jogador)
				{
					persegueJogador(jogador);
				}
			}

			bool Topeira::perto()
			{
				Jogador* jogador = getJogadorAlvo();
				if (jogador == NULL) return false;

				sf::Vector2f posJogador = jogador->getCorpo().getPosition();
				sf::Vector2f posInimigo = corpo.getPosition();
				sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
				return (distancia.x < dist_atk && distancia.y < dist_atk);
			}

			void Topeira::executar()
			{
				if (perto())
				{
					estado = "ATAQUE";
				}
				else if (detectarJogador())
				{
					estado = "SEGUIR";
				}
				else
				{
					estado = "LIVRE";
				}

				if (estado == "ATAQUE")
				{
					atirar();
				}

				else if (estado == "SEGUIR")
				{
					seguir();
				}

				else if (estado == "LIVRE")
				{
					movimentoAleatorio();
				}

				mover();

				sf::Vector2f pos(x, y);
				setPos(pos);

				if (tiro_cd > 0)
				{
					tiro_cd--;
				}
			}

			void Topeira::colisao(Entidade* ent, sf::Vector2f ds)
			{
				if (!ent || !ent->getAtivo())
					return;

				Inimigo::colisao(ent, ds);
			}

			void Topeira::danificar(Jogador* p)
			{
				p->receberDano(dano);
			}

			void Topeira::salvarDataBuffer()
			{
				Inimigo::salvarDataBuffer();
				buffer << tiro_cd << " ";
				buffer << estado;
			}

			void Topeira::salvar()
			{
				buffer.str(""); // Limpa dados de saves anteriores no buffer
				buffer.clear();

				salvarDataBuffer();
			}

			void Topeira::setTiroCd(const int cd)
			{
				tiro_cd = cd;
			}

			void Topeira::setEstado(const string& est)
			{
				estado = est;
			}

			list<Entidades::Projetil*>* Topeira::getProjeteisPendentes() {
				return &projeteisPendentes;
			}

			string Topeira::getArquivoSave() const
			{
				return "saves/topeiraSave.txt";
			}
		}
	}
}