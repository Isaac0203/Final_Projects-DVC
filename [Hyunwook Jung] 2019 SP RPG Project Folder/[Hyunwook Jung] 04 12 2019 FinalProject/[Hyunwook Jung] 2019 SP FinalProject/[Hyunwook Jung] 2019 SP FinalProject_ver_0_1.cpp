#include <iostream>
#include <cstdlib>	// Random Value Generator
#include <ctime>	// Random Value Generator
#include <iomanip>
#include <string>
// Hyunwook Jung Diablo Valley College
// 04 09 2019 Final Project.ver 0.2
// COMSC 165
using namespace std;

int getRandom(int MIN_VALUE, int MAX_VALUE);

class FightStatus
{
private:
	string className;
	int maxHealthPoint;
	int curHealthPoint;
	int maxManaPoint;
	int curManaPoint;

	double attackPoint;		// How strong a person's attack is
	double defensePoint;	// How resistant a person is
	double precisionPoint;	// How precise a person's attack is (%)
	double evasionPoint;	// How often a person avoid attack (%)
	double criticalPoint;	// How often a person attack critically (%)
	double luckPoint;		// How much extra money a person make (%)
	int loyalty;
	int tier;

	static int damage;		// For damage calculation between FightStatus objects


public:

	FightStatus()
	{
		className = "Nameless";
		maxHealthPoint = 1;
		curHealthPoint = maxHealthPoint;
		maxManaPoint = 1;
		curManaPoint = maxManaPoint;

		attackPoint = 0.0;		// How strong a person's attack is
		defensePoint = 0.0;	// How resistant a person is
		precisionPoint = 0.0;	// How precise a person's attack is (%)
		evasionPoint = 0.0;	// How often a person avoid attack (%)
		criticalPoint = 0.0;	// How often a person attack critically (%)
		luckPoint = 0.0;		// How much extra money a person make (%)
		loyalty = 0;
		tier = 1;
	}

	FightStatus(
		string cn,
		int mhp,
		int chp,
		int mmp,
		int cmp,

		double ap,
		double dp,
		double pp,
		double ep,
		double cp,
		double lp,
		int l,
		int t)
	{
		className = cn;
		maxHealthPoint = mhp;
		curHealthPoint = chp;
		maxManaPoint = mmp;
		curManaPoint = cmp;

		attackPoint = ap;		// How strong a person's attack is
		defensePoint = dp;		// How resistant a person is
		precisionPoint = pp;	// How precise a person's attack is (%)
		evasionPoint = ep;		// How often a person avoid attack (%)
		criticalPoint = cp;		// How often a person attack critically (%)
		luckPoint = lp;			// How much extra money a person make (%)
		loyalty = l;
		tier = t;
	}
	void setClassName(string cn);
	const string getClassName() const;

	void setMaxHealthPoint(int mhp);
	const int getMaxHealthPoint() const;

	void setCurHealthPoint(int chp);
	const int getCurHealthPoint() const;

	void setMaxManaPoint(int mmp);
	const int getMaxManaPoint() const;

	void setCurManaPoint(int cmp);
	const int getCurManaPoint() const;

	void setAttackPoint(double ap);
	const double getAttackPoint() const;

	void setDefensePoint(double dp);
	const double getDefensePoint() const;

	void setPrecisionPoint(double pp);
	const double getPrecisionPoint() const;

	void setEvasionPoint(double ep);
	const double getEvasionPoint() const;

	void setCriticalPoint(double cp);
	const double getCriticalPoint() const;

	void setLuckPoint(double lp);
	const double getLuckPoint() const;

	void setLoyalty(int l);
	const int getLoyalty() const;

	void setTier(int t);
	const int getTier() const;

	double attackCalculation();

	void operator-(FightStatus &right);		// It's an attack!!!
};

void FightStatus::setClassName(string cn)
{
	className = cn;
}
const string FightStatus::getClassName() const
{
	return className;
}

void FightStatus::setMaxHealthPoint(int mhp)
{
	maxHealthPoint = mhp;
}
const int FightStatus::getMaxHealthPoint() const
{
	return maxHealthPoint;
}

void FightStatus::setCurHealthPoint(int chp)
{
	curHealthPoint = chp;

	// Did he die by an attack?
	if (curHealthPoint <= 0)
	{

	}
}
const int FightStatus::getCurHealthPoint() const
{
	return curHealthPoint;
}

