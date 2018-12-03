#pragma once

class GameObject;
class Component
{
private:
	std::weak_ptr<GameObject> gameobject;

public:
	virtual ~Component() {}

public:
	void Initialize(const std::weak_ptr<GameObject>& gameobj);
	void Finalize();
	bool Initialized() const;
	std::shared_ptr<GameObject> gameObject() const;

public:
	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}
};
