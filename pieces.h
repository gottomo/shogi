// project/pieces.h
// header file for defining the shogi pieces
#ifndef PIECES_H
#define PIECES_H

#include<string>
#include<vector>
namespace piece {
    class piece
    {
        protected:
        std::string name_en;
        std::string name_jp;
        char name_char;
        bool is_player1; // whether the piece belongs to player 1 or player 2
        bool is_captured;
        bool is_promoted; // whether the piece has been promoted by entering enemy territory
        // friend class board::board;
        public:
        virtual ~piece(){}
        void piece_info();
        virtual std::vector<std::vector<int>> available_moves()=0;
        virtual std::vector<std::vector<int>> available_moves_promoted()=0;
        char get_name_char();
        bool get_is_player1();
        bool get_is_captured();
        bool get_is_promoted();
        std::string get_name();
        void set_is_promoted(bool status);
        void set_is_player1(bool status);
        void set_is_captured(bool status);

    };

    // Oushou (King / K)
    class king: public piece
    {
        public:
        king(){name_en="king"; name_jp="Oushou"; name_char='K';}
        king(bool is_p1);
        ~king(){}
        std::vector<std::vector<int>> available_moves();
        virtual std::vector<std::vector<int>> available_moves_promoted();
    };

    // Hisha (Rook / R)
    class rook: public piece
    {
        public:
        rook(){name_en="rook"; name_jp="Hisha"; name_char='R';}
        rook(bool is_p1);
        ~rook(){}
        std::vector<std::vector<int>> available_moves();
        std::vector<std::vector<int>> available_moves_promoted();
    };

    // Kakugyou (Bishop / B)
    class bishop: public piece
    {
        public:
        bishop(){name_en="bishop"; name_jp="Kakugyou"; name_char='B';}
        bishop(bool is_p1);
        ~bishop(){}
        std::vector<std::vector<int>> available_moves();
        std::vector<std::vector<int>> available_moves_promoted();
    };

    // Kinshou (Gold / G)
    class gold: public piece
    {
        public:
        gold(){name_en="gold"; name_jp="Kinshou"; name_char='G';}
        gold(bool is_p1);
        ~gold(){}
        std::vector<std::vector<int>> available_moves();
        virtual std::vector<std::vector<int>> available_moves_promoted();
    };

    // Ginshou (Silver / S)
    class silver: public piece
    {
        public:
        silver(){name_en="silver"; name_jp="Ginshou"; name_char='S';}
        silver(bool is_p1);
        ~silver(){}
        std::vector<std::vector<int>> available_moves();
        std::vector<std::vector<int>> available_moves_promoted();
    };

    // Keima (Knight / N)
    class knight: public piece
    {
        public:
        knight(){name_en="knight"; name_jp="Keima"; name_char='N';}
        knight(bool is_p1);
        ~knight(){}
        std::vector<std::vector<int>> available_moves();
        std::vector<std::vector<int>> available_moves_promoted();
    };

    // Kyousha (Lance / L)
    class lance: public piece
    {
        public:
        lance(){name_en="lance"; name_jp="Kyousha"; name_char='L';}
        lance(bool is_p1);
        ~lance(){}
        std::vector<std::vector<int>> available_moves();
        std::vector<std::vector<int>> available_moves_promoted();
    };

    // Fuhyou (Pawn / P)
    class pawn: public piece
    {
        public:
        pawn(){name_en="pawn"; name_jp="Fuhyou"; name_char='P';}
        pawn(bool is_p1);
        ~pawn(){}
        std::vector<std::vector<int>> available_moves();
        std::vector<std::vector<int>> available_moves_promoted();
    };

    // Help piece (x) to denote the available moves if board::medium_board::print_available_moves() function is called
    class placeholder: public piece
    {
        public:
        placeholder(){name_char='X';}
        ~placeholder(){}
        std::vector<std::vector<int>> available_moves();
        std::vector<std::vector<int>> available_moves_promoted();
    };
}
#endif