// Code that specifies the board (unnecessary?)
// An array that contains the position of all pieces?
// Or the info of positions of pieces should be contained in each piece objects?
// Or make this code display the board and the positions of pieces?

#include"board.h"
#include"pieces.h"
#include"functions.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>

using namespace board;

// Functions
void medium_board::set_initial_pos()
{
    // Player 1
    grid[{4,8}].reset(new piece::king{true});
    for (int i{}; i<size; i++) {
        grid[{i,6}].reset(new piece::pawn{true});
    }
    grid[{0,8}].reset(new piece::lance{true});
    grid[{8,8}].reset(new piece::lance{true});
    grid[{1,8}].reset(new piece::knight{true});
    grid[{7,8}].reset(new piece::knight{true});
    grid[{2,8}].reset(new piece::silver{true});
    grid[{6,8}].reset(new piece::silver{true});
    grid[{3,8}].reset(new piece::gold{true});
    grid[{5,8}].reset(new piece::gold{true});
    grid[{1,7}].reset(new piece::rook{true});
    grid[{7,7}].reset(new piece::rook{true});
    // Player 2
    grid[{4,0}].reset(new piece::king{false});
    for (int i{}; i<size; i++) {
        grid[{i,2}].reset(new piece::pawn{false});
    }
    grid[{0,0}].reset(new piece::lance{false});
    grid[{8,0}].reset(new piece::lance{false});
    grid[{1,0}].reset(new piece::knight{false});
    grid[{7,0}].reset(new piece::knight{false});
    grid[{2,0}].reset(new piece::silver{false});
    grid[{6,0}].reset(new piece::silver{false});
    grid[{3,0}].reset(new piece::gold{false});
    grid[{5,0}].reset(new piece::gold{false});
    grid[{7,1}].reset(new piece::rook{false});
    grid[{1,1}].reset(new piece::rook{false});
}

bool board::medium_board::get_match_finnished() {return match_finnished;}
void board::medium_board::add_match_history(std::string message) {match_history.push_back(message);}

