#pragma once
#include "Pieces/Piece.h"

#define PAWN_SATRTING_INDEX  7
#define PAWN_NUMBER          8

class Pawn : public Piece
{
public:
	Pawn(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board, std::bitset<NUM_OF_PIECES>** myControlledSquares,
		std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation);
	~Pawn() {};

private:
	virtual bool checkValidMovement(const Square& target) const override;
	void updateThisPieceSquares(const Square& target) const override;
	void startingUpdateArrs() const override;

	bool _moved;
	static int s_pawnNumber;
};

