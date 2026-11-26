#pragma once
#include "bibliotecas.h"

namespace Escavadores_intrepidos {

	namespace Gerenciadores
	{
		class Gerenciador_grafico;
	}
	using namespace Gerenciadores;

	class Ente
	{
	protected:
		static Gerenciador_grafico* pGG;
		sf::Sprite sprite;

	public:
		Ente();
		virtual ~Ente();
		virtual void executar() = 0;
		virtual void desenhar(sf::RenderWindow* window);
		void setTextura(const string& idTextura, const sf::Vector2f& tam = sf::Vector2f(0.0f, 0.0f));
		const void setGG(Gerenciador_grafico* GG) const;
	};

}