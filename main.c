#include "raylib.h"
#include "tetris.h"

static const WindowHeight = 800, WindowWidth = 1200;


//Please report bugs on GitHub, and forgive the serious spaghetti code!







int Game()
{
	struct GRID GameGrid;
	struct GRID* GameGridPointer = &GameGrid;



	Music BackgroundMusic = LoadMusicStream("resources/ambient.ogg");
	Sound rotateSound = LoadSound("resources/rotate.wav");
	Sound lineClearSound = LoadSound("resources/ClearLine.wav");
	Sound groundHitSound = LoadSound("resources/PieceHitsGround.wav");

	Texture2D EmptyTile = LoadTexture("resources/empty_tile.png");
	Texture2D BlockTile = LoadTexture("resources/block_tile.png");

	int level = 1;
	int score = 0;
	int rotation = 1;
	int pieceX = 0;
	int LastKey;
	int PieceStatus = -1;
	unsigned int Ticks = 0;
	int pieceY = 0;
	int LastX = 0;
	int LastY = 0;
	int LastRotation = 1;
	bool JumpToBottom = false;
	bool GameOver = false;
	Move LastMove;
	LastMove = None;
	struct PIECE LONG_BOI =
	{
	{
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0 ,0}
	},

	{
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0}
	},

	{
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	}
	};

	struct PIECE HOOK_THING_1 =
	{
	{
	{1, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0 ,0}
	},

	{
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0}
	}
	};

	struct PIECE HOOK_THING_2 =
	{
	{
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{1, 0, 0, 0},
	{0, 0, 0 ,0}
	},

	{
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 0, 1, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
	}
	};

	struct PIECE T_PIECE =
	{
	{
	{0, 1, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0 ,0}
	},

	{
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
	}
	};

	struct PIECE SQUARE = 
	{
	{
	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0 ,0}
	},

	{
	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	}
	};

	struct PIECE S_PIECE_1 =
	{
	{
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0 ,0}
	},

	{
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
	}
	};


	struct PIECE S_PIECE_2 =
	{
	{
	{0, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0 ,0}
	},

	{
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{1, 0, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	},

	{
	{0, 0, 1, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
	}
	};

	struct PIECE piecearray[7] = {LONG_BOI, HOOK_THING_1, HOOK_THING_2, T_PIECE, SQUARE, S_PIECE_1, S_PIECE_2};

	FlushGrid(GameGridPointer);
	
	struct PIECE* piecepointer = &piecearray[GetRandomValue(0, 6)];

	Font sevenSegmentFont = LoadFont("resources/DSEG7.ttf");


	PlayMusicStream(BackgroundMusic);

	while(!WindowShouldClose() && !GameOver)
	{
		UpdateMusicStream(BackgroundMusic);
		BeginDrawing();
			ClearBackground(BLACK);
			
			DrawGameGrid(EmptyTile, BlockTile, GameGrid);
			if (PieceStatus == 0)
				RemovePiece(GameGridPointer, piecepointer, rotation, pieceX, pieceY);

			LastKey = GetKeyPressed();
			LastX = pieceX;
			LastY = pieceY;

			if (LastKey == KEY_UP)
			{
				LastMove = Rotate;
				LastRotation = rotation;
				rotation++;
				PlaySound(rotateSound);
				
			}
			else if (LastKey == KEY_LEFT)
			{
				LastMove = MoveLeft;
				pieceX--;
			}
			else if (LastKey == KEY_RIGHT)
			{
				LastMove = MoveRight;
				pieceX++;
			}
			else if (LastKey == KEY_SPACE)
			{
				JumpToBottom = true;
			}
			if (Ticks % (30 - level) == 0 || JumpToBottom)
			{
				pieceY++;
			}
			PieceStatus = AddPiece(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
			if (PieceStatus == 1)
			{
				pieceX++;
				PieceStatus = AddPieceAndSet(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
			}
			else if (PieceStatus == 2)
			{
				pieceX--;
				PieceStatus = AddPieceAndSet(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
			}
			else if (PieceStatus == 3)
			{
				while (PieceStatus == 3)
				{ 
					pieceY--;
					PieceStatus = AddPieceAndSet(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
				}
				
				pieceX = 0;
				pieceY = 0;

				ClearLines(GameGridPointer, lineClearSound, groundHitSound, &score);

				JumpToBottom = false;
				piecepointer = &piecearray[GetRandomValue(0, 6)];
				PieceStatus = -1;
				if (CheckGameOver(GameGrid))
				{
					GameOver = true;

				}
			}
			else if (PieceStatus == 4)
			{
				if ((LastMove == MoveLeft) || (LastMove == MoveRight))
				{
					RemovePiece(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
					pieceX = LastX;
					PieceStatus = AddPieceAndSet(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
				}
				else if (LastMove == Rotate)
				{
					RemovePiece(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
					rotation = LastRotation;
					PieceStatus = AddPieceAndSet(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
				}
				else
				{
					RemovePiece(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
					pieceY = LastY;
					PieceStatus = AddPieceAndSet(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
					pieceX = 0;
					pieceY = 0;

					ClearLines(GameGridPointer, lineClearSound, groundHitSound, &score);

					JumpToBottom = false;
					piecepointer = &piecearray[GetRandomValue(0, 6)];
					PieceStatus = -1;
				}
				if (CheckGameOver(GameGrid))
				{
					GameOver = true;

				}
			}

			if (PieceStatus > 0)
			{
				RemovePiece(GameGridPointer, piecepointer, rotation, pieceX, pieceY);
				pieceX = LastX;
				pieceY = LastY;
				if (LastMove == Rotate)
				{
					rotation = LastRotation;
				}
			}
			
			if (level == 30)
				return 2;

			DrawText("TETRIS", 0, 0, 100, WHITE);
			DrawText("By Linker-Error", 0, 100, 30, GRAY);
			DrawTextEx(sevenSegmentFont, TextFormat("SCORE: %d", score), (Vector2) { 500, 350 }, 50, 0.5, RED);
			DrawTextEx(sevenSegmentFont, TextFormat("LVL: %d", level), (Vector2) { 500, 450 }, 50, 0.5, RED);
			if (score > 0 && score % 10 == 0)
				level = ((double)score / 10) + 1;
			LastMove = None;
		EndDrawing();

		Ticks++;
		
	}


	UnloadTexture(EmptyTile);
	UnloadTexture(BlockTile);
	UnloadSound(lineClearSound);
	UnloadSound(rotateSound);
	UnloadMusicStream(BackgroundMusic);
	if (GameOver)
		return 1;
	else
		return 0;
}

int GameOverScreen()
{
	int AnimationTicks = 0;
	int offsetrange = 15;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RED);
		DrawText("GAME OVER", 300 + GetRandomValue(0 - offsetrange, offsetrange), 300 + GetRandomValue(0 - offsetrange, offsetrange), 100, WHITE);
		offsetrange = 3 * (15 - ((double)AnimationTicks + 1) / 4);
		if (offsetrange < 0)
			offsetrange = 0;
		AnimationTicks++;
		EndDrawing();
	}
	return 0;
}

int YouWinScreen()
{
	int AnimationTicks = 0;
	int offsetrange = 15;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GREEN);
		DrawText("YOU WIN!", 300 + GetRandomValue(0 - offsetrange, offsetrange), 300 + GetRandomValue(0 - offsetrange, offsetrange), 100, WHITE);
		offsetrange = 3 * (15 - ((double)AnimationTicks + 1) / 4);
		if (offsetrange < 0)
			offsetrange = 0;
		AnimationTicks++;
		EndDrawing();
	}
	return 0;
}

int main(void)
{
	InitWindow(WindowWidth, WindowHeight, "Tetris");
	InitAudioDevice();

	Sound GameOver = LoadSound("resources/GameOver.wav");
	int GameStatus;

	SetTargetFPS(60);
	GameStatus = Game();
	if (GameStatus == 0)
		CloseWindow();
	else if (GameStatus == 1)
	{
		PlaySound(GameOver);
		GameOverScreen();
		return 0;
	}
	else
	{
		YouWinScreen();
	}
}
