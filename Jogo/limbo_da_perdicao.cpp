#include "Limbo_da_perdicao.h"
#include "Limbo_da_perdicao.h"
#include "Proj_top.h"
#include "Proj_boss.h"

namespace Escavadores_intrepidos {
    namespace Fases {

        Limbo_da_perdicao::Limbo_da_perdicao(bool save, int numJogadores, Jogador* pJ1, Jogador* pJ2) :Fase(numJogadores, pJ1, pJ2)
            , maxRatao(5), contRatao(0), maxEspinhos(50), contEspinhos(0)
        {
            if (!save)
            {
                tilemap.open("fases/limbo_da_perdicao.txt");
                criarCenario();
            }
            else
            {
                criarFundo();
                carregar();
            }

            if (fonteTexto.loadFromFile("arial.ttf")) {
                textoFimDeFase.setFont(fonteTexto);
                textoFimDeFase.setCharacterSize(50);
                textoFimDeFase.setFillColor(sf::Color::Yellow);
                textoFimDeFase.setPosition(sf::Vector2f(200.f, 300.f));
            }
        }

        Limbo_da_perdicao::~Limbo_da_perdicao()
        {
        }


        /*void Caverna_Maldosa::criarObstaculos() {

        }*/

        void Limbo_da_perdicao::criarEspinho(sf::Vector2f pos)
        {
            Espinho* espinho = new Espinho(pos.x, pos.y, GRID, GRID, 5, true, false, pJogador1, pJogador2);
            pGC->adicionarObstaculo(espinho);
            espinho->setAtivo(1);
        }

        void Limbo_da_perdicao::criarRatao(sf::Vector2f pos)
        {
            Ratao* ratao = new Ratao(pos, sf::Vector2f(GRID * 2, GRID * 2), pJogador1, pJogador2);
            pGC->adicionarInimigo(ratao);
        }

        /* void Caverna_Maldosa::criarInimigos() {

        }*/

        void Limbo_da_perdicao::criarFundo()
        {
            if (pGG)
            {
                sf::Texture* tex = pGG->getTextura("fundo2");
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

        void Limbo_da_perdicao::criarEntidade(char tipo, sf::Vector2f pos) {
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
                }
            }
            break;

            case('B'):
            {
                criarRatao(pos);
                contRatao++;
            }
            break;

            case('b'):
            {
                if (contRatao < maxRatao && rand() % 3 != 0)
                {
                    criarRatao(pos);
                    contRatao++;
                }
            }
            break;

            case('E'):
                criarEspinho(pos);
                contEspinhos++;
                break;

            case('e'):
            {
                if (contEspinhos < maxEspinhos && rand() % 3 != 0)
                {
                    criarEspinho(pos);
                    contEspinhos++;
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

        void Limbo_da_perdicao::carregar()
        {
            map<int, string> arquivosSave =
            {
                {0, "saves/jogadorSave.txt"},
                {1, "saves/plataformaSave.txt"},
                {2, "saves/espinhoSave.txt"},
                {3, "saves/topeiraSave.txt"},
                {4, "saves/rataoSave.txt"},
                {5, "saves/projTopSave.txt"},
                {6, "saves/projBossSave.txt"},
                {7, "saves/chaoSave.txt"}
            };

            for (int i = 0; i < 8; i++)
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
                    case 2: // Espinho
                    {
                        ss >> x >> y >> ativo;
                        criarEspinho(sf::Vector2f(x, y));
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
                    case 4: // Ratao
                    {
                        float velX, velY;
                        int num_vidas, nivel_maldade, walk_cd, lado, x_alvo;
                        int bater_cd, batidas_restantes, batidas_esq, batidas_dir, lado_batida;
                        bool batendo;
                        int tempo_batida, ataque_cd, tempo_imune;
                        string estado;

                        ss >> x >> y >> ativo >> velX >> velY >> num_vidas
                            >> nivel_maldade >> walk_cd >> lado >> x_alvo
                            >> bater_cd >> batidas_restantes >> batidas_esq >> batidas_dir
                            >> lado_batida >> batendo >> tempo_batida >> ataque_cd
                            >> tempo_imune >> estado;

                        Ratao* ratao = new Ratao(sf::Vector2f(x, y), sf::Vector2f(GRID * 2, GRID * 2), pJogador1, pJogador2);
                        if (ratao)
                        {
                            ratao->setAtivo(ativo);
                            ratao->setVel(sf::Vector2f(velX, velY));
                            ratao->setNumVidas(num_vidas);
                            ratao->setNivelMaldade(nivel_maldade);
                            ratao->setWalkCd(walk_cd);
                            ratao->setLado(lado);
                            ratao->setXAlvo(x_alvo);

                            ratao->setBaterCd(bater_cd);
                            ratao->setBatidasRestantes(batidas_restantes);
                            ratao->setBatidasEsq(batidas_esq);
                            ratao->setBatidasDir(batidas_dir);
                            ratao->setLadoBatida(lado_batida);
                            ratao->setBatendo(batendo);
                            ratao->setTempoBatida(tempo_batida);
                            ratao->setAtaqueCd(ataque_cd);
                            ratao->setTempoImune(tempo_imune);
                            ratao->setEstado(estado);

                            ratao->atualizaLado();
                            pGC->adicionarInimigo(ratao);
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
                    case 6: // Tiro boss
                    {
                        float velX, velY;
                        short int direcao;
                        int fragmentos;

                        ss >> x >> y >> ativo >> velX >> velY >> direcao >> fragmentos;

                        Proj_boss* proj = new Proj_boss(direcao, static_cast<int>(x), static_cast<short int>(y));
                        if (proj)
                        {
                            proj->setPos(sf::Vector2f(x, y));
                            proj->setAtivo(ativo);
                            proj->setVelX(velX);
                            proj->setVelY(velY);
                            proj->setFragmentos(fragmentos);

                            pGC->adicionarProjetil(proj);
                        }
                        break;
                    }
                    case 7: // chao
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