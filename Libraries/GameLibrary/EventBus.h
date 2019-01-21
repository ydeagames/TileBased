#pragma once

class Event
{
public:
	Event() = default;
	virtual ~Event() = default;
};

class EventBus
{
private:
	std::unordered_multimap<std::type_index, std::function<void(Event&)>> listeners;

public:
	EventBus();
	~EventBus();

public:
	template<class T>
	void Register(const std::function<void(T&)>& listener)
	{
		listeners.insert(std::make_pair<std::type_index, std::function<void(Event&)>>(typeid(T), listener));
	}

	template<class T, class... Args>
	void Post(Args... args)
	{
		std::function<void(T&)> casted = dynamic_cast<std::function<void(T&)>>(listener);
		auto its = listeners.equal_range("apple");
		for (auto it = its.first; it != its.second; ++it)
		{
			cout << (*it).first << " " << (*it).second << endl;
			(*it).second->
		}
	}
};

