#include "raylib.h"
#include "tetris.h"

int CheckGameOver(struct GRID Grid)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 20; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			if (Grid.grid[j][i] >= 1 && (i < 4))
				return 1;
		}
	}
	return 0;
}

int CheckGrid(struct GRID grid)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 20; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			if (grid.grid[j][i] > 1)
				return 1;
		}
	}
	return 0;
};


int CheckPiece(int Piece[4][4], int locationX, int locationY)
{
	int i;
	int j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			if (Piece[i][j] >= 1 && locationX + i < 0)
				return 1;
			else if (Piece[i][j] >= 1 && locationX + i > 9)
				return 2;
			else if (Piece[i][j] >= 1 && locationY + j > 19)
				return 3;
		}
	}
	return 0;
}

void CopyPiece(int piece1[4][4], int piece2[4][4])
{
	int i = 0;
	int j = 0;

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			piece1[i][j] = piece2[j][i];
		}
	}
}

int AddPiece(struct GRID* Grid, struct PIECE* Piece, int Rotation, int locationX, int locationY)
{
	int i = 0;
	int j = 0;
	int usedrotation[4][4];
	switch (Rotation % 4)
	{
		case 0:
			CopyPiece(usedrotation, Piece->rotation4);
			break;
		case 1:
			CopyPiece(usedrotation, Piece->rotation1);
			break;
		case 2:
			CopyPiece(usedrotation, Piece->rotation2);
			break;
		case 3:
			CopyPiece(usedrotation, Piece->rotation3);
			break;
	}
	Grid->CurrentPiece = Piece;
	if (CheckPiece(usedrotation, locationX, locationY) == 0)
	{

		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 4; ++j)
			{
				if (usedrotation[i][j] == 1)
					Grid->grid[i + locationX][j + locationY] += 1;

			}
		}
		if (CheckGrid(*Grid) == 1)
		{
			return 4;
		}
		return 0;
	}
	else
	{
		return CheckPiece(usedrotation, locationX, locationY);
	}
}

int AddPieceAndSet(struct GRID* Grid, struct PIECE* Piece, int Rotation, int locationX, int locationY)
{
	int i = 0;
	int j = 0;
	int usedrotation[4][4];
	switch (Rotation % 4)
	{
	case 0:
		CopyPiece(usedrotation, Piece->rotation4);
		break;
	case 1:
		CopyPiece(usedrotation, Piece->rotation1);
		break;
	case 2:
		CopyPiece(usedrotation, Piece->rotation2);
		break;
	case 3:
		CopyPiece(usedrotation, Piece->rotation3);
		break;
	}
	Grid->CurrentPiece = Piece;
	if (CheckPiece(usedrotation, locationX, locationY) == 0)
	{

		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 4; ++j)
			{
				if (usedrotation[i][j] == 1)
					Grid->grid[i + locationX][j + locationY] = 1;

			}
		}
		return 0;
	}
	else
	{
		return CheckPiece(usedrotation, locationX, locationY);
	}
}

void RemovePiece(struct GRID* Grid, struct PIECE* Piece, int Rotation, int locationX, int locationY)
{
	int usedrotation[4][4];
	switch (Rotation % 4)
	{
	case 0:
		CopyPiece(usedrotation, Piece->rotation4);
		break;
	case 1:
		CopyPiece(usedrotation, Piece->rotation1);
		break;
	case 2:
		CopyPiece(usedrotation, Piece->rotation2);
		break;
	case 3:
		CopyPiece(usedrotation, Piece->rotation3);
		break;
	}
	Grid->CurrentPiece = Piece;
	int i = 0;
	int j = 0;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			if (usedrotation[i][j] >= 1)
				Grid->grid[i + locationX][j + locationY] -= 1;

		}
	}
}

void FlushGrid(struct GRID* Grid)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 20; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			Grid->grid[j][i] = 0;
		}
	}
}

void DrawGameGrid(Texture2D EmptyTile, Texture2D BlockTile, struct GRID Grid)
{
	int i = 0;
	int j = 0;
	
	for (i = 0; i < 20; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			if (Grid.grid[j][i] == 0)
			{
				DrawTextureEx(EmptyTile, (Vector2) { j * 40, i * 40 }, 0, 5, WHITE);
			}
			else if (Grid.grid[j][i] >= 1)
			{
				DrawTextureEx(BlockTile, (Vector2) { j * 40, i * 40 }, 0, 5, WHITE);
			}
			//Just in case I need it! :)
			//DrawText(TextFormat("%d", Grid.grid[j][i]), j * 40, i * 40, 24, GREEN);
		}
		
		DrawRectangle(0, 0, 400, 160, BLACK);

	}
}

void ClearLines(struct GRID* Grid, Sound LineClearSound, Sound GroundHitSound, int *score)
{
	bool LineCleared = false;
	int RowsFull[20] = { 0 };
	int i = 0;
	int j = 0;
	int k = 0;
	int TilesInRow = 0;
	int ScoreAdd = 0;
	for (i = 0; i < 20; ++i)
	{
		TilesInRow = 0;
		for (j = 0; j < 10; ++j)
		{
			if (Grid->grid[j][i] == 1)
			{
				TilesInRow++;
			}
		}
		if (TilesInRow == 10)
		{
			RowsFull[i] = 1;
		}
	}
	for (i = 0; i < 20; ++i)
	{
		if (RowsFull[i] == 1)
		{
			for (j = 0; j < 10; ++j)
			{
				for (k = i; k > 0; --k)
				{
					Grid->grid[j][k] = Grid->grid[j][k - 1];
				}
			}
			LineCleared = true;
			ScoreAdd++;
		}
	}

	if (LineCleared == true)
		PlaySound(LineClearSound);
	else
		PlaySound(GroundHitSound);
	*score += ScoreAdd;
}