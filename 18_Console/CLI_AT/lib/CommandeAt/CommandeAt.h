/* 
 * File:   CommandeAt.h
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 4 août 2022, 10:38
 */

#ifndef COMMANDEAT_H
#define COMMANDEAT_H

#include <Arduino.h>
#include <console.h>

class CommandeAt : public Console
{

public:
    CommandeAt();
    CommandeAt(const CommandeAt& orig);
    virtual ~CommandeAt();
    
private:
    static void AT(ArgList& L, Stream& S);
    static void ATRestart(ArgList& L, Stream& S);
    static void ATGMR(ArgList& L, Stream& S);
    static void unknown(String& L, Stream& S);

};

#endif /* COMMANDEAT_H */

