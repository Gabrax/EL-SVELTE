#ifndef UNTITLED_HEHE_H
#define UNTITLED_HEHE_H

#include <iostream>

class Entity
{
    public:
        const int EntityLevelError=0;
        const int EntityLevelWarning=1;
        const int EntityLevelInfo=2;


    void Error(const char* message) const
    {
        if (p_EntityLevel >= EntityLevelError)
            std::cout << "[ERROR]:" << message << std::endl;
    }
    void Warn(const char* message) const
    {
        if (p_EntityLevel >= EntityLevelWarning)
            std::cout << "[WARNING]:" << message << std::endl;
    }
    void Info(const char* message) const
    {
        if (p_EntityLevel >= EntityLevelInfo)
            std::cout << "[INFO]:" << message << std::endl;
    }

    public:
    void SetLevel(int level)
    {
        p_EntityLevel = level;
    }

    private:
    int p_EntityLevel{};

};


void Write(const char* message)
{
    std::cout << message << std::endl;
}

#endif //UNTITLED_HEHE_H
