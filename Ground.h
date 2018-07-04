#pragma once
#include "Geometry.h"

//地面のクラス
//ファイルなどから地面を読み込んで現在の地面の高さを返す
class Ground
{

public:
	Ground();
	~Ground();

	//現在のプレイヤー位置での 
	//「あるべき地面」の高さを返す。 
	int GetCurrentGroundY(Position2f& pos)const;
};
