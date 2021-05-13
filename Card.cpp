/* 
 * File:   Card.cpp
 * Author: juansterr
 */

#include "Card.h"

Card :: Card(int val)
{
   if(val < 52 && val >= 0) 
   {
       cardNum = val;
   }
   else
   {
       cardNum = 0;
   }
}
Card :: Card(Card* crd)
{
    cardNum=crd->getNum();
}
        
string Card :: getSuit() const
{
    static string suit[] = {"Diamonds","Spades","Hearts","Clubs"};
        return suit[cardNum/13];
    
}
char Card :: getFace() const 
{
    static char face[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    return face[cardNum%13];
}
short Card :: getVal() const
{
    int n = cardNum%13+1;
    n = n>10?10:n;
    return n;
}
int Card::getNum()const
{
    return cardNum;
}
    

