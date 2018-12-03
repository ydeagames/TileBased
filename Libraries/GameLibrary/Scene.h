#pragma once

// <シーン>
class Scene
{
public:
	static constexpr int MAX_LAYERS = 32;

public:
	std::unordered_multimap<std::string, std::shared_ptr<GameObject>> objects;
	std::unordered_multimap<std::string, std::weak_ptr<GameObject>> tags;
	std::vector<std::weak_ptr<GameObject>> layers[MAX_LAYERS];

public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	void Update();
	void Render();
};
