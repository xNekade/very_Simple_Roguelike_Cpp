#include <iostream>
#include <cstdlib>
#include <ctime>

#include "game.h"

/*
    --> Add HP to player and enemy
    --> Add max. 1(x or y) movement to enemy
    --> Add that the enemy tracks the player
    --> Add max. 2(x + y) movement to Player, like in chess.
    --> Add level screen/system. Like: Increase max. movement
    --> Add sword for the player with 1 range, like (x = 1, 0)
*/

constexpr std::int32_t MAX_X_AXIS = 10;
constexpr std::int32_t MAX_Y_AXIS = 10;
constexpr auto EMPTY_SPACE = " "; // Change later to empty aka. replace the dot with space-key
constexpr auto PLAYER = "X";
constexpr auto ENEMY = "O";
constexpr auto MAX_ENEMYS = (MAX_X_AXIS + MAX_Y_AXIS)/2;

std::string playground[MAX_Y_AXIS][MAX_X_AXIS];

void random_Enemy_Spawn(std::int32_t updated_Player_X, std::int32_t updated_Player_Y)
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (auto enemy_Counter = 0; enemy_Counter < MAX_ENEMYS; ++enemy_Counter)
    {
        std::int32_t random_X_Axis = std::rand() % MAX_X_AXIS;
        std::int32_t random_Y_Axis = std::rand() % MAX_Y_AXIS;

        // Adds a radius of 3 to the player on x and y, where the enemy can't spawn. And then spawns the enemy
        bool no_Enemy_Spawn_Radius_X = random_X_Axis > (updated_Player_X + 3) ||
                                    random_X_Axis < (updated_Player_X - 3);
        bool no_Enemy_Spawn_Radius_Y = random_Y_Axis > (updated_Player_Y + 3) ||
                                    random_Y_Axis < (updated_Player_Y - 3);

        if (no_Enemy_Spawn_Radius_X && no_Enemy_Spawn_Radius_Y)
        {
            playground[random_Y_Axis][random_X_Axis] = ENEMY;
        }
    }
}

void initialize_Playground()
{
    constexpr std::int32_t player_Start_Position = 0;

    for (auto y = 0; y < MAX_Y_AXIS; ++y)
    {
        for (auto x = 0; x < MAX_X_AXIS; ++x)
        {
            playground[y][x] = EMPTY_SPACE;
        }
    }

    playground[player_Start_Position][player_Start_Position] = PLAYER;
}

void display_Playground()
{
    for (auto y = 0; y < MAX_Y_AXIS; ++y)
    {
        for (auto x = 0; x < MAX_X_AXIS; ++x)
        {
            std::cout << playground[y][x];
        }
        std::cout << "\n";
    }
}

void player_Input()
{
    std::int32_t updated_Player_Position_X = 0;
    std::int32_t updated_Player_Position_Y = 0;

    while (true)
    {
        char input;
        std::cout << "game is still work in progress...\n"; // Delete
        std::cout << "Input with W/A/S/D to move: ";
        std::cin >> input;

        playground[updated_Player_Position_Y][updated_Player_Position_X] = EMPTY_SPACE;

        if (input == 'd' && updated_Player_Position_X < MAX_X_AXIS - 1)
        {
            ++updated_Player_Position_X;
        }
        else if (input == 'a' && updated_Player_Position_X > 0)
        {
            --updated_Player_Position_X;
        }
        else if (input == 'w' && updated_Player_Position_Y > 0)
        {
            --updated_Player_Position_Y;
        }
        else if (input == 's' && updated_Player_Position_Y < MAX_Y_AXIS - 1)
        {
            ++updated_Player_Position_Y;
        }
        random_Enemy_Spawn(updated_Player_Position_X, updated_Player_Position_Y); // fix that function, for that scroll up

        playground[updated_Player_Position_Y][updated_Player_Position_X] = PLAYER;

        system("clear");
        display_Playground();
    }
}

void process_Game()
{
    initialize_Playground();
    display_Playground();
    player_Input();
}

void game()
{
    process_Game();
}
