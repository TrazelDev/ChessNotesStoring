#pragma once
#include "Pieces/RangePieces/RangePieceChildren/Queen.h"
#include "Pieces/RangePieces/RangePieceChildren/Rook.h"
#include "Pieces/RangePieces/RangePieceChildren/Bishop.h"
#include "Pieces/King/King.h"
#include "Pieces/Pawn/Pawn.h"
#include "Pieces/Knight/Knight.h"

#define COLUMNS 8 
#define ROWS    8
#define BLACK_KING_X 5
#define BLACK_KING_Y 0
#define NUM_PIECES 17
#define BET_NO_PIECES 6
#define HALF_BOARD 5

namespace chessBackend
{
	class Board
	{
	public:
		Board();
		~Board() {};
		void tryMove(std::string& move);

	private:
		// This function puts pieces on the board
		void putPiecesOnBoard();
		void movePiece(const Square& target, const Square& thisSquare);

		Piece*** _board;
		std::bitset<NUM_OF_PIECES>** _whiteControlledSquares;
		std::bitset<NUM_OF_PIECES>** _blackControlledSquares;

		bool _turn;
	};

}
