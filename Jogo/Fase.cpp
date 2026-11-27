#include "Fase.h"

namespace Escavadores_intrepidos {
	namespace Fases {

		Fase::Fase(int numJogadores, Jogador* pJ1, Jogador* pJ2) :Ente(),
			maxTopeiras(5),
			contTopeiras(0),
			maxPlataformas(900),
			contPlataformas(0),
			lista_ents(),
			pGC(Gerenciador_colisao::getGerenciadorColisao()),
			pEv(Gerenciador_eventos::getGerenciadorEventos()),
			pJogador1(pJ1),
			pJogador2(pJ2),
			numJogadores(numJogadores),
			venceu(false)
		{
			if (pGC) {
				pGC->setListaEntidade(&lista_ents);
			}

			if (pGC) {
				pGC->setJogador1(pJogador1);
				pGC->setJogador2(pJogador2);
			}

			if (pEv) {
				pEv->setJogador1(pJogador1);
				pEv->setJogador2(pJogador2);
			}

			faseConcluida = false;
		}

		Fase::~Fase()
		{
			if (pEv) {
				pEv->setJogador1(NULL);
				pEv->setJogador2(NULL); // <--
			}
			if (pGC) {
				pGC->limpar();
			}
			pJogador1 = NULL;
			pJogador2 = NULL; // <--
			pGC = NULL;
			pEv = NULL;
		}

		void Fase::blocosColocados() {
			if (pJogador1 != NULL) {
				list<Obstaculo*>* pendentes = pJogador1->getBlocosPendentes();

				list<Obstaculo*>::iterator it = pendentes->begin();
				while (it != pendentes->end()) {
					Obstaculo* bloco = *it;

					if (bloco != NULL) {
						if (pGC->posicaoLivre(bloco->getPos(), bloco->getTam())) {
							pGC->adicionarObstaculo(bloco);
						}
						else {
							pJogador1->addInventario();
							delete bloco;
							bloco = NULL;
						}
					}
					it = pendentes->erase(it);
				}
			}
			if (pJogador2 != NULL) {
				list<Obstaculo*>* pendentes2 = pJogador2->getBlocosPendentes();
				list<Obstaculo*>::iterator it2 = pendentes2->begin();
				while (it2 != pendentes2->end()) {
					Obstaculo* bloco = *it2;
					if (bloco != NULL) {
						if (pGC->posicaoLivre(bloco->getPos(), bloco->getTam())) {
							pGC->adicionarObstaculo(bloco);
						}
						else {
							pJogador2->addInventario();
							delete bloco;
						}
					}
					it2 = pendentes2->erase(it2);
				}
			}
		}

		void Fase::criarTopeira(sf::Vector2f pos) {
			Topeira* topeira = new Topeira(pos, sf::Vector2f(GRID * 2, GRID * 2), pJogador1, pJogador2);
			pGC->adicionarInimigo(topeira);
		}

		void Fase::criarChao(sf::Vector2f pos)
		{
			Chao* chao = new Chao(pos, sf::Vector2f(WIDTH, 300.0f));
			pGC->setChao(chao);
		}

		void Fase::criarPlataforma(sf::Vector2f pos, bool danoso)
		{
			Plataforma* terra = new Plataforma(pos.x, pos.y, GRID, GRID, 0, false, true);
			if (danoso) {
				terra->setDanoso(true);
			}
			pGC->adicionarObstaculo(terra);
			terra->setAtivo(1);
		}

		void Fase::posJogador(sf::Vector2f pos)
		{
			pJogador1->setPos(pos);
			if (pJogador2) {
				pJogador2->setPos(sf::Vector2f(pos.x + GRID, pos.y));
			}
		}

		void Fase::criarCenario()
		{
			criarFundo();

			string linha;
			if (!tilemap.is_open())
			{
				cout << "Erro ao abrir o arquivo de tilemap!" << endl;
				return;
			}

			int i = 0;
			while (getline(tilemap, linha))
			{
				for (int j = 0; j < linha.length(); j++)
				{
					if (linha[j] != ' ')
					{
						sf::Vector2f pos(j * GRID, i * GRID);
						criarEntidade(linha[j], pos);
					}
				}
				i++;
			}
			tilemap.close();
		}

		void Fase::salvar()
		{
			lista_ents.salvar();
		}

		const bool Fase::getVenceu() const
		{
			return venceu;
		}

		const int Fase::getNumJogadores() const
		{
			return numJogadores;
		}

		void Fase::executar() {
			bool faseRolando = true;

			while (pGG->verificaJanelaAberta() && faseRolando)
			{
				if (pEv->deveSairDaFase())
				{
					return;
				}

				if (!faseConcluida)
				{
					pEv->executar();
					lista_ents.percorrer();
					pGC->executar();
					blocosColocados();

					bool temInimigoVivo = false;
					for (int i = 0; i < lista_ents.getTamanho(); i++) {
						Entidade* ent = lista_ents[i];
						if (ent && ent->getAtivo()) {
							if (dynamic_cast<Inimigo*>(ent)) {
								temInimigoVivo = true;
								break;
							}
						}
					}

					bool jogadorVivo = false;
					if (pJogador1 && pJogador1->getAtivo()) jogadorVivo = true;
					if (pJogador2 && pJogador2->getAtivo()) jogadorVivo = true;

					if (!temInimigoVivo) {
						venceu = true;
						faseConcluida = true;
						return;
					}
					else if (!jogadorVivo) {
						faseConcluida = true;
						textoFimDeFase.setString("Game Over!\nPontos do Time: " + to_string(Jogador::getPontos()));
					}

					if (!faseConcluida) {
						if (pJogador1 && !pJogador1->getAtivo()) {
							pJogador1 = NULL;
							pEv->setJogador1(NULL);
							for (int i = 0; i < lista_ents.getTamanho(); i++) {
								Inimigo* ini = dynamic_cast<Inimigo*>(lista_ents[i]);
								if (ini) ini->setJogador1(NULL);
							}
						}
						if (pJogador2 && !pJogador2->getAtivo()) {
							pJogador2 = NULL;
							pEv->setJogador2(NULL);
							for (int i = 0; i < lista_ents.getTamanho(); i++) {
								Inimigo* ini = dynamic_cast<Inimigo*>(lista_ents[i]);
								if (ini) ini->setJogador2(NULL);
							}
						}

						pGC->limparDestruidos();
						lista_ents.limparDestruidos();
					}
					else {
						pEv->setJogador1(NULL);
						pEv->setJogador2(NULL);
					}
				}

				pGG->limpaJanela();
				pGG->getWindow()->draw(sprite);

				if (!faseConcluida) {
					lista_ents.desenharTodas(pGG);
					desenharPontuacao();
				}
				else {
					pGG->getWindow()->draw(textoFimDeFase);
					pEv->executar();
				}

				pGG->mostrarJanela();
			}
		}

		void Fase::desenharPontuacao()
		{
			sf::RenderWindow* window = pGG->getWindow();
			if (!window) return;

			textoPontuacao.setFont(fonteTexto);
			textoPontuacao.setCharacterSize(28);
			textoPontuacao.setFillColor(sf::Color::White);
			textoPontuacao.setString("Pontos: " + to_string(Jogador::getPontos()));

			float larguraTexto = textoPontuacao.getLocalBounds().width;
			float posX = static_cast<float>(window->getSize().x) - larguraTexto - 20.0f;
			float posY = 15.0f;

			textoPontuacao.setPosition(posX, posY);
			window->draw(textoPontuacao);
		}
	}
}