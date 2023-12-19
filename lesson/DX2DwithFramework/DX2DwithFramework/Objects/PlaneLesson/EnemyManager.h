#pragma once

class EnemyManager : public Singleton<EnemyManager>
{
private:
	const int POOL_SIZE = 30;

private:
	friend Singleton;
	EnemyManager();
	~EnemyManager();

	bool LoadTable(std::wstring name, int level);

public:
	void Update();
	void Render();

	void ChangeStage(int difficulty);

	void Spawn();

	void SetTarget(Quad* target) { this->target = target; }

private:
	std::map<std::wstring, std::vector<class Enemy*>> enemies;
	std::map<std::wstring, std::vector<float>> status;

	Quad* target;
};