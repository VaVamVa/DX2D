#pragma once

class Environment : public Singleton<Environment>
{
private:
	friend Singleton;
	Environment();
	~Environment();

private:
	void SetViewport();
	void SetProjection();

private:
	MatrixBuffer* viewBuffer;
	MatrixBuffer* projectionBuffer;
};