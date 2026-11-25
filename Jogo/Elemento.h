#pragma once
#include "Bibliotecas.h"

namespace Escavadores_intrepidos {
	namespace Listas
	{
		template<class TE>
		class Elemento
		{
		private:
			TE* pInfo;
			Elemento<TE>* pProximo;

		public:
			Elemento(TE* pElemento);
			~Elemento();
			TE* getElemento() const;
			Elemento<TE>* getProximo() const;
			void setProx(Elemento<TE>* pProximo);
			void incluir(TE* pElemento);
		};

		template<class TE>
		Elemento<TE>::Elemento(TE* pElemento)
		{
			this->pInfo = pElemento;
			this->pProximo = NULL;
		}

		template<class TE>
		Elemento<TE>::~Elemento()
		{
			pProximo = NULL;
			delete pInfo;
		}

		template<class TE>
		TE* Elemento<TE>::getElemento() const
		{
			return pInfo;
		}

		template<class TE>
		Elemento<TE>* Elemento<TE>::getProximo() const
		{
			return pProximo;
		}

		template<class TE>
		void Elemento<TE>::setProx(Elemento<TE>* pProximo)
		{
			this->pProximo = pProximo;
		}

		template<class TE>
		void Elemento<TE>::incluir(TE* pElemento)
		{
			this->pInfo = pElemento;
		}
	}
}