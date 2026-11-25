#include "Bibliotecas.h"
#include "Menu.h"
#include "Jogo.h"

Menu::Menu(Jogo* pJogo) :
    pJogo(pJogo),
    opcaoSelecionada(0),
    faseMapeada(1),
    sairDoLoop(false),
    estadoAtual(EstadoMenu::PRINCIPAL)
{
    /*sf::Texture* texFundo = pGG->getTextura("menu");
    if (texFundo) 
    {
        fundoMenu.setSize(sf::Vector2f(WIDTH, HEIGHT));
        fundoMenu.setPosition(0.0f, 0.0f);
        fundoMenu.setTexture(texFundo);
    }*/

    if (!fonte.loadFromFile("arial.ttf")) {
        std::cout << "Erro ao carregar a fonte do menu!" << std::endl;
    }

    tituloMenu.setFont(fonte);
    tituloMenu.setString("Cavadores Intrepidos");
    tituloMenu.setCharacterSize(50);
    tituloMenu.setFillColor(sf::Color::White);
    tituloMenu.setPosition(200.0f, 100.0f);

    atualizarOpcoesBotoes({ "Novo Jogo", "Carregar Jogo", "Ranking", "Sair" });
}

Menu::~Menu() {
}

void Menu::atualizarOpcoesBotoes(const std::vector<std::string>& opcoes, float posYInicial) {
    textosBotoes.clear();
    opcaoSelecionada = 0;

    for (size_t i = 0; i < opcoes.size(); i++) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(opcoes[i]);
        texto.setCharacterSize(30);
        texto.setPosition(175.0f, posYInicial + (i * 60.0f));
        texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        textosBotoes.push_back(texto);
    }
}

void Menu::carregarExibicaoRanking() {
    textosRanking.clear();

    std::ifstream arqLeitura("saves/ranking.txt");
    std::string nome;
    int pontos = 0;
    int jogadores = 1;
    int pos = 0;

    if (arqLeitura.is_open()) {
        while (arqLeitura >> nome >> pontos >> jogadores && pos < 5) {
            sf::Text linhaTexto;
            linhaTexto.setFont(fonte);
            linhaTexto.setCharacterSize(26);
            linhaTexto.setFillColor(pos == 0 ? sf::Color::Yellow : sf::Color::White);
            linhaTexto.setPosition(200.0f, 250.0f + (pos * 40.0f));
            linhaTexto.setString(
                std::to_string(pos + 1) + ". " + nome + " - " +
                std::to_string(pontos) + " pts (" + std::to_string(jogadores) + " Jog.)"
            );
            textosRanking.push_back(linhaTexto);
            pos++;
        }
        arqLeitura.close();
    }

    if (textosRanking.empty()) {
        sf::Text vazio;
        vazio.setFont(fonte);
        vazio.setCharacterSize(28);
        vazio.setFillColor(sf::Color::White);
        vazio.setPosition(220.0f, 240.0f);
        vazio.setString("Nenhuma pontuacao registrada ainda.");
        textosRanking.push_back(vazio);
    }
}

