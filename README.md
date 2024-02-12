# Chess View

## Overview:
> [!Note]
> This project was developed while I was inexperienced with the technologies involved, and it is currently still in development.
> Additionally, the project was initially developed without using Git and was later uploaded after a certain amount of work.

The project is designed as a platform for playing chess games and uploading PGN (Portable Game Notation) files, which can be scanned as chess games. Users can annotate chess games, documenting specific errors that occur in particular positions. This allows users to review their notes about specific errors and then understand their most common mistakes.

### Goals:
- [x] Login and Sighup
- [x] Display notes
- [x] Play simple chess games ( Without rules in the future it will connected to the cpp project that checks if the move is illegal )
- [ ] Display the notes that the user created
- [ ] Store the chess games
- [ ] Connect the cpp code with the C# server to detect if the move is legal 

### Technologies used:
- TypeScript
- HTML
- CSS
- React
- vite
- Material-UI
- Protocol Buffers (a binary protocol developed by Google to optimize JSON functionality)
- C# ASP.NET Core SignalR
- MongoDB in C#
- recharts

### Design:
There is a React GUI that the user can interact with. This GUI communicates with the C# server of ASP.NET Core, which saves the currently connected users and communicates with another C# server containing the MongoDB database. (In the future, the main C# server will communicate with a CPP server to detect legal moves.)
> [!Note]
> This design is far from optimal. It was structured this way because this project was part of my training for a specific company, which had very specific requirements for the design and the technologies used.

## Dependencies:
- npm
- Visual Studio C#
- MongoDB Desktop (running on port 27017)

## Running the project:
1. Clone the project.
2. Navigate to the directory: `gui\chess-gui`.
3. Run: `npm install --legacy-peer-deps`.
4. Run: `npm audit`.
5. Run: `npm run dev`. If errors occur on the first attempt, try running `npm run dev` again.
6. Enter `chessBackendAPI`.
7. Enter the solution and configure it to run both projects together, then execute.
