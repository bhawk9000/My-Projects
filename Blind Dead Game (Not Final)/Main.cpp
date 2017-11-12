/*
   COPYRIGHT (C) 2016 Ben Hawk (bih9) All rights reserved.
   CSI project 2 and 3 - Blind Dead
   Author.  Ben Hawk
   Version. 1.01 11.9.2016.
   Purpose: To create a classic game
*/
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<iomanip>
#include<limits>

using std::cout;
using std::cin;
using std::endl;
using std::fstream;

//gameArray indicies
//gameArray[0] = players current room
const int CURRENT_ROOM_INDEX = 0;
//gameArray[1] = current room of zombie
const int ZOMBIE_ROOM_INDEX = 1;
//gameArray[2]
const int NUM_BULLETS_INDEX = 2;
//gameArray[3]
const int NUM_ROOMS_INDEX = 3;
//boolean whether player has grail or not
const int HAVE_GRAIL_INDEX = 4;

//roomArray indices
//roomArray[gameArray[CURRENT_ROOM_INDEX]][4] = 1 or 0 if the player is
//	or is not in the current room
const int PLAYER_INDEX = 4;
//roomArray[gameArray[ZOMBIE_ROOM_INDEX]][5] = 1, tracks where the zombie is
const int ZOMBIE_INDEX = 5;
//roomArray[room][6] = the room that the grail is in should be marked 1, all others 0
const int GRAIL_INDEX = 6;
// the number of rooms and number of bullets to fend off the zombies
const int MAX_ROOMS = 11;
const int MAX_BULLETS = 6;

//PART 1A prototypes
//reset simply resets the primary game variables
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail);
//print game instructions
void instructions();
//print layout of game memory
void printMemory(int gameArray[],int roomArray[][7]);
// the menu (which calls functions printMemory and instructions)
bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7]);

//PART 1B prototypes
//read in the input file for the map
void readMaze(int roomArray[][7], int gameArray[5]);
//return a random room
int getRandomRoom(int gameArray[5]);
//place the zombie
void placeZombie(int roomArray[][7], int gameArray[5]);
//place the grail
void placeGrail(int roomArray[][7], int gameArray[5]);
// the setup function
void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5]);

//PART 2 prototypes
//checks to see if the zombie is in the room specified by the parameter
bool checkZombie(int, int roomArray[][7]);
//checks to see if the grail is in the room specified by the parameter
bool checkGrail(int, int roomArray[][7]);
//checks to see if the zombie is in a room adjacent to you
bool checkNearZombie(int, int roomArray[][7]);
//checks to see if the grail is in a room adjacent to you
bool checkNearGrail(int, int roomArray[][7]);
//shows the user if they have won or lost the game
bool winOrLose(int, int& currentRoom);
//shows the user all rooms connected to the current one
void showConnectedRooms(int& currentRoom);
//checks to see if a room is connected to the current one
bool isConnected(int, int& currentRoom);

//PART 3 prototypes
int moveRoom(int, int& currentRoom, bool& haveGrail, int roomArray[][7], int gameArray[5]);
void shootRoom(int, int& zombieRoom, int& currentRoom, int& numBullets, int roomArray[][7]);
void moveZombie(int& zombieRoom, int roomArray[][7], int gameArray[5]);
bool validateSelection(std::string);
int doSelection(std::string words, int& zombieRoom, int& currentRoom, int& numBullets, bool& haveGrail, int gameArray[5], int roomArray[][7]);
void waitForMove(int& zombieRoom, int& currentRoom, int& numBullets, bool& haveGrail, int gameArray[5], int roomArray[][7]);

