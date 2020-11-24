#pragma once

class iScene
{
public:
	iScene() = default;
	virtual ~iScene() = default;

	virtual void Init() = 0;
	virtual void HandleEvents(unsigned char key, bool press) = 0;
	virtual void HandleEvents(int key, bool press) = 0;
	virtual void HandleEvents(int button, int state, int x, int y) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
