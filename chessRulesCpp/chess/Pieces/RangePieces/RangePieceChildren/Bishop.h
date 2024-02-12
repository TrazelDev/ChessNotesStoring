#pragma once
#include "Pieces/RangePieces/RangePiece.h"

class Bishop : public RangePiece
{
public:
	Bishop(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
		std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation);
	~Bishop() {};

private:
	bool checkValidMovement(const Square& target) const override;
	void updateThisPieceSquares(const Square& target) const override;
	void plumbDirection(PieceDirection& direction) const override;
	void startingUpdateArrs() const override;
};

