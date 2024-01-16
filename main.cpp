#include <iostream>
/*
consteval int get_value(){
    return 3;
}

int main(){
    constexpr int value = get_value();
    std::cout << "value : " << value << std::endl;
    return 0;
}
*/

int main()
{
    
    while (true)
    {
        std::cout << "1: Print help" << std::endl;
        std::cout << "2: Print exchange stats" << std::endl;
        std::cout << "3: Place an ask" << std::endl;
        std::cout << "4: Place a bid" << std::endl;
        std::cout << "5: Print wallet" << std::endl;
        std::cout << "6: Continue" << std::endl;

        int userOption;
        std::cout << "\033[1;32m"
                  << "Type in 1-6" 
                  << "\033[0m" << std::endl;
        std::cin >> userOption;
        std::cout << "\e[1;1H\e[2J" << std::endl;
        std::cout << "\033[1m"
                  << "You chose " << userOption 
                  << "\033[0m" << std::endl;
        
        switch (userOption) {
            //case 0:
            //    std::cout << "\033[0;31mwarning\033[0m" << std::endl;
            //    break;

            case 1: 
                std::cout << "Help your aim is to make money." << std::endl;
                break;

            case 2:
                std::cout << "Market looks good." << std::endl;
                break;

            case 3:
                std::cout << "Mark and offer - enter the amount" << std::endl;
                break;

            case 4:
                std::cout << "Make a bid - enter the amount" << std::endl;
                break;

            case 5:
                std::cout << "Your wallet is empty." << std::endl;
                break;

            case 6:
                std::cout << "Going to next time frame." << std::endl;
                break;

            default:
                std::cout << "\033[0;31m"
                          << "Invalid choise. Choose 1 - 6"
                          << "\033[0m" << std::endl;
                break;

        }
        std::cout << std::endl
                  << "-----------------------------------------------" << std::endl
                  << std::endl;
    }
}