bool board::board::move_piece(std::string piece_specifier, std::string order, bool controlling_player)
{
    // Piece specifier is in the format of "<current_row><current_column><piece_name>" eg. "6eK" for specifying King in 6-th row e-th column
    // If only the "<piece_name>" is specified without the current position, the program assumes that you want to put the piece captured from the opponent to the board
    // Order consists of "<row><column>" which specifies the position to be moved to.  The program automatically handles captureing of opponent's pieces, promotion, and demotion.
    // (Actual notation method doesn't look like this, there is no current position specificier, the move/capture order should be specified and the ambiguity is dealt differently)
    std::vector<int> curr_pos(2); std::vector<int> order_pos(2); char piece_type;

    curr_pos[0] = static_cast<int>(piece_specifier[0]) - 49;
    curr_pos[1] = static_cast<int>(piece_specifier[1]) - 97; // Converting the alphabetical character to ascii number eg. a=97, b=98 ... etc. then substracting accordingly

    order_pos[0] = static_cast<int>(order[0]) - 49;
    order_pos[1] = static_cast<int>(order[1]) - 97;
    // Check for valid range of position
    for (int i{}; i<2; i++) {
        if (order_pos[0] < 0 || order_pos[0] > 8) return false;
    }

    // Check if the order is to place the captured piece back onto the board and execute it if so
    

    if (piece_specifier.length()>1) {
        piece_type = piece_specifier[2];
    } else {
        piece_type = piece_specifier[0];
        switch (controlling_player) {
            case true:
            for (auto cap_piece_itr = captured.begin(); cap_piece_itr<captured.end(); ++cap_piece_itr) {
                if ((**cap_piece_itr).get_is_player1()) {
                    if ((**cap_piece_itr).get_name_char()==piece_type) {
                        if (order_pos[0]>=0 && order_pos[0]<9 && order_pos[1]>=0 && order_pos[1]<9) { // check border
                            if (!grid.count(order_pos)) {    // Check if there is any piece on the specified position
                                grid[order_pos] = *cap_piece_itr;
                                captured.erase(cap_piece_itr);
                                std::ostringstream out_stream;
                                out_stream << "Player 1's " << (**cap_piece_itr).get_name() << " placed to " << order << ".";
                                std::string place_message{out_stream.str()};
                                std::cout << place_message << std::endl;
                                match_history.push_back(place_message);
                                out_stream.str("");
                                return true;
                            }
                        } 
                    } else return false;
                } else return false;
            }
            break;
            case false:
            for (auto cap_piece_itr = captured.begin(); cap_piece_itr<captured.end(); ++cap_piece_itr) {
                if (!(**cap_piece_itr).get_is_player1()) {
                    if ((**cap_piece_itr).get_name_char()==piece_type) {
                        if (order_pos[0]>=0 && order_pos[0]<9 && order_pos[1]>=0 && order_pos[1]<9) { // check border
                            if (!grid.count(order_pos)) {    // Check if there is any piece on the specified position
                                grid[order_pos] = *cap_piece_itr;
                                captured.erase(cap_piece_itr);
                                std::ostringstream out_stream;
                                out_stream << "Player 2's " << (**cap_piece_itr).get_name() << " placed to " << order << ".";
                                std::string place_message{out_stream.str()};
                                std::cout << place_message << std::endl;
                                match_history.push_back(place_message);
                                out_stream.str("");
                                return true;
                            }
                        } 
                    } else return false;
                } else return false;
            }
        }
    }

    // Check for valid range of position
    for (int i{}; i<2; i++) {
        if (curr_pos[0] < 0 || curr_pos[0] > 8) return false;
    }

    // Check if there is any piece in the specified location (if there is none .count returns 0, if there is one then returns 1)
    if (!grid.count(curr_pos)) {return false;}

    // Check if the piece specified is the controlling player's piece, if not exit the function and return false
    std::shared_ptr<piece::piece> player_piece{grid[curr_pos]};
    if (!controlling_player == player_piece->get_is_player1()) {return false;}

    // Check if the movement is allowed by the piece, 
    std::vector<int> player_move(2); // The relative player move wrt. current position
    player_move[0] = order_pos[0] - curr_pos[0]; player_move[1] = order_pos[1] - curr_pos[1];
    
    bool move_allowed = false;
    // Deal with promoted and unpromoted pieces separately
    if (!player_piece->get_is_promoted()) {
            std::vector<std::vector<int>> allowed_moves{player_piece->available_moves()};
            for (auto move_iter = allowed_moves.begin(); move_iter<allowed_moves.end(); ++move_iter) {
                if (*move_iter==player_move) move_allowed = true;
            }
    } else {
        std::vector<std::vector<int>> allowed_moves_promoted{player_piece->available_moves_promoted()};
        for (auto move_iter = allowed_moves_promoted.begin(); move_iter<allowed_moves_promoted.end(); ++move_iter) {
            if (*move_iter==player_move) move_allowed = true;
        }
    }
    
    // Check if any movement have been made at all
    if (player_move[0]==0 && player_move[1]==0) move_allowed = false;

    // Check if there is no obstruction for movement eg. other pieces, board border etc. (exeption to Knights which can jamp over other pieces)
    if (order_pos[0]<0 && order_pos[0]>8 && order_pos[1]<0 && order_pos[1]>8) move_allowed = false; // check border
    if (player_move[0]==0) { // check obstructing pieces along orthogonal directions
        if (player_move[1]>0) {
            for (int i{1}; i<player_move[1]; i++) {
                if (grid.count({curr_pos[0],curr_pos[1]+i})) move_allowed = false;
            }
        } else if (player_move[1]<0) {
            for (int i{-1}; i>player_move[1]; i--) {
                if (grid.count({curr_pos[0],curr_pos[1]+i})) move_allowed = false;
            }
        }
    } else if (player_move[1]==0) {
        if (player_move[0]>0) {
            for (int i{1}; i<player_move[0]; i++) {
                if (grid.count({curr_pos[0]+i,curr_pos[1]})) move_allowed = false;
            }
        } else if (player_move[0]<0) {
            for (int i{-1}; i>player_move[0]; i--) {
                if (grid.count({curr_pos[0]+i,curr_pos[1]})) move_allowed = false;
            }
        }
    } else if (player_move[0]==player_move[1]) { // check obstructing pieces along diagonal directions
        if (player_move[0]>0) {
            for (int i{1}; i<player_move[0]; i++) {
                if (grid.count({curr_pos[0]+i,curr_pos[1]+i})) move_allowed = false;
            }
        } else if (player_move[0]<0) {
            for (int i{-1}; i>player_move[0]; i--) {
                if (grid.count({curr_pos[0]+i,curr_pos[1]+i})) move_allowed = false;
            }
        }
    }


    // Check if there is oppponent's piece on the specified position, and capture it if there is one (and add the event to match_history)
    if (grid.count(order_pos)) {
        std::shared_ptr<piece::piece> clashing_piece{grid[order_pos]};
        switch(player_piece->get_is_player1()) {
            case true:
                if (clashing_piece->get_is_player1()) {
                    move_allowed = false; // There is friendly piece obstructing movement
                } else {
                    clashing_piece->set_is_captured(true); // Capture the opponents piece, change its allegiance, and demote in case it was promoted
                    clashing_piece->set_is_player1(true);
                    clashing_piece->set_is_promoted(false);
                    if (clashing_piece->get_name_char()=='K') match_finnished=true; // Check if captured piece is king and finish the match if so
                    grid.erase(order_pos);              // Delete the piece from the main board and put into the captured piece holder
                    captured.push_back(clashing_piece);
                    std::ostringstream out_stream;
                    out_stream << "Player 2's " << clashing_piece->get_name_char() << " captured while";
                    std::string capture_message{out_stream.str()};
                    std::cout << capture_message << std::endl;
                    match_history.push_back(capture_message);
                    out_stream.str("");
                }
                break;
            case false:
                if (!clashing_piece->get_is_player1()) {
                    move_allowed = false; // There is friendly piece obstructing movement
                } else {
                    clashing_piece->set_is_captured(true); // Capture the opponents piece, change its allegiance, and demote in case it was promoted
                    clashing_piece->set_is_player1(false);
                    clashing_piece->set_is_promoted(false);
                    grid.erase(order_pos);              // Delete the piece from the main board and put into the captured piece holder
                    captured.push_back(clashing_piece);
                    std::ostringstream out_stream;
                    out_stream << "Player 2's " << clashing_piece->get_name_char() << " captured while";
                    std::string capture_message{out_stream.str()};
                    std::cout << capture_message << std::endl;
                    match_history.push_back(capture_message);
                    out_stream.str("");
                }
                break;
        }
    }

    if (!move_allowed) {return false;}

    // Make the movement
    grid[order_pos] = player_piece; grid.erase(curr_pos);
    std::ostringstream out_stream;
    switch(player_piece->get_is_player1()) {
        case true:
        out_stream << "Player 1's " << player_piece->get_name() << " at " << piece_specifier << " moved to " << order << ".";
        break;
        case false:
        out_stream << "Player 2's " << player_piece->get_name() << " at " << piece_specifier << " moved to " << order << ".";
    }
    std::string move_message{out_stream.str()};
    std::cout << move_message << std::endl;
    match_history.push_back(move_message);
    out_stream.str("");

    // Check if promotion is available if unpromoted, ask user whether to promote
    if (!player_piece->get_is_promoted()) {
        if (player_piece->get_is_player1()) {
            if (order_pos[1]<3) {
                char u_promote;
                u_promote = ask_user_input<char>("Promotion available, would you like to promote your piece? (y/n)");
                if(u_promote=='y' || u_promote=='Y') player_piece->set_is_promoted(true); 
            }
        } else if (!player_piece->get_is_player1()) {
            if (order_pos[1]>5) {
                char u_promote;
                u_promote = ask_user_input<char>("Promotion available, would you like to promote your piece? (y/n)");
                if (u_promote=='y' || u_promote=='Y') player_piece->set_is_promoted(true); 
            }
        }
    }

    return true;

}

