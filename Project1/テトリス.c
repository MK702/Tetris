
//A�ō��AD�ŉE�AS�ŉ��Ɉړ��A���̑��̃L�[�ŉ�]���܂�


#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define FIELD_WIDTH		(10)
#define FIELD_HEIGHT	(20)

#define BLOCK_WIDTH		(4)
#define BLOCK_HEIGHT	(4)

#define FPS				(1)
#define INTERVAL		(1000/FPS)


typedef struct
{
	int width, height;
	int pattern[BLOCK_HEIGHT][BLOCK_WIDTH];

}BLOCK;

typedef struct
{
	int x, y;
	BLOCK block;

}MINO;


//�e�g���~�m�̌`����`
BLOCK blocks[8] = {
	//BLOCK_I
	{
		4,4,
		{
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}

		}
	},

	//BLOCK_O
	{
		2,2,
		{
			{1,1},
			{1,1}

		}
	},

	//BLOCK_S
	{
		3,3,
		{
			{0,1,1},
			{1,1,0},
			{0,0,0}


		}
	},

	//BLOCK_Z
	{
		3,3,
		{
			{1,1,0},
			{0,1,1},
			{0,0,0}

		}
	},

	//BLOCK_J
	{
		3,3,
		{
			{1,0,0},
			{1,1,1},
			{0,0,0}

		}
	},

	//BLOCK_L
	{
		3,3,
		{
			{0,0,1},
			{1,1,1},
			{0,0,0}

		}
	},

	//BLOCK_T
	{
		3,3,
		{
			{0,1,0},
			{1,1,1},
			{0,0,0}

		}
	},


};

int field[FIELD_HEIGHT][FIELD_WIDTH];
int screen[FIELD_HEIGHT][FIELD_WIDTH];



MINO mino;

//�e�g���~�m�̏Փ˔���
bool Collision() {
	for (int y = 0; y < mino.block.height; y++)
	{
		for (int x = 0; x < mino.block.width; x++)
		{
			if (mino.block.pattern[y][x])
			{
				if ((mino.y + y < 0) || (mino.y + y >= FIELD_HEIGHT) || (mino.x + x < 0) || (mino.x + x >= FIELD_WIDTH))
				{
					return true;
				}

				if (field[mino.y + y][mino.x + x])return true;

			}

		}
	}
	return false;
}


//�Q�[����ʂ̕`��
void DrawField()
{
	memcpy(screen, field, sizeof field);

	for (int y = 0; y < mino.block.height; y++)
	{
		for (int x = 0; x < mino.block.width; x++)
		{

			if (mino.block.pattern[y][x])
			{
				if (screen[mino.y + y][mino.x + x] == 0)
				{
					screen[mino.y + y][mino.x + x] = 1;
				}
			}
		}

	}

	system("cls");

	for (int j = 0; j < FIELD_HEIGHT; j++)
	{
		printf("��");

		for (int i = 0; i < FIELD_WIDTH; i++)
		{
			printf("%s", screen[j][i] ? "��" : "  ");//�e�g���~�m��`��
		}
		printf("��");
		printf("\n");
	}
	for (int i = 0; i < FIELD_WIDTH + 2; i++)
	{
		printf("��");
	}
}

//�V�����e�g���~�m�̐���
void InitMino()
{
	mino.block = blocks[rand() % 7]; //�e�g���~�m�̌`�󌈒�

	//�e�g���~�m�̏����ʒu
	mino.x = (FIELD_WIDTH - mino.block.width) / 2;
	mino.y = 0;
}


void Init() {
	memset(field, 0, sizeof field);

	InitMino();

	DrawField();
}

int main()
{
	srand((unsigned int)time(NULL));//��������

	Init();
	clock_t lastClock = clock();

	while (1)
	{
		//���Ԍo�߂ɂ�藎��������
		clock_t nowClock = clock();
		if (nowClock >= lastClock + INTERVAL)
		{
			lastClock = nowClock;

			MINO lastMino = mino;
			mino.y++;
			if (Collision())
			{
				mino = lastMino;

				for (int y = 0; y < mino.block.height; y++)
				{
					for (int x = 0; x < mino.block.width; x++)
					{
						if (mino.block.pattern[y][x])
						{
							field[mino.y + y][mino.x + x] |= 1;
						}

					}
				}

				for (int y = 0; y < FIELD_HEIGHT; y++)
				{
					bool completed = true;
					for (int x = 0; x < FIELD_WIDTH; x++)
					{
						if (!field[y][x])
						{
							completed = false;
							break;
						}
					}

					if (completed)
					{
						for (int x = 0; x < FIELD_WIDTH; x++)
						{
							field[y][x] = 0;
						}

						for (int y2 = y; y2 >= 1; y2--)
						{
							for (int x = 0; x < FIELD_WIDTH; x++)
							{
								field[y2][x] = field[y2 - 1][x];
								field[y2 - 1][x] = 0;
							}
						}
					}

				}

				InitMino();

				if (Collision())
				{
					system("cls");
					printf("GAME OVER");
					_getch();
					Init();// �Q�[�������Z�b�g����
				}
			}
			DrawField();
		}

		//�L�[�{�[�h�ő���o����悤�ɂ���
		if (_kbhit())
		{
			MINO lastMino = mino;
			switch (_getch())
			{
			case 'w':
				break;
			case 's':
				mino.y++;
				break;
			case 'a':
				mino.x--;
				break;
			case 'd':
				mino.x++;
				break;

				//�e�g���~�m�̉�]
			default:
			{
				MINO newMino = mino;
				for (int y = 0; y < mino.block.height; y++)
				{
					for (int x = 0; x < mino.block.width; x++)
					{
						newMino.block.pattern[mino.block.width - 1 - x][y] = mino.block.pattern[y][x];


					}
				}
				mino = newMino;
			}

			}

			//�~�m���ǂƐڐG������O�̏�Ԃ�ێ�
			if (Collision())
			{
				mino = lastMino;

			}

			DrawField();
		}
	}


}


