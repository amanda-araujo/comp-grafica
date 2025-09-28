//
// Created by Amanda on 28/09/2025.
//

#ifndef MENU_H
#define MENU_H



class Menu {
public:
    Menu();
    void init();
    void help();

private:
    void chooseOption();
    void handleOption1(); // Desenhar polígono
    void handleOption2(); // Cor
    void handleOption3(); // Espessura da linha
    void handleOption4(); // Limpar
    void handleOption5(); // Implementação
    void handleOption6(); // Preencher
    void exit();
};



#endif //MENU_H