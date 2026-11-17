#pragma once
#include "Elemento.h"

namespace Listas
{
	template<class TL>
	class Lista
	{
	private:
		Elemento<TL>* pPrimeiro;
		Elemento<TL>* pUltimo;
		unsigned int tamanho;

	public:
		Lista();
		~Lista();
		void incluir(TL* pElemento);
		void limpar();
		void removerElemento(TL* pElemento);
		const int getTamanho() const;
		TL* operator[](int pos);
	};

	template<class TL>
	Lista<TL>::Lista()
	{
		pPrimeiro = NULL;
		pUltimo = NULL;
		tamanho = 0;
	}

	template<class TL>
	Lista<TL>::~Lista()
	{
		limpar();
	}

	template<class TL>
	void Lista<TL>::incluir(TL* pElemento)
	{
		if(pElemento)
		{
			Elemento<TL>* novoNo = new Elemento<TL>(pElemento);
			novoNo->setProx(NULL); 

			if (pPrimeiro == NULL)
			{
				pPrimeiro = novoNo;
				pUltimo = novoNo;
			}
			else
			{
				pUltimo->setProx(novoNo);
				pUltimo = novoNo;
			}
			tamanho++;
		}
	}

	template<class TL>
	void Lista<TL>::limpar()
	{
		if(pPrimeiro)
		{
			Elemento<TL>* temp = pPrimeiro;
			while(temp)
			{
				pPrimeiro = temp->getProximo();
				delete temp;
				temp = pPrimeiro;
			}
			pUltimo = NULL;
			tamanho = 0;
		}
	}

	template<class TL>
	void Lista<TL>::removerElemento(TL* pElemento) 
	{
		if (pElemento == NULL || pPrimeiro == NULL)
			return;

		// CASO oelemento a ser removido é o PRIMEIRO da lista
		if (pPrimeiro->getElemento() == pElemento)
		{
			Elemento<TL>* pDelete = pPrimeiro;
			pPrimeiro = pPrimeiro->getProximo();

			if (pPrimeiro == NULL) {
				pUltimo = NULL;
			}

			delete pDelete;
			tamanho--;
			return;
		}

		// CASO o elemento a ser removido está no MEIO ou no FIM da lista
		Elemento<TL>* temp = pPrimeiro;
		while (temp->getProximo() != NULL)
		{
			if (temp->getProximo()->getElemento() == pElemento)
			{
				Elemento<TL>* pDelete = temp->getProximo();
				temp->setProx(temp->getProximo()->getProximo());

				if (pDelete == pUltimo) {
					pUltimo = temp;
				}

				delete pDelete;
				tamanho--;
				return;
			}
			temp = temp->getProximo();
		}
	}

	template<class TL>
	const int Lista<TL>::getTamanho() const
	{
		return tamanho;
	}

	template<class TL>
	TL* Lista<TL>::operator[](int pos) //considero pesado para chamar varias vezes, eh de se pensar sobre
	{
		Elemento<TL>* temp = pPrimeiro;
		for(int i = 0; i < pos && temp; i++)
		{
			temp = temp->getProximo();
		}
		return temp ? temp->getElemento() : NULL;
	}
}
