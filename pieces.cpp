// Code that contains the pieces for the game
// Need to deal with pieces being "promoted". Create separate object and deal at main code? Or use if statement for each classes that can get promoted?
// What to include in class?
// Rule of movement. Position. Side. Status.
// Functions: move, get_captured, capture, show_position
#include"pieces.h"
#include<iostream>
#include<string>
#include<vector>
using namespace piece;

// Constructor definitions
king::king(bool is_p1){
    name_en = "King";
    name_jp = "Oushou";
    name_char = 'K';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}

rook::rook(bool is_p1){
    name_en = "Rook";
    name_jp = "Hisha";
    name_char = 'R';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}

bishop::bishop(bool is_p1){
    name_en = "Bishop";
    name_jp = "Kakugyou";
    name_char = 'B';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}

gold::gold(bool is_p1){
    name_en = "Gold";
    name_jp = "Kinshou";
    name_char = 'G';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}

silver::silver(bool is_p1){
    name_en = "Silver";
    name_jp = "Ginshou";
    name_char = 'S';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}

knight::knight(bool is_p1){
    name_en = "Knight";
    name_jp = "Keima";
    name_char = 'N';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}

lance::lance(bool is_p1){
    name_en = "Lance";
    name_jp = "Kyousha";
    name_char = 'L';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}

pawn::pawn(bool is_p1){
    name_en = "Pawn";
    name_jp = "Fuhyou";
    name_char = 'P';
    is_player1 = is_p1;
    is_captured = false;
    is_promoted = false;
}


// Function definitions
char piece::piece::get_name_char() {return name_char;}
bool piece::piece::get_is_player1() {return is_player1;}
bool piece::piece::get_is_captured() {return is_captured;}
bool piece::piece::get_is_promoted() {return is_promoted;}
void piece::piece::set_is_promoted(bool status) {is_promoted = status;}
void piece::piece::set_is_player1(bool status) {is_player1 = status;}
void piece::piece::set_is_captured(bool status) {is_captured = status;}
std::string piece::piece::get_name() {return name_en;}


void piece::piece::piece_info()
{
    std::cout << "Piece name: " << name_en << " (" << name_jp << " in Japanese)" << std::endl;
}

std::vector<std::vector<int>> king::available_moves()
{
    // std::cout << "Available moves:" << std::endl;
    std::vector<std::vector<int>> moveset(8);
    moveset[0] = {1,0};
    moveset[1] = {1,1};
    moveset[2] = {0,1};
    moveset[3] = {-1,1};
    moveset[4] = {-1,0};
    moveset[5] = {-1,-1};
    moveset[6] = {0,-1};
    moveset[7] = {1,-1};
    return moveset;
}

std::vector<std::vector<int>> king::available_moves_promoted()
{
    // std::cout << "Available moves:" << std::endl;
    std::vector<std::vector<int>> moveset(8);
    moveset[0] = {1,0};
    moveset[1] = {1,1};
    moveset[2] = {0,1};
    moveset[3] = {-1,1};
    moveset[4] = {-1,0};
    moveset[5] = {-1,-1};
    moveset[6] = {0,-1};
    moveset[7] = {1,-1};
    return moveset;
}

std::vector<std::vector<int>> rook::available_moves()
{
    int num_of_moves = 8 * 4;
    std::vector<std::vector<int>> moveset(num_of_moves);
    for (int i{}; i<4; i++) {
        for (int j{}; j<8; j++) {
            switch(i) {
                case 0:
                moveset[i*8+j] = {0,j};
                break;
                case 1:
                moveset[i*8+j] = {j,0};
                break;
                case 2:
                moveset[i*8+j] = {0,-j};
                break;
                case 3:
                moveset[i*8+j] = {-j,0};
                break;
            }
        }
    }
    return moveset;
}

