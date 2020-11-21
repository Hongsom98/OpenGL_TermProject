#pragma once

class iScene
{
public:
	iScene() = default;
	virtual ~iScene() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destory() = 0;
};