#pragma once
class GameObject
{
private:
	
public:
	GameObject() {};
	virtual ~GameObject() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
};

