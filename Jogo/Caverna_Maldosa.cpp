#include "Caverna_Maldosa.h"
#include "Proj_top.h"

namespace Escavadores_intrepidos {
    namespace Fases {

        Caverna_Maldosa::Caverna_Maldosa(bool save, int numJogadores, Jogador* pJ1, Jogador* pJ2) :
            Fase(numJogadores, pJ1, pJ2), maxRato(5), contRato(0), maxMagma(50), contMagma(0)
        {
            if (!save)
            {
                tilemap.open("fases/caverna_maldosa.txt");
                criarCenario();
            }
            else
            {
                criarFundo();
                carregar();
            }

            faseConcluida = false;

            // Configure a fonte e o texto
            if (fonteTexto.loadFromFile("arial.ttf")) {
                textoFimDeFase.setFont(fonteTexto);
                textoFimDeFase.setCharacterSize(50);
                textoFimDeFase.setFillColor(sf::Color::Yellow);
                textoFimDeFase.setPosition(sf::Vector2f(200.f, 300.f));
            }
        }

        Caverna_Maldosa::~Caverna_Maldosa()
        {
        }

        void Caverna_Maldosa::criarMagma(sf::Vector2f pos, bool danoso)
        {
            Magma* magma = new Magma(pos.x, pos.y, GRID, GRID, 5, true, false);
            if (!danoso) {
                magma->setDanoso(false);
            }
            pGC->adicionarObstaculo(magma);
            magma->setAtivo(true);
        }

        void Caverna_Maldosa::criarRato(sf::Vector2f pos)
        {
            Rato* rato = new Rato(pos, sf::Vector2f(GRID, GRID), pJogador1, pJogador2);
            pGC->adicionarInimigo(rato);
        }

        void Caverna_Maldosa::criarFundo()
        {
            if (pGG)
            {
                sf::Texture* tex = pGG->getTextura("fundo");
                if (tex)
                {
                    tex->setRepeated(true);
                    sprite.setTexture(*tex);

                    sprite.setScale(3.0f, 3.0f); //relacao grid com o tamanho da textura

                    int larguraRepeticao = static_cast<int>(WIDTH / 3.0f);
                    int alturaRepeticao = static_cast<int>(HEIGHT / 3.0f);
                    sprite.setTextureRect(sf::IntRect(0, 0, larguraRepeticao, alturaRepeticao));
                    sprite.setPosition(0.0f, 0.0f);
                }
            }
        }

        void Caverna_Maldosa::criarEntidade(char tipo, sf::Vector2f pos)
        {
            switch (tipo)
            {
            case('#'):
                criarChao(pos);
                break;

            case('@'):
                if (contPlataformas < maxPlataformas)
                {
                    criarPlataforma(pos);
                    contPlataformas++;
                }
                break;

            case('j'):
                posJogador(pos);
                break;

            case('T'):
                criarTopeira(pos);
                break;

            case('t'):
            {
                if (contTopeiras < maxTopeiras && rand() % 3 != 0)
                {
                    criarTopeira(pos);
                    contTopeiras++;
                }
            }
            break;

            case('R'):
                criarRato(pos);
                break;

            case('r'):
            {
                if (contRato < maxRato && rand() % 3 != 0)
                {
                    criarRato(pos);
                    contRato++;
                }
            }
            break;

            case('M'):
                criarMagma(pos);
                contMagma++;
                break;

            case('m'):
            {
                if (contMagma < maxMagma && rand() % 3 != 0)
                {
                    criarMagma(pos);
                    contMagma++;
                }
                else if (contPlataformas < maxPlataformas)
                {
                    criarPlataforma(pos);
                    contPlataformas++;
                }
            }
            break;
            }
        }