std::vector<std::vector<int>> rook::available_moves_promoted()
{
    int num_of_moves = 8 * 4 + 4;
    std::vector<std::vector<int>> moveset(num_of_moves);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    for (int i{}; i<4; i++) {
        for (int j{}; j<8; j++) {
            switch(i) {
                case 0:
                moveset[i*8+j] = {0,j};
                break;
                case 1:
                moveset[i*8+j] = {j,0};
                break;
                case 2:
                moveset[i*8+j] = {0,-j};
                break;
                case 3:
                moveset[i*8+j] = {-j,0};
                break;
            }
        }
    }
    moveset[32] = {1,1 * flip};
    moveset[33] = {-1,1 * flip};
    moveset[34] = {1,-1 * flip};
    moveset[35] = {-1,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> bishop::available_moves()
{
    int num_of_moves = 8 * 4;
    std::vector<std::vector<int>> moveset(num_of_moves);
    for (int i{}; i<4; i++) {
        for (int j{}; j<8; j++) {
            switch(i) {
                case 0:
                moveset[i*8+j] = {j,j};
                break;
                case 1:
                moveset[i*8+j] = {j,-j};
                break;
                case 2:
                moveset[i*8+j] = {-j,j};
                break;
                case 3:
                moveset[i*8+j] = {-j,-j};
                break;
            }
        }
    }
    return moveset;
}

std::vector<std::vector<int>> bishop::available_moves_promoted()
{
    int num_of_moves = 8 * 4 + 4;
    std::vector<std::vector<int>> moveset(num_of_moves);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    for (int i{}; i<4; i++) {
        for (int j{}; j<8; j++) {
            switch(i) {
                case 0:
                moveset[i*8+j] = {j,j};
                break;
                case 1:
                moveset[i*8+j] = {j,-j};
                break;
                case 2:
                moveset[i*8+j] = {-j,j};
                break;
                case 3:
                moveset[i*8+j] = {-j,-j};
                break;
            }
        }
    }
    moveset[32] = {0,1 * flip};
    moveset[33] = {1,0};
    moveset[34] = {-1,0};
    moveset[35] = {0,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> gold::available_moves()
{
    std::vector<std::vector<int>> moveset(6);
    // Account for flip in movable direction depending on player 1 or player 2
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,1 * flip};
    moveset[1] = {0,1 * flip};
    moveset[2] = {-1,1 * flip};
    moveset[3] = {1,0};
    moveset[4] = {-1,0};
    moveset[5] = {0,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> gold::available_moves_promoted()
{
    std::vector<std::vector<int>> moveset(6);
    // Account for flip in movable direction depending on player 1 or player 2
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,1 * flip};
    moveset[1] = {0,1 * flip};
    moveset[2] = {-1,1 * flip};
    moveset[3] = {1,0};
    moveset[4] = {-1,0};
    moveset[5] = {0,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> silver::available_moves()
{
    std::vector<std::vector<int>> moveset(5);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,1 * flip};
    moveset[1] = {0,1 * flip};
    moveset[2] = {-1,1 * flip};
    moveset[3] = {1,-1 * flip};
    moveset[4] = {-1,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> silver::available_moves_promoted()
{
    std::vector<std::vector<int>> moveset(6);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,1 * flip};
    moveset[1] = {0,1 * flip};
    moveset[2] = {-1,1 * flip};
    moveset[3] = {1,0};
    moveset[4] = {-1,0};
    moveset[5] = {0,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> knight::available_moves()
{
    std::vector<std::vector<int>> moveset(2);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,2 * flip};
    moveset[1] = {-1,2 * flip};
    return moveset;
}

std::vector<std::vector<int>> knight::available_moves_promoted()
{
    std::vector<std::vector<int>> moveset(6);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,1 * flip};
    moveset[1] = {0,1 * flip};
    moveset[2] = {-1,1 * flip};
    moveset[3] = {1,0};
    moveset[4] = {-1,0};
    moveset[5] = {0,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> lance::available_moves()
{
    std::vector<std::vector<int>> moveset(8);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    for (int i{}; i<8; i++) {
        moveset[i] = {0,i * flip};
    }
    return moveset;
}

std::vector<std::vector<int>> lance::available_moves_promoted()
{
    std::vector<std::vector<int>> moveset(6);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,1 * flip};
    moveset[1] = {0,1 * flip};
    moveset[2] = {-1,1 * flip};
    moveset[3] = {1,0};
    moveset[4] = {-1,0};
    moveset[5] = {0,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> pawn::available_moves()
{
    std::vector<std::vector<int>> moveset(1);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {0,1 * flip};
    return moveset;
}

std::vector<std::vector<int>> pawn::available_moves_promoted()
{
    std::vector<std::vector<int>> moveset(6);
    bool is_p1{this->get_is_player1()};
    int flip{1};
    if (is_p1) flip=-1;
    moveset[0] = {1,1 * flip};
    moveset[1] = {0,1 * flip};
    moveset[2] = {-1,1 * flip};
    moveset[3] = {1,0};
    moveset[4] = {-1,0};
    moveset[5] = {0,-1 * flip};
    return moveset;
}

std::vector<std::vector<int>> placeholder::available_moves()
{
    std::vector<std::vector<int>> moveset{};
    return moveset;
}

std::vector<std::vector<int>> placeholder::available_moves_promoted()
{
    std::vector<std::vector<int>> moveset{};
    return moveset;
}