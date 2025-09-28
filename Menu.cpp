//
// Created by Amanda on 28/09/2025.
//

#include "Menu.h"
#include "OpenGLWindow.h"
#include <atomic>
#include <iostream>
#include <thread>

#include "PolygonDrawer.h"

// Variáveis globais: lidas pelo OpenGl
extern std::atomic<bool> onScreen; // Op1
extern std::atomic<int> fillColor; // Op2
extern std::atomic<int> lineWidth; // Op3
extern std::atomic<bool> clearScreen;  // Op4
extern std::atomic<int> dataStructure; // Op5
extern std::atomic<bool> exitSystem; // Op0 EXIT
extern std::atomic<bool> fillPolygon; // OP6


Menu::Menu() {} // Constructor

void Menu::init() {
    std::cout << "=====================================\n";
    std::cout << "  Bem vindo ao POLYGON System! \n";
    std::cout << "=====================================\n";

    std::cout << "Loading menu";

    // Loading ... (animação)
    for (int i = 0; i < 4; i++) {
        std::cout << "." << std::flush;
    }

    std::cout << "\n\n Qual polígono você gostaria de desenhar e preencher hoje?\n";
    chooseOption();
}

void Menu::help() {
    std::cout << "================ Help Menu =================\n";
    std::cout << "Comandos disponíveis:\n";
    std::cout << "  1. Desenhar polígono a partir de pontos via cliques do mouse\n";
    std::cout << "  2. Selecionar cor para pintar o polígono (default: branco)\n";
    std::cout << "  3. Selecionar espessura da linha\n";
    std::cout << "  4. Limpar a tela apagando todos os pontos e polígono desenhado\n";
    std::cout << "  5. Escolher a estrutura de dados da implementação de preenchimento (ET ou AET)\n";
    std::cout << "  6. Preenchimento do polígono\n";
    std::cout << "  7. Help - Ajuda com listagem dos comandos disponíveis e suas funções\n";
    std::cout << "  0. Exit - Fecha a tela e encerra o sistema \n";
    std::cout << "===========================================\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}


void Menu::chooseOption() {

    int option = -1;  // Initialize with an invalid value to enter the loop

    while (option != 0) {
        try {
            std::cout << "\nChoose an option:\n";
            std::cout << "1. Desenhar polígono\n";
            std::cout << "2. Selecionar Cor\n";
            std::cout << "3. Espessura da linha\n";
            std::cout << "4. Limpar tela\n";
            std::cout << "5. Escolher implementação \n";
            std::cout << "6. Preenchimento do polígono\n";
            std::cout << "7. Help\n";
            std::cout << "0. Exit\n";
            std::cout << "Entrar sua escolha: ";

            if (!(std::cin >> option)) {  // Handle invalid input
                std::cin.clear();  // Clear error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
                std::cout << "Input inválido. Por favor digite um número.\n";
                continue;
            }

            switch (option) {
                case 1: handleOption1(); break;
                case 2: handleOption2(); break;
                case 3: handleOption3(); break;
                case 4: handleOption4(); break;
                case 5: handleOption5(); break;
                case 6: handleOption6(); break;
                case 7: help(); break;
                case 0: exit(); break;
                default:
                    std::cout << "Opção inválida. Por favor tente novamente.\n";
                break;
            }
        } catch (const std::exception &e) {  // Catch standard exceptions
            std::cerr << "Um erro ocorreu: " << e.what() << "\n";
        } catch (...) {  // Catch unknown exceptions
            std::cerr << "Please make sure the right configuration\n";
        }
    }
}

void Menu::handleOption1() {
    /* Desenhar polígono */
    std::cout << "Abrindo janela para desenhar o polígono...\n";
    std::cout << "Clique para definir os pontos que formam o polígono\n";

    // // GLUT precisa de argc/argv (dummy)
    // int argc = 1;
    // char* argv[1] = { (char*) "POLYGON System"};
    //
    // startOpenGLWindow(argc, argv);
    onScreen = true;
}

void Menu::handleOption2() {
    /* Selecionar cor de preenchimento */

    std::cout << "Selecione uma cor para pintar o polígono:\n";
    std::cout << "1. Branco (default)\n";
    std::cout << "2. Vermelho\n";
    std::cout << "3. Azul\n";
    std::cout << "4. Verde\n";
    std::cout << "0. Retornar ao menu principal\n";

    int option = -1;
    std::cin >> option;

    if (option == 0) {
        // Return to main menu
        chooseOption();
    } else {
        // Change fill color
        fillColor = option;
    }

}

void Menu::handleOption3() {
    /* Espessura da linha */
    std::cout << "Entrar com uma espessura de linha (1 - 100):\n";

    int t;
    std::cin >> t;

    // if (t > 0 && t <= 10) {
    //     lineWidth = t;
    // } else {
    //     std::cout << "Input inválido. Por favor digite um valor de 1 a 10.\n";
    // }
    lineWidth = (t > 0? t : 1); // Inválido: default
}

void Menu::handleOption4() {
    /* Limpar a tela */
    std::cout << "Limpando a tela... Adeus polígono!\n";
    clearScreen = true;
}

void Menu::handleOption5() {
    /* Implementação */
    std::cout << "Escolher implementação para preenchimento do polígono usando coerência de arestas:\n";
    std::cout << "1. Estrutura de dados ET (Tabela de Lados) [default]\n";
    std::cout << "2. Estrutura de dados AET (Tabela de Lados Ativos)\n";

    int option; std::cin >> option;
    dataStructure = (option == 2 ? 2 : 1); // ET default (cobre entrada inválida)
}

void Menu::handleOption6() {
    /* Preenchimento*/
    fillPolygon = true;
}


void Menu::exit() {
    std::cout << "END. That's all folks!\n";
    exitSystem = true;
    //exit(0); // Encerra, porém exit code 139
}


