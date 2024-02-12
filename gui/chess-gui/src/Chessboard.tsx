import React, { Component } from 'react';
import './Chessboard.css';
import InputTaker from './inputTaker.tsx';
interface ChessboardState 
{
  chessboard: string[][];
  previousCoordinates: (number)[];
  note: string;
}


class Chessboard extends Component<{}, ChessboardState> {

  constructor(props: {}) 
  {
    super(props);

    this.state = 
    {
      chessboard: 
      [
        ['R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'],
        ['P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'],
        Array(8).fill(null),
        Array(8).fill(null),
        Array(8).fill(null),
        Array(8).fill(null),
        ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
        ['r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'],
      ],
      previousCoordinates: [-1, -1],
      note: '', 
    };
  }

  updateBoard = (rowIndex: number , cellIndex: number ) => 
  {
    const { previousCoordinates } = this.state;
    
    // checks if this is the first time that the user clicks on a square:
    if(previousCoordinates[0] === -1)
    {
      this.setState({previousCoordinates : [rowIndex, cellIndex]});
      return;
    }
    
    // in the case that the same square has been pressed:
    if (previousCoordinates[0] === rowIndex && previousCoordinates[1] === cellIndex) 
    {
      return;
    }


    const newChessBoard = [...this.state.chessboard];
    newChessBoard[rowIndex][cellIndex] = newChessBoard[previousCoordinates[0]][previousCoordinates[1]];
    newChessBoard[previousCoordinates[0]][previousCoordinates[1]] = ' ';
    this.setState({chessboard: newChessBoard})
    this.setState({previousCoordinates : [-1, -1]});

    console.log(`Clicked on square: ${rowIndex} - ${cellIndex}`);
  };

  
  handleInputChange = (value : string) => {
    this.setState({note: value});
    };

  render()
  {
    const { chessboard, note } = this.state;
    return (
      <div className="chessboard">
        <div>
            {chessboard.map((row: any[], rowIndex: number) => 
            (
            <div className="chessboard-row" key={rowIndex}>
              {row.map((cell: any, cellIndex: number) => 
              (
                <div
                  className={(rowIndex + cellIndex) % 2 === 0 ? 'white-cell' : 'black-cell'}
                  key={cellIndex}
                  onClick={() => this.updateBoard(rowIndex, cellIndex)}
                >
                  {chessboard[rowIndex][cellIndex] ? (
                    <div className="chess-piece">{chessboard[rowIndex][cellIndex]}</div>
                  ) : null}
                </div>
              )
              )}
            </div>
          )
          )}
        </div>
        <div>
          <InputTaker
              inputText="enter your note:"
              inputType="Text"
              inputValue={note}
              inputValueFunction={(value) => this.handleInputChange(value)}
            />
        </div>
    </div>
    )
  }
}

export default Chessboard;