        void Caverna_Maldosa::carregar()
        {
            map<int, string> arquivosSave =
            {
                {0, "saves/jogadorSave.txt"},
                {1, "saves/plataformaSave.txt"},
                {2, "saves/magmaSave.txt"},
                {3, "saves/topeiraSave.txt"},
                {4, "saves/ratoSave.txt"},
                {5, "saves/projTopSave.txt"},
                {6, "saves/chaoSave.txt"}
            };

            for (int i = 0; i < 7; i++)
            {
                ifstream arquivo(arquivosSave[i]);

                if (!arquivo.is_open()) continue;

                string linha;

                while (getline(arquivo, linha))
                {
                    if (linha.empty()) continue;

                    istringstream ss(linha);

                    float x, y;
                    bool ativo;

                    switch (i)
                    {
                    case 0: // Jogador
                    {
                        float velX, velY;
                        int num_vidas, pontos, inventario, t_dano;
                        ss >> x >> y >> ativo >> velX >> velY >> num_vidas >> pontos >> inventario >> t_dano;
                        Jogador* pAlvo = (!pJogador1 || pJogador1->getPos().x != 0.0f || pJogador1->getPos().y != 0.0f) && pJogador2 ? pJogador2 : pJogador1;
                        if (pAlvo)
                        {
                            pAlvo->setPos(sf::Vector2f(x, y));
                            pAlvo->setAtivo(ativo);
                            pAlvo->setVel(sf::Vector2f(velX, velY));
                            pAlvo->setNumVidas(num_vidas);
                            pAlvo->setInventario(inventario);
                            pAlvo->setTDano(t_dano);

                            Jogador::setPontos(pontos);
                        }
                        break;
                    }
                    case 1: // Plataforma
                    {
                        int ticks = 0;
                        bool danoso = false;
                        ss >> x >> y >> ativo >> ticks >> danoso;
                        criarPlataforma(sf::Vector2f(x, y), danoso);
                        Plataforma::setTicks(ticks);
                        break;
                    }
                    case 2: // Magma
                    {
                        int ticks = 0;
                        bool danoso = true;
                        ss >> x >> y >> ativo >> ticks >> danoso;
                        criarMagma(sf::Vector2f(x, y), danoso);
                        Magma::setTicks(ticks);
                        break;
                    }
                    case 3: // Topeira
                    {
                        float velX, velY;
                        int num_vidas, nivel_maldade, walk_cd, lado, x_alvo, tiro_cd;
                        string estado;

                        ss >> x >> y >> ativo >> velX >> velY >> num_vidas
                            >> nivel_maldade >> walk_cd >> lado >> x_alvo
                            >> tiro_cd >> estado;

                        Topeira* top = new Topeira(sf::Vector2f(x, y), sf::Vector2f(GRID * 2, GRID * 2), pJogador1, pJogador2);
                        if (top)
                        {
                            top->setAtivo(ativo);
                            top->setVel(sf::Vector2f(velX, velY));
                            top->setNumVidas(num_vidas);
                            top->setNivelMaldade(nivel_maldade);
                            top->setWalkCd(walk_cd);
                            top->setLado(lado);
                            top->setXAlvo(x_alvo);
                            top->setTiroCd(tiro_cd);
                            top->setEstado(estado);

                            pGC->adicionarInimigo(top);
                        }
                        break;
                    }
                    case 4: // Rato
                    {
                        float velX, velY;
                        int num_vidas, nivel_maldade, walk_cd, lado, x_alvo;
                        string estado;

                        ss >> x >> y >> ativo >> velX >> velY >> num_vidas
                            >> nivel_maldade >> walk_cd >> lado >> x_alvo
                            >> estado;

                        Rato* rato = new Rato(sf::Vector2f(x, y), sf::Vector2f(GRID, GRID), pJogador1, pJogador2);
                        if (rato)
                        {
                            rato->setAtivo(ativo);
                            rato->setVel(sf::Vector2f(velX, velY));
                            rato->setNumVidas(num_vidas);
                            rato->setNivelMaldade(nivel_maldade);
                            rato->setWalkCd(walk_cd);
                            rato->setLado(lado);
                            rato->setXAlvo(x_alvo);
                            rato->setEstado(estado);

                            pGC->adicionarInimigo(rato);
                        }
                        break;
                    }
                    case 5: // Tiro Topera
                    {
                        float velX, velY;
                        short int direcao;
                        int dano;

                        ss >> x >> y >> ativo >> velX >> velY >> direcao >> dano;

                        Proj_top* proj = new Proj_top(direcao, x, y);
                        if (proj)
                        {
                            proj->setAtivo(ativo);
                            proj->setVelX(velX);
                            proj->setVelY(velY);
                            proj->setDano(dano);

                            pGC->adicionarProjetil(proj);
                        }
                        break;
                    }
                    case 6: // chao
                    {
                        int ticks;
                        ss >> x >> y >> ativo >> ticks;

                        Chao* chao = new Chao(sf::Vector2f(x, y), sf::Vector2f(WIDTH, 300.0f));
                        if (chao)
                        {
                            chao->setAtivo(ativo);
                            chao->setTicks(ticks);

                            pGC->setChao(chao);
                        }
                        break;
                    }
                    }
                }
                arquivo.close();
            }
        }
    }
}