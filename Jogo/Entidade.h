#pragma once
#include "Bibliotecas.h"
#include "Ente.h"

namespace Entidades
{
	class Entidade : public Ente
	{
	protected:
		float x;
		float y;
		ostringstream buffer;
		sf::RectangleShape corpo;
		bool ativo;
		static const float gravidade;
		float vely;
		float max_vely;

		void salvarDataBuffer();

	public:
		Entidade(ID id, float xx = 0.0, float yy = 0.0);
		virtual ~Entidade();

		virtual void executar() = 0;
		virtual void salvar() = 0;

		const float getX() const;
		const float getY() const;
		const sf::Vector2f getPos() const;
		virtual void setPos(const sf::Vector2f pos);

		const sf::Vector2f getTam();
		const sf::RectangleShape getCorpo() const;
		virtual void colisao(Entidade* ent, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));

		void setAtivo(bool a);
		const bool getAtivo() const;
		void aplicarGravidade();

		const string getBuffer() const;
		virtual string getArquivoSave() const = 0;
	};
}
