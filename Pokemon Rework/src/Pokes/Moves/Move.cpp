#include "Move.h"

Move::Move(Moves moves, std::string name, Type type, int accuracy, int damage, Category category)
{
    this->moves = moves;
    this->type = type;
    this->accuracy = accuracy;
    this->damage = damage;
    this->category = category;
    this->name = name;
}

void Move::UseMove(Pokemon* pokemon)
{
    //pokemon->SetHP(-damage * AttackType::GetDamageMultiplyer(type, pokemon));
}

std::string Move::GetMoveName()
{
    /*switch (moves)
    {
    case Moves::TACKLE: return "Tackle";
        break;
    case Moves::GROWL: return "Growl";
        break;
    case Moves::SCRATCH: return "Scratch";
        break;
    case Moves::EMBER: return "Ember";
        break;
    case Moves::LEER: return "Leer";
        break;
    case Moves::RAGE: return "Rage";
        break;
    case Moves::SLASH: return "Slash";
        break;
    case Moves::FLAMETHROWER: return "Flamethrower";
        break;
    case Moves::FIRESPIN: return "Firespin";
        break;
    case Moves::LEECHSEED: return "Leech seed";
        break;
    case Moves::VINEWHIP: return "Vinewhip";
        break;
    case Moves::POISONPOWDER: return "Poison Powder";
        break;
    case Moves::RAZORLEAF: return "Razorleaf";
        break;
    case Moves::GROWTH: return "Growth";
        break;
    case Moves::SLEEPPOWDER: return "Sleep Powder";
        break;
    case Moves::SOLARBEAM: return "Solarbeam";
        break;
    case Moves::TAILWHIP: return "Tailwhip";
        break;
    case Moves::BUBBLE: return "Bubble";
        break;
    case Moves::WATERGUN: return "Watergun";
        break;
    case Moves::BITE: return "Bite";
        break;
    case Moves::WITHDRAW: return "Withdraw";
        break;
    case Moves::SKULLBASH: return "Skullbash";
        break;
    case Moves::HYDROPUMP: return "Hydropump";
        break;
    case Moves::GUST: return "Gust";
        break;
    case Moves::SAND_ATTACK: return "Sand Attack";
        break;
    case Moves::QUICK_ATTACK: return "Quick Attack";
        break;
    case Moves::WHIRLWIND: return "Whirlwind";
        break;
    case Moves::WING_ATTACK: return "Wing Attack";
        break;
    case Moves::AGILITY: return "Agility";
        break;
    case Moves::MIRROR_MOVE: return "Mirror Move";
        break;
    case Moves::HYPER_FANG: return "Hyper Fang";
        break;
    case Moves::FOCUS_ENERGY: return "Focus Energy";
        break;
    case Moves::SUPER_FANG: return "Super Fang";
        break;
    }*/
    return name;
}

//GUST, SAND_ATTACK, QUICK_ATTACK, WHIRLWIND, WING_ATTACK, AGILITY, MIRROR_MOVE, HYPER_FANG, FOCUS_ENERGY, SUPER_FANG

Type Move::GetType()
{
    return type;
}

int Move::GetAccuracy()
{
    return accuracy;
}

int Move::GetDamage()
{
    return damage;
}

bool Move::GetIsSpecial()
{
    if (type == Type::FIRE || type == Type::WATER || type == Type::GRASS || type == Type::ICE || type == Type::ELECTRIC || type == Type::DRAGON)
        return true;
    return false;
}
