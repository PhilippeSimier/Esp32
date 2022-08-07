/* 
 * File:   CommandeAt.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Created on 4 août 2022, 10:38
 */

#include "CommandeAt.h"

CommandeAt::CommandeAt():
Console()
{
    setPrompt("");                // Pas de prompt
    onCmd("AT", AT);              // Association de la commande AT avec methode statique AT
    onCmd("AT+RST", ATRestart);   // Association de la commande AT+RST avec la méthode statique ATRestart
    onCmd("AT+GMR", ATGMR);       // Association de la commande AT+GMR avec la méthode statique ATGMR
    onUnknown(unknown);           // Association pour les commandes inconnues
}

CommandeAt::CommandeAt(const CommandeAt& orig) {
}

CommandeAt::~CommandeAt() {
}

void CommandeAt::AT(ArgList& L, Stream& S) {
    S.println("OK\r\n");
}

void CommandeAt::ATRestart(ArgList& L, Stream& S) {
    ESP.restart();
    
}

void CommandeAt::unknown(String& L, Stream& S) {
    S.println("Error\r\n");
}

void CommandeAt::ATGMR(ArgList& L, Stream& S) {
    
    S.printf("Chip model      : %s\r\n",     ESP.getChipModel());
    S.printf("Sdk version     : %s\r\n",     ESP.getSdkVersion());
    S.printf("CPU freq        : %d MHz\r\n", ESP.getCpuFreqMHz());
    S.printf("Flash size      : %d MB\r\n",  ESP.getFlashChipSize() / 1000000);
    S.printf("Tick rate       : %d Hz\r\n",  configTICK_RATE_HZ);
    S.printf("Heap size       : %d KB\r\n",  ESP.getHeapSize() /1000);
    S.printf("Free Heap       : %d KB\r\n",  ESP.getFreeHeap() /1000);   
    S.printf("Heap max alloc  : %d KB\r\n",  ESP.getMaxAllocHeap() /1000); 
    S.println();

    
}