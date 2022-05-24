#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<string>
#include<iostream>
#include<limits>
#include<cmath>
#include"board.h"

// Functions
bool need_help(std::string u_input);
bool need_history_print(std::string u_input);
std::string u_input_handler(std::string message, board::medium_board myboard);

template <class c_type> c_type ask_user_input(std::string message)
{
    // This function checks for character input, and if input is invalid asks again
    c_type user_input;
    std::cout << message;
    std::cin >> user_input;
    while(std::cin.fail()) {
        std::cout << "Invalid input! Please try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin >> user_input;
    }
    // Put cin.ignore here in case the user enters more than one word (c_type=string) or character (c_type=char)
    // (Personal note: when inputting eg. "No please" it just reads "No" (if inputting string) and ignores the rest)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    return user_input;
}

// DEPRECATED
char ask_char_input(std::string message);
std::string ask_str_input(std::string message);

#endif