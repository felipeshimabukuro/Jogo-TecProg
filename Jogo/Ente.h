#pragma once
#include "bibliotecas.h"

namespace Gerenciadores
{
	class Gerenciador_grafico;
}

class Ente 
{
protected:
	int id;
	static int cont;
	static Gerenciadores::Gerenciador_grafico* pGG;
	sf::Sprite sprite;

public:
	Ente();
	virtual ~Ente();
	const int getID() const;
	virtual void executar() = 0;
	virtual void desenhar(sf::RenderWindow* window);
	void setTextura(const std::string& idTextura, const sf::Vector2f& tam = sf::Vector2f(0.0f, 0.0f));
 };