void Menu::moverCima() {
    if (opcaoSelecionada - 1 >= 0) {
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada--;
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void Menu::moverBaixo() {
    if (opcaoSelecionada + 1 < static_cast<int>(textosBotoes.size())) {
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada++;
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void Menu::interagir() {
    if (estadoAtual == EstadoMenu::PRINCIPAL) {
        if (opcaoSelecionada == 0) {
            estadoAtual = EstadoMenu::SELECIONAR_FASE;
            atualizarOpcoesBotoes({ "Jogar Caverna Maldosa (Fase1)", "Jogar Limbo da Perdicao (Fase2)", "Voltar" });
        }
        else if (opcaoSelecionada == 1) {
            pJogo->solicitarCarregamento();
            sairDoLoop = true;
        }
        else if (opcaoSelecionada == 2) {
            estadoAtual = EstadoMenu::RANKING;
            tituloMenu.setString("RANKING");
            carregarExibicaoRanking();
            atualizarOpcoesBotoes({ "Voltar" }, 450.0f);
        }
        else if (opcaoSelecionada == 3) {
            pJogo->getWindow()->close();
        }
    }

    else if (estadoAtual == EstadoMenu::SELECIONAR_FASE) {
        if (opcaoSelecionada == 0) {
            faseMapeada = 1;
            estadoAtual = EstadoMenu::QTD_JOGADORES;
            atualizarOpcoesBotoes({ "1 Jogador", "2 Jogadores", "Voltar" });
        }
        else if (opcaoSelecionada == 1) {
            faseMapeada = 2;
            estadoAtual = EstadoMenu::QTD_JOGADORES;
            atualizarOpcoesBotoes({ "1 Jogador", "2 Jogadores", "Voltar" });
        }
        else if (opcaoSelecionada == 2) {
            estadoAtual = EstadoMenu::PRINCIPAL;
            atualizarOpcoesBotoes({ "Novo Jogo", "Carregar Jogo", "Ranking", "Sair" });
        }
    }

    else if (estadoAtual == EstadoMenu::QTD_JOGADORES) {
        if (opcaoSelecionada == 0) {
            pJogo->carregarFase(faseMapeada, 1);
            sairDoLoop = true;
        }
        else if (opcaoSelecionada == 1) {
            pJogo->carregarFase(faseMapeada, 2);
            sairDoLoop = true;
        }
        else if (opcaoSelecionada == 2) {
            estadoAtual = EstadoMenu::SELECIONAR_FASE;
            atualizarOpcoesBotoes({ "Jogar Caverna Maldosa (Fase1)", "Jogar Limbo da Perdicao (Fase2)", "Voltar" });
        }
    }

    else if (estadoAtual == EstadoMenu::RANKING) {
        if (opcaoSelecionada == 0) {
            estadoAtual = EstadoMenu::PRINCIPAL;
            tituloMenu.setString("Cavadores Intrepidos");
            atualizarOpcoesBotoes({ "Novo Jogo", "Carregar Jogo", "Ranking", "Sair" });
        }
    }

    else if (estadoAtual == EstadoMenu::PAUSE) {
        if (opcaoSelecionada == 0) {
            sairDoLoop = true;
        }
        else if (opcaoSelecionada == 1) {
            pJogo->salvar();
            textosBotoes[1].setString("Jogo Salvo!");
        }
        else if (opcaoSelecionada == 2) {
            pJogo->irParaMenu();
            sairDoLoop = true;
        }
    }

    for (size_t i = 0; i < textosBotoes.size(); i++) {
        if (static_cast<int>(i) == opcaoSelecionada) {
            textosBotoes[i].setFillColor(sf::Color::Red);
        }
        else {
            textosBotoes[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::executarTelaPause() {
    estadoAtual = EstadoMenu::PAUSE;

    tituloMenu.setString("JOGO PAUSADO");
    tituloMenu.setPosition(250.0f, 100.0f);

    atualizarOpcoesBotoes({ "Continuar", "Salvar Jogo", "Voltar Menu Principal"});

    sairDoLoop = false;
    sf::RenderWindow* window = pJogo->getWindow();

    Gerenciadores::Gerenciador_eventos* pEv = Gerenciadores::Gerenciador_eventos::getGerenciadorEventos();
    pEv->setMenu(this);

    while (window->isOpen() && !sairDoLoop) {
        pEv->executar();

        window->clear(sf::Color::Black);
        desenhar();
        window->display();
    }

    pEv->setMenu(NULL);
}

void Menu::executar() {
    if (pGG) {
        sf::Texture* texFundo = pGG->getTextura("menu");
        if (texFundo) {
            fundoMenu.setSize(sf::Vector2f(WIDTH, HEIGHT));
            fundoMenu.setPosition(0.0f, 0.0f);
            fundoMenu.setTexture(texFundo);
        }
    }
    estadoAtual = EstadoMenu::PRINCIPAL;
    sairDoLoop = false;

    tituloMenu.setString("Cavadores Intrepidos");
    tituloMenu.setPosition(147.5f, 160.0f);

    atualizarOpcoesBotoes({ "Novo Jogo", "Carregar Jogo", "Ranking", "Sair" });

    sf::RenderWindow* window = pJogo->getWindow();

    Gerenciadores::Gerenciador_eventos* pEv = Gerenciadores::Gerenciador_eventos::getGerenciadorEventos();
    pEv->setMenu(this);

    while (window->isOpen() && !sairDoLoop) {
        pEv->executar();

        window->clear(sf::Color::Black);
        desenhar();
        window->display();
    }

    pEv->setMenu(NULL);
}

void Menu::desenhar() {
    sf::RenderWindow* window = pJogo->getWindow();
    if (estadoAtual == EstadoMenu::PRINCIPAL ||
        estadoAtual == EstadoMenu::SELECIONAR_FASE ||
        estadoAtual == EstadoMenu::QTD_JOGADORES)
    {
        window->draw(fundoMenu);
    }
    window->draw(tituloMenu);
    if (estadoAtual == EstadoMenu::RANKING) {
        for (auto& linha : textosRanking) {
            window->draw(linha);
        }
    }
    for (auto& texto : textosBotoes) {
        window->draw(texto);
    }
}

void Menu::setJogo(Jogo* p) {
    pJogo = p;
}

void Menu::registrarRanking(int pontos, int numJogadores) {
    sf::RenderWindow* window = pJogo->getWindow();
    if (!window) return;

    std::string nomeJogador = "";
    bool confirmado = false;

    sf::Text txtTitulo;
    txtTitulo.setFont(fonte);
    txtTitulo.setString("FASE 2 CONCLUIDA!");
    txtTitulo.setCharacterSize(45);
    txtTitulo.setFillColor(sf::Color::Yellow);
    txtTitulo.setPosition(200.0f, 80.0f);

    sf::Text txtInfo;
    txtInfo.setFont(fonte);
    txtInfo.setString("Pontuacao: " + std::to_string(pontos) + "  |  Jogadores: " + std::to_string(numJogadores));
    txtInfo.setCharacterSize(28);
    txtInfo.setFillColor(sf::Color::White);
    txtInfo.setPosition(200.0f, 160.0f);

    sf::Text txtInstrucao;
    txtInstrucao.setFont(fonte);
    txtInstrucao.setString("Digite seu nome e pressione ENTER para salvar:");
    txtInstrucao.setCharacterSize(26);
    txtInstrucao.setFillColor(sf::Color::Cyan);
    txtInstrucao.setPosition(200.0f, 240.0f);

    sf::Text txtNome;
    txtNome.setFont(fonte);
    txtNome.setCharacterSize(34);
    txtNome.setFillColor(sf::Color::Red);
    txtNome.setPosition(200.0f, 300.0f);

    while (window->isOpen() && !confirmado) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                return;
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!nomeJogador.empty()) {
                        nomeJogador.pop_back();
                    }
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    if (!nomeJogador.empty()) {
                        confirmado = true;
                    }
                }
                else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    if (c == ' ') c = '_';
                    if (nomeJogador.size() < 20) {
                        nomeJogador += c;
                    }
                }
            }
        }

        txtNome.setString(nomeJogador + "_");

        window->clear(sf::Color::Black);
        window->draw(txtTitulo);
        window->draw(txtInfo);
        window->draw(txtInstrucao);
        window->draw(txtNome);
        window->display();
    }

    if (confirmado && !nomeJogador.empty()) {
        struct RegistroRanking {
            std::string nome;
            int pontos;
            int jogadores;
        };

        std::vector<RegistroRanking> ranking;

        std::ifstream arqLeitura("saves/ranking.txt");
        if (arqLeitura.is_open()) {
            RegistroRanking reg;
            while (arqLeitura >> reg.nome >> reg.pontos >> reg.jogadores) {
                ranking.push_back(reg);
            }
            arqLeitura.close();
        }

        ranking.push_back({ nomeJogador, pontos, numJogadores });

        std::sort(ranking.begin(), ranking.end(), [](const RegistroRanking& a, const RegistroRanking& b) {
            return a.pontos > b.pontos;
            });

        std::ofstream arqEscrita("saves/ranking.txt");
        if (arqEscrita.is_open()) {
            for (size_t i = 0; i < ranking.size(); i++) {
                arqEscrita << ranking[i].nome << " " << ranking[i].pontos << " " << ranking[i].jogadores << "\n";
            }
            arqEscrita.close();
        }
    }
}