void medium_board::print_board()
{
    // Print the captured pieces of player 2
    std::cout << "Captured: ";
    for (auto piece_iter=captured.begin(); piece_iter<captured.end(); ++piece_iter) {
        if (!(*piece_iter)->get_is_player1()) std::cout << (*piece_iter)->get_name_char() << ", ";
    }
    std::cout << std::endl;

    // Print the board using the "grid" map container
    std::cout << "              Player 2               " << std::endl;
    std::cout << "  9   8   7   6   5   4   3   2   1" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    for(int i{};i<size;i++) {
        std::cout << "|";
        for(int j{static_cast<int>(size)-1};j>=0;j--) { // The numbering must start from top right
            if (grid.count({j,i})) {
                std::shared_ptr<piece::piece> display_piece{grid[{j,i}]};
                char promo_status;
                if(display_piece->get_is_promoted()) {
                    promo_status = '+';
                } else {
                    promo_status = ' ';
                }
                if(display_piece->get_is_player1()) {
                    std::cout << promo_status << display_piece->get_name_char() << "1|";
                } else {
                    std::cout << promo_status << display_piece->get_name_char() << "2|";
                }
            } else {
                std::cout << "   |";
            }
        }
        std::cout << static_cast<char>(i+97) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    std::cout << "              Player 1               " << std::endl;

    // Print the captured pieces of player 1
    std::cout << "Captured: ";
    for (auto piece_iter=captured.begin(); piece_iter<captured.end(); ++piece_iter) {
        if ((*piece_iter)->get_is_player1()) std::cout << (*piece_iter)->get_name_char() << ", ";
    }
    std::cout << std::endl;

}

// Print available movements
void medium_board::print_available_moves(std::string piece_specifier)
{
    // Create a copy of grid so that we won't tamper with the original one
    std::map<std::vector<int>, std::shared_ptr<piece::piece>> grid_copy{grid};
    // Show on the board where the piece can move with "x"
    std::vector<int> curr_pos(2);

    curr_pos[0] = static_cast<int>(piece_specifier[2]) - 49;
    curr_pos[1] = static_cast<int>(piece_specifier[3]) - 97; // Converting the alphabetical character to ascii number eg. a=97, b=98 ... etc. then substracting accordingly
    
    // Check for valid range of position
    for (int i{}; i<2; i++) {
        if (curr_pos[0] < 0 || curr_pos[0] > 8 || curr_pos[0] < 0 || curr_pos[0] > 8) return;
    }
    
    // Check if there is any piece in the specified location (if there is none .count returns 0, if there is one then returns 1)
    if (!grid.count(curr_pos)) {return;}

    std::shared_ptr<piece::piece> player_piece{grid_copy[curr_pos]};
    std::vector<std::vector<int>> allowed_moves{player_piece->available_moves()};
    bool move_allowed{true};
    for (auto move_iter = allowed_moves.begin(); move_iter<allowed_moves.end(); ++move_iter) {
        // Check if there is no obstruction for movement eg. other pieces, board border etc. (exeption to Knights which can jamp over other pieces)
        move_allowed = true;
        if ((*move_iter)[0]==0) { // check obstructing pieces along orthogonal directions
            if ((*move_iter)[1]>0) {
                for (int i{1}; i<(*move_iter)[1]; i++) {
                    if (grid.count({curr_pos[0],curr_pos[1]+i})) move_allowed = false;
                }
            } else if ((*move_iter)[1]<0) {
                for (int i{-1}; i>(*move_iter)[1]; i--) {
                    if (grid.count({curr_pos[0],curr_pos[1]+i})) move_allowed = false;
                }
            }
        } else if ((*move_iter)[1]==0) {
            if ((*move_iter)[0]>0) {
                for (int i{1}; i<(*move_iter)[0]; i++) {
                    if (grid.count({curr_pos[0]+i,curr_pos[1]})) move_allowed = false;
                }
            } else if ((*move_iter)[0]<0) {
                for (int i{-1}; i>(*move_iter)[0]; i--) {
                    if (grid.count({curr_pos[0]+i,curr_pos[1]})) move_allowed = false;
                }
            }
        } else if ((*move_iter)[0]==(*move_iter)[1]) { // check obstructing pieces along diagonal directions
            if ((*move_iter)[0]>0) {
                for (int i{1}; i<(*move_iter)[0]; i++) {
                    if (grid.count({curr_pos[0]+i,curr_pos[1]+i})) move_allowed = false;
                }
            } else if ((*move_iter)[0]<0) {
                for (int i{-1}; i>(*move_iter)[0]; i--) {
                    if (grid.count({curr_pos[0]+i,curr_pos[1]+i})) move_allowed = false;
                }
            }
        }


        // Check if there is oppponent's piece on the specified position
        std::vector<int> order_pos(2);
        order_pos[0] = curr_pos[0] + (*move_iter)[0]; 
        order_pos[1] = curr_pos[1] + (*move_iter)[1]; 
        if (grid.count(order_pos)) {
            std::shared_ptr<piece::piece> clashing_piece{grid_copy[order_pos]};
            switch(player_piece->get_is_player1()) {
                case true:
                    if (clashing_piece->get_is_player1()) {
                        move_allowed = false; // There is friendly piece obstructing movement
                    }
                    break;
                case false:
                    if (!clashing_piece->get_is_player1()) {
                        move_allowed = false; // There is friendly piece obstructing movement
                    }
                    break;
            }
        }
        if (move_allowed) grid_copy[order_pos].reset(new piece::placeholder());
    }
    // Print the board using the "grid" map container
    std::cout << "              Player 2               " << std::endl;
    std::cout << "  9   8   7   6   5   4   3   2   1" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    for(int i{};i<size;i++) {
        std::cout << "|";
        for(int j{static_cast<int>(size)-1};j>=0;j--) { // The numbering must start from top right
            if (grid_copy.count({j,i})) {
                std::shared_ptr<piece::piece> display_piece{grid_copy[{j,i}]};
                char promo_status;
                if(display_piece->get_is_promoted()) {
                    promo_status = '+';
                } else {
                    promo_status = ' ';
                }
                if (display_piece->get_is_player1()) {
                    std::cout << promo_status << display_piece->get_name_char() << "1|";
                } else if (!display_piece->get_is_player1() && display_piece->get_name_char()!='X') {
                    std::cout << promo_status << display_piece->get_name_char() << "2|";
                } else if (display_piece->get_is_player1()!=player_piece->get_is_player1()) {
                    std::cout << promo_status << display_piece->get_name_char() << " |";
                }
            } else {
                std::cout << "   |";
            }
        }
        std::cout << static_cast<char>(i+97) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    std::cout << "              Player 1               " << std::endl;

    // Remove the placeholder pieces that showed the available moves
    for (auto move_iter = allowed_moves.begin(); move_iter<allowed_moves.end(); ++move_iter) grid_copy.erase((*move_iter));

}


void board::board::print_match_history()
{
    for (auto line_itr = match_history.begin(); line_itr<match_history.end(); ++line_itr) {
        std::cout << *line_itr << std::endl;
    }
    // std::cout << "Match history placeholder" << std::endl;
}