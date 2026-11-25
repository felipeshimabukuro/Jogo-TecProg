#include "Inimigo.h"
#include "Jogador.h"

using namespace Personagens;
using namespace Entidades;

const int Inimigo::walk_tm = 120;

Inimigo::Inimigo(ID id, const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j1, Jogador* j2):
Personagem(id, pos, tam),relogio(),pJogador1(j1),pJogador2(j2), dist_detec(100), nivel_maldade(rand()%5 + 1), 
jaDeuPontos(false), pontosBase(nivel_maldade * 100)
{
	inicializa();
	srand(time(NULL));
}

Inimigo::~Inimigo() 
{

}

void Inimigo::inicializa() {
	vel = sf::Vector2f(max_velx/5.0f, max_vely/5.0f);
	dano = nivel_maldade;

	corpo.setSize(sf::Vector2f(GRID, GRID));
	corpo.setFillColor(sf::Color::Red);
	corpo.setPosition(x, y);
}

sf::Vector2f Inimigo::distanciaAlvo(sf::Vector2f posJogador, sf::Vector2f posInimigo)
{
	sf::Vector2f distancia;
	distancia.x = fabs(posJogador.x - posInimigo.x);
	distancia.y = fabs(posJogador.y - posInimigo.y);

	return distancia;
}

void Inimigo::persegueJogador(Jogador* j) {
	if (!j) return;

	sf::Vector2f posJogador = j->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	float tamJogadorX = j->getTam().x;
	float tamInimigoX = corpo.getSize().x;
	float deltaX = 0.0f;

	if (posJogador.x > posInimigo.x) {
		// Inimigo à esquerda do jogador: persegue para a direita (+X)
		float gap = posJogador.x - (posInimigo.x + tamInimigoX);
		if (gap > 0.0f) {
			deltaX = (gap < vel.x) ? gap : vel.x;
			x += deltaX;
			lado = 1;
		}
	}
	else {
		// Inimigo à direita do jogador: persegue para a esquerda (-X)
		float gap = posInimigo.x - (posJogador.x + tamJogadorX);
		if (gap > 0.0f) {
			deltaX = (gap < vel.x) ? gap : vel.x;
			x -= deltaX;
			lado = -1;
		}
	}

	atualizaLado();

	sf::Vector2f pos (x, y);
	setPos(pos);
}

void Inimigo::mover() 
{
	aplicarGravidade();
	x += velx;

	sf::Vector2f pos(x, y);
	setPos(pos);
}

void Inimigo::receberDano(int dano) {
	num_vidas -= dano;
	if (num_vidas > 0) {	
		cout << "Vidas inimigo " << num_vidas << endl;
	}
	else {
		cout << "Inimigo neutralizado" << endl;
		setAtivo(false);
		jaDeuPontos = true;

		float tempoDecorrido = relogio.getElapsedTime().asSeconds();

		int pontosFinais = pontosBase - (int)(tempoDecorrido * 2);

		if (pontosFinais < pontosBase * 0.2f) {
			pontosFinais = pontosBase * 0.2f;
		}

		Jogador::setPontos( Jogador::getPontos()  + pontosFinais);
	}
}

void Inimigo::executar() {
	mover();
}

void Inimigo::colisao(Entidade* ent, sf::Vector2f ds) 
{
	Jogador* pJog = dynamic_cast<Jogador*>(ent);
	if (pJog) 
	{
		if (ds.x > ds.y && pJog->getY() > (y - GRID / 2.0f)) 
		{
			if (pJog->getX() < x) 
			{
				pJog->setPos(sf::Vector2f(x - pJog->getTam().x, pJog->getY()));
			}
			else 
			{
				pJog->setPos(sf::Vector2f(x + corpo.getSize().x, pJog->getY()));
			}
		}
		return;
	}

	Entidade::colisao(ent, ds);

	if (ds.x <= ds.y) {
		if (getY() < ent->getY() && vely >= 0.0f) {
			vely = 0.0f;
			chao = true;
		}
		else if (getY() > ent->getY() && vely < 0.0f) {
			vely = 0.0f;
		}
	}
	else {
		x_alvo = static_cast<int>(x);
		lado = -lado;
		atualizaLado();
		walk_cd = 45;
	}
}

const bool Inimigo::getBoss() const {
	return boss;
}

