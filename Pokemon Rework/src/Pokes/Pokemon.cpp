#include "Pokemon.h"
#include <math.h>
#include "TypeChart.h"

Pokemon::Pokemon()
{
	InitMultipliers();
}

Pokemon::~Pokemon()
{
}

void Pokemon::InitStats(int hp, int attack, int defense, float spAtk, float spDef, int speed)
{
	stats.MaxHP = (int)floor((hp * stats.Level) / 100.0f) + 10 + stats.Level;
	stats.Attack = (int)floor((attack * stats.Level) / 100.0f) + 5;
	stats.Defense = (int)floor((defense * stats.Level) / 100.0f) + 5;
	stats.SPATK = (int)floor((spAtk * stats.Level) / 100.0f) + 5;
	stats.SPDEF = (int)floor((spDef * stats.Level) / 100.0f) + 5;
	stats.Speed = (int)floor((speed * stats.Level) / 100.0f) + 5;

	hp = stats.MaxHP;
}



int Pokemon::GetLevel()
{
	return stats.Level;
}

int Pokemon::GetHP()
{
	return hp;
}

std::vector<Move*> Pokemon::GetMoves()
{
	std::vector<Move*> temp;
	for (int i = 0; i < temp.size(); i++)
		delete temp[i];
	temp.clear();
	for (int i = 0; i < 4; i++)
		if (moveset[i] != nullptr)
			temp.push_back(moveset[i]);
	return temp;
}

void Pokemon::AddLevel()
{
	stats.Level++;
}

int Pokemon::GetExpForLevel(int level)
{
	if (growthRate == GrowthRate::Fast)
		return 4 * (level * level * level) / 5;
	else if (growthRate == GrowthRate::MediumFast)
		return level * level * level;
	return -1;
}

//void Pokemon::GenerateMoves()
//{
//	for (int i = 0; i < stats.learnableMoves.size(); i++)
//	{
//		if (stats.learnableMoves[i].level <= level)
//			moves.push_back(new Move(stats.learnableMoves[i].base));
//
//		if (moves.size() >= 4)
//			break;
//	}
//}


std::string Pokemon::GetName()
{
	return name;
}

void Pokemon::LevelUp()
{
	if (experience >= requiredExp)
	{
		AddLevel();
		int remains = experience - requiredExp;
		UpdateStats();
		experience = remains;
		requiredExp = GetExpForLevel(stats.Level);
		std::cout << stats.MaxHP << "\n";
	}
}

void Pokemon::UpdateStats()
{
	stats.MaxHP = (int)floor((defaultHP * stats.Level) / 100.0f) + 10 + stats.Level;
	stats.Attack = (int)floor((defaultAttack * stats.Level) / 100.0f) + 5;
	stats.Defense = (int)floor((defaultDefense * stats.Level) / 100.0f) + 5;
	stats.SPATK = (int)floor((defaultSPATK * stats.Level) / 100.0f) + 5;
	stats.SPDEF = (int)floor((defaultSPDEF * stats.Level) / 100.0f) + 5;
	stats.Speed = (int)floor((defaultSpeed * stats.Level) / 100.0f) + 5;

	//hp = stats.MaxHP;
}

void Pokemon::Attack()
{
}

bool Pokemon::TakeDamage(Pokemon* attacker, int x)
{

	float attackType = TypeChart::GetEffectiveness(attacker->GetMoveAt(x)->GetType(), GetType()) * TypeChart::GetEffectiveness(attacker->GetMoveAt(x)->GetType(), GetType());

	float attack = (attacker->GetMoveAt(x)->GetIsSpecial()) ? attacker->stats.SPATK : attacker->stats.Attack;
	float defense = (attacker->GetMoveAt(x)->GetIsSpecial()) ? stats.SPDEF : stats.Defense;

	float modifiers = Random::InRange(0.85, 1.0f) * attackType;
	float a = (2 * attacker->stats.Level + 10) / 250.0f;
	float d = a * attacker->GetMoveAt(x)->GetDamage() * ((float)attack / defense);// +2;
	int damage = (int)floor(d * modifiers);

	hp -= damage;

	if (hp <= 0)
		return true;
	return false;
}


void Pokemon::OnUpdate()
{
}

std::string Pokemon::GetMoveName()
{
	for (int i = 0; i < 3; i++)
	{
		return moveset[i]->GetMoveName();
	}
}

