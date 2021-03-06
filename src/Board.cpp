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
#include "../include/CheckException.hpp"
#include "../include/CheckMateException.hpp"
#include "../include/DrawException.hpp"

Board::Board(const bool& player_color, const bool& log_match) : logger_ (log_match), log_moves {log_match} {

    // reserve space in the vectors to store all pieces
    pieces_.resize(4*Board::DIM);
    dashboard_.resize(Board::DIM);

    // for every row in dashboard reserve 8 cells and initialize them to nullptr
    for (short i = 0; i < DIM; i++) {
        std::vector<Piece*> vP;
        dashboard_.push_back(vP);
        dashboard_.at(i).resize(DIM);
        std::fill(dashboard_.at(i).begin(), dashboard_.at(i).end(), nullptr);
    }
    // sets the index of dashboard rows in wich there are pawns
    int pawns_row_w = (player_color == Piece::WHITE)? 1 : 6;
    int pawns_row_b = (player_color == Piece::BLACK)? 1 : 6;

    // add 8 pawns for each color in the correct position of the array
    // and add pawns to the dashboard
    int idx = 0;
    for(idx = 0; idx < DIM; idx++) {
        // white pawns
        pieces_.at(idx) = new Pawn(Piece::WHITE, this, char('A'+idx) + std::to_string(pawns_row_w+1), player_color);
        dashboard_.at(pawns_row_w).at(idx) = pieces_.at(idx);
        // black pawns
        pieces_.at(COLOR_OFFSET + idx) = new Pawn(Piece::BLACK, this, char('A'+idx) + std::to_string(pawns_row_b+1), player_color);
        dashboard_.at(pawns_row_b).at(idx) = pieces_.at(COLOR_OFFSET + idx);
    }

    // set the index of dashboard rows in wich there are non pawns pieces
    int pieces_row_w = player_color == Piece::WHITE? 0 : 7;
    int pieces_row_b = player_color == Piece::BLACK? 0 : 7;

    // add non pawn pieces in the pieces_ vector
    pieces_.at(idx)                 = new Rook(Piece::WHITE, this, 'A'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new Rook(Piece::BLACK, this, 'A'+std::to_string(pieces_row_b+1));
    idx++;
    pieces_.at(idx)                 = new Knight(Piece::WHITE, this, 'B'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new Knight(Piece::BLACK, this, 'B'+std::to_string(pieces_row_b+1));
    idx++;
    pieces_.at(idx)                 = new Bishop(Piece::WHITE, this, 'C'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new Bishop(Piece::BLACK, this, 'C'+std::to_string(pieces_row_b+1));
    idx++;
    pieces_.at(idx)                 = new Queen(Piece::WHITE, this, 'D'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new Queen(Piece::BLACK, this, 'D'+std::to_string(pieces_row_b+1));
    idx++;
    pieces_.at(idx)                 = new King(Piece::WHITE, this, 'E'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new King(Piece::BLACK, this, 'E'+std::to_string(pieces_row_b+1));
    idx++;
    pieces_.at(idx)                 = new Bishop(Piece::WHITE, this, 'F'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new Bishop(Piece::BLACK, this, 'F'+std::to_string(pieces_row_b+1));
    idx++;
    pieces_.at(idx)                 = new Knight(Piece::WHITE, this, 'G'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new Knight(Piece::BLACK, this, 'G'+std::to_string(pieces_row_b+1));
    idx++;
    pieces_.at(idx)                 = new Rook(Piece::WHITE, this, 'H'+std::to_string(pieces_row_w+1));
    pieces_.at(idx + COLOR_OFFSET)  = new Rook(Piece::BLACK, this, 'H'+std::to_string(pieces_row_b+1));

    // copy references to white pieces to the dashboard
    std::copy(pieces_.begin() + Board::DIM, 
              pieces_.begin() + Board::COLOR_OFFSET, 
              dashboard_.at(pieces_row_w).begin());
            
    // copy references to black pieces to the dashboard
    std::copy(pieces_.begin() + Board::COLOR_OFFSET + Board::DIM, 
              pieces_.begin() + 2*Board::COLOR_OFFSET, 
              dashboard_.at(pieces_row_b).begin());

    // logger setup and player color log
    if(log_moves) {
        logger_.log_player_ID(player_color);
    }

    //moves counter to zero
    moves_counter = 0;
}

Board::Board(const Board& arg) : log_moves {false} {
    // reserve space in the vectors to store all pieces
    pieces_.resize(4*Board::DIM);
    dashboard_.resize(Board::DIM);

    // for every row in dashboard reserve 8 cells and initialize them to nullptr
    for (short i = 0; i < DIM; i++) {
        std::vector<Piece*> vP;
        dashboard_.push_back(vP);
        dashboard_.at(i).resize(DIM);
        std::fill(dashboard_.at(i).begin(), dashboard_.at(i).end(), nullptr);
    }

    // copies the Pawns or the promoted Pieces of arg.pieces_ in pieces_ in their right positions
    for(int i=0; i<Board::DIM; i++){
        Piece* p = (arg).get_piece_at(i, Piece::WHITE);
        if(p != nullptr && p->to_char()=='p'){
            Pawn* pw = dynamic_cast<Pawn*>(p);
            pieces_.at(i) = new Pawn(Piece::WHITE, this, pw->get_pos(), pw->get_direction(), pw->get_en_passant());
        } 
        else if(p != nullptr && p->to_char()!='p'){
            char c = p->to_char();
            switch(c){
                case 't':
                    pieces_.at(i) = new Rook(Piece::WHITE, this, p->get_pos(), false);
                    break;
                case 'c':
                    pieces_.at(i) = new Knight(Piece::WHITE, this, p->get_pos());
                    break;
                case 'a':
                    pieces_.at(i) = new Bishop(Piece::WHITE, this, p->get_pos());
                    break;
                case 'd':
                    pieces_.at(i) = new Queen(Piece::WHITE, this, p->get_pos());
                    break;

                default:
                    break;
            }
        }
        p = (arg).get_piece_at(i, Piece::BLACK);
        if(p != nullptr && p->to_char()=='P'){
            Pawn* pw = dynamic_cast<Pawn*>(p);
            pieces_.at(i+Board::COLOR_OFFSET) = new Pawn(Piece::BLACK, this, pw->get_pos(), pw->get_direction(), pw->get_en_passant());
        }
        else if(p != nullptr && p->to_char()!='P'){
            char c = p->to_char();
            switch(c){
                case 'T':
                    pieces_.at(i+Board::COLOR_OFFSET) = new Rook(Piece::BLACK, this, p->get_pos(), false);
                    break;
                case 'C':
                    pieces_.at(i+Board::COLOR_OFFSET) = new Knight(Piece::BLACK, this, p->get_pos());
                    break;
                case 'A':
                    pieces_.at(i+Board::COLOR_OFFSET) = new Bishop(Piece::BLACK, this, p->get_pos());
                    break;
                case 'D':
                    pieces_.at(i+Board::COLOR_OFFSET) = new Queen(Piece::BLACK, this, p->get_pos());
                    break;

                default:
                    break;
            }
        }
    }

    // copies the Rooks of arg.pieces_ in pieces_ in their right positions
    if((arg).get_piece_at(8, Piece::WHITE) != nullptr){
        Rook* r = dynamic_cast<Rook*>((arg).get_piece_at(8, Piece::WHITE));
        pieces_.at(8) = new Rook(Piece::WHITE, this, r->get_pos(), r->get_castling());
    }
    if((arg).get_piece_at(8, Piece::BLACK) != nullptr){
        Rook* r = dynamic_cast<Rook*>((arg).get_piece_at(8, Piece::BLACK));
        pieces_.at(8+Board::COLOR_OFFSET) = new Rook(Piece::BLACK, this, r->get_pos(), r->get_castling());
    }
    if((arg).get_piece_at(15, Piece::WHITE) != nullptr){
        Rook* r = dynamic_cast<Rook*>((arg).get_piece_at(15, Piece::WHITE));
        pieces_.at(15) = new Rook(Piece::WHITE, this, r->get_pos(), r->get_castling());
    }
    if((arg).get_piece_at(15, Piece::BLACK) != nullptr){
        Rook* r = dynamic_cast<Rook*>((arg).get_piece_at(15, Piece::BLACK));
        pieces_.at(15+Board::COLOR_OFFSET) = new Rook(Piece::BLACK, this, r->get_pos(), r->get_castling());
    }

    // copies the Knights of arg.pieces_ in pieces_ in their right positions
    if((arg).get_piece_at(9, Piece::WHITE) != nullptr){
        Knight* k = dynamic_cast<Knight*>((arg).get_piece_at(9, Piece::WHITE));
        pieces_.at(9) = new Knight(Piece::WHITE, this, k->get_pos());
    }
    if((arg).get_piece_at(9, Piece::BLACK) != nullptr){
        Knight* k = dynamic_cast<Knight*>((arg).get_piece_at(9, Piece::BLACK));
        pieces_.at(9+Board::COLOR_OFFSET) = new Knight(Piece::BLACK, this, k->get_pos());
    }
    if((arg).get_piece_at(14, Piece::WHITE) != nullptr){
        Knight* k = dynamic_cast<Knight*>((arg).get_piece_at(14, Piece::WHITE));
        pieces_.at(14) = new Knight(Piece::WHITE, this, k->get_pos());
    }
    if((arg).get_piece_at(14, Piece::BLACK) != nullptr){
        Knight* k = dynamic_cast<Knight*>((arg).get_piece_at(14, Piece::BLACK));
        pieces_.at(14+Board::COLOR_OFFSET) = new Knight(Piece::BLACK, this, k->get_pos());
    }

    // copies the Bishops of arg.pieces_ in pieces_ in their right positions
    if((arg).get_piece_at(10, Piece::WHITE) != nullptr){
        Bishop* b = dynamic_cast<Bishop*>((arg).get_piece_at(10, Piece::WHITE));
        pieces_.at(10) = new Bishop(Piece::WHITE, this, b->get_pos());
    }
    if((arg).get_piece_at(10, Piece::BLACK) != nullptr){
        Bishop* b = dynamic_cast<Bishop*>((arg).get_piece_at(10, Piece::BLACK));
        pieces_.at(10+Board::COLOR_OFFSET) = new Bishop(Piece::BLACK, this, b->get_pos());
    }
    if((arg).get_piece_at(13, Piece::WHITE) != nullptr){
        Bishop* b = dynamic_cast<Bishop*>((arg).get_piece_at(13, Piece::WHITE));
        pieces_.at(13) = new Bishop(Piece::WHITE, this, b->get_pos());
    }
    if((arg).get_piece_at(13, Piece::BLACK) != nullptr){
        Bishop* b = dynamic_cast<Bishop*>((arg).get_piece_at(13, Piece::BLACK));
        pieces_.at(13+Board::COLOR_OFFSET) = new Bishop(Piece::BLACK, this, b->get_pos());
    }

    // copies the Queens of arg.pieces_ in pieces_ in their right positions
    if((arg).get_piece_at(11, Piece::WHITE) != nullptr){
        Queen* q = dynamic_cast<Queen*>((arg).get_piece_at(11, Piece::WHITE));
        pieces_.at(11) = new Queen(Piece::WHITE, this, q->get_pos());
    }
    if((arg).get_piece_at(11, Piece::BLACK)){
        Queen* q = dynamic_cast<Queen*>((arg).get_piece_at(11, Piece::BLACK));
        pieces_.at(11+Board::COLOR_OFFSET) = new Queen(Piece::BLACK, this, q->get_pos());
    }

    // copies the Kings of arg.pieces_ in pieces_ in their right positions
    if((arg).get_piece_at(12, Piece::WHITE) != nullptr){
        King* kg = dynamic_cast<King*>((arg).get_piece_at(12, Piece::WHITE));
        pieces_.at(12) = new King(Piece::WHITE, this, kg->get_pos(), kg->get_castling());
    }
    if((arg).get_piece_at(12, Piece::BLACK) != nullptr){
        King* kg = dynamic_cast<King*>((arg).get_piece_at(12, Piece::BLACK));
        pieces_.at(12+Board::COLOR_OFFSET) = new King(Piece::BLACK, this, kg->get_pos(), kg->get_castling());
    }

    // sets dashboard_ with the informations contained in pieces_
    for(int i=0; i<2*Board::COLOR_OFFSET; i++){
        Piece* p = pieces_.at(i);
        if(p != nullptr){
            (*this)[p->get_pos()] = p;
        }
    }

    // the -1 is written to prevent any throw of DrawException while trying moves in this copy of Board. 
    // Since looking for a draw is legal, we want to consider moves that lead to a Draw as legal
    moves_counter = arg.get_moves_counter()-1;
}

Board::~Board() {
    // set to nullptr every reference to pieces in the dashboard vectors
    for(short i = 0; i < DIM; i++)
        std::fill(dashboard_.at(i).begin(), dashboard_.at(i).end(), nullptr);
    // delete all pieces from free space
    for(Piece* p : pieces_){
        delete p;
        p=nullptr;
    }
}

bool Board::move(const std::string& from, const std::string& to, const bool player_ID, const char promote) {
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
        //verify if a pawn moves
        if(std::toupper(((*this)[from])->to_char())=='P'){
            moves_counter = 0;
        }else{
            moves_counter++;
        }   
        // manage the capture of the piece or castling, if there is one, in cell "to"
        if((*this)[to] != nullptr) {        
            // if the piece in to cell has the player color it must be a castling move
            if((*this)[to]->get_ID() == player_ID){
                this->castling(from, to, player_ID);
            }
            // if it can't be a castling it have to be a capture
            else{
                this->capture(from, to);
            }
        } else {
            // if the cell "to" is empty simply move the piece
            // make the pointer in the "to" cell pointing to the moved piece
            (*this)[to] = (*this)[from];
            std::string up_to;
            up_to.push_back(std::toupper(to.at(0)));
            up_to.push_back(to.at(1));
            (*this)[to]->set_pos(up_to);
            // set to nullptr the pointer in the cell from;
            (*this)[from] = nullptr;
        }

        // after every move all the en-passant variables are set to false
        for(int i=0; i<Board::DIM; i++){
            Piece* p = (*this).get_piece_at(i, Piece::WHITE);
            if(p != nullptr && p->to_char()=='p'){
                Pawn* pw = dynamic_cast<Pawn*>(p);
                pw->set_en_passant(false);
            }
            p = (*this).get_piece_at(i, Piece::BLACK);
            if(p != nullptr && p->to_char()=='P'){
                Pawn* pw = dynamic_cast<Pawn*>(p);
                pw->set_en_passant(false);
            }
        }

        // the only en-passant that could be true is the one of the Pawn which moved two tiles from its starting position
        if((*this)[to]!=nullptr && std::toupper((*this)[to]->to_char())=='P' && std::abs(from.at(1)-to.at(1))==2){
            Pawn* pw = dynamic_cast<Pawn*>((*this)[to]);
            pw->set_en_passant(true);
        }

        // castling flag setting for rook and king
        Rook* r = dynamic_cast<Rook*>((*this)[to]);
        if(r != nullptr)
            r->set_castling(false);
        King* k = dynamic_cast<King*>((*this)[to]);
        if(k != nullptr)
            k->set_castling(false);

        // log the move
        if(log_moves)
            logger_.log_move(from, to);

        // promotion manage
        if(promote != 'N')
            this->promote(to, player_ID, promote);

        // check if there is check
        King* opponents_king = dynamic_cast<King*>(get_piece_at(12, !player_ID));
        if(opponents_king->is_under_check(opponents_king->get_pos()))
            throw CheckException("The opponent player is now undergoing Check!");

        
        // control for the draw
        if(moves_counter >=50)
            throw DrawException("Draw: the players didn't move pawns or captured pieces in the last 50 moves");
        
        return true;
    }
    else
        throw IllegalMoveException("Can't made the move" + from + " " + to);      
    return false;   
}

bool Board::capture(const std::string& from, const std::string& to) {
    // find and replace with nullptr the captured piece into the pieces_ vector
    std::replace(pieces_.begin(), pieces_.end(), (*this)[to], (Piece*)nullptr);
    // delete the piece from the free space
    delete (*this)[to];
    // make the pointer in the "to" cell pointing to the moved piece
    (*this)[to] = (*this)[from];
    std::string up_to;
    up_to.push_back(std::toupper(to.at(0)));
    up_to.push_back(to.at(1));
    (*this)[to]->set_pos(up_to);
    (*this)[from] = nullptr;
    moves_counter = 0;
    return true;   
}

bool Board::castling(const std::string& from, const std::string& to, const bool player_ID) {
    // set the row in wich the castling is made
    std::string coord ("XX");
    coord.at(1) = from.at(1);
    // check if it is a long castling
    if(std::abs(std::toupper(from.at(0)) - std::toupper(to.at(0))) == 4) {
        // make the cell Cx pointing to the king
        coord.at(0) = 'C';
        (*this)[coord] = this->get_piece_at(12, player_ID);
        this->get_piece_at(12, player_ID)->set_pos(coord);
        // make the cell Dx pointing to the first rook
        coord.at(0) = 'D';
        (*this)[coord] = this->get_piece_at(8, player_ID);
        this->get_piece_at(8, player_ID)->set_pos(coord);
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
        (*this)[coord] = this->get_piece_at(12, player_ID);
        this->get_piece_at(12, player_ID)->set_pos(coord);
        // make the cell Fx pointing to the first rook
        coord.at(0) = 'F';
        (*this)[coord] = this->get_piece_at(15, player_ID);
        this->get_piece_at(15, player_ID)->set_pos(coord);
        // set to null pointers in cells Hx and Ex
        coord.at(0) = 'H';
        (*this)[coord] = nullptr;
        coord.at(0) = 'E';
        (*this)[coord] = nullptr;
    }

    // sets castling=false for the King and the two Rooks (if alive) of this player
    if(get_piece_at(12, player_ID) != nullptr){
        King* kg = dynamic_cast<King*>(get_piece_at(12, player_ID));
        kg->set_castling(false);
    }
    if(get_piece_at(8, player_ID) != nullptr){
        Rook* r = dynamic_cast<Rook*>(get_piece_at(8, player_ID));
        r->set_castling(false);
    }
    if(get_piece_at(15, player_ID) != nullptr){
        Rook* r = dynamic_cast<Rook*>(get_piece_at(15, player_ID));
        r->set_castling(false);
    }

    return true;
}

bool Board::promote(const std::string& piece_pos, const bool player_ID, const char promotion) {
    Piece* promoted_piece; 
    // choose what is the new piece for promotion
    switch (promotion) {
    case 'T':
    case 't':
        promoted_piece = new Rook(player_ID, this, piece_pos, false);
        break;
    case 'C':
    case 'c':
        promoted_piece = new Knight(player_ID, this, piece_pos);
        break;
    case 'A':
    case 'a':
        promoted_piece = new Bishop(player_ID, this, piece_pos);
        break;
    case 'D':
    case 'd':
        promoted_piece = new Queen(player_ID, this, piece_pos);
        break;

    default:
        return false;
        break;
    }
    // deletes the old Pawn
    delete (*this)[piece_pos];
    // replace the promoted piece in pieces_
    std::replace(pieces_.begin(), pieces_.end(), (*this)[piece_pos], promoted_piece);
    // replaces the promoted piece in the dashboard
    (*this)[piece_pos] = promoted_piece;
    // log the promotion
    if(log_moves)
        logger_.log_promotion(piece_pos, promotion);

    return true;
}

// check if the chosen move is a promotion
bool Board::isPromotion(const std::string& from, const std::string& to){
    std::regex coord_pattern ("[A-Ha-h][1,8]");
    if((*this)[from]!=nullptr && std::toupper((*this)[from]->to_char()) == 'P' && (*this)[from]->can_move(to) && std::regex_match(to, coord_pattern)){
        return true;
    }
    return false;
}

// returns a string version of dashboard_
std::string Board::to_string(){
    std::string ret;
    for(char i = 'A'; i<='H'; i++){
        for(int j=1; j<=8; j++){
            std::string to;
            to.push_back(i);
            to.push_back(j+'0');
            if((*this)[to]!=nullptr)
                ret.push_back((*this)[to]->to_char());
            else    
                ret.push_back(' ');  
        }
    }
    return ret;
}

// tells if there are enough pieces to go on with the match 
// if false, a CheckMate cannot be forced by any Player
bool Board::enough_pieces(){
    std::string str_pieces;
    for(int i=0; i<2*Board::COLOR_OFFSET; i++){
        if(pieces_.at(i)!=nullptr)
            str_pieces.push_back(pieces_.at(i)->to_char());
    }
    // if King vs King then false
    if(str_pieces.compare("rR")==0 )
        return false;
    // if King & Bishop vs King then false
    else if( str_pieces.compare("arR")==0  || str_pieces.compare("raR")==0 || str_pieces.compare("rAR")==0 || str_pieces.compare("rRA")==0 )
        return false;
    // if King & Knight vs King then false
    else if( str_pieces.compare("crR")==0  || str_pieces.compare("rcR")==0 || str_pieces.compare("rCR")==0 || str_pieces.compare("rRC")==0 )
        return false;
    // if King & Bishop vs King & Bishop then false
    else if( str_pieces.compare("arAR")==0  || str_pieces.compare("raAR")==0 || str_pieces.compare("arRA")==0 || str_pieces.compare("raRA")==0 )
        return false;
    else 
        return true;
}

int Board::get_moves_counter() const{
    return moves_counter;
}

Piece* Board::get_piece_at(const int i, const bool ID) const {
    if(i < 0 || i >= Board::COLOR_OFFSET)
        throw IllegalMoveException("parameter i must be in [0,15]");
    short index = i;
    index += ID == Piece::BLACK? Board::COLOR_OFFSET:0;
    return pieces_.at(index);
}
       
Piece* Board::get_random_piece(const bool ID) {
    srand(time(NULL));
    Piece* p = nullptr;
    while (p == nullptr) {
        p = this->get_piece_at(rand()%Board::COLOR_OFFSET, ID);
    }
    return p;
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