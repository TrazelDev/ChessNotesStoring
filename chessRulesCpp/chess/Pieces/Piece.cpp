#include "Piece.h"
#include <iostream>
#include <array>

Piece::Method Piece::blockCheck = { &Piece::checkBlockingRange, &Piece::checkEatKnight, &Piece::checkEatPawn };

Piece::Piece(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
	std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation) : _square(x, y)
{
	this->_kingLocation = kingLocation;
	this->_color = color;
	this->_board = board;
	this->_myControlledSquares = myControlledSquares;
	this->_enemyControlledSquares = enemyControlledSquares;
}

bool Piece::checkMove(Square& target)
{
	// checking if the piece is going to a new square:
	if (target == this->_square)
	{
		throw(SAME_SQUARE);
		return false;
	}


	// checking if the square that the piece wants to go to does't match the color of this piece:
	if (this->_board[target.y][target.x] != nullptr)
	{
		if (this->_board[target.y][target.x]->getColor() == this->_color)
		{
			throw(DEST_YOUR_PIECE);
			return false;
		}
	}

	// checking if indexes are invalid
	if (target.x > 7 || target.x < 0 || this->_square.x > 7 || this->_square.x < 0 ||
		target.y > 7 || target.y < 0 || this->_square.y > 7 || this->_square.y < 0)
	{
		throw(NOT_LEGAL_INDEXES);
		return false;
	}

	// checking if the king is in check
	if (kingInCheck())
	{
		if (this->_indexControlledSquaresArr != KING_INDEX)
		{
			if (!canBlock(target))
			{
				// the move is letting the oppnent to capture the king 
				throw(ILLEGAL_MOVE);
				return false;
			}
		}
	}

	// this function has some work to do to it:
	if (exposedKing(target))
	{
		throw(DISCOVER_CHECK_YOURSELF);
		return false;
	}

	// REMEMBER order does matter, you cant make new functions after check valid move because of rook
	// To do - check when the piece is king or blocking
	if (!checkValidMovement(target))
	{
		throw(ILLEGAL_MOVE);
		return false;
	}


	return true;
}

bool Piece::getColor() const
{
	return this->_color;
}

int Piece::getIndex() const
{
	return this->_indexControlledSquaresArr;
}

void Piece::setSquare(Square target)
{
	this->_square = target;
}


bool Piece::kingInCheck() const
{
#ifdef _DEBUG
	if ((this->_enemyControlledSquares[this->_kingLocation->y][this->_kingLocation->x].count() != 0))
	{
		std::cout << "the king is in check this is the arr of the piece that checks it:" << std::endl;
		debug::printaArrIndex(this->_enemyControlledSquares, findCheckIndex());
		return true;
	}
	return false;
#endif // DEBUG

#ifndef _DEBUG
	return (this->_enemyControlledSquares[this->_kingLocation->y][this->_kingLocation->x].count() != 0);
#endif
}

