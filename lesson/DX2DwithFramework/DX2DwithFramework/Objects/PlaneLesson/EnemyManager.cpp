#include "Framework.h"
#include "Enemy.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	FOR_OBJ(enemies)
	{
		FOR_OBJ_P(iter.second)
		{
			delete ptrIter;
		}
	}
}

bool EnemyManager::LoadTable(std::wstring name, int level)
{
	std::wstring fileName = L"DataTable/" + name + L"_Status.tsv";
	std::ifstream file(fileName, std::ios::in);

	int columSize = 5;
	std::string buffer;

	for (int i = 0; i < columSize; i++) 
		file >> buffer;

	if (status.count(name) == 0)
	{
		status[name].resize(columSize);
		enemies[name].resize(POOL_SIZE);
		FOR_OBJ_P(enemies[name])
		{
			ptrIter = new Enemy(name);
			ptrIter->SetTarget(target);
		}
	}

	while (true)
	{
		file >> buffer; // key

		if (file.eof())
			break;

		if (std::stoi(buffer) == level)
		{
			// hp, power, speed, interval 
			file >> status[name][0] >> status[name][1] >> status[name][2] >> status[name][3];
			file.close();
			status[name][4] = 0.0f;
			return true;
		}
	}

	file.close();
	return false;
}

void EnemyManager::Update()
{
	FOR_OBJ(status)
	{
		bool flag = false;
		if (iter.second[4] < iter.second[3])
			iter.second[4] += DELTA;
		else
		{
			flag = true;
			iter.second[4] = 0.0f;
		}

		FOR_OBJ_P(enemies[iter.first])
		{
			if (flag && !ptrIter->IsActive())
			{
				ptrIter->Spawn(iter.second);
				flag = false;
			}
			else 
				ptrIter->Update();
		}
	}
}

void EnemyManager::Render()
{
	FOR_OBJ(enemies)
	{
		FOR_OBJ_P(iter.second)
		{
			ptrIter->Render();
		}
	}
}

void EnemyManager::ChangeStage(int difficulty)
{
	switch (difficulty)
	{
	case 1:
		LoadTable(L"triEnemy", 0);
		break;

	}
}

void EnemyManager::Spawn()
{
	FOR_OBJ(status)
	{
		if (iter.second[4] < iter.second[3])
			iter.second[4] += DELTA;
		else
		{
			iter.second[4] = 0.0f;
			FOR_OBJ_P(enemies[iter.first])
			{
				if (!ptrIter->IsActive())
					ptrIter->Spawn(iter.second);
			}
		}
	}

}