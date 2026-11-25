#include "Personagem.h"

namespace Escavadores_intrepidos {
	namespace Entidades {
		namespace Personagens {

			Personagem::Personagem(ID id, const sf::Vector2f pos, const sf::Vector2f tam) :
				Entidade(id, pos.x, pos.y),
				chao(true),
				velx(0),
				max_velx(5.0f),
				dano(dano)
			{
				barraFundo.setFillColor(sf::Color(40, 40, 40, 200));
				barraFundo.setOutlineThickness(1.0f);
				barraFundo.setOutlineColor(sf::Color::Black);
				barraVida.setFillColor(sf::Color(50, 205, 50));
			}

			Personagem::~Personagem() {

			}

			void Personagem::salvarDataBuffer()
			{
				Entidade::salvarDataBuffer();
				buffer << velx << " ";
				buffer << vely << " ";
				buffer << num_vidas << " ";
			}

			const float Personagem::getVely() const {
				return vely;
			}

			const float Personagem::getVelx() const {
				return velx;
			}

			int Personagem::getDano() const {
				return dano;
			}

			void Personagem::setVel(const sf::Vector2f v) {
				velx = v.x;
				vely = v.y;
			}

			void Personagem::desenhar(sf::RenderWindow* window)
			{
				Ente::desenhar(window);

				if (ativo)
				{
					desenharBarra(window, x, y, getTam().x);
				}
			}

			void Personagem::desenharBarra(sf::RenderWindow* window, const float x, const float y, const float largura)
			{
				if (!window) return;

				float larguraBarra = (largura > 0.0f) ? largura : 50.0f;
				float alturaBarra = 6.0f;
				float offsetY = 10.0f; // Distância acima da cabeça da entidade

				float proporcao = static_cast<float>(num_vidas) / static_cast<float>(max_vidas);
				if (proporcao < 0.0f) proporcao = 0.0f;
				if (proporcao > 1.0f) proporcao = 1.0f;

				barraFundo.setSize(sf::Vector2f(larguraBarra, alturaBarra));
				barraVida.setSize(sf::Vector2f(larguraBarra * proporcao, alturaBarra));

				barraFundo.setPosition(x, y - offsetY);
				barraVida.setPosition(x, y - offsetY);

				if (proporcao > 0.5f)
				{
					barraVida.setFillColor(sf::Color::Green);
				}
				else if (proporcao > 0.25f)
				{
					barraVida.setFillColor(sf::Color::Yellow);
				}
				else
				{
					barraVida.setFillColor(sf::Color::Red);
				}

				window->draw(barraFundo);
				window->draw(barraVida);
			}
			void Personagem::inicializarVida(const int vidasMax)
			{
				max_vidas = (vidasMax > 0) ? vidasMax : 1;
				num_vidas = max_vidas;
			}
			void Personagem::setNumVidas(const int vidas)
			{
				num_vidas = vidas;
			}

			const int Personagem::getNumVidas() const
			{
				return num_vidas;
			}

			const int Personagem::getMaxVidas() const
			{
				return max_vidas;
			}
		}
	}
}