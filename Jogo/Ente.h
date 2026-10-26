#pragma once
#include "Gerenciador_grafico.h"

namespace Gerenciadores //Rever isso pq wtf
{ 
	class Gerenciador_grafico; 
}

class Ente 
{
protected:
	int id;
	static int cont;
	static Gerenciadores::Gerenciador_grafico* pGG;


public:
	Ente();
	virtual ~Ente();
	//virtual void executar() = 0;
	void desenhar();
	int getID();
	static void staticSetGG(Gerenciadores::Gerenciador_grafico* pG);
	//virtual sf::Sprite getDrawData() const = 0;
 };