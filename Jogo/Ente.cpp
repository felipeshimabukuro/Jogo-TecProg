#include "Ente.h"
#include "Gerenciador_grafico.h"

using namespace Gerenciadores;

Gerenciador_grafico* Ente::pGG = NULL;
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

void Ente::staticSetGG(Gerenciador_grafico* pG)
{
	if(pG) pGG = pG;
}