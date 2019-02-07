#include <iostream>
#include <string>
#include <cstdlib>  // Random
#include <ctime>    // Random (Time seed)
#include <iomanip>
// FinalProject.cpp
// Starting Date : 9 Nov 2018
// Simple RPG
// Hyunwook Jung Diablo Valley College

using namespace std;

string getUserName();   // Get username
int getRandom(int, int);    // Get random Value
void getUserInfo(int []);   // Get value of abilities
void getUserJob(int []);    // Get user Job
void printJobSwitch(int);    // Print Job Description
void getUserAge(int []);    // Get User Age
int getWhereToGo();    // Place to go?
double setHp(int []);   // set Health point of character by the age and random seeds
int setAtkp(int []);    // set Attack point of character by the data of user characteristic
void printStatus(string, int, int, int, int, int, int[]);
void inn(int, int &, int, int &, int &, int []);
void dungeon(int, int &, int, int &, int &, int []);
void gameOver(int, int, int, int []); // Check death

const int CHARSIZE = 5;

const string classes[CHARSIZE + 1] ={   "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",
                                        "Chief",
                                        "Thief",
                                        "Wizard",
                                        "Priest",
                                        "Knight" };

const string userCharacter[CHARSIZE] ={ "an outgoing",
                                        "a hostile",
                                        "an imaginative",
                                        "a sympathetic",
                                        "a disciplined" };

const string placelist[3] =  {  "@@@@@@@@@@@@@@@ERROR@@@@@@@@@@@@@@@@",
                                "Inn",
                                "Dungeon"};



int main()
{
    string userName;
    int userInfo[10];

    userName = getUserName();
    getUserInfo(userInfo);
    getUserJob(userInfo);

        cout << "Do you like your class? (Y or N)";
        char yesOrNo;
        cin >> yesOrNo;
        while (yesOrNo != 'y' && yesOrNo != 'Y')
        {
            if (yesOrNo == 'n' || yesOrNo == 'n')
                {
                    getUserJob(userInfo);
                    cout << "Do you like your class? (Y or N)";
                    cin >> yesOrNo;
                }
            else
            {
                cout << "Please enter between 'y', 'Y', 'n' or 'N'.\n";
                cin >> yesOrNo;
            }
        }
    cout << "Your class is " << classes[userInfo[5]] << endl;
    getUserAge(userInfo);

    int baseHp, currentHp, atkp;
    baseHp = userInfo[7] - userInfo[6];
    baseHp = baseHp * setHp(userInfo);  // HP data made done
    int maxHp = baseHp;
    currentHp = maxHp;
    atkp = setAtkp(userInfo);

    int gold = 0;
    int score = 0;

    do
    {
        if (currentHp > maxHp)
        {
            currentHp = maxHp;
        }
        printStatus(userName, maxHp, currentHp, atkp, score, gold, userInfo);
        int placeCommand = getWhereToGo();

        switch (placeCommand)
        {
        case 1 :    inn(maxHp, currentHp, atkp, score, gold, userInfo);  // "Inn",
            break;
        case 2 :    dungeon(maxHp, currentHp, atkp, score, gold, userInfo);     // "Dungeon"
            break;
        }

        maxHp--;
        gameOver(maxHp, currentHp, score, userInfo);   // Double check death just in case

        userInfo[6]++;  // Aging
        cout << "\nYou are now " << userInfo[6] << " years old.\n";



    } while (userInfo[6] < userInfo[7] || currentHp <= 0 || maxHp <= 0);

    gameOver(maxHp, currentHp, score, userInfo);   // Double check death just in case

    return 0;
}

