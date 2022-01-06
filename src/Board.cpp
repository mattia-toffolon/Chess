// Author: Guerrini Alberto

#ifndef BOARD_CPP
#define BOARD_CPP

#include "Board.hpp"

Board::Board(bool player_color = Piece::WHITE) {
    // reserve space in the vectors to store all pieces
    pieces_.reserve(4*DIM);
    dashboard_.reserve(DIM);
    // for every fow in dashboard reserves 8 cells and initializes them to nullptr
    for (short i = 0; i < DIM; i++) {
        dashboard_.at(i).reserve(DIM);
        std::fill(dashboard_.at(i).begin(), dashboard_.at(i).end(), nullptr);
    }
    // sets the index of dashboard rows in wich there are pawns
    int pawns_row_w = player_color == Piece::WHITE? 1 : 6;
    int pawns_row_b = player_color == Piece::BLACK? 1 : 6;
    // adds 8 pawns for each color in the correct position of the array
    // and adds pawns to the dashboard
    int idx = 0;
    for(idx = 0; idx < DIM; idx++) {
        // white pawns
        pieces_.at(idx) = new Pawn(Piece::WHITE);
        dashboard_.at(pawns_row_w).at(idx) = pieces_.at(idx);
        // black pawns
        pieces_.at(COLOR_OFFSET + idx) = new Pawn(Piece::BLACK);
        dashboard_.at(pawns_row_b).at(idx) = pieces_.at(COLOR_OFFSET + idx);
    }
    // adds non pawn pieces in the pieces_ vector
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
    
    // sets the index of dashboard rows in wich there are non pawns pieces
    int pieces_row_w = player_color == Piece::WHITE? 0 : 7;
    int pieces_row_b = player_color == Piece::BLACK? 0 : 7;
    // copy references to white pieces to the dashboard
    std::copy(pieces_.begin() + DIM, 
              pieces_.begin() + COLOR_OFFSET, 
              dashboard_.at(pieces_row_w).begin());
    // copies references to black pieces to the dashboard
    std::copy(pieces_.begin() + DIM, 
              pieces_.begin() + COLOR_OFFSET, 
              dashboard_.at(pieces_row_w).begin());
}
#endif