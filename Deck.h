/* 
 * File:   Deck.h
 * Author: juansterrr
 */

#ifndef DECK_H
#define DECK_H
#include "Card.h"

#include <string>
using namespace std;

class Deck
{
private:
    Card** deck;
    int index[52];
    
public:
    Deck();
    void prntdeck();
    void shuff_deck();
    Card* retCard();
    ~Deck()
    {
      delete [] deck;  
    }
    
    friend ostream& operator<<(ostream&, const Deck&);
};

#endif /* CARD_H */

