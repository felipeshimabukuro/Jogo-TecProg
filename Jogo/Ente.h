#pragma once
#include "bibliotecas.h"

class Ente 
{
protected:
	int id;
	static int cont;

public:
	Ente();
	virtual ~Ente();
	//virtual void executar() = 0;
	void desenhar();
	int getID();
	//virtual sf::Sprite getDrawData() const = 0;
 };