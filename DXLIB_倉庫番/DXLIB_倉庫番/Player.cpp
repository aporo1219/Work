#include"Player.h"

Player::Player()
{
	pos.x = 50;
	pos.y = 50;

	//IDÇÃë„ì¸
	ID = PLAYER;
}

int Player::Action(list<unique_ptr<Base>>& base)
{
	

	//ÉLÅ[ì¸óÕ
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
