//
// Created by zheboss on 12/3/2023.
//

#include "color.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/** ************************************
* FONCTION DE COULEURS - TEXTE ET FOND *
************************************ **/

void rouge() {
    ///FONCTION DE COULEUR TEXTE ROUGE
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}
void jaune() {
    ///FONCTION DE COULEUR TEXTE JAUNE
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED); }
void bleu() {
    ///FONCTION DE COULEUR TEXTE BLEUE
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}
void gris() {
    ///FONCTION DE COULEUR TEXTE GRIS
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void vert() {
    ///FONCTION DE COULEUR TEXTE VERT
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}
void magenta() {
    ///FONCTION DE COULEUR TEXTE MAGENTA
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
}
void light() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
}
void reset() {
    ///FONCTION DE REMISE A ZERO DE COULEUR TEXTE
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}