#pragma once

class GameObject : public Transform
{
public:
	GameObject(int depth = 0.0f);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;

	int GetDepth() { return depth; }
	void SetDetph(int depth) { this->depth = depth; }

	void SetPS(wstring file);

	static int CompareObject(GameObject* obj1, GameObject* obj2)
	{
		return obj1->GetDepth() < obj2->GetDepth();
	}

protected:
	int depth = 0;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
};