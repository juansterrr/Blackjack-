/* 
 * File:   Card.cpp
 * Author: juansterrr
 */

#include "Deck.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Deck :: Deck()
{
    deck = new Card*[52];
    int k = 0;
    for(int i = 0; i < 52; i++)
    {
        deck[i]=new Card(i);
        index[i]=i;
    }
    shuff_deck();
}
void Deck :: prntdeck()
{
    for(int i = 0; i < 52; i++)
    {
        cout << deck[i] << endl;
    }
}
void Deck ::shuff_deck()
{
    int temp;
    int m = 0;
  for(int j = 0; j < 7; j++)
   {
        for(int i = 0; i < 52; i++)
        {

            m = rand()%52;
            temp = index[i];
            index[i] = index[m];
            index[m] = temp;
        }
   }
}
Card* Deck :: retCard()
{
    static int i=0;
    if(i==52){
        i=0;
        shuff_deck();
    }
    return deck[index[i++]];
    
}

ostream& operator<<(ostream& out,const Deck& var)
{
    for(int i = 0; i < 52; i++)
    {
        cout << var.index[i] << endl;
    }
}
