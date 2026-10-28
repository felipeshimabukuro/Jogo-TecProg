#pragma once
#include "Bibliotecas.h"

namespace Listas
{
	template<class TE>
	class Elemento
	{
	private:
		TE* pElemento;
		Elemento<TE>* pProximo;

	public:
		Elemento(TE* pElemento);
		~Elemento();
		TE* getElemento();
		Elemento<TE>* getProximo();
		void setProximo(Elemento<TE>* pProximo);
		void incluir(TE* pElemento);
	};

	template<class TE>
	Elemento<TE>::Elemento(TE* pElemento)
	{
		this->pElemento = pElemento;
		this->pProximo = NULL;
	}

	template<class TE>
	Elemento<TE>::~Elemento()
	{
		pProximo = NULL;
		delete pElemento;
	}

	template<class TE>
	TE* Elemento<TE>::getElemento()
	{
		return pElemento;
	}

	template<class TE>
	Elemento<TE>* Elemento<TE>::getProximo()
	{
		return pProximo;
	}

	template<class TE>
	void Elemento<TE>::setProximo(Elemento<TE>* pProximo)
	{
		this->pProximo = pProximo;
	}

	template<class TE>
	void Elemento<TE>::incluir(TE* pElemento)
	{
		this->pElemento = pElemento;
	}
}