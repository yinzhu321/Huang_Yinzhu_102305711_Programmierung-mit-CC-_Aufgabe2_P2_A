#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<Windows.h>
#define FILENAME "Berechnungsprotokoll.txt"

using namespace std;

//Funktion deklarieren
bool verbindung();
void sendToMCU(const std::string& text);
std::string  receiveFromMCU();
void speichern(int s_zahl_1, int s_zahl_2);
