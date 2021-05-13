/* 
 * File:   AbsCard.h
 * Author: juansterrr
 */

#ifndef ABSCARD_H
#define ABSCARD_H
#include <string>
using namespace std;

class AbsCard {
    
public:
    virtual string getSuit()const = 0;
};

#endif /* ABSCARD_H */

