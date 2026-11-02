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
	const int getID() const;
	virtual void executar() = 0;
	void desenhar();
	//virtual sf::Sprite getDrawData() const = 0;
 };