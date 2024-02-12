#pragma once
#include "Pieces/Piece.h"
#define SECOND_KNIGHT_COLUMNS 6
#define STARTING_KNIGHT_INDEX 2

class Knight : public Piece
{
public:
	Knight(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
		std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation);
	~Knight() {};

private:
	virtual bool checkValidMovement(const Square& target) const override;
	void updateThisPieceSquares(const Square& target) const override;
	void startingUpdateArrs() const override;
};

