// The main code that runs the game

// Ideas:
// Use move to move a captured piece into other side

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include"pieces.h"
#include"board.h"
#include"functions.h"
// #include"board.h"

int main(){
    bool continue_game{true};
    while (continue_game) {
        // Title page
        std::cout << "=====================================" << std::endl;
        std::cout << "                 SHOGI               " << std::endl;
        std::cout << "=====================================" << std::endl;

        std::cout << "# To get a help on what moves are available for a specified piece, type !h followed immediately with the position of the piece (<number><akphabet>)" << std::endl;
        std::cout << "# 'X' denotes the movable places" << std::endl;
        std::cout << "# Example input: !h5g" << std::endl;
        std::cout << "# To print the match history so far in the game type '!p'" << std::endl;

        // Create the board and initialize it
        board::medium_board myboard;
        myboard.set_initial_pos();

        // Start the match (player 1 starts)
        bool in_match{true};
        bool controlling_player{true}; // To track who's turn is it, true is player 1, false is player 2
        while (in_match) {
            // Print who's turn is it
            switch (controlling_player) {
                case true:
                std::cout << "### Player 1's turn ###" << std::endl;
                break;
                case false:
                std::cout << "### Player 2's turn ###" << std::endl;
            }
            // Print board
            myboard.print_board();
            // Ask player for input
            std::string piece_specifier;
            std::string order;
            std::string piece_specifier_message = "# Enter the position of the piece to be moved (<number><alphabet>) or \nEnter the captured piece you want to put on the board (<piece_type>): ";
            piece_specifier = u_input_handler(piece_specifier_message, myboard);
            std::string order_message = "# Enter the move order (<number><alphabet>): ";
            order = u_input_handler(order_message, myboard);
            // Move pieces
            while (!myboard.move_piece(piece_specifier, order, controlling_player)) {
                std::cout << "# The specified move is forbidden, check that:" << std::endl;
                std::cout << "  0. Who's turn is it" << std::endl;
                std::cout << "  1. You entered the piece specifier (<number><alphabet><piece_type>) and" << std::endl;
                std::cout << "     order (<number><alphabet>) correctly." << std::endl;
                std::cout << "  2. The move is allowed by the piece (type !h for help)." << std::endl;
                std::cout << "  3. The move is unobstructed by other pieces (except for Knights which can jump over pieces)." << std::endl;
                piece_specifier = u_input_handler("Enter the piece specifier <number><alphabet><piece_type>: ", myboard);
                order = u_input_handler("Enter the move order <number><alphabet>: ", myboard);
            }
            // Check if there is any winner
            if (myboard.get_match_finnished()) {
                switch(controlling_player) {
                    case true:
                    std::cout << "### Player 1 WINS! ###";
                    myboard.add_match_history("### Player 1 WINS! ###");
                    break;
                    case false:
                    std::cout << "### Player 2 WINS! ###";
                    myboard.add_match_history("### Player 2 WINS! ###");
                }
                in_match = false;
            }
            controlling_player = !controlling_player;
        }
        std::cout << "# Match history:" << std::endl; // Print the entire match history
        myboard.print_match_history();
        continue_game = false;
    }


    // ------------------------ Testing stuff ------------------------------
    // int p1{0};
    // piece::piece *king1 = new piece::king(p1);
    // king1->piece_info();

    // std::vector<std::vector<int>> king_move{king1->available_moves()};
    // std::vector<std::vector<int>>::iterator vector_it;
    // std::vector<std::vector<int>>::iterator vector_begin{king_move.begin()};
    // std::vector<std::vector<int>>::iterator vector_end{king_move.end()};
    // for(vector_it=vector_begin;vector_it<vector_end;++vector_it) {
    //     for(auto i{})
    //     std::cout << *vector_it << std::endl;
    // }
    // int i{king_move[0][0]};
    // int j{king_move[0][1]};
    // std::cout << i << " " << j << std::endl;
    // std::cout<<static_cast<int>('a')<<std::endl;

    // board::medium_board myboard;
    // myboard.set_initial_pos();
    // myboard.print_board();
    // myboard.move_piece("5iK", "5g");
    // myboard.print_board();

    // std::string u_input;
    // u_input = ask_str_input("Enter a string: ");
    // std::cout << u_input << std::endl;
    // u_input = ask_user_input<std::string>("Enter a string: ");
    // std::cout << u_input << std::endl;

    // std::cout << king1->available_moves().size() << std::endl;
    // std::vector<std::vector<int>> allowed_moves(king1->available_moves().size());
    // allowed_moves = king1->available_moves();
    // std::vector<std::vector<int>> allowed_moves2{king1->available_moves()};
    // std::cout << allowed_moves[0][0] << std::endl;
    // std::cout << allowed_moves2[0][0] << std::endl;
    // std::vector<int> player_move{1,1};
    // bool move_allowed{false};
    // for (auto move_iter = allowed_moves2.begin(); move_iter<allowed_moves2.end(); ++move_iter) {
    //     if (*move_iter==player_move) move_allowed = false;
    // }
    // std::cout << move_allowed << std::endl;
    // std::string piece_specifier{"5iK"};
    // curr_pos[0] = (int)(piece_specifier[0]) - 1;
    // std::cout << curr_pos[0] << std::endl;

    // std::map<std::vector<int>, std::shared_ptr<piece::piece>> grid;
    // std::shared_ptr<piece::piece> piece1(new piece::pawn{true});
    // std::shared_ptr<piece::piece> piece2(new piece::pawn{true});
    // grid[{0,0}].reset(new piece::pawn{true});
    // grid[{0,0}] = piece2;
    // std::cout << grid.count({0,0}) << std::endl;

    return 0;
}