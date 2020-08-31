#pragma once
#include <list>
using namespace std;

class GameObject {
protected:
	list <GameObject*>::iterator it;
public:
	virtual ~GameObject() {};
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void setItList(list <GameObject*>::iterator i) { it = i; }
	virtual list <GameObject*>::iterator GetIt() { return it; }
};