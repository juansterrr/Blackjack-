/* 
 * File:   main.cpp
 * Author: juansterrr
 *
 * Created on December 12, 2020, 11:34 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Deck.h"
#include "PlayerInfo.h"

void getInfo(int,int&);
void dealInf(int&);
void ifWon(int,int);
void ifLoss(int,int);
void cmpSc2(int,int,int&);
void cmpSc3(int,int,int,int&);
void cmpSc4(int,int,int,int,int&);
void farPlay();

using namespace std;


int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    string ag,nam,schl;
    char ch;
    int nPlayers;
    int player1 = 1, player2 = 2;
    int player3 = 3, player4 = 4;
    int play1_tot = 0, play2_tot = 0;
    int play3_tot = 0, play4_tot = 0;
    int deal_tot = 0;
    PlayerInfo star;
    Deck deck;
   
      //game begins with giving the user instructions of what the game is about
    cout << "Hello user! Welcome to the game of BlackJack..." << endl;
    cout << "You will be given the chance to input the number of players playing " << endl;
    cout << "this game momentarily, but for now sit tight and listen to the rules" << endl;
    cout << "of this game." << endl << endl;
    //more instructions
    cout << "Players will be randomly given two cards face up, the goal of this game" << endl;
    cout << "is to pull cards that add up closest to or on the value of 21." << endl;
    cout << "If a player pulls 21 on the first 2 given cards he automatically wins the money" << endl;
    cout << "they have bet back!" << endl << endl;
    cout << "However, if no players pulls 21 on the first cards, they all have to try their best to " << endl;
    cout << "beat the dealer (myself) by pulling cards and getting closest or on the number 21." << endl << endl;
    
    
    cout << "*****************************************************************************" << endl << endl;
    
    cout << "Now please enter the number of players. Be sure to pick between 2-4 players." << endl;
    
    cin >> nPlayers;
    //verification for the user to input a certain amount of players to keep the game
    //short and sweet
    while(nPlayers < 2 || nPlayers > 4)
    {
        cout << "Please enter players between 2-4!" << endl;
            cin >> nPlayers;
    }
    
    //this is the file used to store the data for the players that are playing
    fstream people("people.dat", ios:: out | ios::binary);
    
    int count = 0;
    //begins the process of the data storage
    for(int i = 0; i < nPlayers; i++)
    {
        if(count < 1)
        {
        cout << "Please enter the data for the " << nPlayers << " players playing this game." << endl;
        cout << "Begin by entering the data for player " << i+1 << endl;
            count++;
        }
        cin.ignore();
        cout << "Enter the full name of player " << i+1 << ":" << endl;
        getline(cin,nam);
        cout << "Now enter the age of this player: " << endl;
        getline(cin,ag);
        cout << "Now enter the school they attend: " << endl;
        getline(cin,schl);
        
        PlayerInfo player(ag,nam,schl);
        
        cout << "Now this info is being written into a file for records of the players.." << endl;
        
        people.write(reinterpret_cast<char *>(&player), sizeof(player));
        
        cout << "Player " << i + 1 << " done!" << endl;
    }
    //closes the file for the players playing
      people.close();
   
    cout << "The game is beginning and the cards are being shuffled! Please press Enter to continue." << endl;
    cin.get(ch);
    
     cout << "Now that the cards have been shuffled, Player 1, you are going to be given your cards first!" << endl;
     cout << "If your cards do not add up to 21, you can choose 'h' to hit for another card, or 's' to stay if you are happy with your total!" << endl;
     cout << "Press Enter to continue." << endl;
     cin.get(ch);
     
     
     getInfo(player1,play1_tot);
     
      if(nPlayers >= 2)
                        {
                                cout << "Player 2 please press Enter to continue." << endl;
                                cin.get(ch);
                                cin.get(ch);
                            getInfo(player2,play2_tot);
                            if(nPlayers == 2)
                            {
                            cmpSc2(play1_tot,play2_tot,deal_tot);
                            }
                            
                        }
                    //if there are 3 or more players do this vv
                    if(nPlayers >= 3)
                        {
                            cout << "Player 3 please press Enter to continue." << endl;
                            cin.get(ch);
                            cin.get(ch);
                            getInfo(player3,play3_tot);
                            if(nPlayers == 3)
                            {
                            cmpSc3(play1_tot,play2_tot,play3_tot,deal_tot);
                            }
                        }
                    if(nPlayers == 4)
                        {
                            cout << "Player 4 please press Enter to continue." << endl;
                            cin.get(ch);
                            cin.get(ch);
                            getInfo(player4,play4_tot);
                            if(nPlayers == 4)
                            {
                             cmpSc4(play1_tot,play2_tot,play3_tot,play4_tot,deal_tot);
                            }
                        }
 
    return 0;
}
 
void getInfo(int play_num, int &playtot)
{
    Deck deck;
    
    
    //char cards are used to assign value to the players
        Card* card1;
        Card* card2;
        bool turn = true;
        char inp;
        int total = 0, count = 0;
        int aVal = 0;
        int card1val=0;
        int card2val=0;
        int newCardVal=0;
        Card* newCard;
    do
        {
            //after counter is greater than 0 the players will be able to chose to take one more card
           if(count == 0)
           {
            card1 = deck.retCard();
            card2 = deck.retCard();
            card1val=card1->getVal();
            card2val=card2->getVal();
           }
            //outputs the card value to the user
            if(count>0)
            {
                newCard = deck.retCard();
                newCardVal=newCard->getVal();
                cout << "You chose to hit, your new card value is: " << newCard->getFace() << " of " << newCard->getSuit()<< endl;
            }
        //outputs the total of the card values to the user
        if(count == 0)
        {
           cout << "Player " << play_num << ", your cards are " << card1->getFace() << " of " << card1->getSuit();
           cout << " and " << card2->getFace() << " of " << card2->getSuit() << endl;
        }
        //if the player draws an Ace card, the have the option to choose between the value 1 or 11
        if(card1->getFace() == 'A'&&count==0)
        {
            cout << "You have drawn an 'A', would you like that value to equal 1 or 11?" << endl;
            cin >> aVal;
            
            if(aVal == 1)
            {
                card1val = 1;
            }else
            {
                card1val = 11;
            }
        }
               //if the player draws an Ace card, the have the option to choose between the value 1 or 11
                    if(card2->getFace() == 'A'&&count==0)
                    {
                        
                        cout << "You have drawn an 'A', would you like that value to equal 1 or 11?" << endl;
                        cin >> aVal;
                        
                        if(aVal == 1)
                        {
                            card2val = 1;
                        }else
                        {
                            card2val = 11;
                        }
                    }
               //if the player draws an Ace card, the have the option to choose between the value 1 or 11
                                            if(newCard->getFace() == 'A')
                                               {
                                                 
                                                   cout << "You have drawn an 'A', would you like that value to equal 1 or 11?" << endl;
                                                   cin >> aVal;
                                                   
                                                   if(aVal == 1)
                                                   {
                                                       newCardVal = 1;
                                                   }else
                                                   {
                                                       newCardVal = 11;
                                                   }
                                               }
//returns the total of the players score
            if(count == 0)
            {
                total += card1val+ card2val;
            }
            
            if(count > 0)
            {
                total += newCardVal;
            }
            
            if(total < 21)
            {
                cout << "Your combined card total is: " << total << endl;
                cout << "Would you like to 'h' or 's'?" << endl;
                    cin >> inp;
                
                        if(inp == 'h')
                            {
                               turn = true;
                            }
                                    else if(inp == 's')
                                        {
                                            playtot = total;
                                            turn = false;
                                        }
            }
    if(total == 21)
    {
       ifWon(total,play_num);
       playtot = total;
       turn = false;
    }
            
                    if(total > 21)
                    {
                        ifLoss(total,play_num);
                        playtot = total;
                        turn = false;
                    }

            count ++;
            
        }while(turn == true);
}
//function for the dealers info
void dealInf(int &deal_tot)
{
    Deck deck;
    
    
    //char cards are used to assign value to the players
        Card* card1;
        Card* card2;
        bool turn = true;
        char inp;
        int total = 0, count = 0;
        int aVal = 0;
        int card1val=0;
        int card2val=0;
        int newCardVal=0;
        Card* newCard;
    do
        {
            //after counter is greater than 0 the players will be able to chose to take one more card
           if(count == 0)
           {
            card1 = deck.retCard();
            card2 = deck.retCard();
            card1val=card1->getVal();
            card2val=card2->getVal();
           }
            //outputs the card value to the user
            if(count>0)
            {
                newCard = deck.retCard();
                newCardVal=newCard->getVal();
                cout << "You chose to hit, your new card value is: " << newCard->getFace() << " of " << newCard->getSuit()<< endl;
            }
        //outputs the total of the card values to the user
        if(count == 0)
        {
           cout << "Dealer, your cards are " << card1->getFace() << " of " << card1->getSuit();
           cout << " and " << card2->getFace() << " of " << card2->getSuit() << endl;
        }
        //if the player draws an Ace card, the have the option to choose between the value 1 or 11
        if(card1->getFace() == 'A'&&count==0)
        {
            cout << "You have drawn an 'A', would you like that value to equal 1 or 11?" << endl;
            cin >> aVal;
            
            if(aVal == 1)
            {
                card1val = 1;
            }else
            {
                card1val = 11;
            }
        }
               //if the player draws an Ace card, the have the option to choose between the value 1 or 11
                    if(card2->getFace() == 'A'&&count==0)
                    {
                        
                        cout << "You have drawn an 'A', would you like that value to equal 1 or 11?" << endl;
                        cin >> aVal;
                        
                        if(aVal == 1)
                        {
                            card2val = 1;
                        }else
                        {
                            card2val = 11;
                        }
                    }
               //if the player draws an Ace card, the have the option to choose between the value 1 or 11
                                            if(newCard->getFace() == 'A')
                                               {
                                                 
                                                   cout << "You have drawn an 'A', would you like that value to equal 1 or 11?" << endl;
                                                   cin >> aVal;
                                                   
                                                   if(aVal == 1)
                                                   {
                                                       newCardVal = 1;
                                                   }else
                                                   {
                                                       newCardVal = 11;
                                                   }
                                               }
//returns the total of the players score
            if(count == 0)
            {
                total += card1val+ card2val;
            }
            
            if(count > 0)
            {
                total += newCardVal;
            }
            
            if(total < 17)
            {
                cout << "Your combined card total is: " << total << endl;
                cout << "The dealer is forced to hit until his total is above 17." << endl;
                turn = true;
            }
                        if(total >= 17 && total < 21)
                        {
                            cout << "The dealers score is: " << total << endl;
                            deal_tot = total;
                            turn = false;
                        }
    if(total == 21)
    {
       deal_tot = total;
       turn = false;
    }
            
                    if(total > 21)
                    {
                        
                        deal_tot = total;
                        turn = false;
                    }

            count ++;
            
        }while(turn == true);
}
void ifWon(int tot, int playNum)
{
    //if the player scores 21 it lets them know that they have won
    cout << "Player " << playNum << " you have beat the dealer, your total score is: " << tot << "!" << endl;
}
void ifLoss(int tot, int playNum)
{
    //if the player scores over 21 it lets them know that they have lost
    cout << "Player " << playNum << " you have busted! You have lost to the dealer because your score is: " << tot << "!):" << endl;
}
void cmpSc2(int play1, int play2, int &deal_tot)
{
    char ch;
    cout << "Before we can display the scores against the dealer, the dealer must reveal their cards! Press Enter" << endl;
    cin.get(ch);
    cin.get(ch);
    dealInf(deal_tot);
    cout << "Press Enter to see the scores." << endl;
    cin.get(ch);
    cout << "Here are the scores of the players against the dealers score:" << endl;
    cout << "Player 1: " << setw(6) << play1 << endl;
    cout << "Player 2: " << setw(6) << play2 << endl;
    cout << "Dealer: " << setw(8)<< deal_tot << endl << endl;
    
            if( play1 == 21 && deal_tot < 21)
            {
                cout << "Player 1 has beat the dealer." << endl;
            }
            else if(play2 == 21 && deal_tot < 21)
            {
                cout << "Player 2 has beat the dealer." << endl;
            }
            else if(play1 < 21 && play1 > deal_tot && deal_tot < 21)
            {
                cout << "Player 1 has beat the dealer." << endl;

            }
            else if(play2 < 21 && play2 > deal_tot && deal_tot < 21)
            {
                cout << "Player 2 has beat the dealer." << endl;

            }
            else if(deal_tot == 21 && play1 < 21 &&  play2 < 21 )
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 && play1 > 21 &&  play2 > 21 )
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 && play1 < 21 &&  play2 > 21 )
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 && play1 > 21 &&  play2 < 21 )
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 &&  play1 == 21)
            {
                cout << "There is no winner because the dealer and Player 1 have both scored 21." << endl;
            }
            else if(deal_tot == 21 &&  play2 == 21)
            {
                cout << "There is no winner because the dealer and Player 2 have both scored 21." << endl;
            }
            else if (deal_tot < 21 && deal_tot > play1 && deal_tot > play2)
            {
                 cout << "The dealer has won!" << endl;
            }
            else if (deal_tot > 21 && play1 < 21 && play2 < play1)
            {
                 cout << "Player 1 has won!" << endl;
            }
            else if (deal_tot > 21 && play1 < 21 && play2 > 21)
            {
                 cout << "Player 1 has won!" << endl;
            }
            else if (deal_tot > 21 && play2 < 21 && play1 < play2)
            {
                 cout << "Player 2 has won!" << endl;
            }
            else if (deal_tot > 21 && play2 < 21 && play1 > 21)
            {
                 cout << "Player 2 has won!" << endl;
            }
            else if (deal_tot < 21 && play2 > 21 && play1 > 21)
            {
                 cout << "The dealer has won!" << endl;
            }

}
void cmpSc3(int play1,int play2,int play3,int &deal_tot)
{
       char ch;
       cout << "Before we can display the scores against the dealer, the dealer must reveal their cards! Press Enter" << endl;
       cin.get(ch);
       cin.get(ch);
       dealInf(deal_tot);
       cout << "Press Enter to see the scores." << endl;
       cin.get(ch);
       cout << "Here are the scores of the players against the dealers score:" << endl;
       cout << "Player 1: " << setw(6) << play1 << endl;
       cout << "Player 2: " << setw(6) << play2 << endl;
       cout << "Player 3: " << setw(6) << play3 << endl;
       cout << "Dealer: " << setw(8)<< deal_tot << endl << endl;
       
               if( play1 == 21 && deal_tot < 21)
               {
                   cout << "Player 1 has beat the dealer." << endl;
               }
                else if(play1 == 21 && deal_tot > 21 )
                {
                    cout << "Player 1 has beat the dealer." << endl;
                }
               else if(play2 == 21 && deal_tot < 21 )
               {
                   cout << "Player 2 has beat the dealer." << endl;
               }
                else if(play2 == 21 && deal_tot > 21 )
                {
                    cout << "Player 2 has beat the dealer." << endl;
                }
               else if(play3 == 21 && deal_tot < 21)
                {
                    cout << "Player 3 has beat the dealer." << endl;
                }
                else if(play3 == 21 && deal_tot > 21)
                {
                    cout << "Player 3 has beat the dealer." << endl;
                }
               else if(play1 < 21 && play1 > deal_tot && deal_tot < 21)
               {
                   cout << "Player 1 has beat the dealer." << endl;

               }
               else if(play2 < 21 && play2 > deal_tot && deal_tot < 21)
               {
                   cout << "Player 2 has beat the dealer." << endl;

               }
               else if(play3 < 21 && play3 > deal_tot && deal_tot < 21)
               {
                   cout << "Player 3 has beat the dealer." << endl;

               }
               else if(deal_tot == 21 && play1 < 21 &&  play2 < 21 && play3 < 21)
               {
                   cout << "The dealer has won!" << endl;
               }
               else if(deal_tot == 21 && play1 > 21 &&  play2 > 21 && play3)
               {
                   cout << "The dealer has won!" << endl;
               }
               else if(deal_tot == 21 && play1 < 21 &&  play2 > 21 && play3 > 21)
               {
                   cout << "The dealer has won!" << endl;
               }
               else if(deal_tot == 21 && play1 > 21 &&  play2 < 21 && play3 > 21)
               {
                   cout << "The dealer has won!" << endl;
               }
                else if(deal_tot == 21 && play1 > 21 &&  play2 > 21 && play3 < 21)
                {
                    cout << "The dealer has won!" << endl;
                }
               else if(deal_tot == 21 &&  play1 == 21)
               {
                   cout << "There is no winner because the dealer and Player 1 have both scored 21." << endl;
               }
               else if(deal_tot == 21 &&  play2 == 21)
               {
                   cout << "There is no winner because the dealer and Player 2 have both scored 21." << endl;
               }
                else if(deal_tot == 21 &&  play3 == 21)
                {
                    cout << "There is no winner because the dealer and Player 3 have both scored 21." << endl;
                }
               else if (deal_tot < 21 && deal_tot > play1 && deal_tot > play2 && deal_tot > play3)
               {
                    cout << "The dealer has won!" << endl;
               }
               else if (deal_tot > 21 && play1 < 21 && play2 < play1 && play3 < play1)
               {
                    cout << "Player 1 has won!" << endl;
               }
               else if (deal_tot > 21 && play2 < 21 && play1 < play2 && play3 < play2)
               {
                    cout << "Player 2 has won!" << endl;
               }
                else if (deal_tot > 21 && play3 < 21 && play1 < play3 && play2 < play3)
                {
                     cout << "Player 3 has won!" << endl;
                }
               else if (deal_tot > 21 && play1 < 21 && play2 > 21 && play3 > 21)
               {
                    cout << "Player 1 has won!" << endl;
               }
               else if (deal_tot > 21 && play2 < 21 && play1 > 21 && play3 > 21)
               {
                    cout << "Player 2 has won!" << endl;
               }
               else if (deal_tot > 21 && play2 > 21 && play1 > 21 && play3 < 21)
               {
                    cout << "Player 3 has won!" << endl;
               }
               else if (deal_tot < 21 && play2 > 21 && play1 > 21 && play3 > 21)
               {
                    cout << "The dealer has won!" << endl;
               }
}

void cmpSc4(int play1,int play2,int play3,int play4,int &deal_tot)
{
    char ch;
    cout << "Before we can display the scores against the dealer, the dealer must reveal their cards! Press Enter" << endl;
    cin.get(ch);
    cin.get(ch);
    dealInf(deal_tot);
    cout << "Press Enter to see the scores." << endl;
    cin.get(ch);
    cout << "Here are the scores of the players against the dealers score:" << endl;
    cout << "Player 1: " << setw(6) << play1 << endl;
    cout << "Player 2: " << setw(6) << play2 << endl;
    cout << "Player 3: " << setw(6) << play3 << endl;
    cout << "Player 4: " << setw(6) << play4 << endl;
    cout << "Dealer: " << setw(8)<< deal_tot << endl << endl;
    
             if( play1 == 21 && deal_tot < 21)
            {
                cout << "Player 1 has beat the dealer." << endl;
            }
             else if(play1 == 21 && deal_tot > 21 )
             {
                 cout << "Player 1 has beat the dealer." << endl;
             }
            else if(play2 == 21 && deal_tot < 21 )
            {
                cout << "Player 2 has beat the dealer." << endl;
            }
             else if(play2 == 21 && deal_tot > 21 )
             {
                 cout << "Player 2 has beat the dealer." << endl;
             }
            else if(play3 == 21 && deal_tot < 21)
             {
                 cout << "Player 3 has beat the dealer." << endl;
             }
             else if(play3 == 21 && deal_tot > 21)
             {
                 cout << "Player 3 has beat the dealer." << endl;
             }
            else if(play4 == 21 && deal_tot < 21)
            {
                cout << "Player 4 has beat the dealer." << endl;
            }
            else if(play4 == 21 && deal_tot > 21)
            {
                cout << "Player 4 has beat the dealer." << endl;
            }
            else if(play1 < 21 && play1 > deal_tot && deal_tot < 21)
            {
                cout << "Player 1 has beat the dealer." << endl;

            }
            else if(play2 < 21 && play2 > deal_tot && deal_tot < 21)
            {
                cout << "Player 2 has beat the dealer." << endl;

            }
            else if(play3 < 21 && play3 > deal_tot && deal_tot < 21)
            {
                cout << "Player 3 has beat the dealer." << endl;

            }
            else if(play4 < 21 && play3 > deal_tot && deal_tot < 21)
            {
                cout << "Player 3 has beat the dealer." << endl;

            }
            else if(deal_tot == 21 && play1 < 21 &&  play2 < 21 && play3 < 21 && play4 < 21)
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 && play1 > 21 &&  play2 > 21 && play3 > 21 && play4 > 21)
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 && play1 < 21 &&  play2 > 21 && play3 > 21)
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 && play1 > 21 &&  play2 < 21 && play3 > 21)
            {
                cout << "The dealer has won!" << endl;
            }
             else if(deal_tot == 21 && play1 > 21 &&  play2 > 21 && play3 < 21)
             {
                 cout << "The dealer has won!" << endl;
             }
            else if(deal_tot == 21 && play1 > 21 &&  play2 > 21 && play3 > 21 && play4 < 21)
            {
                cout << "The dealer has won!" << endl;
            }
            else if(deal_tot == 21 &&  play1 == 21)
            {
                cout << "There is no winner because the dealer and Player 1 have both scored 21." << endl;
            }
            else if(deal_tot == 21 &&  play2 == 21)
            {
                cout << "There is no winner because the dealer and Player 2 have both scored 21." << endl;
            }
             else if(deal_tot == 21 &&  play3 == 21)
             {
                 cout << "There is no winner because the dealer and Player 3 have both scored 21." << endl;
             }
            else if(deal_tot == 21 &&  play4 == 21)
            {
                cout << "There is no winner because the dealer and Player 4 have both scored 21." << endl;
            }
            else if (deal_tot < 21 && deal_tot > play1 && deal_tot > play2 && deal_tot > play3 && deal_tot > play4)
            {
                 cout << "The dealer has won!" << endl;
            }
            else if (deal_tot > 21 && play1 < 21 && play2 < play1 && play3 < play1)
            {
                 cout << "Player 1 has won!" << endl;
            }
            else if (deal_tot > 21 && play2 < 21 && play1 < play2 && play3 < play2)
            {
                 cout << "Player 2 has won!" << endl;
            }
             else if (deal_tot > 21 && play3 < 21 && play1 < play3 && play2 < play3)
             {
                  cout << "Player 3 has won!" << endl;
             }
            else if (deal_tot > 21 && play4 < 21 && play1 < play4 && play2 < play4 && play3 < play4)
            {
                 cout << "Player 4 has won!" << endl;
            }
            else if (deal_tot > 21 && play1 < 21 && play2 > 21 && play3 > 21)
            {
                 cout << "Player 1 has won!" << endl;
            }
            else if (deal_tot > 21 && play2 < 21 && play1 > 21 && play3 > 21)
            {
                 cout << "Player 2 has won!" << endl;
            }
            else if (deal_tot > 21 && play2 > 21 && play1 > 21 && play3 < 21)
            {
                 cout << "Player 3 has won!" << endl;
            }
            else if (deal_tot > 21 && play2 > 21 && play1 > 21 && play3 > 21 && play4 < 21)
            {
                 cout << "Player 4 has won!" << endl;
            }
            else if (deal_tot < 21 && play2 > 21 && play1 > 21 && play3 > 21 && play4 > 21)
            {
                 cout << "The dealer has won!" << endl;
            }
}
