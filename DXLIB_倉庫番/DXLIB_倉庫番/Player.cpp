#include"Player.h"

Player::Player()
{
	pos.x = 50;
	pos.y = 50;

	//IDの代入
	ID = PLAYER;
}

int Player::Action(list<unique_ptr<Base>>& base)
{
	

	//キー入力
	if (CheckHitKey(KEY_INPUT_W))
	{
		pos.y--;
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		
		pos.x--;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		
		pos.x++;
	}
	else if (CheckHitKey(KEY_INPUT_S))
	{
		pos.y++;
	}

	return 0;
}

void Player::Draw()
{
	LoadGraphScreen(pos.x, pos.y, "Image\\player.png", TRUE);
}
