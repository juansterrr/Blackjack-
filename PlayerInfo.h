/* 
 * File:   PlayerInfo.h
 * Author: juan
 */
#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include <string>
using namespace std;

class PlayerInfo { 
private:
    string age;
    string name;
    string school;
public:
    PlayerInfo();
    PlayerInfo(string,string,string);
    void setAge(string);
    void setName(string);
    void setSchool(string);
    
    string getAge() const
        {return age;}
    string getName() const
        {return name;}
    string getSchool() const
        {return school;}
};

#endif /* PLAYERINFO_H */

