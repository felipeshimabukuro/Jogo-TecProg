#include "Bibliotecas.h"
#include "Ratao.h"
#include "Proj_boss.h"
#include "Gerenciador_colisao.h"
#define SEGUNDOS *60
#define COR_DEFAULT sf::Color(140, 20, 20)

using namespace Personagens;
using namespace Entidades;
using namespace Gerenciadores;

Ratao::Ratao(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j) :
	Inimigo(ID::ratao, pos, tam, j),
	estado("IDLE"),
	forca(15),                       // Dano
	bater_cd(0),                     // Cooldown da próxima batida
	bater_tm(40),                    // Intervalo entre batidas
	batidas_restantes(0),            // Batidas faltantes
	batidas_esq(0),                  // Contador de batidas esquerda
	batidas_dir(0),                  // Contador de batidas direita
	lado_batida(1),                  // Direção (1 = direita, -1 = esquerda)
	batendo(false),                  // Flag que indica se a hitbox da batida está ativa
	tempo_batida(0),                 // Duração restante do hit atual
	duracao_batida(12),              // Frames em que o hit permanece ativo 
	x_batida(pos.x),
	y_batida(pos.y),
	largura_batida(GRID),              // Largura da hitbox de dano ao lado
	altura_batida(GRID*2),               // Altura da hitbox
	chance_atacar(3),                // Chance percentual por frame de iniciar ataque
	ataque_cd(0),                    // Cooldown geral entre sequências de ataque 
	ataque_tm(5 SEGUNDOS),           // Tempo de recarga do ataque
	tempo_imune(0)                   // Temporizador de invulnerabilidade pós-hit
{
	boss = true;
	num_vidas = 3;
	dist_detec = GRID * 8;           // Raio de detecção do jogador (usado em detectarJogador e verificarAtaque)
	lado = 1;                        // Olhando para a direita
	x = pos.x;
	y = pos.y;
	x_alvo = static_cast<int>(x);
	velx = 0.0f;
	vely = 0.0f;

	corpo.setSize(tam);
	corpo.setFillColor(COR_DEFAULT);
	corpo.setPosition(x, y);

	setTextura("ratao", getTam());
	sprite.setPosition(x, y);
	atualizaLado();
}

Ratao::~Ratao()
{
}

void Ratao::criarTerra(int dir, int ind)
{
	float spawn_x = x_batida + 20;
	float spawn_y = y_batida;
	if (dir == 1)
		spawn_x = x_batida + largura_batida - 20;

	//mudar para o novo ///////////////////////////////////////////////////
	Gerenciador_colisao* pGC = Gerenciador_colisao::getGerenciadorColisao();
	if (!pGC)
		return;

	Proj_boss* novoProjetil = new Proj_boss(dir, static_cast<int>(spawn_x), static_cast<int>(spawn_y));
	if (novoProjetil)
	{
		novoProjetil->setFragmentos(3 + (ind % 3));
		pGC->adicionarProjetil(novoProjetil);
	}
}

void Ratao::verificarAtaque()
{
	if (ataque_cd > 0)
	{
		ataque_cd--;
		return;
	}

	// Usa detectarJogador() da base, que compara com dist_detec
	if (jogador && detectarJogador())
	{
		if ((rand() % 100) < chance_atacar)
		{
			batidas_restantes = 6;       
			batidas_esq = 0;
			batidas_dir = 0;
			bater_cd = 20;				//Tempo antes da loucura comecar
			lado_batida = lado;
			batendo = false;
			velx = 0.0f;

			estado = "BATENDO";
		}
	}
}

void Ratao::idle()
{
	verificarAtaque();
	if (estado == "BATENDO")
		return;

	movimentoAleatorio();
}

void Ratao::movimentar()
{
	verificarAtaque();
	if (estado == "BATENDO")
		return;

	movimentoAleatorio();

	if (walk_cd > 0)
	{
		estado = "IDLE";
	}
}

void Ratao::bater()
{
	velx = 0.0f;

	if (batendo)
	{
		tempo_batida--;
		if (tempo_batida <= 0)
		{
			batendo = false;
		}
	}

	bater_cd--;
	if (bater_cd <= 0)
	{
		if (batidas_restantes > 0)
		{
			bater_cd = bater_tm;

			lado_batida = -lado_batida;
			lado = lado_batida;

			int indice = (lado_batida == -1) ? batidas_esq++ : batidas_dir++;

			float hitY = y + getTam().y - (altura_batida);
			float hitX;

			if (lado_batida == 1)
			{
				hitX = x + getTam().x; 
			}
			else
			{
				hitX = x - (largura_batida); 
			}

			x_batida = hitX;
			y_batida = hitY;
			batendo = true;
			tempo_batida = duracao_batida;

			criarTerra(lado_batida, indice);

			batidas_restantes--;
		}
		else
		{
			ataque_cd = ataque_tm;
			walk_cd = 60 + (rand() % 61);
			estado = "IDLE";
			batendo = false;
		}
	}
}

