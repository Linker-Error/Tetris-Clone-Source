#include "raylib.h"
#ifndef TETRIS_HEADER
#define TETRIS_HEADER


//Structures and enum types
struct PIECE
{
	int rotation1[4][4];
	int rotation2[4][4];
	int rotation3[4][4];
	int rotation4[4][4];
};



struct GRID
{
	int grid[10][20];
	struct PIECE* CurrentPiece;
};

typedef enum { Rotate, MoveLeft, MoveRight, None }Move;





//GridDraw.c Function Declarations
void CopyPiece(int piece1[4][4], int piece2[4][4]);
void FlushGrid(struct GRID* Grid);
void DrawGameGrid(Texture2D EmptyTile, Texture2D BlockTile, struct GRID Grid);
int AddPiece(struct GRID* Grid, struct PIECE* Piece, int Rotation, int locationX, int locationY);
void RemovePiece(struct GRID* Grid, struct PIECE* Piece, int Rotation, int locationX, int locationY);
int CheckPiece(int Piece[4][4], int locationX, int locationY);
int AddPieceAndSet(struct GRID* Grid, struct PIECE* Piece, int Rotation, int locationX, int locationY);
int CheckGrid(struct GRID grid);
void ClearLines(struct GRID* Grid, Sound LineClearSound, Sound GroundHitSound, int *score);
int CheckGameOver(struct GRID Grid);


#endif