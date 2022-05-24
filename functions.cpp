#include"functions.h"
#include<string>
#include<iostream>
#include<limits>
#include<cmath>


// Functions definitions
bool need_help(std::string u_input) 
{
    if (u_input[0] == '!' && u_input[1] == 'h') {
        return true;
    } else {
        return false;
    }
}

bool need_history_print(std::string u_input) 
{
    if (u_input[0] == '!' && u_input[1] == 'p') {
        return true;
    } else {
        return false;
    }
}

std::string u_input_handler(std::string message, board::medium_board myboard)
{
    bool proceed;
    // Ask user input checks for any commands
    proceed = false;
    std::string u_input;
    while (!proceed) {
        u_input = ask_user_input<std::string>(message);
        // Checks if '!h' has been inputted
        if (need_help(u_input)) {
            myboard.print_available_moves(u_input);
        } else if (need_history_print(u_input)) {
            myboard.print_match_history();
        } else proceed = true;
    }
    return u_input;
}


// DEPRECATED
// char ask_char_input(std::string message)
// {
//     // This function checks for character input, and if input is invalid asks again
//     char user_input;
//     std::cout << message;
//     std::cin >> user_input;
//     while(std::cin.fail()) {
//         std::cout << "Invalid input! Please try again: ";
//         std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//         std::cin >> user_input;
//     }
//     // Put cin.ignore here in case the user enters more than one charachter
//     // (Personal note: when inputting eg. "No please" it just reads "N" and ignores the rest)
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     return user_input;
// }

// std::string ask_str_input(std::string message)
// {
//     // This function checks for character input, and if input is invalid asks again
//     std::string user_input;
//     std::cout << message;
//     std::cin >> user_input;
//     while(std::cin.fail()) {
//         std::cout << "Invalid input! Please try again: ";
//         std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//         std::cin >> user_input;
//     }
//     // Put cin.ignore here in case the user enters more than one word
//     // (Personal note: when inputting eg. "No please" it just reads "No" and ignores the rest)
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     return user_input;
// }