void FightStatus::setMaxManaPoint(int mmp)
{
	maxManaPoint = mmp;
}
const int FightStatus::getMaxManaPoint() const
{
	return maxManaPoint;
}

void FightStatus::setCurManaPoint(int cmp)
{
	curManaPoint = cmp;
}
const int FightStatus::getCurManaPoint() const
{
	return curManaPoint;
}

void FightStatus::setAttackPoint(double ap)
{
	attackPoint = ap;
}
const double FightStatus::getAttackPoint() const
{
	return attackPoint;
}

void FightStatus::setDefensePoint(double dp)
{
	defensePoint = dp;
}
const double FightStatus::getDefensePoint() const
{
	return defensePoint;
}

void FightStatus::setPrecisionPoint(double pp)
{
	precisionPoint = pp;
}
const double FightStatus::getPrecisionPoint() const
{
	return precisionPoint;
}

void FightStatus::setEvasionPoint(double ep)
{
	evasionPoint = ep;
}
const double FightStatus::getEvasionPoint() const
{
	return evasionPoint;
}

void FightStatus::setCriticalPoint(double cp)
{
	criticalPoint = cp;
}
const double FightStatus::getCriticalPoint() const
{
	return criticalPoint;
}

void FightStatus::setLuckPoint(double lp)
{
	luckPoint = lp;
}
const double FightStatus::getLuckPoint() const
{
	return luckPoint;
}

void FightStatus::setLoyalty(int l)
{
	loyalty = l;
}
const int FightStatus::getLoyalty() const
{
	return loyalty;
}

void FightStatus::setTier(int t)
{
	tier = t;
}
const int FightStatus::getTier() const
{
	return tier;
}
/*
double FightStatus::attackCalculation()
{
	cout << getClassName() << " is ready to attack!" << endl;
	double damage;
	damage = getAttackPoint() + 
	
}*/



void FightStatus::operator-(FightStatus &right) // Left object attack right
{
	// 1. Evasion Attempt
	// (1) With right object's evasionPoint and this's accuracyPoint
	// (2) Calculate the attack success percentage first
	int attackSuccessPercentage = (this->getPrecisionPoint()) - right.getEvasionPoint();	// (%)
	// (3) Roll the dice with the percentage
	// (4) If the value of (0 ~ 100) die is within attackSuccessPercentage,
	//     evasion fails, attack succeed.	
	//	   If the value of (0 ~ 100) die is bigger than attackSuccessPercentage,
	//     evasion succeed, attack fails.	
	if (attackSuccessPercentage < getRandom(0, 100))
	{
		cout << "It missed..." << endl;
		// No Damage
	}
	else if(attackSuccessPercentage >= getRandom(0, 100))
	{
	// 2. Attack damage calculation
	// left's attackPoint
	// If critical attack occurred, *1.5 to the damage
		int damage = this->getAttackPoint();
		int criticalSuccessPercentage = this->getCriticalPoint();

		if (criticalSuccessPercentage >= getRandom(0, 100))
		{
			damage *= 1.5;
		}

	// 3. Total damage calculation
	// Attack damage - right's defense
		damage -= right.getDefensePoint();
	// Check if the damage is higher than defense,
	// which means if damage is positive or negative right now
		if (damage <= 0)
		{
			cout << right.getClassName() << " has successfully blocked that attack!" << endl;
		}
		else if (damage > 0)
		{

		
	// 4. Apply the damage to right's current healthPoint
			cout << damage << " damage to " << right.getClassName() << "!" << endl;
			int originalHealthPoint = right.getCurHealthPoint();
			int damagedHealthPoint = originalHealthPoint - damage;
			right.setCurHealthPoint(damagedHealthPoint);
	// 5. Check if right die with the damage
	// Death or Fainted Function will be inside the setCurHealthPoint() function.
		}
	}
}


int main()
{
	cout << getRandom(1, 6) + getRandom(1, 6);
	return 0;
}

int getRandom(int MIN_VALUE, int MAX_VALUE)
{
	// Get the system time.
	unsigned seed = time(0);

	// Seed the random number generator.
	srand(seed);

	int randomValue = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

	return randomValue;
}