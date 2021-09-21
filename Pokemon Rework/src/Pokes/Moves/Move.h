#pragma once
#include "Type.h"
#include <string>

enum class Moves
{
    TACKLE, GROWL, SCRATCH, EMBER, LEER, RAGE, SLASH, FLAMETHROWER, FIRESPIN, LEECHSEED, VINEWHIP, POISONPOWDER, RAZORLEAF, GROWTH, SLEEPPOWDER, SOLARBEAM, TAILWHIP,
    BUBBLE, WATERGUN, BITE, WITHDRAW, SKULLBASH, HYDROPUMP, GUST, SAND_ATTACK, QUICK_ATTACK, WHIRLWIND, WING_ATTACK, AGILITY, MIRROR_MOVE, HYPER_FANG, FOCUS_ENERGY, SUPER_FANG
};


class Pokemon;
class Move
{
public:
    Move() = default;
    Move(Moves moves, std::string name, Type type, int accuracy, int damage, Category category);
    ~Move() = default;

public:
    virtual void UseMove(Pokemon* pokemon);
    std::string GetMoveName();
    Type GetType();
    int GetAccuracy();
    int GetDamage();
    Moves GetMove() { return moves; }
    bool GetIsSpecial();

private:
    Moves moves;
    Type type;
    int accuracy;
    int damage;
    Category category;
    bool isSpecial = false;
    std::string name;
};

//class AttackMove : public Move
//{
//public:
//    AttackMove(Moves moves, Type type, int accuracy, int damage, bool selfInflict) : Move(moves, type, accuracy)
//    {
//        this->damage = damage;
//        this->selfInflict = selfInflict;
//    }
//    ~AttackMove() = default;
//
//public:
//    virtual void UseMove(Pokemon pokemon) override
//    {
//
//    }
//
//private:
//    int damage;
//    bool selfInflict;
//};

//class DefenseMove : public Move
//{
//public:
//    DefenseMove(Moves moves, Type type, int accuracy, BuffDefense buffDefense) : Move(moves, type, accuracy)
//    {
//        this->buffDefense = buffDefense;
//    }
//    ~DefenseMove() = default;
//
//private:
//    BuffDefense buffDefense;
//};