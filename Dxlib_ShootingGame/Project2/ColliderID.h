#pragma once
enum COLLIDE_LIST {
	PLAYER_TO_SHOT,		//プレイヤーと弾
	PLAYER_TO_ITEM,
	ENEMY_TO_SHOT,		//敵と弾
	ENEMY_TO_PLAYERSHOT,	//敵とプレイヤーの弾

	COLLIDER_MAX		//当たり判定IDの最大値(何に使うん？
};