#pragma once
#include <bitset>

#ifdef _DEBUG
#include "debug_functions/debugHelpers.h"
#endif

#define COLUMNS 8 
#define ROWS    8
#define BIT_ON 1
#define BIT_OFF 0

#define BISHOP_INDEX 4
#define QUEEN_INDEX 5
#define ROOK_FIRST_INDEX 0
#define ROOK_SECOND_INDEX 1
#define KING_INDEX 7

#define NUM_OF_PIECES 15
#define NEIGHBOR_ROWS 2
#define NEIGHBOR_COLS 2

#define WHITE true
#define BLACK false

#define NUM_POSSIBILITIES 8

// for the function updateOtherSquares:
#define RANGEPIECE_MAX_INDEX_PLUS_ONE 7
#define CONFIGURTIONS 4 

#define LEGAL 0 // used
#define CEHCK 1 // not sure where to use
#define NOT_SRC_PIECE 2 // didnt account for that, needs to be used in the main
#define DEST_YOUR_PIECE 3 // used
#define DISCOVER_CHECK_YOURSELF 4 // nir currently works on that
#define NOT_LEGAL_INDEXES 5 // The graphical interface prevents the user from making moves with incorrect indexes but still used that
#define ILLEGAL_MOVE 6 // used
#define SAME_SQUARE 7 // used
#define CHECKMATE 8 // not used

struct PieceDirection
{
	PieceDirection(const int& x, const int& y)
	{
		this->x = x;
		this->y = y;
	};

	// the copy constrcutor is just to create plumb direction there is no use of copying a PieceDirection
	PieceDirection(PieceDirection* other)
	{
		this->x = other->x;
		this->y = other->y;
	};

	void operator++()
	{
		this->x += (this->x > 0) + ((this->x < 0) * -1);
		this->y += (this->y > 0) + ((this->y < 0) * -1);
	}

	void operator=(PieceDirection& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	void cangeValues(const int& x, const int& y)
	{
		this->x = x;
		this->y = y;
	}

	void reverseDirection()
	{
		this->x *= -1;
		this->y *= -1;
	}

	int x;
	int y;
};

struct Square
{
	Square(const unsigned int x, const unsigned int y)
	{
		this->x = x;
		this->y = y;
	}

	void operator+=(const PieceDirection& other)
	{
		this->x += other.x;
		this->y += other.y;
	}

	bool operator==(const Square& other)
	{
		return (other.x == this->x && other.y == this->y);
	}

	int x;
	int y;
};



class Piece
{
public:
	Piece(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
		std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation);
	~Piece() {};

	/* the function is checking if the move is legal if it is the function is chaning the x and y of the piece 
	and changing the arr of the pieces that the enemy controls and that the my side controls and than the function returning true
	input: the square that the piece wants to go to 
	output: whether the the move is legal or not */
	bool checkMove(Square& target);

	/* function that returns the color 
	output: bool that says the color of Piece***/
	bool getColor() const;

	/* function that returns the index that the piece represents the location of this piece in the the arr this->_myControlledSquares */
	int getIndex() const;

	void setSquare(Square target);

	// this function checks if a checkmate occurred
	//void checkmate(const Square& king);

	void updateOtherSquares(const Square& target, const int& myIndedx) const;
	virtual void updateThisPieceSquares(const Square& target) const = 0;

protected:
	// this function changes the arr of _myControlledSquares acording to the squares that each piece controlls in its starting position
	virtual void startingUpdateArrs() const = 0;

	// the function is checking if the piece can move to the target based on the rules of how the piece moves in the game chess
	virtual bool checkValidMovement(const Square& target) const = 0;
	
	/* the function is checking if the king is in check
	output: bool that is true if the king is in check*/
	bool kingInCheck() const;



	/* function that checks if the move will leave the king open to opennet piece to captureqs 
	input: the target that the user wants to move to */
	bool exposedKing(const Square& target) const;

	/* the function is checking what is the first index index that is turned on in the arr 
	_enemyControlledSquares in the position of this king
	output: the first index */
	int findCheckIndex() const;

	/* if the king is not attacked by a knight or pawn than calling this function
	the function is checking if the piece is going to block the check or eat the piece that is checking
	input: the index of the range piece that is checking the king, the target the square that the piece wants to move to
	output: boolean that says if the piece target is standing in a place that blocks the check */
	bool checkBlockingRange(const int& index, const Square& target) const;
	
	// TODO: must be a way to make it better.
	/* if the king is checked by pawn than checking if the target is on the same square as the pawn that threatens the king 
	input: the index of the pawn that is checking the king, the target of the piece that the user moved
	output: boolean that says if the move eats the pawn or not */
	bool checkEatPawn(const int& index, const Square& target) const;
	
	/* if the king is checked by knight than checking if the target is on the same square as the knight that threatens the king
	input: the index of the knight that is checking the king, the target of the piece that the user moved
	output: boolean that says if the move eats the knight or not */
	bool checkEatKnight(const int& index, const Square& target) const;

	bool canBlock(const Square& target) const;

	
	void blockOrRelease(const int& index, Square square, const PieceDirection& dir, const bool& onOrOff, std::bitset<NUM_OF_PIECES>** arr) const;

	Square _square;
	Square* _kingLocation;
	bool _color;  // 0 - black, 1 - white
	Piece*** _board;
	int _indexControlledSquaresArr;

	// [0] - Rock 1, [1] - Rock 2, [2] - Knight 1, [3] - Knight 2, [4] - bishop, [5] - Queen, [6] - king, [7 - 14] - pawns
	std::bitset<NUM_OF_PIECES>** _myControlledSquares;
	std::bitset<NUM_OF_PIECES>** _enemyControlledSquares;

	typedef bool(Piece::* Method[3])(const int& index, const Square& target) const;
	static Method blockCheck;
};