void Inimigo::movimentoAleatorio()
{
	if (static_cast<int>(x) == x_alvo)
	{
		if (walk_cd > 0)
		{
			walk_cd--;
			return;
		}

		float distancia = static_cast<float>((rand() % 100) + 50);

		if (rand() % 2 == 0) 
		{
			x_alvo = static_cast<int>(x + distancia);
		}
		else 
		{
			x_alvo = static_cast<int>(x - distancia);
		}

		if (x_alvo < 0) {
			x_alvo = 0;
		}
		if (x_alvo > WIDTH - corpo.getSize().x) {
			x_alvo = WIDTH - corpo.getSize().x;
		}
	}

	float movX = x_alvo - x;
	if (fabs(movX) > vel.x)
	{
		if (movX > 0.0f)
		{
			x += vel.x;
			lado = 1; 
		}
		else
		{
			x -= vel.x;
			lado = -1; 
		}
	}
	else
	{
		x = static_cast<float>(x_alvo);
		walk_cd = walk_tm + (rand()%60 - 30);
	}

	atualizaLado();
	sf::Vector2f pos(x, y);
	setPos(pos);
}

void Inimigo::atualizaLado()
{
	Jogador* jogador = getJogadorAlvo();
	if (jogador)
	{
		if (detectarJogador())
		{
			if (jogador->getCorpo().getPosition().x > x)
			{
				lado = 1;
			}
			else
			{
				lado = -1;
			}
		}

		const sf::Texture* tex = sprite.getTexture();
		if (tex) 
		{
			int w = tex->getSize().x;
			int h = tex->getSize().y;
			if (lado == 1) 
			{
				sprite.setTextureRect(sf::IntRect(0, 0, w, h));
				sprite.setOrigin(0.0f, 0.0f);
			}
			else 
			{
				sprite.setTextureRect(sf::IntRect(w, 0, -w, h)); // Espelha horizontalmente
				sprite.setOrigin(0.0f, 0.0f);
			}
		}
	}
}

bool Inimigo::detectarJogador()
{
	Jogador* jogador = getJogadorAlvo();
	if (jogador == NULL) return false;

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
	return (distancia.x < dist_detec && distancia.y < dist_detec);
}

void Inimigo::salvarDataBuffer()
{
	Personagem::salvarDataBuffer();
	buffer << nivel_maldade << " ";
	buffer << walk_cd << " ";
	buffer << lado << " ";
	buffer << x_alvo << " ";
	// Projeteis pendentes sla como faz ainda
}

void Inimigo::setNivelMaldade(const int nm) 
{
	nivel_maldade = nm;
	dano = nivel_maldade;
}

void Inimigo::setWalkCd(const int cd) 
{
	walk_cd = cd;
}

void Inimigo::setLado(const int l) 
{
	lado = l;
}

void Inimigo::setXAlvo(const int xa) 
{
	x_alvo = xa;
}

Jogador* Inimigo::getJogadorAlvo()
{
	if (!pJogador1 && !pJogador2) return NULL;

	bool jog1Valido = pJogador1 && pJogador1->getAtivo();
	bool jog2Valido = pJogador2 && pJogador2->getAtivo();

	if (jog1Valido && jog2Valido)
	{
		sf::Vector2f posInimigo = corpo.getPosition();
		sf::Vector2f dist1 = distanciaAlvo(pJogador1->getCorpo().getPosition(), posInimigo);
		sf::Vector2f dist2 = distanciaAlvo(pJogador2->getCorpo().getPosition(), posInimigo);

		// Compara quem está mais perto somando a distância X e Y
		if ((dist1.x + dist1.y) < (dist2.x + dist2.y)) return pJogador1;
		else return pJogador2;
	}
	else if (jog1Valido) return pJogador1;
	else if (jog2Valido) return pJogador2;

	return NULL;
}

int Inimigo::getPontosBase() const {
	return pontosBase;
}
bool Inimigo::getJaDeuPontos() const {
	return jaDeuPontos;
}
void Inimigo::setJaDeuPontos(bool status) {
	jaDeuPontos = status;
}

void Inimigo::setJogador1(Jogador* j)
{
	pJogador1 = j;
}

void Inimigo::setJogador2(Jogador* j)
{
	pJogador2 = j;
}