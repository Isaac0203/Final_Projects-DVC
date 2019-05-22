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
string start();
class KnockOut {};
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
    int gold;
	bool fainted;
public:

	FightStatus()
	{
		className = "Monster";
		maxHealthPoint = 10.0;
		curHealthPoint = maxHealthPoint;
		maxManaPoint = 10.0;
		curManaPoint = maxManaPoint;

		attackPoint = 5.0;		// How strong a person's attack is
		defensePoint = 0.0;	// How resistant a person is
		precisionPoint = 90.0;	// How precise a person's attack is (%)
		evasionPoint = 1.0;	// How often a person avoid attack (%)
		criticalPoint = 1.0;	// How often a person attack critically (%)
		luckPoint = 1.0;		// How much extra money a person make (%)

		gold = 0;
		fainted = false;
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
	~FightStatus()
	{

	}
	void setClassName(string cn);
	const string getClassName() const;

	void setMaxHealthPoint(int mhp);
	const int getMaxHealthPoint() const;
	void trainHealth(int th);

	void setCurHealthPoint(int chp);
	const int getCurHealthPoint() const;

	void setMaxManaPoint(int mmp);
	const int getMaxManaPoint() const;

	void setCurManaPoint(int cmp);
	const int getCurManaPoint() const;

	void setAttackPoint(double ap);
	const double getAttackPoint() const;
    void trainAttack(int ta);

	void setDefensePoint(double dp);
	const double getDefensePoint() const;
    void trainDefense(int td);

	void setPrecisionPoint(double pp);
	const double getPrecisionPoint() const;
    void trainPrecision(int tp);

	void setEvasionPoint(double ep);
	const double getEvasionPoint() const;

	void setCriticalPoint(double cp);
	const double getCriticalPoint() const;

	void setLuckPoint(double lp);
	const double getLuckPoint() const;
    void trainLuck(int tl);

	void setLoyalty(int l);
	const int getLoyalty() const;

	void setTier(int t);
	const int getTier() const;

	void setGold(int tp);
	const int getGold() const;

	void operator-(FightStatus* &right);		// It's an attack!!!
	void display() const;	// Display general status

	void setFainted();
	void setFainted(bool);
	const bool getFainted() const;

    void training();
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
	// HP change applied if it is not fainted
	// Else if it is fainted, fail to apply the change
	if (!fainted)
	{
		curHealthPoint = chp;

		// Did he die by an attack?
		setFainted();
	}
	else if (fainted)
	{
		cout << "It is fainted now..." << endl;
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

void FightStatus::operator-(FightStatus* &right) // Left object attack right
{
	int damage = 0;
	if (right->fainted)
	{
		cout << right->className << " is already fainted!" << endl;
		throw KnockOut();
	}
	else
	{
		cout << className << " attacks " << right->className << "!" << endl;
		// 1. Evasion Attempt
		// (1) With right object's evasionPoint and this's accuracyPoint
		// (2) Calculate the attack success percentage first
		int attackSuccessPercentage = (this->getPrecisionPoint()) - right->getEvasionPoint();	// (%)
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
		else if (attackSuccessPercentage >= getRandom(0, 100))
		{
			// 2. Attack damage calculation
			// left's attackPoint
			// If critical attack occurred, *1.5 to the damage
			damage = this->getAttackPoint();
			int criticalSuccessPercentage = this->getCriticalPoint();

			if (criticalSuccessPercentage >= getRandom(0, 100))
			{
				damage *= 2.0;
			}

			// 3. Total damage calculation
			// Attack damage - right's defense
			damage -= right->getDefensePoint();
			// Check if the damage is higher than defense,
			// which means if damage is positive or negative right now
			if (damage <= 0)
			{
				cout << right->getClassName() << " has successfully blocked that attack!" << endl;
			}
			else if (damage > 0)
			{


				// 4. Apply the damage to right's current healthPoint
				cout << damage << " damage to " << right->getClassName() << "!" << endl;
				int originalHealthPoint = right->getCurHealthPoint();
				int damagedHealthPoint = originalHealthPoint - damage;
				right->setCurHealthPoint(damagedHealthPoint);
				// 5. Check if right die with the damage
				// Death or Fainted Function will be inside the setCurHealthPoint() function.

			}
			// 6. HP Report
			cout << right->className << "'s HP: " << right->curHealthPoint << " / " << right->maxHealthPoint << endl;
			if (right->curHealthPoint <= 0.0)
                throw KnockOut();
		}
	}
}
void FightStatus::trainHealth(int th)
{
    // Simply increase the ability
    maxHealthPoint += th;
    curHealthPoint = maxHealthPoint;
}

void FightStatus::trainAttack(int ta)
{
    // Simply increase the ability
    attackPoint += ta;
}

void FightStatus::trainDefense(int td)
{
    // Simply increase the ability
    defensePoint += td;
}

void FightStatus::trainPrecision(int tp)
{
    // Simply increase the ability
    precisionPoint += tp;
}

void FightStatus::trainLuck(int tl)
{
    // Simply increase the ability
    luckPoint += tl;
    criticalPoint += tl;
}


void FightStatus::display() const
{
	cout << endl << "============= Display the player character =============" << endl;
	cout << "Name: \t\t" << className << endl;
	cout << "HP: \t\t" << curHealthPoint << " / "<< maxHealthPoint << endl;
	cout << "MP: \t\t" << curManaPoint << " / " << maxManaPoint << endl;
	cout << "ATK: \t\t" << attackPoint << endl;
	cout << "DEF: \t\t" << defensePoint << endl;
	cout << "PRECISION: \t" << precisionPoint << "%" << endl;
	cout << "EVASION: \t" << evasionPoint << endl;
	cout << "CRITICAL: \t" << criticalPoint << endl;
	cout << "LUCK: \t\t" << luckPoint << endl;
	cout << "GOLD: \t\t" << gold << endl;
	cout << "FAINTED: \t";
	if (fainted)
		cout << "Fainted" << endl;
	else if (!fainted)
		cout << "Energetic" << endl;
	cout << "========================================================" << endl;
}
void FightStatus::training()
{
    char trainAbility;
    do
    {
        cout << "Choose one ability to train" << endl;
        cout << "(H)ealth" << setw(13) << "(A)ttack" << setw(13) << "(D)efense" << setw(13) << "(P)recision" << setw(13) << "(L)uck" << endl;
        cin >> trainAbility;
        if (trainAbility != 'H' && trainAbility != 'A' && trainAbility != 'D' && trainAbility != 'P' && trainAbility != 'L')
        {
            cout << "Please enter a capital letter between H, A, D, P, or L." << endl;
        }
    } while(trainAbility != 'H' && trainAbility != 'A' && trainAbility != 'D' && trainAbility != 'P' && trainAbility != 'L');

    switch (trainAbility)
    {
    case 'H':
        cout << "You trained your health." << endl;
	cout << endl << "============= Display the player character =============" << endl;
	cout << "Name: \t\t" << className << endl;
	cout << "HP: \t\t" << curHealthPoint << " / "<< maxHealthPoint << " -> ";
	cout << maxHealthPoint + 5 << endl;
	cout << "MP: \t\t" << curManaPoint << " / " << maxManaPoint << endl;
	cout << "ATK: \t\t" << attackPoint << endl;
	cout << "DEF: \t\t" << defensePoint << endl;
	cout << "PRECISION: \t" << precisionPoint << "%" << endl;
	cout << "EVASION: \t" << evasionPoint << endl;
	cout << "CRITICAL: \t" << criticalPoint << endl;
	cout << "LUCK: \t\t" << luckPoint << endl;
	cout << "GOLD: \t\t" << gold << endl;
	cout << "FAINTED: \t";
	if (fainted)
		cout << "Fainted" << endl;
	else if (!fainted)
		cout << "Energetic" << endl;
	cout << "========================================================" << endl;
        maxHealthPoint += 5;
        curHealthPoint = maxHealthPoint;
        break;

    case 'A':
        cout << "You trained your attack." << endl;
	cout << endl << "============= Display the player character =============" << endl;
	cout << "Name: \t\t" << className << endl;
	cout << "HP: \t\t" << curHealthPoint << " / "<< maxHealthPoint << endl;
	cout << "MP: \t\t" << curManaPoint << " / " << maxManaPoint << endl;
	cout << "ATK: \t\t" << attackPoint << " -> " << attackPoint + 1.0 << endl;
	cout << "DEF: \t\t" << defensePoint << endl;
	cout << "PRECISION: \t" << precisionPoint << "%" << endl;
	cout << "EVASION: \t" << evasionPoint << endl;
	cout << "CRITICAL: \t" << criticalPoint << endl;
	cout << "LUCK: \t\t" << luckPoint << endl;
	cout << "GOLD: \t\t" << gold << endl;
	cout << "FAINTED: \t";
	if (fainted)
		cout << "Fainted" << endl;
	else if (!fainted)
		cout << "Energetic" << endl;
	cout << "========================================================" << endl;
        attackPoint += 1.0;
        break;

    case 'D':
        cout << "You trained your defense." << endl;
	cout << endl << "============= Display the player character =============" << endl;
	cout << "Name: \t\t" << className << endl;
	cout << "HP: \t\t" << curHealthPoint << " / "<< maxHealthPoint << endl;
	cout << "MP: \t\t" << curManaPoint << " / " << maxManaPoint << endl;
	cout << "ATK: \t\t" << attackPoint << endl;
	cout << "DEF: \t\t" << defensePoint << " -> " << defensePoint + 1.0 << endl;
	cout << "PRECISION: \t" << precisionPoint << "%" << endl;
	cout << "EVASION: \t" << evasionPoint << endl;
	cout << "CRITICAL: \t" << criticalPoint << endl;
	cout << "LUCK: \t\t" << luckPoint << endl;
	cout << "GOLD: \t\t" << gold << endl;
	cout << "FAINTED: \t";
	if (fainted)
		cout << "Fainted" << endl;
	else if (!fainted)
		cout << "Energetic" << endl;
	cout << "========================================================" << endl;
        defensePoint += 1.0;
        break;

    case 'P':
        cout << "You trained your precision." << endl;
	cout << endl << "============= Display the player character =============" << endl;
	cout << "Name: \t\t" << className << endl;
	cout << "HP: \t\t" << curHealthPoint << " / "<< maxHealthPoint << endl;
	cout << "MP: \t\t" << curManaPoint << " / " << maxManaPoint << endl;
	cout << "ATK: \t\t" << attackPoint << endl;
	cout << "DEF: \t\t" << defensePoint << endl;
	cout << "PRECISION: \t" << precisionPoint << "%" << " -> " << precisionPoint + 5.0 << "%" << endl;
	cout << "EVASION: \t" << evasionPoint << endl;
	cout << "CRITICAL: \t" << criticalPoint << endl;
	cout << "LUCK: \t\t" << luckPoint << endl;
	cout << "GOLD: \t\t" << gold << endl;
	cout << "FAINTED: \t";
	if (fainted)
		cout << "Fainted" << endl;
	else if (!fainted)
		cout << "Energetic" << endl;
	cout << "========================================================" << endl;
        precisionPoint += 5.0;
        break;

    case 'L':
        cout << "You trained your luck." << endl;
	cout << endl << "============= Display the player character =============" << endl;
	cout << "Name: \t\t" << className << endl;
	cout << "HP: \t\t" << curHealthPoint << " / "<< maxHealthPoint << endl;
	cout << "MP: \t\t" << curManaPoint << " / " << maxManaPoint << endl;
	cout << "ATK: \t\t" << attackPoint << endl;
	cout << "DEF: \t\t" << defensePoint << endl;
	cout << "PRECISION: \t" << precisionPoint << "%" << endl;
	cout << "EVASION: \t" << evasionPoint << endl;
	cout << "CRITICAL: \t" << criticalPoint << " -> " << criticalPoint + 9.0 << endl;
	cout << "LUCK: \t\t" << luckPoint << " -> " << luckPoint + 9.0 << endl;
	cout << "GOLD: \t\t" << gold << endl;
	cout << "FAINTED: \t";
	if (fainted)
		cout << "Fainted" << endl;
	else if (!fainted)
		cout << "Energetic" << endl;
	cout << "========================================================" << endl;
        luckPoint += 9.0;
        criticalPoint += 9.0;
        break;
    }

}
void FightStatus::setFainted()
{
	if (curHealthPoint <= 0.0)
	{
		fainted = true;
	}
	else if (curHealthPoint > 0.0)
	{
		fainted = false;
	}
}
void FightStatus::setFainted(bool)
{
    // When player escape, to force the monster got fainted
    fainted = true;
}
const bool FightStatus::getFainted() const
{
	return fainted;
}

void FightStatus::setGold(int loot)
{
    gold += loot;
}
const int FightStatus::getGold() const
{
    return gold;
}
class Shop
	{
    private:
    public:
        void welcome()
        {
            cout << "Welcome to our shop!" << endl;
            cout << "You may hire some soldiers here." << endl;
        }
        void createSoldier(int treasurePoint, FightStatus* player)
        {
            FightStatus* newSoldier = new FightStatus;
            // Generate the status randomly
            // ATK, Precision, Critical
            int tempAtk = getRandom(0, treasurePoint / 7);
            int tempPrecision = getRandom(0, treasurePoint / 6);
            int tempLuck = getRandom(0, treasurePoint / 5);
            int price = getRandom(treasurePoint / 2 , treasurePoint * 3 / 2);
            newSoldier->trainAttack(tempAtk);
            newSoldier->trainPrecision(tempPrecision);
            newSoldier->trainLuck(tempLuck);
            cout << "Here is our deal for today!" << endl;
            newSoldier->setClassName("this guy");
            newSoldier->display();
            cout << "The price for this guy is " << price << " gold." << endl;

            char yesNo;
            do{
                cout << "Will you hire him? ( Y / N )" << endl;
                cin >> yesNo;
                if (yesNo != 'Y' && yesNo != 'N')
                    cout << "Please enter Y or N." << endl;
            } while (yesNo != 'Y' && yesNo != 'N');

            if (price > player->getGold())
            {
                cout << "Nah, you only have " << player->getGold() << " gold." << endl;
            }
            else if(yesNo == 'N')
            {
                cout << "Maybe next time." << endl;
            }
            else if (price <= player->getGold())
            {
                player->setGold(price * -1);
                cout << "Thank you for the hire!" << endl;
                cout << "You will be stronger now." << endl;
                player->trainAttack(newSoldier->getAttackPoint());
                player->trainLuck(newSoldier->getLuckPoint());
                player->setPrecisionPoint( (newSoldier->getPrecisionPoint() + player->getPrecisionPoint()) / 2);
            }
            delete newSoldier;
        }
	};
class Room
{
private:
	int floorNum;
	int treasurePoint;
	bool monsterInside;				// Is there a monster inside this room?
	FightStatus* monster;
	Shop shopInRoom;
public:
	Room()
	{
		monster = new FightStatus;
		floorNum = 1;
		setTreasurePoint();
	}
	/*Room(FightStatus* player)
	{
		monster = new FightStatus;
		floorNum = 1;
		setTreasurePoint();
		setRoomKind(player);
	}*/
	~Room()
	{
		delete monster;
	}
	void addFloorNum();				// The floor index number 1, 2, 3, ...
	const int getFloorNum() const;
	void setTreasurePoint();		// Setting the loot per each room
	const int getTreasurePoint() const;
	void setRoomKind(FightStatus* player);
	void setMonsterInside();
	void battle(FightStatus* player);
	void givePlayerGold(FightStatus* player);
};

void Room::addFloorNum()
{
	floorNum++;
}
const int Room::getFloorNum() const
{
	return floorNum;
}

void Room::setTreasurePoint()
{
	int tempTP = floorNum * 10;
	treasurePoint = getRandom(tempTP / 2, tempTP);
}
const int Room::getTreasurePoint() const
{
    return treasurePoint;
}
void Room::setRoomKind(FightStatus* player)
{
	// Decide if it is a monster room / a shop room / or an empty room with treasure
	cout << "You entered next room." << endl;
	int roomKind = getRandom(1, 4);
	switch (roomKind)
	{
	case 1:
	case 2:
		// A Monster Room
		cout << endl;
		setMonsterInside();
        battle(player);
        if (monster->getFainted() && monster->getCurHealthPoint() <= 0.0)
        {
            // Filter out escaping situation
            // that monster got fainted with positive curHealthPoint
            givePlayerGold(player);
        }
		break;
	case 3:
		// A Shop
        cout << "You have found a shop." << endl;
        shopInRoom.welcome();
        shopInRoom.createSoldier(treasurePoint, player);
		break;
	case 4:
		// An empty Room
        cout << "The room is empty but a chest." << endl;
        givePlayerGold(player);
		break;
	default:
		break;
	}
	floorNum++;
}
void Room::setMonsterInside()
{
	// Create a Monster with FightStatus class inside the room
	monster = new FightStatus;
	// Get a score to distribute for the monster's status by the floor number
	int monsterStatusScore = floorNum * 2;
	// Distribute the monsterStatusScore into HP, ATK, DEF
	int tempHP = getRandom(0, monsterStatusScore / 3);
	int tempAtk = getRandom(0, monsterStatusScore / 3);
	int tempAgil = getRandom(0, monsterStatusScore / 3);
	int tempDef = monsterStatusScore - tempHP - tempAtk;
	// Monster's HP modification
	tempHP = (tempHP * 5) + monster->getMaxHealthPoint();
	monster->setMaxHealthPoint(tempHP);
	// Monster's Atk modification
	tempAtk = tempAtk + monster->getAttackPoint();
	monster->setAttackPoint(tempAtk);
	// Monster's Def modification
	tempDef = tempDef + monster->getDefensePoint();
	monster->setDefensePoint(tempDef);
	// Monster's Def modification
	tempAgil = tempAgil * 10.0 + monster->getEvasionPoint();
	monster->setEvasionPoint(tempAgil);
	monster->setCriticalPoint(tempAgil);

}

void Room::givePlayerGold(FightStatus* player)
{
    // Setting the amount of maximum gold
    int maximumGold = treasurePoint * (100.0 + player->getLuckPoint()) / 100.0 + player->getLuckPoint();
    int foundGold = getRandom(maximumGold/2, maximumGold);
    // Give him credit for a room!
    cout << "You have found " << foundGold << "G!" << endl;
    player->setGold(foundGold);
    player->getGold();
}

void Room::battle(FightStatus* player)
{
    int escapeChance = 50.0 + player->getEvasionPoint() - monster->getEvasionPoint() / 2;
	cout << "A dangerous monster has appeared!" << endl;
	cout << "Monster's HP: " << monster->getCurHealthPoint() << endl;
	int nextCommand;
	do
	{
		cout << "What's your next move?" << endl;
		cout << "1. Attack \t\t 2. Escape \t\t 3. Display the player" << endl;
		cin >> nextCommand;
		switch (nextCommand)
		{
		case 1:
            try
            {
                *player - monster;
                //cout << "Monster's HP: " << monster->getCurHealthPoint() << " / " << monster->getMaxHealthPoint() << endl;
                *monster - player;
                //cout << "Player's HP: " << player->getCurHealthPoint() << " / " << player->getMaxHealthPoint()<< endl;
            }
            catch (KnockOut K)
            {
                cout << "One down, one remain." << endl;
                cout << "Battle finished." << endl;
            }
            cout << "Attack ended" << endl;
			break;
		case 2:
		    if (getRandom(0, 100) < escapeChance)
            {
                cout << "You successfully escaped from the monster!" << endl;
                cout << "In a rush, you skipped two floors at once." << endl;
                addFloorNum();
                monster->setFainted(true);
            }
            else
            {
                // If one down, stop the battle and throw error.
                try
                {
                cout << "You failed to escape from the monster!" << endl;
                *monster - player;
                }
                catch (KnockOut K)
                {
                cout << "One down, one remain." << endl;
                cout << "Battle finished." << endl;
                }
            }
            break;
		case 3:
			player->display();
			break;
		default:
			cout << "Please enter 1, 2 or 3." << endl;
			break;
		}
	} while (!monster->getFainted() && !player->getFainted());
	delete monster;
}


int main()
{
    // Create player
	FightStatus* player = new FightStatus;
	// Set player name
	player->setClassName(start());
	player->setMaxHealthPoint(20);
	player->setCurHealthPoint(20);
	cout << endl << endl;
	Room firstRoom;
    char trainAbility;
	do
    {
        cout << "You entered: Floor - " << firstRoom.getFloorNum() << endl;
        // Train
        player->training();

        // Prepare the Room, Room kind, Room monster.
        firstRoom.setMonsterInside();
        firstRoom.setRoomKind(player);
        cin.ignore(1, '\n');
        cout << "Press any key to proceed." << endl;
        cin.get();
        cin.clear();

        // Player survived
        if (!player->getFainted())
        {
            // Room clear
            cout << "You take a rest in this room for a while." << endl;

            // HP restored
            player->setCurHealthPoint(player->getMaxHealthPoint());
        }
        player->display();
        cin.ignore(1, '\n');
        cout << "Press enter to proceed." << endl;
        cin.get();
        cin.clear();

    } while (!player->getFainted());    // While the player is not fainted

    cout << "You died..." << endl;

    // When player died, delete the player pointer
	delete player;

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

string start()
{
	string playerName;
	char yesNo = 'N';
	cout << "This is a game program that explore into deeper dungeon with your companions." << endl;
	while (yesNo != 'Y' && yesNo != 'y')
	{
		cout << "Who are you?" << endl;
		getline(cin, playerName);
		cout << playerName << ", is that you? ( Y / N )" << endl;
		cin >> yesNo;
		if (yesNo != 'Y' && yesNo != 'y' && yesNo != 'N' && yesNo != 'n')
			cout << "Please type an alphabet between Y or N" << endl;
		cin.ignore(2, '\n');
	}
	cout << "Entering into the dark dungeon..." << endl;
	return playerName;
}
