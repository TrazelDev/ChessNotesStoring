#pragma once
#include "Pieces/RangePieces/RangePiece.h"


class Rook : public RangePiece
{
public:
	Rook(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
		std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation);
	~Rook();
	bool getMoved() const;

private:
	virtual bool checkValidMovement(const Square& target) const override;
	void plumbDirection(PieceDirection& direction) const override;
	void startingUpdateArrs() const override;
	bool* _moved; // made as a pointer because we want to change moved in check valid move which is a const function
};

