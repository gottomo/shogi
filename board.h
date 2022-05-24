#ifndef BOARD_H
#define BOARD_H

#include"pieces.h"
#include<string>
#include<vector>
#include<map>
#include<memory>

namespace board {
    class board {
        protected:
        std::size_t size;
        std::map<std::vector<int>, std::shared_ptr<piece::piece>> grid;
        std::vector<std::shared_ptr<piece::piece>> captured;
        bool match_finnished;
        std::vector<std::string> match_history;
        public:
        virtual ~board(){}
        virtual void set_initial_pos()=0;
        virtual void print_board()=0;
        virtual void print_available_moves(std::string piece_specifier)=0;
        bool move_piece(std::string piece_specifier, std::string order, bool controlling_player);
        void print_match_history();
    };
    
    class medium_board: public board{
        public:
        medium_board() {size=9; match_finnished=false; match_history.push_back("### Match Begins ###");}
        ~medium_board(){}
        void set_initial_pos();
        void print_board();
        void print_available_moves(std::string piece_specifier);
        bool get_match_finnished();
        void add_match_history(std::string message);
    };
}


#endif