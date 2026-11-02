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

int Ente::getID()
{
	return id;
}