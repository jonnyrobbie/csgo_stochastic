#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <iomanip>


using namespace std;

struct resultAbs
{
    int wins;
    int loses;
    int ties;
};

struct gameStat
{
    int wins;
    int loses;
};

float probability(float teamProb, float sideProb, float momProb)
{
    return ((teamProb*sideProb*momProb)/(teamProb*sideProb + teamProb*momProb + sideProb*momProb - teamProb - sideProb - momProb + 1));
}

float getRandom(float a, float b)
{
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}

gameStat game(float teamProb, float sideProb, float pistolProb, float momentum, int showGames, int tries)
{
    gameStat result;
    result.loses = 0;
    result.wins = 0;
    string teamA = "Team A: ";
    string teamB = "Team B: ";
    int i;
    float sideProbAll;
    float momentumProb = 0.5;
    float winProb;
    bool wonLast = true;
    for (i=1; i<=30&&(result.wins<16)&&(result.loses<16); i++)
    {
        if (i==1 || i==16)
        {
            sideProbAll = pistolProb;
            momentumProb = 0.5;
            if (showGames <= 100)
            {
                teamA = teamA + "|";
                teamB = teamB + "|";
            }
        } else
        {
            sideProbAll = sideProb;
            if (wonLast==true)
            {
                momentumProb = momentum;
            } else
            {
                momentumProb = 1-momentum;
            }
        }
        if (i<=15)
        {
            winProb = probability(teamProb, sideProbAll, momentumProb);
        } else
        {
            winProb = probability(teamProb, 1-sideProbAll, momentumProb);
        }
        if(getRandom(0, 1) <= winProb)
        {
            result.wins++;
            wonLast = true;
            if (showGames <= 100)
            {
                teamA = teamA + "X";
                teamB = teamB + "_";
            }
        }
        else
        {
            result.loses++;
            wonLast = false;
            if (showGames <= 100)
            {
                teamA = teamA + "_";
                teamB = teamB + "X";
            }
        }
    }
    if (showGames <= 50)
    {
        teamA = teamA + "|";
        teamB = teamB + "|";
        cout << endl << "Game " << showGames << ": " << result.wins << ":" << result.loses << endl << teamA << endl << teamB << endl;
    } else if (showGames == 51)
    {
        cout << endl << "Game 51-" << tries <<":" << endl << "[not shown to speed up the simulation]" << endl;
        cout << endl << "Simulation progress ('Ctrl + Pause/Break' to force stop):" << endl << "==================================================" << endl;
    }
    return result;
}

int main()
{
    float teamProb;
    float sideProb;
    float momentum;
    float pistolProb;
    int tries;
    int i;
    gameStat onegame;
    resultAbs simulation;
    srand (time(NULL));
    do
    {
        simulation.wins = 0;
        simulation.loses = 0;
        simulation.ties = 0;
        cout << "Enter the number of games to simulate (1..2147483647), 0 to quit: ";
        cin >> tries;
        if (tries==0)
            break;
        cout << "Enter the probability of Team A winning rounds with their skill (0..1): ";
        cin >> teamProb;
        cout << "Enter the probability of team winning rounds on the side Team A started given the map imbalance (0..1): ";
        cin >> sideProb;
        cout << "Enter the probability of Team A winning pistol rounds (0..1): ";
        cin >> pistolProb;
        cout << "Enter the probability of a team winning the next round given they won the previous round (momentum) (0..1): ";
        cin >> momentum;
        for (i=1; i<=tries;i++)
        {
            onegame = game(teamProb, sideProb, pistolProb, momentum, i, tries);
            if (onegame.wins < onegame.loses)
            {
                simulation.loses++;
            }
            else if (onegame.loses < onegame.wins)
            {
                simulation.wins++;
            }
            else
            {
                simulation.ties++;
            }
            if (i%(tries/50) == 0)
                cout << "*";
        }
        cout << endl << "\nTeam A wins:  " << setprecision(4) << (float)simulation.wins*100/(float)tries << "% (" << simulation.wins << ")\nTies:         " << (float)simulation.ties*100/(float)tries << "% (" << simulation.ties << ")\nTeam A loses: " << (float)simulation.loses*100/(float)tries << "% (" << simulation.loses << ")\n\n";
    } while (tries != 0);
    return 0;
}










