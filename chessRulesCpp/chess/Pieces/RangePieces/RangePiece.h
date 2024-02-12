#pragma once
#include "Pieces/Piece.h"

#define NO_MOVEMENT 0


class RangePiece : public Piece 
{
public:
	RangePiece(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
		std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation);
	~RangePiece();
	// in public because we want to be able to use this function in king for castling
	void updateThisPieceSquares(const Square& target) const override;

protected:
	// finds the direction that the piece is going to
	void checkDirection(const Square& target) const;
	// checking if the way to the target square is clear
	bool checkClearWay(const Square& targetSquare) const;
	// turning off or on the bits in a specific direction  
	void changeMySquaresBits(const bool& revrseDirection, const bool& onOrOff, PieceDirection& direction, const Square& location) const;
	// plumbing the direction
	virtual void plumbDirection(PieceDirection& direction) const = 0;
	PieceDirection* _lastDirection;
	
};

