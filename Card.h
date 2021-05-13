/* 
 * File:   Card.h
 * Author: juansterrr
 */

#ifndef CARD_H
#define CARD_H
#include "AbsCard.h"

class Card : public AbsCard
{
    
private:
    int cardNum;
public:
    Card(int);
    Card(Card*);
    string getSuit() const;
    char getFace() const;
    short getVal() const;
    int getNum()const;

};

#endif /* CARD_H */

