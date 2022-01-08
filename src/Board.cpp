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
        pieces_.at(idx) = new Pawn(Piece::WHITE);
        dashboard_.at(pawns_row_w).at(idx) = pieces_.at(idx);
        // black pawns
        pieces_.at(COLOR_OFFSET + idx) = new Pawn(Piece::BLACK);
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

bool Board::move(const std::string& from, const std::string& to) {
    // check if the "from" coordinates are referred to an empty cell
    if((*this)[from] == nullptr)
        throw std::invalid_argument("No piece in the cell " + from);
    // check if the "to" coordinates are valid (operator[] can throw exceptions)
    (*this)[to];
    // check if the piece in coordinates from can move to the cell "to"
    if((*this)[from]->can_move(from, to)) {
        // manage the capture of the piece, if there is one, in cell "to"
        if((*this)[to] != nullptr) {
            // find and replace with nullptr the captured piece into the pieces_ vector
            std::replace(pieces_.begin(), pieces_.end(), (*this)[to], (Piece*)nullptr);
            // delete the piece from the free space
            delete (*this)[to];
        }
        // make the pointer in the "to" cell pointing to the moved piece
        (*this)[to] = (*this)[from];
        // set to nullptr the pointer in the cell from;
        (*this)[from] = nullptr;
        return true;
    }        
    return false;   
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

// unused code lambda function 
//  std::vector<Piece*>::iterator piece_it = std::replace_if(pieces_.begin(), pieces_.end(), 
//                 [this, to] (Piece* p) {
//                     return dynamic_cast<void*>(p) == dynamic_cast<void*>((*this)[to]);
//                 }, nullptr);