int main()
{
    // these variables are passed throughout this program
    int roomArray[MAX_ROOMS][7],
        gameArray[5],
        currentRoom = 0,
        zombieRoom = 0,
        numBullets = 0,
        numRooms = 0,
        menuSelection = 0;
    bool haveGrail = false;

    menu(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, gameArray, roomArray);
    //reset(currentRoom, zombieRoom, numBullets, numRooms, haveGrail);

    return 0;
}
// Preconditions - function is sent the int zombieRoom, int numBullets, int numRooms, bool haveGrail variables
// Postconditions - function resets all of the given variables to zero
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail)
{
    currentRoom = 0;
    zombieRoom = 0;
    numBullets = 0;
    numRooms = 0;
    haveGrail = 0;
}
// Preconditions - function is not sent anything
// Postconditions - function displays the instructions to the screen
void instructions()
{
    cout << " YOUR MISSION, SHOULD YOU CHOOSE TO ACCEPT IT, IS TO SEEK THE HOLY " << endl
         << " GRAIL WITHIN THE RUINS OF AN ANCIENT CHURCH. TO SUCCEED YOU MUST " << endl
         << " ENTER THE CHURCH, AVOID THE UNDEAD GUARDIANS, FIND THE GRAIL AND " << endl
         << " ESCAPE. YOU HAVE SIX SILVER BULLETS TO PROTECT YOU. IF THE ZOMBIES " << endl
         << " FIND YOU OR YOU RUN OUT OF BULLETS YOU WILL LOSE!" << endl << endl;
}
// Preconditions - function is sent the gameArray, and the roomArray
// Postconditions - function displays the parameters' content to the screen
void printMemory(int gameArray[],int roomArray[][7])
{
    int x = 1;

    cout << "Game Array:" << endl << "  [current] [bullets] [  rooms]" << endl;
    cout << "  [      " << gameArray[0] << "] " << "[      " << gameArray[1]
         << "] " << "[      " << gameArray[2] << "] " << endl << endl;

    cout << "Room Array:" << endl << "          [ north] [ south] [   west] [   east] [player] "
         << "[zombie] [ grail]" << endl;

    for (int y = 0; y < 11; y++)
    {
        cout << "[R " << x << "] ->  [     " << roomArray[y][0] << "] [     " << roomArray[y][1] << "] [      "
             << roomArray[y][2] << "] [      " << roomArray[y][3] << "] [     " << roomArray[y][4]
             << "] [     " << roomArray[y][5] << "] [     " << roomArray[y][6] << "]" << endl;
        x++;
    }
}
//Pre - function is sent the currentRoom, zombieRoom, numBullets, numRooms, and haveGrail variables, and is sent the gameArray and roomArray arrays
//Post - function displays the menu and gets user input
bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7])
{
    int selection = 0;
    //while(1)
    {
        cout << std::setw(7) << std::setfill(' ') << " " << "Enter, if you dare..." << endl;
        cout << "*** THE TOMB OF THE BLIND DEAD ***" << endl << endl;
        cout << std::setw(8) << std::setfill(' ') << " " << "Main Menu" << endl;
        cout << "1. Instructions" << endl << "2. Begin" << endl << "3. Exit" << endl << endl;
        cin >> selection;
        cout << "Enter Menu Selection: " << selection << endl << endl;

        if ((cin.fail()) || selection < 1 || selection > 3)
        {
            cout << "You MUST choose an option between 1 and 3." << endl << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        if (selection == 1)
        {
            instructions();
        }
        if (selection == 2)
        {
            setup(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, roomArray, gameArray);
        }
        if (selection == 3)
        {
            return 0;
        }
    }
}
//Pre - function is sent the room and game arrays
//Post - function reads in the "easyMaze" file and stores it in the roomArray
void readMaze(int roomArray[][7], int gameArray[5])
{
    std::ifstream in;
    in.open("easyMaze.txt");

    int num = 0;
    int numRooms = 0;
    in >> numRooms;

    for (int x = 0; x <= 11; x++)
        for (int y = 0; y < 7; y++)
        {
            in >> num;
            roomArray[x][y] = num;
        }
}
//Pre - function is sent the game array
//Post - function generates a random room
int getRandomRoom(int gameArray[5])
{
    return (rand() % 11) + 1;
}
// Pre - function is sent the room and game array
// Post - function places the zombie in a random room
void placeZombie(int roomArray[][7], int gameArray[5])
{
    bool y = true;

    while(y)
    {
        int x = getRandomRoom(gameArray);
        if (x >= 6)
        {
            roomArray[x - 1][ZOMBIE_INDEX] = 1;

            y = false;
        }
    }
}
// Pre - function is sent the room and game array
// Post - function places grail in a random room
void placeGrail(int roomArray[][7], int gameArray[5])
{
    bool y = true;

    while(y)
    {
        int x = getRandomRoom(gameArray);
        if (x >= 6)
        {
            roomArray[x - 1][GRAIL_INDEX] = 1;

            y = false;
        }
    }
}
// Pre - function is sent the currentRoom, numBullets, numRooms, and haveGrail variables, and is sent the room and game array
// Post - function provides the initial setup for the game
void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5])
{
    std::string words;

    srand(time(0));
    currentRoom = 1;
    haveGrail = 0;
    numBullets = MAX_BULLETS;

    readMaze(roomArray, gameArray);
    currentRoom = 1;
    gameArray[CURRENT_ROOM_INDEX] = 1;
    roomArray[currentRoom - 1][PLAYER_INDEX] = 1;

    placeZombie(roomArray, gameArray);
    placeGrail(roomArray, gameArray);

    waitForMove(zombieRoom, currentRoom, numBullets, haveGrail, gameArray, roomArray);
}
// Pre - function is sent an int variable and the room array
// Post - function checks to see if the zombie is in the room specified by x
bool checkZombie(int x, int roomArray[][7])
{
    if (roomArray[x - 1][ZOMBIE_INDEX] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Pre - function is sent an int variable and the room array
// Post - function checks to see if the grail is in the room specified by x
bool checkGrail(int x, int roomArray[][7])
{
    if (roomArray[x - 1][GRAIL_INDEX] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Pre - function is sent an int variable and the room array
// Post - function checks to see if the zombie is in a room adjacent to the one specified by x
bool checkNearZombie(int x, int roomArray[][7])
{
    if (x == 2)
    {
        if (checkZombie(4, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 4)
    {
        if (checkZombie(2, roomArray) == 1 || checkZombie(3, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 3)
    {
        if (checkZombie(4, roomArray) == 1 || checkZombie(9, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 9)
    {
        if (checkZombie(5, roomArray) == 1 || checkZombie(3, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 5)
    {
        if (checkZombie(9, roomArray) == 1 || checkZombie(7, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 7)
    {
        if (checkZombie(5, roomArray) == 1 || checkZombie(8, roomArray) == 1 || checkZombie(6, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 6)
    {
        if (checkZombie(7, roomArray) == 1 || checkZombie(10, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 10)
    {
        if (checkZombie(6, roomArray) == 1 || checkZombie(11, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 11)
    {
        if (checkZombie(10, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 8)
    {
        if (checkZombie(7, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
// Pre - function is sent an int variable and the room array
// Post - function checks to see if the grail is in a room adjacent to the one specified by x
bool checkNearGrail(int x, int roomArray[][7])
{
    if (x == 2)
    {
        if (checkGrail(4, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    if (x == 4)
    {
        if (checkGrail(2, roomArray) == 1 || checkGrail(3, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 3)
    {
        if (checkGrail(4, roomArray) == 1 || checkGrail(9, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 9)
    {
        if (checkGrail(5, roomArray) == 1 || checkGrail(3, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 5)
    {
        if (checkGrail(9, roomArray) == 1 || checkGrail(7, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 7)
    {
        if (checkGrail(5, roomArray) == 1 || checkGrail(8, roomArray) == 1 || checkGrail(6, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 6)
    {
        if (checkGrail(7, roomArray) == 1 || checkGrail(10, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 10)
    {
        if (checkGrail(6, roomArray) == 1 || checkGrail(11, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 11)
    {
        if (checkGrail(10, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 8)
    {
        if (checkGrail(7, roomArray) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
// Pre - function is sent an int variable and the current room variable
// Post - function shows the user if they have won or not
bool winOrLose(int x, int& currentRoom)
{
    if (x == 0)
    {
        cout << "YOU HAVE EMERGED FROM THE TEMPLE WITH THE" << endl
             << "GRAIL!! YOU WIN!!" << endl << endl
             << "==========================================" << endl
             << endl;
        currentRoom = -1;
    }
    if (x == 1)
    {
        cout << "As you walk in the room, the zombie sees you, and" << endl
             << "devours you whole!" << endl << endl << "YOU LOST!" << endl
             << endl << "==========================================" << endl
             << endl;
        currentRoom = -1;
    }
}
//Pre - function is sent the current room variable
//Post - function shows the user all rooms connected to the current one
void showConnectedRooms(int& currentRoom)
{
    if (currentRoom == 2)
    {
        cout << "Room 1 and Room 4 are connected." << endl;
    }
    if (currentRoom == 4)
    {
        cout << "Room 2 and Room 3 are connected." << endl;
    }
    if (currentRoom == 3)
    {
        cout << "Room 4 and Room 9 are connected." << endl;
    }
    if (currentRoom == 9)
    {
        cout << "Room 3 and Room 5 are connected." << endl;
    }
    if (currentRoom == 5)
    {
        cout << "Room 9, Room 1, and Room 7 are connected." << endl;
    }
    if (currentRoom == 7)
    {
        cout << "Room 5, Room 8, and Room 6 are connected." << endl;
    }
    if (currentRoom == 8)
    {
        cout << "Room 7 is connected." << endl;
    }
    if (currentRoom == 6)
    {
        cout << "Room 7 and Room 10 are connected." << endl;
    }
    if (currentRoom == 10)
    {
        cout << "Room 6 and Room 11 are connected." << endl;
    }
    if (currentRoom == 11)
    {
        cout << "Room 10 is connected." << endl;
    }
    if (currentRoom == 1)
    {
        cout << "Room 2 and Room 5 are connected." << endl;
    }
}
//Pre - function is sent an int and the current room variable
//Post - function tests to see if a room specified by x is connected to the current room
bool isConnected(int x, int& currentRoom)
{
    if (x == 1)
    {
        if (currentRoom == 2 || currentRoom == 5 || currentRoom == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 2)
    {
        if (currentRoom == 1 || currentRoom == 4 || currentRoom == 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 4)
    {
        if (currentRoom == 2 || currentRoom == 3 || currentRoom == 4)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 3)
    {
        if (currentRoom == 4 || currentRoom == 9 || currentRoom == 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 9)
    {
        if (currentRoom == 3 || currentRoom == 5 || currentRoom == 9)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 5)
    {
        if (currentRoom == 9 || currentRoom == 1 || currentRoom == 5)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 7)
    {
        if (currentRoom == 5 || currentRoom == 8 || currentRoom == 6 || currentRoom == 7)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 8)
    {
        if (currentRoom == 7 || currentRoom == 8)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 6)
    {
        if (currentRoom == 7 || currentRoom == 10 || currentRoom == 6)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 10)
    {
        if (currentRoom == 6 || currentRoom == 11 || currentRoom == 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (x == 11)
    {
        if (currentRoom == 10 || currentRoom == 11)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
int moveRoom(int room, int& currentRoom, bool& haveGrail, int roomArray[][7], int gameArray[5])
{
    if (isConnected(room, currentRoom) == 1)
    {
        gameArray[CURRENT_ROOM_INDEX] = 0;
        gameArray[room - 1] = 1;
        currentRoom = room;
    }
    else
    {
        cout << "You can NOT move there ;(" << endl;
    }
    if (checkGrail(room, roomArray) == 1)
    {
        haveGrail = true;
    }
    if (haveGrail == 1)
    {
        roomArray[currentRoom][GRAIL_INDEX] = 0;
        roomArray[room - 1][GRAIL_INDEX] = 1;
    }
    if (haveGrail == 1 && room == 1)
    {
        winOrLose(0, currentRoom);
    }
}
void shootRoom(int room, int& zombieRoom, int& currentRoom, int& numBullets, int roomArray[][7])
{
    if (isConnected(room, currentRoom) == 1)
    {
        numBullets--;
        if (checkZombie(room, roomArray) == 1)
        {
            roomArray[room - 1][ZOMBIE_INDEX] = 0;
            zombieRoom = 0;
            cout << "You killed the zombie!" << endl;
        }
        else
        {
            cout << "You missed the zombie..." << endl;
        }
    }
}
void moveZombie(int& zombieRoom, int roomArray[][7], int gameArray[5])
{
    if (!zombieRoom == 0)
    {
        bool loop = true;
        while(loop)
        {
            int newZombieRoom = getRandomRoom(gameArray);
            if (isConnected(newZombieRoom, zombieRoom) == 1 && !newZombieRoom == 1)
            {
                zombieRoom = newZombieRoom;
                loop = false;
            }
        }
    }
}
bool validateSelection(std::string words)
{
    if (words[0] == 'Q' || words[0] == 'D' || words[0] == 'S' || words[0] == 'M')
    {
        return true;
    }
    else
    {
        return false;
    }
}
int doSelection(std::string words, int& zombieRoom, int& currentRoom, int& numBullets, bool& haveGrail, int gameArray[5], int roomArray[][7])
{
    if (words[0] == 'Q')
    {
        exit(1);
    }
    if (words[0] == 'D')
    {
        printMemory(gameArray, roomArray);
    }
    if (words[0] == 'S')
    {
        std::string room = words.substr(1,words.length() - 1);
        int roomNumber = atoi(room.c_str());

        shootRoom(roomNumber, zombieRoom, currentRoom, numBullets, roomArray);
        moveZombie(zombieRoom, roomArray, gameArray);
    }
    if (words[0] == 'M')
    {
        std::string room = words.substr(1,words.length() - 1);
        int roomNumber = atoi(room.c_str());

        moveRoom(roomNumber, currentRoom, haveGrail, roomArray, gameArray);
        moveZombie(zombieRoom, roomArray, gameArray);
    }
}
void waitForMove(int& zombieRoom, int& currentRoom, int& numBullets, bool& haveGrail, int gameArray[5], int roomArray[][7])
{
    std::string words;
    bool loop = true;
    while(loop)
    {
        cout << endl << " Type M#: to move to the indicated room #" << endl;
        cout << " Type S#: to shoot into the indicated room #" << endl;
        cout << " Type D: to print the game memory" << endl;
        cout << " Type Q: to quit the game" << endl;

        cin >> words;
        if (validateSelection(words) == 1)
        {
            doSelection(words, zombieRoom, currentRoom, numBullets, haveGrail, gameArray, roomArray);
        }
        else
        {
            cout << "Error. User entered wrong input." << endl << endl;
        }
    }
}
