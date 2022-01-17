// Author: Guerrini Alberto

#ifndef BOARD_CPP
#define BOARD_CPP

#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include "../include/Pawn.hpp"
#include "../include/Rook.hpp"
#include "../include/Knight.hpp"
#include "../include/Bishop.hpp"
#include "../include/Queen.hpp"
#include "../include/King.hpp"
#include "../include/IllegalMoveException.hpp"

Board::Board(const bool& player_color) {

    // reserve space in the vectors to store all pieces
    pieces_.resize(4*Board::DIM);
    dashboard_.resize(Board::DIM);
    // for every row in dashboard reserve 8 cells and initialize them to nullptr

    std::cout<<"TEST 1\n";

    for (short i = 0; i < DIM; i++) {
        std::vector<Piece*> vP;
        dashboard_.push_back(vP);

        dashboard_.at(i).resize(DIM);
        
        std::fill(dashboard_.at(i).begin(), dashboard_.at(i).end(), nullptr);
    }
    // sets the index of dashboard rows in wich there are pawns
    int pawns_row_w = (player_color == Piece::WHITE)? 1 : 6;
    int pawns_row_b = (player_color == Piece::BLACK)? 1 : 6;

    std::cout<<" w: "<<pawns_row_w<<" b: "<<pawns_row_b<<"\n";

    std::cout<<"TEST 2\n";

    // add 8 pawns for each color in the correct position of the array
    // and add pawns to the dashboard
    int idx = 0;
    for(idx = 0; idx < DIM; idx++) {
        // white pawns
        pieces_.at(idx) = new Pawn(Piece::WHITE, this, std::to_string(pawns_row_w)+char('A'+idx));
        dashboard_.at(pawns_row_w).at(idx) = pieces_.at(idx);
        // black pawns
        pieces_.at(COLOR_OFFSET + idx) = new Pawn(Piece::BLACK, this, std::to_string(pawns_row_b)+char('A'+idx));
        dashboard_.at(pawns_row_b).at(idx) = pieces_.at(COLOR_OFFSET + idx);
    }

    std::cout<<"TEST 3\n";

    // add non pawn pieces in the pieces_ vector
    pieces_.at(idx)                 = new Rook(Piece::WHITE, this, 'A'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new Rook(Piece::BLACK, this, 'A'+std::to_string(pawns_row_b));
    idx++;
    pieces_.at(idx)                 = new Knight(Piece::WHITE, this, 'B'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new Knight(Piece::BLACK, this, 'B'+std::to_string(pawns_row_b));
    idx++;
    pieces_.at(idx)                 = new Bishop(Piece::WHITE, this, 'E'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new Bishop(Piece::BLACK, this, 'E'+std::to_string(pawns_row_b));
    idx++;
    pieces_.at(idx)                 = new Queen(Piece::WHITE, this, 'C'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new Queen(Piece::BLACK, this, 'C'+std::to_string(pawns_row_b));
    idx++;
    pieces_.at(idx)                 = new King(Piece::WHITE, this, 'D'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new King(Piece::BLACK, this, 'D'+std::to_string(pawns_row_b));
    idx++;
    pieces_.at(idx)                 = new Bishop(Piece::WHITE, this, 'F'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new Bishop(Piece::BLACK, this, 'F'+std::to_string(pawns_row_b));
    idx++;
    pieces_.at(idx)                 = new Knight(Piece::WHITE, this, 'G'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new Knight(Piece::BLACK, this, 'G'+std::to_string(pawns_row_b));
    idx++;
    pieces_.at(idx)                 = new Rook(Piece::WHITE, this, 'H'+std::to_string(pawns_row_w));
    pieces_.at(idx + COLOR_OFFSET)  = new Rook(Piece::BLACK, this, 'H'+std::to_string(pawns_row_b));
    
    // set the index of dashboard rows in wich there are non pawns pieces
    int pieces_row_w = player_color == Piece::WHITE? 0 : 7;
    int pieces_row_b = player_color == Piece::BLACK? 0 : 7;

    std::cout<<"TEST 4\n";

    // copy references to white pieces to the dashboard
    std::copy(pieces_.begin() + Board::DIM, 
              pieces_.begin() + Board::COLOR_OFFSET, 
              dashboard_.at(pieces_row_w).begin());

    std::cout<<"TEST 5\n";
            
    // copy references to black pieces to the dashboard
    std::copy(pieces_.begin() + Board::COLOR_OFFSET + Board::DIM, 
              pieces_.begin() + 2*Board::COLOR_OFFSET, 
              dashboard_.at(pieces_row_b).begin());
    std::cout << "constr\n";
}

Board::~Board() {
    // set to nullptr every reference to pieces in the dashboard vectors
    for(short i = 0; i < DIM; i++)
        std::fill(dashboard_.at(i).begin(), dashboard_.at(i).end(), nullptr);
    // delete all pieces from free space
    for(Piece* p : pieces_)
        delete p;
}

bool Board::move(const std::string& from, const std::string& to, const bool player_ID) {
    // check if the "from" coordinates are referred to an empty cell
    if((*this)[from] == nullptr)
        throw IllegalMoveException("No piece in the cell " + from);
     // check if the piece in "from" coordinates has the opponent color
    if((*this)[from]->get_ID() != player_ID)
        throw IllegalMoveException("Player can't move an opponent piece");
    // check if the "to" coordinates are valid (operator[] can throw exceptions)
    (*this)[to];
    // check if the piece in coordinates from can move to the cell "to"
    if((*this)[from]->can_move(to)) {
        // manage the capture of the piece or castling, if there is one, in cell "to"
        if((*this)[to] != nullptr) {
            // if the piece in to cell has the player color it must be a castling move
            if((*this)[to]->get_ID() == player_ID)
                this->castling(from, to, player_ID);
            // if it can't be a castling it have to be a capture
            else
                this->capture(from, to);
        } else {
        // if the cell "to" is empty simply move the piece
        // make the pointer in the "to" cell pointing to the moved piece
        (*this)[to] = (*this)[from];
        (*this)[to]->set_pos(to);
        // set to nullptr the pointer in the cell from;
        (*this)[from] = nullptr;
        
        // en passant flag setting for pawns
        Pawn* p = dynamic_cast<Pawn*>((*this)[to]);
        // if it is a pawn
        if( p != nullptr)
            // and en_passant is set to true
            if(p->get_en_passant())
                p->set_en_passant(false);
            // if en passant is false and pawn has just done the first move
            else if (std::abs(from.at(1)-to.at(1)) == 2)
                p-> set_en_passant(true);

        // castling flag setting for rook and king
        Rook* r = dynamic_cast<Rook*>((*this)[to]);
        if(r != nullptr)
            r->set_castling(false);
        King* k = dynamic_cast<King*>((*this)[to]);
        if(k != nullptr)
            k->set_castling(false);
        return true;
        }
    }
    else
        throw IllegalMoveException("Can't made the move" + from + " " + to);      
    return false;   
}

bool Board::capture(const std::string& from, const std::string& to) {
    // if the pieces have the same color, it can't capture
    // if((*this)[from]->get_ID() == (*this)[to]->get_ID())
    //     return false;

    // find and replace with nullptr the captured piece into the pieces_ vector
    std::replace(pieces_.begin(), pieces_.end(), (*this)[to], (Piece*)nullptr);
    // delete the piece from the free space
    delete (*this)[to];
    return true;   
}

bool Board::castling(const std::string& from, const std::string& to, const bool player_ID) {
    // set the row in wich the castling is made
    std::string coord ("XX");
    coord.at(1) = from.at(1);
    // check if it is a long castling
    if(std::abs(from.at(0) - to.at(0) == 4)) {
        // make the cell Cx pointing to the king
        coord.at(0) = 'C';
        (*this)[coord] = &this->get_piece_at(12, player_ID);
        // make the cell Dx pointing to the first rook
        coord.at(0) = 'D';
        (*this)[coord] = &this->get_piece_at(8, player_ID);
        // set to null pointers in cells Ax and Ex
        coord.at(0) = 'A';
        (*this)[coord] = nullptr;
        coord.at(0) = 'E';
        (*this)[coord] = nullptr;

    } 
    // if it is a short castling
    else {
        // make the cell Gx pointing to the king
        coord.at(0) = 'G';
        (*this)[coord] = &this->get_piece_at(12, player_ID);
        // make the cell Fx pointing to the first rook
        coord.at(0) = 'F';
        (*this)[coord] = &this->get_piece_at(15, player_ID);
        // set to null pointers in cells Hx and Ex
        coord.at(0) = 'H';
        (*this)[coord] = nullptr;
        coord.at(0) = 'E';
        (*this)[coord] = nullptr;
    }
    return true;
}

Piece& Board::get_piece_at(const int i, const bool ID) {
    if(i < 0 || i >= Board::COLOR_OFFSET)
        throw IllegalMoveException("parameter i must be in [0,15]");
    short index = i;
    index += ID == Piece::BLACK? Board::COLOR_OFFSET:0;
    return *pieces_.at(index);
}
       
Piece& Board::get_random_piece(const bool ID) {
    srand(time(NULL));
    Piece* p = nullptr;
    while (p == nullptr) {
        this->get_piece_at(rand()%Board::COLOR_OFFSET, ID);
    }
    return *p;
}

std::ostream& operator<<(std::ostream& os, Board& board) {
    // print all the rows with its related number
    for(short i = 8; i > 0; i--) {
        os << i << " ";
        for(char j = 'A'; j <= 'H'; j++) {
            if(board[j+std::to_string(i)] != nullptr)
                os << board[j+std::to_string(i)]->to_char();
            else
                os << " ";
        }
        os << std::endl;
    }
    // print the letters row
    os << "  ";
    for (char c = 'A'; c <= 'H'; c++) {
        os << c;
    }
    // end the line
    os << std::endl;
    return os; 
}
        
Piece*& Board::operator[](const std::string& coord) {
    std::regex coord_pattern ("[A-Ha-h][1-8]");
    // check if coordinates are in the right format and in the right range
    if(!std::regex_match(coord, coord_pattern)) 
        throw IllegalMoveException("Illegal Coordinates: Coordinates must be in [A-Ha-h][1-8] format");
    return dashboard_.at(coord.at(1) - '1').at(std::toupper(coord.at(0)) - 'A');
}

#endif

// unused code lambda function 
//  std::vector<Piece*>::iterator piece_it = std::replace_if(pieces_.begin(), pieces_.end(), 
//                 [this, to] (Piece* p) {
//                     return dynamic_cast<void*>(p) == dynamic_cast<void*>((*this)[to]);
//                 }, nullptr);



//     // if the pieces have different colors, it can't castle
//     if((*this)[from]->get_ID() != (*this)[to]->get_ID())
//         return false;
//     // try if the first cell contains the king
//     King* k = dynamic_cast<King*>((*this)[from]);
//     Rook* r = dynamic_cast<Rook*>((*this)[to]);
//     // if the first cell don't contains the king, try the second
//     if(k == nullptr) {
//         k = dynamic_cast<King*>((*this)[to]);
//         r = dynamic_cast<Rook*>((*this)[from]);
//         // can't castle with theese two cells so return false
//         if(k == nullptr) 
//             return false; 
//     }
//     // if one of the two pieces can't castle return false
//     if(!k.can_castle() || !k.can_castle())
//         return false;
//
//     // da finire
//
//     return true;
