#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>

int generateRandom()
{
    int random_num = std::rand() % 3;
    std::cout << "Random number (0 or 1): " << random_num << std::endl; 

    return random_num;
}


int getInput()
{
    int choice;

    while(true)
    {

        std::cout << "Enter your choice (0 for Paper, 1 for Rock, 2 for Scissors): ";
        
        if(std::cin >> choice && choice >= 0 && choice <= 2)
        {
            return choice;
        }

        std::cout << "Invalid Input, Please try agian" << std::endl;


    }

}


// 0 = Paper 
// 1 = Rock
// 2 = Scissors
void compareChoices(int userChoice, int computerChoice)
{

    switch (userChoice) 
    {
        case 0:
            if(computerChoice == userChoice)
                std::cout << "Tie!" << std::endl;
            if(computerChoice == 1)
                std::cout << "You Win!" << std::endl;
            if(computerChoice == 2)
                std::cout << "Computer choose Scissors, You Lose!" << std::endl;
        
        case 1:
            if(computerChoice == 0)
                std::cout << "Computer choose Paper, You Lose!" << std::endl;
            if(computerChoice == userChoice)
                std::cout << "Computer also choose Rock, Tie!" << std::endl;
            if(computerChoice == 2)
                std::cout << "Computer Choose Scissors, You Win!" << std::endl;
        
        case 2:
            if(computerChoice == 0)
                std::cout << "Computer choose Paper, You Win!" << std::endl;
            if(computerChoice == 1)
                std::cout << "Computer choose Rock, You Lose!" << std::endl;
            if(computerChoice == userChoice)
                std::cout << "Computer choose Scissors, Tie!" << std::endl;
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Rock Paper Scissors Game!" << std::endl;
    
    int choice;
    choice = getInput();

    compareChoices(choice, generateRandom());

    

};