void Pokemon::InitMultipliers()
{
	////Special attacks
	//AttackType::atkMoves.emplace(Type::FIRE, std::vector<AttackMove> {AttackMove(Type::FIRE, 0.5f), AttackMove(Type::WATER, 0.5f), AttackMove(Type::GRASS, 2.0f), AttackMove(Type::ICE, 2.0f), AttackMove(Type::BUG, 2.0f), AttackMove(Type::ROCK, 0.5f), AttackMove(Type::DRAGON, 0.5f) });
	//AttackType::atkMoves.emplace(Type::WATER, std::vector<AttackMove> {AttackMove(Type::FIRE, 2.0f), AttackMove(Type::WATER, 0.5f), AttackMove(Type::GRASS, 0.5f), AttackMove(Type::ROCK, 2.0f), AttackMove(Type::DRAGON, 0.5f), AttackMove(Type::GROUND, 2.0f) });
	//AttackType::atkMoves.emplace(Type::GRASS, std::vector<AttackMove> {AttackMove(Type::FIRE, 0.5f), AttackMove(Type::WATER, 2.0f), AttackMove(Type::GRASS, 0.5f), AttackMove(Type::ROCK, 2.0f), AttackMove(Type::DRAGON, 0.5f), AttackMove(Type::GROUND, 2.0f), AttackMove(Type::FLYING, 0.5f), AttackMove(Type::BUG, 0.5f), AttackMove(Type::POISON, 0.5f) });
	//AttackType::atkMoves.emplace(Type::ELECTRIC, std::vector<AttackMove> {AttackMove(Type::WATER, 2.0f), AttackMove(Type::GRASS, 0.5f), AttackMove(Type::DRAGON, 0.5f), AttackMove(Type::GROUND, 0.0f), AttackMove(Type::FLYING, 2.0f), AttackMove(Type::ELECTRIC, 0.5f) });
	//AttackType::atkMoves.emplace(Type::ICE, std::vector<AttackMove> {AttackMove(Type::WATER, 0.5f), AttackMove(Type::GRASS, 2.0f), AttackMove(Type::ICE, 0.5f), AttackMove(Type::DRAGON, 2.0f), AttackMove(Type::GROUND, 2.0f), AttackMove(Type::FLYING, 2.0f) });
	//AttackType::atkMoves.emplace(Type::PSYCHIC, std::vector<AttackMove> {AttackMove(Type::PSYCHIC, 0.5f), AttackMove(Type::FIGHTING, 2.0f), AttackMove(Type::POISON, 2.0f) });
	////Physical attacks
	//AttackType::atkMoves.emplace(Type::NORMAL, std::vector<AttackMove> {AttackMove(Type::ROCK, 0.5f), AttackMove(Type::GHOST, 0.0f) });
	//AttackType::atkMoves.emplace(Type::FIGHTING, std::vector<AttackMove> {AttackMove(Type::ROCK, 2.0f), AttackMove(Type::GHOST, 0.0f), AttackMove(Type::ICE, 2.0f), AttackMove(Type::PSYCHIC, 0.5f), AttackMove(Type::NORMAL, 2.0f), AttackMove(Type::FLYING, 0.5f), AttackMove(Type::BUG, 0.5f), AttackMove(Type::POISON, 0.5f) });
	//AttackType::atkMoves.emplace(Type::FLYING, std::vector<AttackMove> {AttackMove(Type::ROCK, 0.5f), AttackMove(Type::GRASS, 2.0f), AttackMove(Type::ELECTRIC, 0.5f), AttackMove(Type::FIGHTING, 2.0f), AttackMove(Type::BUG, 2.0f) });
	//AttackType::atkMoves.emplace(Type::GROUND, std::vector<AttackMove> {AttackMove(Type::FIRE, 2.5f), AttackMove(Type::GRASS, 0.5f), AttackMove(Type::ELECTRIC, 2.0f), AttackMove(Type::FLYING, 0.0f), AttackMove(Type::ROCK, 2.0f), AttackMove(Type::BUG, 0.5f), AttackMove(Type::POISON, 2.0f) });
	//AttackType::atkMoves.emplace(Type::ROCK, std::vector<AttackMove> {AttackMove(Type::FIRE, 2.0f), AttackMove(Type::ICE, 2.0f), AttackMove(Type::FIGHTING, 0.5f), AttackMove(Type::FLYING, 2.0f), AttackMove(Type::GROUND, 0.5f), AttackMove(Type::BUG, 2.0f) });
	//AttackType::atkMoves.emplace(Type::BUG, std::vector<AttackMove> {AttackMove(Type::ICE, 0.5f), AttackMove(Type::GRASS, 2.0f), AttackMove(Type::PSYCHIC, 2.0f), AttackMove(Type::FIGHTING, 0.5f), AttackMove(Type::FLYING, 0.5f), AttackMove(Type::POISON, 2.0f) });
	//AttackType::atkMoves.emplace(Type::POISON, std::vector<AttackMove> {AttackMove(Type::GRASS, 2.0f), AttackMove(Type::GROUND, 0.5f), AttackMove(Type::ROCK, 0.5f), AttackMove(Type::BUG, 2.0f), AttackMove(Type::POISON, 0.5f), AttackMove(Type::GHOST, 0.5f) });
	//AttackType::atkMoves.emplace(Type::GHOST, std::vector<AttackMove> {AttackMove(Type::PSYCHIC, 0.0f), AttackMove(Type::NORMAL, 0.0f) });
	////AttackType::atkMoves.emplace(Type::DRAGON, std::vector<AttackMove> {AttackMove(Type::ROCK, 0.5f), AttackMove(Type::GHOST, 0.0f), });
}
