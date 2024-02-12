#pragma once
#include "Pieces/RangePieces/RangePiece.h"

// we decided that Queen won't inherit from Rook and Bishop because both of those classes are using RangePiece so the Queen will have two values of the same fields
// that it will inherit from the Piece class and the Queen will have to use both the constrctor of the Bishop and the Rook and to make it efficent we will have to make empty
// constructors for almost evry class that comes befor


class Queen : public RangePiece
{
public:
	Queen(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
		std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation);
	~Queen() {};

private:
	virtual bool checkValidMovement(const Square& target) const override;
	void plumbDirection(PieceDirection& direction) const override;
	// This funciton updates this piece controlled squares
	virtual void updateThisPieceSquares(const Square& target) const;
	// This function turnes off or on all of the Bishop or Rook controlled squares
	void changeRookSquaresInArr(bool onOrOff, const Square& target, PieceDirection initailDirection) const;
	void startingUpdateArrs() const override;
};

