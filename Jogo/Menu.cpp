#include "Bibliotecas.h"
#include "Menu.h"
#include "Jogo.h"

Menu::Menu(Jogo* pJogo) :
    Ente(ID::vazio),
    pJogo(pJogo),
    opcaoSelecionada(0),
    sairDoLoop(false),
    estadoAtual(EstadoMenu::PRINCIPAL)
{
    if (!fonte.loadFromFile("arial.ttf")) {
        std::cout << "Erro ao carregar a fonte do menu!" << std::endl;
    }

    tituloMenu.setFont(fonte);
    tituloMenu.setString("Cavadores Intrépidos");
    tituloMenu.setCharacterSize(50);
    tituloMenu.setFillColor(sf::Color::White);
    tituloMenu.setPosition(200.0f, 100.0f);

    std::vector<std::string> opcoes = { "Jogar Caverna_Maldosa (Fase1)", "Jogar Limbo da Perdicao (Fase2)", "Sair" };

    for (size_t i = 0; i < opcoes.size(); i++) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(opcoes[i]);
        texto.setCharacterSize(30);
        texto.setPosition(300.0f, 250.0f + (i * 60.0f));

        if (i == 0) {
            texto.setFillColor(sf::Color::Red);
        }
        else {
            texto.setFillColor(sf::Color::White);
        }

        textosBotoes.push_back(texto);
    }
}

Menu::~Menu() {
}

void Menu::moverCima() {
    if (opcaoSelecionada - 1 >= 0) {
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada--;
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void Menu::moverBaixo() {
    if (opcaoSelecionada + 1 < textosBotoes.size()) {
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada++;
        textosBotoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void Menu::interagir() {
    if (estadoAtual == EstadoMenu::PRINCIPAL) {
        if (opcaoSelecionada == 0) {
            pJogo->carregarFase(1);
            sairDoLoop = true;
        }
        else if (opcaoSelecionada == 1) {
            pJogo->carregarFase(2);
            sairDoLoop = true;
        }
        else if (opcaoSelecionada == 2) {
            exit(0);
        }
    }
    else if (estadoAtual == EstadoMenu::PAUSE) {
        if (opcaoSelecionada == 0) {
            sairDoLoop = true;
        }
        else if (opcaoSelecionada == 1) {
            pJogo->irParaMenu();
            sairDoLoop = true;
        }
    }
}

void Menu::executarTelaPause() {
    estadoAtual = EstadoMenu::PAUSE;

    tituloMenu.setString("JOGO PAUSADO");
    tituloMenu.setPosition(250.0f, 100.0f);

    textosBotoes.resize(2);
    textosBotoes[0].setString("Continuar");
    textosBotoes[1].setString("Voltar ao Menu Principal");

    opcaoSelecionada = 0;
    textosBotoes[0].setFillColor(sf::Color::Red);
    textosBotoes[1].setFillColor(sf::Color::White);

    sairDoLoop = false;
    sf::RenderWindow* window = pJogo->getWindow();

    while (window->isOpen() && !sairDoLoop) {
        sf::Event evento;
        while (window->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                window->close();
                exit(0);
            }
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Up) {
                    moverCima();
                }
                else if (evento.key.code == sf::Keyboard::Down) {
                    moverBaixo();
                }
                else if (evento.key.code == sf::Keyboard::Enter) {
                    interagir();
                }
            }
        }

        window->clear(sf::Color::Black);
        desenhar();
        window->display();
    }
}

void Menu::executar() {
    sairDoLoop = false;

    sf::RenderWindow* window = pJogo->getWindow();

    while (window->isOpen() && !sairDoLoop) {
        sf::Event evento;
        while (window->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                window->close();
                exit(0);
            }
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Up) {
                    moverCima();
                }
                else if (evento.key.code == sf::Keyboard::Down) {
                    moverBaixo();
                }
                else if (evento.key.code == sf::Keyboard::Enter) {
                    interagir();
                }
            }
        }

        window->clear(sf::Color::Black);
        desenhar();
        window->display();
    }
}

void Menu::desenhar() {
    sf::RenderWindow* window = pJogo->getWindow();
    window->draw(tituloMenu);
    for (auto& texto : textosBotoes) {
        window->draw(texto);
    }
}

void Menu::setJogo(Jogo* p) { 
    pJogo = p; 
}
void Menu::escolheAcao() {}
void Menu::escolheJogador() {}
void Menu::escolheFase() {}
void Menu::escolhePause() {}
void Menu::atualizarRanking(int pontos) {}
void Menu::mostrarRanking() {}
void Menu::centralizarTexto() {}
void Menu::continuarJogo() {}