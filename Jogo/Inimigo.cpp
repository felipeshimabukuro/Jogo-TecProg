#include "Inimigo.h"
#include "Jogador.h"

using namespace Personagens;

const int Inimigo::walk_tm = 120;

Inimigo::Inimigo(const sf::Vector2f pos, const sf::Vector2f tam, Jogador* j):
Personagem(pos,tam),relogio(),jogador(j), dist_detec(100)
{
	inicializa();
	srand(time(NULL));
	//moveAleatorio = rand() % 1;
}

Inimigo::~Inimigo() {

}

void Inimigo::inicializa() {
	vel = sf::Vector2f(max_velx/5.0f, max_vely/5.0f);

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

void Inimigo::mover() {
	if (vely < max_vely) {
		vely += gravidade;
	}
	y += vely;

	sf::Vector2f pos(x, y);
	setPos(pos);
}

void Inimigo::salvar() {

}

void Inimigo::receberDano(int dano) {
	if (num_vidas > 0) {
		num_vidas -= dano;
		cout << "Vidas inimigo" << num_vidas << endl;
	}
	else {
		setAtivo(false);
	}
}

void Inimigo::setPos(const sf::Vector2f pos) {
	x = pos.x; 
	y = pos.y;
	corpo.setPosition(x, y);
	sprite.setPosition(x, y); 
}

void Inimigo::executar() {
	mover();
}

void Inimigo::colisao(Entidade* ent, sf::Vector2f ds) {
	
	Entidades::Entidade::colisao(ent, ds);

	if (ds.x <= ds.y) {
		// Só zera vely se o inimigo estiver acima do obstáculo e caindo para baixo
		if (getY() < ent->getY() && vely >= 0.0f) {
			vely = 0.0f;
			chao = true;
		}
		else if (getY() > ent->getY() && vely < 0.0f) {
			vely = 0.0f; // Bateu a cabeça por baixo
		}
	}
	else {
		// Colisão horizontal (bateu de lado na parede)
		x_alvo = static_cast<int>(x);
		lado = -lado;
		atualizaLado();
		walk_cd = 45; // Pausa o movimento contra a parede
	}
}

const bool Inimigo::getBoss() const {
	return boss;
}

std::list<Entidades::Projetil*>* Inimigo::getProjeteisPendentes() {
	return &projeteisPendentes;
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
	if (jogador == NULL) return false;

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f distancia = distanciaAlvo(posJogador, posInimigo);
	return (distancia.x < dist_detec && distancia.y < dist_detec);
}