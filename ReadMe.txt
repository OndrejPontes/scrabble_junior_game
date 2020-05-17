The Scrabble Junior Game consists of two sub-programs: BoardBuilder and ScrabbleJunior, in which all objectives have been accomplished. 
The first part is BoardBuilder, which sets the board and the other part - ScrabbleJunior let us  play the game.

The code itself contains all comments needed to understand specific functions.

Program "Board Builder": 
- allows select the size of the game board with maximum 20x20
- user can adds words from WORDS.TXT by specifying the position of the first letter and orientation
- to save the content of the board to a text file with the file name that the user chooses ( format of the board file based on the rules)
- 2D view of the board was also added at the end of the file that user decided to save

Program "Scrabble Junior":
- starts with asking for number of players (2-4) and name of the board
- game board can be either default or previously created in BoardBuilder
- board is shown based on the example 
- program contains controls for entering invalid letter or positions of the board
- the game ends with the announcement of the winner

