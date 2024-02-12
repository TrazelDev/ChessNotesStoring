#include "Board.h"
#include <iostream>

namespace chessBackend
{
    Board::Board()
    {
        this->_turn = WHITE;
        putPiecesOnBoard();

    #ifdef _DEBUG
        std::cout << "the _whiteControlledSquares arr: " << std::endl;
        debug::printArrs(this->_whiteControlledSquares);

        std::cout << "the _blackControlledSquares arr: " << std::endl;
        debug::printArrs(this->_blackControlledSquares);
    #endif 
    }
    
    void Board::tryMove(std::string& move)
    {
        Square thisSquare = Square(move[0] - 97, COLUMNS - (move[1] - 48));
        Square target = Square(move[2] - 97, COLUMNS - (move[3] - 48));

        if (this->_board[thisSquare.y][thisSquare.x] == nullptr)
        {
            throw(NOT_SRC_PIECE);
            return;
        }
        
        if (this->_board[thisSquare.y][thisSquare.x]->getColor() != this->_turn)
        {
            throw(NOT_SRC_PIECE);
            return;
        }

        if (this->_board[thisSquare.y][thisSquare.x]->checkMove(target))
        {
            movePiece(target, thisSquare);

            this->_turn = !this->_turn;
            #ifdef _DEBUG
            std::cout << "\n\n\nthe _whiteControlledSquares arr: " << std::endl;
            debug::printArrs(this->_whiteControlledSquares);
            
            std::cout << "\n\n\nthe _whiteControlledSquares this piece: " << std::endl;
            debug::printaArrIndex(this->_whiteControlledSquares, this->_board[target.y][target.x]->getIndex());

            std::cout << "the _blackControlledSquares arr: " << std::endl;
            debug::printArrs(this->_blackControlledSquares);

            std::cout << "the _blackControlledSquares arr: " << std::endl;
            debug::printaArrIndex(this->_blackControlledSquares, this->_board[target.y][target.x]->getIndex());
            #endif 

            throw(LEGAL);
        }
    }
    
    void Board::putPiecesOnBoard()
    {
       this->_board = new Piece**[ROWS];
       std::bitset<NUM_OF_PIECES>*** arrControls[2] = { &this->_whiteControlledSquares, &this->_blackControlledSquares };

       this->_whiteControlledSquares = new std::bitset<NUM_OF_PIECES>*[ROWS];
       this->_blackControlledSquares = new std::bitset<NUM_OF_PIECES>*[ROWS];
       
       for (int i = 0; i < ROWS; i++)
       {
           this->_whiteControlledSquares[i] = new std::bitset<NUM_OF_PIECES>[COLUMNS];
           this->_blackControlledSquares[i] = new std::bitset<NUM_OF_PIECES>[COLUMNS];
           for (int j = 0; j < COLUMNS; j++)
           {
                this->_whiteControlledSquares[i][j].reset();
                this->_blackControlledSquares[i][j].reset();
           }
       }

        // delte memory later:
        Square* whiteKing = new Square(0, 0);
        Square* blackKing = new Square(0, 0);
        Square* kingLocation[2] = { blackKing, whiteKing };
        const char pieceString[NUM_PIECES * 2] = "rnbkqbnrpppppppppppppppprnbkqbnr";
        int countPiece = 0;
        int i = 0;
        int j = 0;
        
        for (int i = 0; i < ROWS; i++)
        {
            this->_board[i] = new Piece*[COLUMNS];
            if (i == 0 || i == ROWS - 1)
            {
                this->_board[i][3] = new King(j, i, (i > HALF_BOARD), _board, *arrControls[i < HALF_BOARD], *arrControls[i > HALF_BOARD], &kingLocation[(i < HALF_BOARD)]);
            }
        }

        for (i = 0; i < ROWS; i++)
        {
            if (i > 1 && i < BET_NO_PIECES)
            {
                for (j = 0; j < COLUMNS; j++)
                {
                    this->_board[i][j] = nullptr;
                }
                continue;
            }
            
            for (j = 0; j < COLUMNS; j++)
            {
                switch (pieceString[countPiece])
                {
                case 'r':
                    this->_board[i][j] = new Rook(j, i, (i > HALF_BOARD), _board, *arrControls[i < HALF_BOARD], *arrControls[i > HALF_BOARD], kingLocation[(i < HALF_BOARD)]);
                    break;
                case 'n':
                    this->_board[i][j] = new Knight(j, i, (i > HALF_BOARD), _board, *arrControls[i < HALF_BOARD], *arrControls[i > HALF_BOARD], kingLocation[(i < HALF_BOARD)]);
                    break;                                                                                        
                case 'b':                                                                                         
                    this->_board[i][j] = new Bishop(j, i, (i > HALF_BOARD), _board, *arrControls[i < HALF_BOARD], *arrControls[i > HALF_BOARD], kingLocation[(i < HALF_BOARD)]);
                    break;                                                                                        
                case 'q':                                                                                         
                    this->_board[i][j] = new Queen(j, i, (i > HALF_BOARD), _board, *arrControls[i < HALF_BOARD], *arrControls[i > HALF_BOARD], kingLocation[(i < HALF_BOARD)]);
                    break;                                                                                        
                case 'p':                                                                                         
                    this->_board[i][j] = new Pawn(j, i, (i > HALF_BOARD), _board, *arrControls[i < HALF_BOARD], *arrControls[i > HALF_BOARD], kingLocation[(i < HALF_BOARD)]);
                    break;
                case 'k':
                    break;
                }
                countPiece++;
            }
        }
    }

    void Board::movePiece(const Square& target, const Square& thisSquare)
    {
        // if there is piece in there then delting the memory for it:
        if (this->_board[target.y][target.x] != nullptr)
        {
            delete this->_board[target.y][target.x];
        }
        
        //physicaly moving the piece in the board:
        this->_board[target.y][target.x] = this->_board[thisSquare.y][thisSquare.x];
        
        // updating the arrays of the controll:
        this->_board[target.y][target.x]->updateOtherSquares(target, this->_board[target.y][target.x]->getIndex());
        this->_board[target.y][target.x]->updateThisPieceSquares(target);

        this->_board[thisSquare.y][thisSquare.x] = nullptr;

        // updating the x and y of the piece in its properties:
        this->_board[target.y][target.x]->setSquare(target);
    }
}
