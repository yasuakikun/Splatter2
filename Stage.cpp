#include "Stage.h"
#include <DxLib.h>

Stage::Stage() : readX(0)
{
	ReadFile("stage/stage1.fmf");

	stageRange.center = { (int)((header.chipW * header.mapW)), 0 };
	stageRange.size = { (int)((header.chipW * 2) * header.mapW), 0 };

	mapSize.center = { 0, 0 };
	mapSize.size = { (int)header.mapW, (int)header.mapH };
}

Stage::~Stage()
{
}

void Stage::ReadFile(const char * filePath)
{
	int h = DxLib::FileRead_open(filePath);

	//パス
	DxLib::FileRead_read(&header, sizeof(header), h);

	//配置データの読み込み
	std::vector<unsigned char> range(header.mapW * header.mapH);
	DxLib::FileRead_read(&range[0], range.size(), h);

	DxLib::FileRead_close(h);

	enemyData.resize(range.size());

	for (int y = 0; y < header.mapH; y++)
	{
		for (int x = 0; x < header.mapW; x++)
		{
			enemyData[x * header.mapH + y] = range[y * header.mapW + x];
		}
	}
}

const Rect & Stage::GetStageRange() const
{
	return stageRange;
}

const Rect & Stage::GetMapSize()
{
	return mapSize;
}

std::vector<unsigned char> Stage::GetEnemySpawnRange(int first, int last)
{
	int L = max(first / (header.chipW * 2), readX);
	int R = last / (header.chipW * 2);
	if (R <= readX)
	{
		//読み込み範囲がなかった場合読み込みなしにする
		return std::vector<unsigned char>();
	}

	auto idxL = L * header.mapH;
	auto idxR = R * header.mapH;
	auto begin = enemyData.begin() + idxL;
	auto end = enemyData.begin();

	if (idxR >= enemyData.size())
	{
		end = enemyData.end();
	}
	else
	{
		end = enemyData.begin() + idxR;
	}

	readX = R;	//読み込んだ最大Xを記録しておく

	return std::vector<unsigned char>(begin, end);
}
