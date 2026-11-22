#pragma once
#include "Inimigo.h"
#include "Jogador.h"

namespace Personagens
{
	class Ratao : public Inimigo
	{
	private:
		string estado;

		short int forca;
		int bater_cd;
		const int bater_tm;
		short int batidas_restantes;
		short int batidas_esq;
		short int batidas_dir;
		short int lado_batida;
		bool batendo;
		int tempo_batida;
		int duracao_batida;
		float x_batida;
		float y_batida;
		float largura_batida;
		float altura_batida;
		const int chance_atacar;
		int ataque_cd;
		int ataque_tm;
		int tempo_imune; 

	public:
		Ratao(const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(80.0f, 80.0f), Jogador* j = nullptr);
		~Ratao();
		void criarTerra(int dir, int ind);
		void verificarAtaque();
		void idle();
		void movimentar();
		void bater();
		void atualizaLado() override;
		void executar();
		void colisao(Entidade* ent, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
		const sf::FloatRect getHitboxBatida() const;
		const bool getBatendo() const;
		const short int getForca() const;
		void danificar(Jogador* p);
		void salvarDataBuffer();
		void salvar();
		void setBaterCd(const int cd);
		void setBatidasRestantes(const int br);
		void setBatidasEsq(const int be);
		void setBatidasDir(const int bd);
		void setLadoBatida(const int lb);
		void setBatendo(const bool b);
		void setTempoBatida(const int tb);
		void setAtaqueCd(const int acd);
		void setTempoImune(const int ti);
		void setEstado(const string& est);
	};
}
