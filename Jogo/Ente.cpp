#include "Ente.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;

int Ente::cont = 0;

Ente::Ente() : id(cont++)
{	
}

Ente::~Ente() 
{	
}

void Ente::desenhar() {
	
}

const int Ente::getID() const
{
	return id;
}