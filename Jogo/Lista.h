#pragma once
#include "Bibliotecas.h"

namespace Escavadores_intrepidos {
	namespace Listas
	{
		template<class TL>
		class Lista
		{
		private:
			template<class TE>

			// Classe aninhada p/ elemento =================
			class Elemento
			{
			private:
				TE* pInfo;
				Elemento<TE>* pProximo;

			public:
				Elemento(TE* pElemento = NULL);
				~Elemento();
				TE* getElemento() const;
				Elemento<TE>* getProximo() const;
				void setProx(Elemento<TE>* pProximo);
				void incluir(TE* pElemento);
			};

			Elemento<TL>* pPrimeiro;
			Elemento<TL>* pUltimo;
			unsigned int tamanho;

		public:
			Lista();
			~Lista();
			void incluir(TL* p);
			void limpar();
			void removerElemento(TL* p);
			const int getTamanho() const;
			TL* operator[](int pos);
		};

		// IMPLEMENTAÇÕES DE ELEMENTO =================

		template<class TL>
		template<class TE>
		Lista<TL>::Elemento<TE>::Elemento(TE* pElemento)
		{
			this->pInfo = pElemento;
			this->pProximo = NULL;
		}

		template<class TL>
		template<class TE>
		Lista<TL>::Elemento<TE>::~Elemento()
		{
			pProximo = NULL;
			delete pInfo;
		}

		template<class TL>
		template<class TE>
		TE* Lista<TL>::Elemento<TE>::getElemento() const
		{
			return pInfo;
		}

		template<class TL>
		template<class TE>
		typename Lista<TL>::template Elemento<TE>* Lista<TL>::Elemento<TE>::getProximo() const
		{
			return pProximo;
		}

		template<class TL>
		template<class TE>
		void Lista<TL>::Elemento<TE>::setProx(Elemento<TE>* pProximo)
		{
			this->pProximo = pProximo;
		}

		template<class TL>
		template<class TE>
		void Lista<TL>::Elemento<TE>::incluir(TE* pElemento)
		{
			this->pInfo = pElemento;
		}

		// IMPLEMENTAÇÕES DE LISTA =================

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
		void Lista<TL>::incluir(TL* p)
		{
			if (p)
			{
				Elemento<TL>* novoNo = new Elemento<TL>(p);
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
			if (pPrimeiro)
			{
				Elemento<TL>* temp = pPrimeiro;
				while (temp)
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
		void Lista<TL>::removerElemento(TL* p)
		{
			if (p == NULL || pPrimeiro == NULL)
				return;

			if (pPrimeiro->getElemento() == p)
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

			Elemento<TL>* temp = pPrimeiro;
			while (temp->getProximo() != NULL)
			{
				if (temp->getProximo()->getElemento() == p)
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
		TL* Lista<TL>::operator[](int pos)
		{
			Elemento<TL>* temp = pPrimeiro;
			for (int i = 0; i < pos && temp; i++)
			{
				temp = temp->getProximo();
			}
			return temp ? temp->getElemento() : NULL;
		}
	}
}