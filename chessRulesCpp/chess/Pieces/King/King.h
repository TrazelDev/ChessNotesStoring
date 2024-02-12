#pragma once
#include "Pieces/Piece.h"
#include "Pieces/RangePieces/RangePieceChildren/Rook.h"

#define KING_X 3
class King : public Piece
{
public:
	King(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
		std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square** kingLocation);
	~King();
	bool getMoved() const;
private:
	void startingUpdateArrs() const override;
	virtual bool checkValidMovement(const Square& target) const override;
	void updateThisPieceSquares(const Square& target) const override;
	/*
	This function checks if castling can occur and changes board, enemyControlledSquares and myControlledSquares
	accordingly, it is assumed that the rook and the king are standing in the right position to castle
	*/
	bool castling(Square& target, Rook& rook);
	// This function is for checking if in between the rook and the king there are pieces and if king is moving through enemy controlled squares
	bool checkCastling(Square& target, int diff);

	bool* _moved;
};