void Piece::updateOtherSquares(const Square& target, const int& myIndedx) const
{
	const Square squares[2] = { this->_square, target };
	std::bitset<NUM_OF_PIECES>** controlArrArrs[2] = { this->_myControlledSquares, this->_enemyControlledSquares };

	// the direction the piece is going to be checked at
	PieceDirection dir = PieceDirection(0, 0);

	// what indexs so wont double check the same index form both sides: ( rook first, rook second, bishop, queen)
	// (0 - 3) - this->_square + this->_myControlledSquares
	// (4 - 7) - target + this->_enemyControlledSquares
	// (8 - 11) - target + this->_myControlledSquares
	// (12 - 15) - target + this->_enemyControlledSquares
	std::bitset<16> usedIndex;

	// values of the indexs: 
	// 0 - the index of the the sournding of the square that this piece stands in and for the myControlledSqaures
	// 1 - the index of the the sournding of the square that this piece stands in and for the enemyControlledSqaures
	// 2 - the index of the the sournding of the square that this piece wants to go to in and for the myControlledSqaures
	// 3 - the index of the the sournding of the square that this piece wants to go to in and for the EnemyControlledSqaures
	int PieceIndex = 0;
	for (int yInc = -1; yInc < 2; yInc++)
	{
		for (int xInc = -1; xInc < 2; xInc++)
		{
			// only the squares around the piece
			if (yInc == 0 && xInc == 0)
			{
				continue;
			}
			dir.cangeValues(xInc, yInc);

			// for loop for each config uration
			// 1. this->_square + this->_myControlledSquares
			// 2. this->_square + this->_enemyControlledSquares
			// 3. target + this->_myControlledSquares
			// 4. target + this->_enemyControlledSquares
			usedIndex.reset();
			for (int config = 0 /* var for each of the options above */; config < CONFIGURTIONS; config++)
			{
				// checking if the square around the piece is in the bounds of the board:
				if (squares[config > 1].y + dir.y < 0 || squares[config > 1].y + dir.y >= COLUMNS ||
					squares[config > 1].x + dir.x < 0 || squares[config > 1].x + dir.x >= ROWS)
				{
					continue;
				}

				if (this->_board[squares[config > 1].y + yInc][squares[config > 1].x + xInc] != nullptr)
				{
					PieceIndex = this->_board[squares[config > 1].y + yInc][squares[config > 1].x + xInc]->getIndex() + 1;

					if ((PieceIndex == ROOK_FIRST_INDEX + 1 || PieceIndex == ROOK_SECOND_INDEX + 1 ||
						PieceIndex == BISHOP_INDEX + 1 || PieceIndex == QUEEN_INDEX + 1) && myIndedx != PieceIndex - 1)
					{
						if (!usedIndex.test((((PieceIndex - 1) < 2) * (PieceIndex - 1)) + (((PieceIndex - 1) > 1) * (PieceIndex - 3)) + (config * 4 + (config * -1))))
						{
							// if the index is turnned on than checking if the piece goes in the direction of the piece 
							if (controlArrArrs[config % 2][squares[config > 1].y][squares[config > 1].x].test(PieceIndex - 1 /* explained befor why (index - 1)*/))
							{
								// if goes inside then found the piece that need to blocked or realed and reales it 

								// make the direction
								dir.reverseDirection();

								blockOrRelease(PieceIndex - 1, squares[config > 1], dir, config < 2, controlArrArrs[config % 2]);

								usedIndex.set((((PieceIndex - 1) < 2) * (PieceIndex - 1)) + (((PieceIndex - 1) > 1) * (PieceIndex - 3)) + (config * 4 - 1));
								// reseting the index 
								PieceIndex = 0;
								continue;
							}
						}
					}

					// reseting the value for the next checks:
					PieceIndex = 0;
				}


				// going in a loop and checking if the piece is was blocked and needs to be realed or now is getting blocked
				for (int indx = 1; indx <= RANGEPIECE_MAX_INDEX_PLUS_ONE; indx++)
				{
					// checking if a piece that is rook or bishop queen is controlling this square 
					// then multilpling by indx to get exact value of the (index of piece + 1) becaues the first index of the rook is represented by zero 
					// the count has to be initalized from the number 1
					// also checking if there is a piece standing there
					PieceIndex = controlArrArrs[config % 2][squares[config > 1].y + yInc][squares[config > 1].x + xInc].test(indx - 1) * indx;

					// if passed the first test and there is range controll in the square around the piece and goes into this if
					if (PieceIndex)
					{
						// if the index is turnned on than checking if the piece goes in the direction of the piece 
						if (!((((PieceIndex - 1) < 2) * (PieceIndex - 1)) + (((PieceIndex - 1) > 1) * (PieceIndex - 3)) + (config * 4 - 1)) &&
							controlArrArrs[config % 2][squares[config > 1].y][squares[config > 1].x].test(PieceIndex - 1 /* explained befor why (index - 1)*/))
						{
							// if goes inside then found the piece that need to blocked or realed and reales it 

							// make the direction
							dir.reverseDirection();
							blockOrRelease(PieceIndex - 1, squares[config > 1], dir, config < 2, controlArrArrs[config % 2]);

							usedIndex.set((((PieceIndex - 1) < 2) * (PieceIndex - 1)) + (((PieceIndex - 1) > 1) * (PieceIndex - 3)) + (config * 4 - 1));
							// reseting the index 
							PieceIndex = 0;
							break;
						}
					}

					// there aro no indexs between 2 - 3
					if ((indx - 1) == ROOK_SECOND_INDEX)
					{
						indx = BISHOP_INDEX;
					}
				}
			}
		}
	}
}



