#pragma once
#include "Bibliotecas.h"
#include "Ente.h"

namespace Entidades
{
	class Entidade : public Ente
	{
	protected:
		int x;
		int y;
		ostream buffer;

		void salvarDataBuffer();

	public:
		Entidade(int x, int y);
		virtual ~Entidade();

		virtual void executar() = 0;
		virtual void salvar() = 0;

		const int getX() const;
		const int getY() const;
	};
}