

#pragma once
class RouteJudge :public IGameObject
{
public:
	RouteJudge();
	~RouteJudge();
	bool Start();
	void Update();

private:
	struct grid
	{
		int x;
		int y;
	};

	grid prevGrid;
	grid currentGrid;
};