void Piece::blockOrRelease(const int& index, Square square, const PieceDirection& dir,
	const bool& onOrOff, std::bitset<NUM_OF_PIECES>** arr) const
{
	// looping through the arr in the direction and turning on piece until hitting a piece
	for (; this->_board[square.y][square.x] == nullptr && this->_square.x != square.x && this->_square.y != square.y &&
		square.y < ROWS && square.x < COLUMNS && square.y > -1 && square.x > -1; // not going out of the borders 
		square += dir)
	{
		arr[square.y][square.x][index] = onOrOff;
	}

	// if the reason the loop stopped was becaues of piece than the range piece still controlls this piece
	if (this->_board[square.y][square.x] != nullptr &&
		square.y < ROWS && square.x < COLUMNS && square.y > -1 && square.x > -1)
	{
		arr[square.y][square.x][index] = onOrOff;
	}
}


bool Piece::exposedKing(const Square& target) const
{
	PieceDirection kingPieceDis = PieceDirection(this->_square.x - this->_kingLocation->x, this->_square.y - this->_kingLocation->y);
	int xInc = (kingPieceDis.x > 0) + ((kingPieceDis.x < 0) * -1);
	int yInc = (kingPieceDis.y > 0) + ((kingPieceDis.y < 0) * -1);
	int index = 0;

	// if the piece is goign in direction that it would still protect the king than returning false
	if ((kingPieceDis.x == 0 && target.y == 0) || (kingPieceDis.y == 0 && target.x == 0))
	{
		return false;
	}

	// if the piece is not in direction that could be protecting king than just returning false
	if (abs(kingPieceDis.x) != abs(kingPieceDis.y) && kingPieceDis.y != 0 && kingPieceDis.x != 0)
	{
		return false;
	}

	// checking if there is even posible piece that could stand and pin the piece to the king
	if ((kingPieceDis.x + (2 * xInc)) < 0 || (kingPieceDis.x + (2 * xInc)) >= COLUMNS ||
		(kingPieceDis.y + (2 * yInc)) < 0 && (kingPieceDis.y + (2 * yInc)) >= ROWS)
	{
		return false;
	}

	// checking if there is range piece in front of this spot that could pin the piece:
	for (int i = 1; i < RANGEPIECE_MAX_INDEX_PLUS_ONE; i++)
	{
		index = (this->_enemyControlledSquares[(target.y + yInc)][(target.x + xInc)].test(i - 1)) * i;

		if (index)
		{
			break;
		}
	}
	if (!index)
	{
		return false;
	}

	// check if there are two controlled squares in a row from the same direction if there are not the piece is not pinned to the king
	if (!(this->_enemyControlledSquares[(kingPieceDis.y + (2 * yInc))][(kingPieceDis.x + (2 * xInc))].test(index - 1)))
	{
		return false;
	}

	return true;
}

int Piece::findCheckIndex() const
{
	int index = 0;

	for (int i = 0; i < NUM_OF_PIECES; i++)
	{
		index = this->_enemyControlledSquares[this->_kingLocation->y][this->_kingLocation->x].test(index) * i;
	}


	return index;
}