string getUserName()    // Get userName
{
    cout << "What is your last name?\n";
    string userLastName;
    cin >> userLastName;    // Get User Input
    cout << "\"" << userLastName << "\" Is this your last name?(Y or N)";

    char yesOrNo;
    cin >> yesOrNo;
    while (yesOrNo != 'y' && yesOrNo != 'Y')
    {
        if (yesOrNo == 'n' || yesOrNo == 'N')
        {
            cout << "What is your last name?\n";
            string userLastName;
            cin >> userLastName;    // Get User Input
        }
        else
        {
            cout << "Please enter between 'Y', 'y', 'N' or 'n'.";
        }
        cout << "\"" << userLastName << "\" Is this your last name?(Y or N)";
        cin >> yesOrNo;
    }


    cout << "What is your first name?\n";
    string userName;
    cin >> userName;    // Get User Input
    cout << "\"" << userName << "\" Is this your first name?(Y or N)";

    char yesOrNoTwo;
    cin >> yesOrNoTwo;
    while (yesOrNoTwo != 'y' && yesOrNoTwo != 'Y')
    {
        if (yesOrNoTwo == 'n' || yesOrNoTwo == 'N')
        {
            cout << "What is your name?\n";
            string userName;
            cin >> userName;    // Get User Input
        }
        else
        {
            cout << "Please enter between 'Y', 'y', 'N' or 'n'.";
        }
        cout << endl << "\"" << userName << "\" Is this your first name?(Y or N)";
        cin >> yesOrNoTwo;
    }
    cout << "Hello! " << userName << "!\n";
    return userName;
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

void getUserInfo(int array[])   // Get user Characteristic
{
    for (int count = 0; count < CHARSIZE; count++)     // Get Characteristics 1~5
    {
        cout << "Are you " << userCharacter[count] <<" person?[1~5]" << endl;
        cout << "1\t2\t3\t4\t5\n";
        cout << "Not at all\t\tAbsolutely\n";
        cin >> array[count];

        while (array[count] < 1 || CHARSIZE < array[count] )   // Filtering
        {
            cout << "Please enter a number between 1~5\n";
            cin >> array[count];
        }
    }
    /****************************
     *   array[0] Outgoing      *
     *   array[1] Hostile       *
     *   array[2] Imaginative   *
     *   array[3] Sympathetic   *
     *   array[4] Disciplined   *
     ****************************/
     // Check Highest Characteristic Value
    int highest = CHARSIZE;
    bool isThisHighest = false;

    while (highest >= 1 && isThisHighest == false)
        {
            for (int count = 0; count < CHARSIZE; count++) // Check 1, 2, 3, 4, 5 value
            {
                if (array[count] == highest)
                    {
                        isThisHighest = true;   // Is there any array value == highest???
                    }
            }
            if (isThisHighest == false)
                highest--;  // If we don't have any number, reduce the value of highest
        }

    cout << "I recommend you to become following jobs: ";
    if (highest == 1)   // If five value == 1
        cout << "Nothing. You don't have any talent at all..." << endl;
    else
    {
        for (int count = 0; count < CHARSIZE; count++)
        {
            if (array[count] == highest)
                cout << classes[count + 1] << "  ";
        }
    }
}
void getUserJob(int array[])    // userInfo[5] is for CLASS!!
{
    cout << "\nWhat do you want to become?\n";
    for (int count = 0; count < CHARSIZE; count ++) // Print Jobs
        cout << (count + 1) << ". " << classes[count + 1] << endl;
    cin >> array[5];

while (1 > array[5] && array[5] > CHARSIZE)
{
    cout << "Please enter a number between 1~5.";
    cout << "\nWhat do you want to become?\n";
    for (int count = 0; count < CHARSIZE; count ++) // Print Jobs
        cout << (count + 1) << ". " << classes[count + 1] << endl;
    cin >> array[5];
}
printJobSwitch(array[5]);

}

void printJobSwitch(int jobNum)
{
    switch (jobNum)
    {
            case 1: {cout << "You chose " << classes[(jobNum)] << endl;    // CHIEF
                    cout << "A chief is good at gathering some teammates." << endl;
                    cout << "You may want to save some money for later." << endl;
                    break;
            }
            case 2: {cout << "You chose " << classes[(jobNum)] << endl;  //  THIEF
                    cout << "A thief is good at gathering some items." << endl;
                    cout << "Resources are everywhere. Treasure Box, Monster... or human." << endl;
                    break;
            }
            case 3: {cout << "You chose " << classes[(jobNum)] << endl;  // WIZARD
                    cout << "A wizard has mysterious magics to make enemy powerless." << endl;
                    cout << "It is extremely efficient to use your magic to strong enemies." << endl;
                    break;
            }
            case 4: {cout << "You chose " << classes[(jobNum)] << endl;  //  PRIEST
                    cout << "A priest can borrow mystic power to help teammates." << endl;
                    cout << "It will be an hard adventure if you adventure alone." << endl;
                    cout << "Try to get teammates as soon as possible." << endl;
                    break;
            }
            case 5: {cout << "You chose " << classes[(jobNum)] << endl;  //  KNIGHT
                    cout << "A knight is a strong warrior who can bash enemies." << endl;
                    cout << "Or you can be a shield to protect your friends." << endl;
                    cout << "But behave wisely. Your teammates can't live your life instead of you!" << endl;
            }
                    break;
    }
}

void getUserAge(int array[])    // userInfo[6] is for AGE!!
{
    cout << "How old are you? (10~100)\n";
    cin >> array[6];
    while (array[6] < 10 || 100 < array[6])
    {
        cout << "Please enter a number between 10 ~ 100\n";
        cout << "How old are you? (10~100)\n";
        cin >> array[6];
    }
    if (array[6] > 50)
    {
        array[7] = array[6] + array[0] - array[1] + getRandom(1, 10);   // array[7] is for DEATH!!
    }
    else    // Age <= 50
    {
        array[7] = array[6] + array[0] - array[1] + getRandom(20, 40);
    }
}

int getWhereToGo()
{
    cout << "Where do you want to go?\n";
    for (int count = 1; count < 3; count++)
        cout << count << ". " << placelist[count] << endl;
    int select;
    cin >> select;  // 1, 2, 3, 4, 5
    while (select < 1 || 2 < select)
    {
        cout << "Please enter a number between 1 ~ 2.";
        cout << "Where do you want to go?";
        for (int count = 1; count < 3; count++)
            cout << count << ". " << placelist[count] << endl;
        cin >> select;
    }
    return select;
}



double setHp(int array[])
{
    double timesHp;
    switch (array[5])
    {
        case 1: timesHp = 1.4;    // CHIEF

                break;
        case 2: timesHp = 1.0;  //  THIEF

                break;
        case 3: timesHp = 1.0;  // WIZARD

                break;
        case 4: timesHp = 1.2;  //  PRIEST

                break;
        case 5: timesHp = 1.4;  //  KNIGHT

                break;
    }
    return timesHp;
}

int setAtkp(int array[])
{
    int atkp;
    switch (array[5])
    {
        case 1: atkp = 3 + array[0];    //  CHIEF
                break;

        case 2: atkp = 4 + array[1];    //  THIEF
                break;

        case 3: atkp = 6 + array[2];    //  WIZARD
                break;

        case 4: atkp = 2 + array[3];    //  PRIEST
                break;

        case 5: atkp = 3 + array[4];    //  KNIGHT
                break;
    }
    return atkp;
}

void printStatus(string userName, int maxHp, int currentHp, int atkp, int score, int gold, int array[])
{
    cout << "\n\n---------------------------------------------\n\n";
    cout << "\tName: " << userName << endl;
    cout << "\tAge: " << array[6] << endl;
    cout << "\tHP: " << currentHp << "/" << maxHp << endl;
    cout << "\tATK: " << atkp << endl;
    cout << "\tGold: " << gold << endl;
    cout << "\tScore: " << score << endl;
    cout << "\n---------------------------------------------\n";
}

void inn(int maxHp, int &currentHp, int atkp, int &score, int &gold, int array[])
{
    cout << "\n\"Welcome to our Inn! You can stay a while and get rest here.\"\n";
    cout << "\"The cost will be 50 golds.\"\n";
    cout << "1. Stay\t\t2. Leave\n";
    int restCommand;
    do
    {
        cout << "Your golds: " << gold << endl;
        cin >> restCommand;
        switch (restCommand)
        {
            case 1: {cout << "You took a rest.";
                    currentHp = maxHp;
                    cout << "\nHP: " << currentHp << "/" << maxHp;
                    gold = gold - 50;
                    cout << "\nGold: " << gold;
                    score = score - 100;
                    if (gold < 0)
                    {
                        cout << "\nNow you have " << gold << " gold in debt.\n";
                    }
                    break;
            }

            case 2: break;
            default: cout << "\"Uh... What?\"\n";
        }
    } while(restCommand > 3 || 0 > restCommand);
}

void dungeon(int maxHp, int &currentHp, int atkp, int &score, int &gold, int array[])
{
    cout << "\nThere comes a new scary monster!\n";
    int monHp = getRandom(10, 50);
    int monAtkp = getRandom(2, 5);
    int runSuccess = 0;
    do
    {
        cout << "\n\t\t\tMonster's HP: ";
        int asterisks = monHp / 10 + 1;
        for (int count = 0; count < asterisks; count++)
        {
            cout << "*";
        }

        cout << "\n\nYour HP: " << currentHp << "/" << maxHp;
        cout << "\n\nWhat will you do?\n";
        cout << "1. Fight\t\t2.Run\n";

        int fightCommand = 0;
        cin >> fightCommand;

        switch (fightCommand)
        {
        case 1:
                {
                    cout << "You attacked the monster!\n";
                int damage = 0;
                damage = atkp + getRandom(0, atkp);
                cout << damage << " damage to the monster.\n";
                monHp = monHp - damage;

                if (monHp <= 0) //  If it dies
                {
                    break;
                }

                cout << "Monster is about to attack you!\n";
                int monDamage = 0;
                monDamage = monAtkp + getRandom(0, monAtkp);
                cout << monDamage << " damage to you.\n";
                currentHp = currentHp - monDamage;
                score = score + (10 * damage) + (10 * monDamage);
                break;
                }
        case 2:
            {
                runSuccess = getRandom(1, 2);
            if (runSuccess == 1)
            {
                cout << "You failed to escape...\n";
                cout << "Monster is about to attack you!\n";
                int monDamage = 0;
                monDamage = monAtkp + getRandom(0, monAtkp);
                currentHp = currentHp - monDamage;
                score = score + (10 * monDamage);
            }
            else
            {
                cout << "You succeeded to escape.\n";
            }
            break;
            }
        }

        if (monHp <= 0)
        {
            cout << "\nThe scary monster died.\n";
            int monGold = 0;
            monGold = getRandom(20, 90);
            gold = gold + monGold;
            score = score + (monGold * 2);
            cout << "You got " << monGold << " golds!\n";
        }
    } while (runSuccess != 2 && monHp > 0 && currentHp > 0);

}

void gameOver(int maxHp, int currentHp, int score, int userInfo[])
{
    score = score * (25 - (userInfo[0] + userInfo[1] + userInfo[2] + userInfo[3] + userInfo[4])) / 10;
    if (maxHp <= 0)
    {
        cout << "\nYou died because of your old age...";
        cout << "\nYour age: " << userInfo[6] << endl;
        cout << "\nScore: " << score << endl;
        exit(0);
    }
    if (userInfo[6] >= userInfo[7])
    {
        cout << "\nYou died because of your old age...";
        cout << "\nYour age: " << userInfo[6] << endl;
        cout << "\nScore: " << score << endl;
        exit(0);
    }
    if (currentHp <= 0)
    {
        cout << "\nYou died because of monster...";
        cout << "\nYour age: " << userInfo[6] << endl;
        cout << "\nScore: " << score << endl;
        exit(0);
    }
}
