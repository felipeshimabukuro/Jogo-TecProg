#include "Rato.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Personagens {

			const int Rato::dist_detec = 360;
			const int Rato::dist_atk = 180;

			Rato::Rato(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j1, Jogador* j2) :
				Inimigo(ID::rato, pos, tam, j1, j2)
			{
				boss = false;
				inicializarVida(15);
				lado = 1;                        // Olhando para a direita
				x = pos.x;
				y = pos.y;
				x_alvo = static_cast<int>(x);
				velx = 0.0f;
				vely = 0.0f;
				estado = "IDLE";

				corpo.setSize(tam);
				corpo.setPosition(x, y);
				sprite.setPosition(x, y);
				inicializa();
			}

			Rato::~Rato()
			{
			}

			bool Rato::detectarJogador()
			{
				Jogador* jogador = getJogadorAlvo();
				if (jogador == NULL) return false;

				sf::Vector2f posJogador = jogador->getCorpo().getPosition();
				sf::Vector2f posInimigo = corpo.getPosition();
				sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
				return (distancia.x < dist_detec && distancia.y < dist_detec);
			}

			void Rato::seguir()
			{
				Jogador* jogador = getJogadorAlvo();
				atualizaLado();

				if (jogador)
				{
					if (jogador->getX() > x) {
						velx = 2.5f;
					}
					else {
						velx = -2.5f;
					}
				}
			}

			bool Rato::perto()
			{
				Jogador* jogador = getJogadorAlvo();
				if (jogador == NULL) return false;

				sf::Vector2f posJogador = jogador->getCorpo().getPosition();
				sf::Vector2f posInimigo = corpo.getPosition();
				sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
				return (distancia.x < dist_atk && distancia.y < dist_atk);
			}

			void Rato::atualizaLado()
			{
				Jogador* jogador = getJogadorAlvo();
				if (jogador)
				{
					if (detectarJogador()) {
						if (jogador->getCorpo().getPosition().x > x)
						{
							lado = 1;
						}
						else
						{
							lado = -1;
						}
					}

					const sf::Texture* tex = sprite.getTexture();
					if (tex) {
						int w = tex->getSize().x;
						int h = tex->getSize().y;
						if (lado == 1) {
							sprite.setTextureRect(sf::IntRect(w, 0, -w, h));
							sprite.setOrigin(0.0f, 0.0f);
						}
						else {
							sprite.setTextureRect(sf::IntRect(0, 0, w, h));
							sprite.setOrigin(0.0f, 0.0f);
						}
					}
				}
			}

			void Rato::executar()
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
					estado = "IDLE";
				}

				velx = 0.0f;

				if (estado == "ATAQUE")
				{
					Jogador* jogador = getJogadorAlvo();
					atualizaLado();
					if (jogador) {
						if (jogador->getX() > x) {
							velx = 1.5f * nivel_maldade;
						}
						else if (jogador->getX() < x) {
							velx = -1.5f * nivel_maldade;
						}
						else {
							velx = 0.0f;
						}
					}
				}
				else if (estado == "SEGUIR")
				{
					Jogador* jogador = getJogadorAlvo();
					persegueJogador(jogador);
				}
				else
				{
					movimentoAleatorio();
				}

				mover();

				corpo.setPosition(x, y);
				sprite.setPosition(x, y);
			}

			void Rato::colisao(Entidade* ent, sf::Vector2f ds)
			{
				if (!ent || !ent->getAtivo())
					return;

				Inimigo::colisao(ent, ds);
			}

			void Rato::danificar(Jogador* p) {
				if (p->getImune()) return;

				p->receberDano(dano);
				p->setChao(true);
				p->pular();
			}

			void Rato::inicializa() {
				setTextura("rato", getTam());
			}

			void Rato::salvarDataBuffer()
			{
				Inimigo::salvarDataBuffer();
				buffer << estado;
			}

			void Rato::salvar()
			{
				buffer.str(""); // Limpa dados de saves anteriores no buffer
				buffer.clear();

				salvarDataBuffer();
			}

			void Rato::setEstado(const string& est)
			{
				estado = est;
			}

			string Rato::getArquivoSave() const
			{
				return "saves/ratoSave.txt";
			}
		}
	}
}