bool Piece::checkBlockingRange(const int& index, const Square& target) const
{
	PieceDirection dir = PieceDirection(0, 0);

	// finding out what is the direction that the rangePiece is attacking the king and putting this direction in dir
	for (int i = 0; i < COLUMNS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (j == 0 && i == 0)
			{
				continue;
			}

			if ((this->_kingLocation->x + j) > 0 && (this->_kingLocation->x + j) < ROWS &&
				(this->_kingLocation->y + i) > 0 && (this->_kingLocation->y + i))
			{
				// checking if the range piece that is threatening the king is in the 8 squares around it 
				if (this->_board[this->_kingLocation->y + j][this->_kingLocation->x + i]->getIndex() == index &&
					this->_board[this->_kingLocation->y + j][this->_kingLocation->x + i]->getColor() == !this->_color)
				{
					// if the taregt is eating the piece then returning true:
					if (target.x == (this->_kingLocation->x + i) && target.y == (this->_kingLocation->y + i))
					{
						return true;
					}

					return false;
				}

				// checking if this square that is around the king also controlled by the same piece that controlls the 
				// square that the king stands in and  if it is than can calculte the direction 
				if (this->_enemyControlledSquares[this->_kingLocation->y + i][this->_kingLocation->x + j].test(index))
				{
					dir.cangeValues(j, i);
					break;
				}
			}
		}
	}

	// checking untill giting a piece beacause of the way we checked things it has to be the range piece with th index that we got
	for (; this->_board[this->_kingLocation->y + dir.y][this->_kingLocation->x + dir.y] == nullptr;
		dir.x += (dir.x > 0) + ((dir.x < 0) * -1),
		dir.y += (dir.y > 0) + ((dir.y < 0) * -1))
	{
		if ((this->_kingLocation->y + dir.y) == target.y && (this->_kingLocation->x + dir.x) == target.x)
		{
			return true;
		}
	}

	// TODO: MAKE sure that the value of dir is realy holding the distance from the king and land exacly on where the range piece
	if ((this->_kingLocation->y + dir.y) == target.y && (this->_kingLocation->x + dir.x) == target.x)
	{
		return true;
	}

	return false;
}

bool Piece::checkEatPawn(const int& index, const Square& target) const
{
	int yInc = ((this->_color == WHITE) * -1) + (this->_color == BLACK);
	int xInc = 0;

	for (int i = 0; i < 2; i++)
	{
		xInc = ((i == 0) * -1) + (i == 1);
		// only checking x not possible that y is going out of the boundreies
		// checking if the x is going out of the boundreis:
		if (this->_kingLocation->x + xInc < 0 || this->_kingLocation->x + xInc >= COLUMNS)
		{
			continue;
		}

		// incase the board is empty:
		if (this->_board[this->_kingLocation->y + yInc][this->_kingLocation->x + xInc] == nullptr)
		{
			continue;
		}

		// checking if the pawn is checking the king 
		if (this->_board[this->_kingLocation->y + yInc][this->_kingLocation->x + xInc]->getIndex() == index &&
			this->_board[this->_kingLocation->y + yInc][this->_kingLocation->x + xInc]->getColor() != this->_color)
		{
			if (this->_kingLocation->x + xInc == target.x && this->_kingLocation->y + xInc == target.y)
			{
				return true;
			}

			return false;
		}
	}

	return false; // not supose to run untill here there is a bug that's why the break point
}

bool Piece::checkEatKnight(const int& index, const Square& target) const
{
	int possibleX[NUM_POSSIBILITIES] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int possibleY[NUM_POSSIBILITIES] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	// looping to find the knight location
	for (int i = 0; i < NUM_POSSIBILITIES; i++)
	{
		// if found the knight location
		if ((this->_kingLocation->x + possibleX[i]) < 0 || (this->_kingLocation->x + possibleX[i]) >= 0
			|| (this->_kingLocation->y + possibleY[i]) < 0 || (this->_kingLocation->y + possibleY[i]) >= ROWS)
		{
			continue;
		}

		if (this->_board[this->_kingLocation->y + possibleY[i]][this->_kingLocation->x + possibleX[i]] == nullptr)
		{
			continue;
		}

		if (this->_board[this->_kingLocation->y + possibleY[i]][this->_kingLocation->x + possibleX[i]]->getColor() != this->_color &&
			this->_board[this->_kingLocation->y + possibleY[i]][this->_kingLocation->x + possibleX[i]]->getIndex() != this->_color)
		{
			return true;
		}
	}
	return false;
}

bool Piece::canBlock(const Square& target) const
{
	int index = findCheckIndex();

	// what index calles what function:
	// (0 - 1), (4 - 5): checkBlockingRange
	// (2 - 3): checkEatKnight
	// (7 - 15): checkEatPawn

	//return blockCheck[((index < BISHOP_INDEX) && (index > ROOK_SECOND_INDEX)) + ((index > KING_INDEX) * 2)](index, target);
	return false;
}