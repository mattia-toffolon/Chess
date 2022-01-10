// Author: Guerrini Alberto

#ifndef BOARD_CPP
#define BOARD_CPP

#include "../include/Board.hpp"

Board::Board(const bool player_color) {
    // reserve space in the vectors to store all pieces
    pieces_.reserve(4*Board::DIM);
    dashboard_.reserve(Board::DIM);
    // for every row in dashboard reserve 8 cells and initialize them to nullptr
    for (short i = 0; i < DIM; i++) {
        dashboard_.at(i).reserve(DIM);
        std::fill(dashboard_.at(i).begin(), dashboard_.at(i).end(), nullptr);
    }
    // sets the index of dashboard rows in wich there are pawns
    int pawns_row_w = player_color == Piece::WHITE? 1 : 6;
    int pawns_row_b = player_color == Piece::BLACK? 1 : 6;
    // add 8 pawns for each color in the correct position of the array
    // and add pawns to the dashboard
    int idx = 0;
    for(idx = 0; idx < DIM; idx++) {
        // white pawns
        pieces_.at(idx) = new Pawn::Pawn(Piece::WHITE);
        dashboard_.at(pawns_row_w).at(idx) = pieces_.at(idx);
        // black pawns
        pieces_.at(COLOR_OFFSET + idx) = new Pawn::Pawn(Piece::BLACK);
        dashboard_.at(pawns_row_b).at(idx) = pieces_.at(COLOR_OFFSET + idx);
    }
    // add non pawn pieces in the pieces_ vector
    pieces_.at(idx) = new Rook::Rook(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new Rook::Rook(Piece::BLACK);
    idx++;
    pieces_.at(idx) = new Knight::Knight(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new Knight::Knight(Piece::BLACK);
    idx++;
    pieces_.at(idx) = new Queen::Queen(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new Queen::Queen(Piece::BLACK);
    idx++;
     pieces_.at(idx) = new King::King(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new King::King(Piece::BLACK);
    idx++;
     pieces_.at(idx) = new Bishop::Bishop(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new Bishop::Bishop(Piece::BLACK);
    idx++;
     pieces_.at(idx) = new Bishop::Bishop(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new Bishop::Bishop(Piece::BLACK);
    idx++;
    pieces_.at(idx) = new Knight::Knight(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new Knight::Knight(Piece::BLACK);
    idx++;
    pieces_.at(idx) = new Rook::Rook(Piece::WHITE);
    pieces_.at(idx + COLOR_OFFSET) = new Rook::Rook(Piece::BLACK);
    
    // set the index of dashboard rows in wich there are non pawns pieces
    int pieces_row_w = player_color == Piece::WHITE? 0 : 7;
    int pieces_row_b = player_color == Piece::BLACK? 0 : 7;
    // copy references to white pieces to the dashboard
    std::copy(pieces_.begin() + Board::DIM, 
              pieces_.begin() + Board::COLOR_OFFSET, 
              dashboard_.at(pieces_row_w).begin());
    // copy references to black pieces to the dashboard
    std::copy(pieces_.begin() + Board::DIM, 
              pieces_.begin() + Board::COLOR_OFFSET, 
              dashboard_.at(pieces_row_w).begin());
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
        throw std::invalid_argument("No piece in the cell " + from);
     // check if the piece in "from" coordinates has the opponent color
    if((*this)[from]->get_ID() != player_ID)
        throw std::invalid_argument("Player can't move an opponent piece");
    // check if the "to" coordinates are valid (operator[] can throw exceptions)
    (*this)[to];
    // check if the piece in coordinates from can move to the cell "to"
    if((*this)[from]->can_move(from, to)) {
        // manage the capture of the piece or castling, if there is one, in cell "to"
        if((*this)[to] != nullptr) {
            // if the piece in to cell has the player color it must be a castling move
            if((*this)[to]->get_ID() == player_ID)
                return this->castling(from, to, player_ID);
            // if it can't be a castling it have to be a capture
            else
                return this->capture(from, to);
        } else {
        // if the cell "to" is empty simply move the piece
        // make the pointer in the "to" cell pointing to the moved piece
        (*this)[to] = (*this)[from];
        // set to nullptr the pointer in the cell from;
        (*this)[from] = nullptr;
        return true;
        }
    }       
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
        throw std::invalid_argument("parameter i must be in [0,15]");
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

std::ostream& Board::operator<<(std::ostream& os) const {
    // print all the rows with its related number
    for(short i = DIM; i > 0; i++) {
        os << i << " ";
        for(short j = 0; i < DIM; i++) {
            if(dashboard_.at(i).at(j) != nullptr)
                os << dashboard_.at(i).at(j)->to_char();
            else
                os << " ";
        }
        os << std::endl;
    }
    // print the letters row
    os << "  ";
    for (char c = 'A'; c < 'A' + DIM; c++) {
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
        throw std::invalid_argument("Illegal Coordinates: Coordinates must be in [A-Ha-h][1-8] format");
    return dashboard_.at(coord.at(1) - '1').at(std::toupper(coord.at(0)) - 'A');
}

#endif


int main(void) {
    return 0;
}

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