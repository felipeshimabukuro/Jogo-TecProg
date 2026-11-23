//Adicionar setGG

#pragma once
#include "bibliotecas.h"
#include "IDS.h"

namespace Gerenciadores
{
	class Gerenciador_grafico;
}

using namespace IDs;

class Ente 
{
protected:
	const ID id;
	static Gerenciadores::Gerenciador_grafico* pGG;
	sf::Sprite sprite;

public:
	Ente(ID id);
	virtual ~Ente();
	const ID getID() const;
	virtual void executar() = 0;
	virtual void desenhar(sf::RenderWindow* window);
	void setTextura(const std::string& idTextura, const sf::Vector2f& tam = sf::Vector2f(0.0f, 0.0f));
 };