void Ratao::atualizaLado()
{
	//rato maldito tem flip invertido
	const sf::Texture* tex = sprite.getTexture();
	if (tex) {
		int w = tex->getSize().x;
		int h = tex->getSize().y;
		if (lado == 1) {
			sprite.setTextureRect(sf::IntRect(w, 0, -w, h));
			sprite.setOrigin(0.0f, 0.0f);
		}
		else {
			sprite.setTextureRect(sf::IntRect(0, 0, w, h));
			sprite.setOrigin(0.0f, 0.0f);
		}
	}
}

void Ratao::executar()
{
	if(estado == "IDLE")
	{
		idle();
	}
	else if (estado == "MOVENDO")
	{
		movimentar();
	}
	else if (estado == "BATENDO")
	{
		bater();
	}

	vely += gravidade;
	if (vely > max_vely * pot_queda)
	{
		vely = max_vely * pot_queda;
	}
	y += vely;
	setPos(sf::Vector2f(x, y));
	atualizaLado();

	if (tempo_imune > 0)
	{
		tempo_imune--;

		if ((tempo_imune / 5) % 2 == 0)
		{
			corpo.setFillColor(sf::Color(255, 120, 120));
			sprite.setColor(sf::Color(255, 120, 120));
		}
		else
		{
			corpo.setFillColor(COR_DEFAULT);
			sprite.setColor(sf::Color::White);
		}
	}
	else
	{
		if (batendo)
		{
			corpo.setFillColor(sf::Color(220, 50, 20));
			sprite.setColor(sf::Color(255, 180, 180));
		}
		else
		{
			corpo.setFillColor(COR_DEFAULT);
			sprite.setColor(sf::Color::White);
		}
	}

	if (num_vidas <= 0) // n sei se isso vai no gerenciador ou aqui, mas por enquanto ta aqui msm
	{
		Gerenciador_colisao* pGC = Gerenciador_colisao::getGerenciadorColisao();
		if (pGC)
		{
			pGC->removerInimigo(this);
		}
	}
}

void Ratao::colisao(Entidade* ent, sf::Vector2f ds)
{
	if (!ent)
		return;

	Jogador* pJog = dynamic_cast<Jogador*>(ent);
	if (pJog)
	{
		if ((pJog->getY() + pJog->getTam().y <= y + 25.0f) || (ds.x <= ds.y && pJog->getY() < y))
		{
			if (tempo_imune <= 0)
			{
				receberDano(1);
				tempo_imune = 60;

				pJog->setPos(sf::Vector2f(pJog->getX(), y - pJog->getTam().y - 8.0f));
				pJog->setChao(true);
				pJog->pular();
			}
		}
		return;
	}

	Inimigo::colisao(ent, ds);

	if (ds.x > ds.y && (estado == "MOVENDO" || estado == "IDLE"))
	{
		velx = 0.0f;
		estado = "IDLE";
	}
}

const sf::FloatRect Ratao::getHitboxBatida() const
{
	if (!batendo)
		return sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);

	return sf::FloatRect(
		(x_batida),
		(y_batida),
		(largura_batida),
		(altura_batida)
	);
}

const bool Ratao::getBatendo() const
{
	return batendo;
}

const short int Ratao::getForca() const
{
	return forca;
}

void Ratao::danificar(Jogador* p)
{ 
}

void Ratao::salvarDataBuffer()
{
	Inimigo::salvarDataBuffer();
	buffer << bater_cd << " ";
	buffer << batidas_restantes << " ";
	buffer << batidas_esq << " ";
	buffer << batidas_dir << " ";
	buffer << lado_batida << " ";
	buffer << batendo << " ";
	buffer << tempo_batida << " ";
	buffer << ataque_cd << " ";
	buffer << tempo_imune << " ";
	buffer << estado;
}

void Ratao::salvar()
{
	buffer.str(""); // Limpa dados de saves anteriores no buffer
	buffer.clear();

	salvarDataBuffer();
}