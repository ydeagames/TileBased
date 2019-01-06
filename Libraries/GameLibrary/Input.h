#pragma once
#include "Singleton.h"

class Input;

class InputButton final
{
private:
	std::shared_ptr<Input> input;
	int button;

public:
	InputButton(std::shared_ptr<Input> input, int button);

	// 消費
	void Consume() const;

	// 押されているか
	bool GetButton() const;

	// 押されたか
	bool GetButtonDown() const;

	// 離されたか
	bool GetButtonUp() const;
};

// <入力デバイス>
class Input : public std::enable_shared_from_this<Input>
{
public:
	Input();

	virtual ~Input();

	// 更新
	virtual void Update() = 0;

	// 消費
	virtual void Consume(int button) = 0;

	// ボタンハンドラ
	InputButton GetInputButton(int button);

	// 押されているか
	virtual bool GetButton(int button) = 0;

	// 押されたか
	virtual bool GetButtonDown(int button) = 0;

	// 離されたか
	virtual bool GetButtonUp(int button) = 0;
};

// <ボタン入力デバイス>
class ButtonInput : public Input
{
protected:
	int input_state;
	int input_state_last;

public:
	ButtonInput();

	virtual ~ButtonInput();

	void Consume(int button) override;

	bool GetButton(int button) override;

	bool GetButtonDown(int button) override;

	bool GetButtonUp(int button) override;
};

// <ジョイパッド入力デバイス>
class JoypadInput final : public ButtonInput
{
private:
	// ジョイパッドの識別子
	int pad_id;

public:
	JoypadInput(int pad_id = DX_INPUT_KEY_PAD1);

	~JoypadInput();

	void Update() override;
};

// <マウス入力デバイス>
class MouseInput final : public ButtonInput
{
private:
	Vector2 position;
	float wheel_pos;
	float wheel_delta;

public:
	MouseInput();

	~MouseInput();

	void Update() override;

	// マウスを座標を取得
	const Vector2& GetPosition();

	// マウスを座標を設定
	void SetPosition(const Vector2& pos);

	// マウスの回転量を取得
	float GetWheel();

	// マウスの回転量の差を取得
	float GetDeltaWheel();
};

// <キー入力デバイス>
class KeyInput final : public Input
{
private:
	char input_state[256];
	char input_state_last[256];

public:
	KeyInput();

	virtual ~KeyInput();

	void Update() override;

	void Consume(int button) override;

	bool GetButton(int button) override;

	bool GetButtonDown(int button) override;

	bool GetButtonUp(int button) override;
};

// <入力デバイスマネージャ>
class InputManager final : public Singleton<InputManager>
{
private:
	std::unordered_map<std::string, std::shared_ptr<Input>> inputsname;
	std::unordered_map<std::type_index, std::string> inputstype;

public:
	std::shared_ptr<JoypadInput> joypad;
	std::shared_ptr<MouseInput> mouse;
	std::shared_ptr<KeyInput> key;

private:
	InputManager();
	friend class Singleton<InputManager>;

public:
	template<class T> std::shared_ptr<T> Register(const std::string& name, const std::shared_ptr<T> input)
	{
		inputsname[name] = input;
		if (inputstype.count(typeid(T)) <= 0)
			inputstype[typeid(T)] = name;
		return input;
	}

	inline void Unregister(const std::string& name)
	{
		inputsname.erase(name);
	}

	template<class T> std::shared_ptr<T> GetInput(const std::string& name)
	{
		return std::dynamic_pointer_cast<T, Input>(inputsname[name]);
	}

	template<class T> std::shared_ptr<T> GetInput()
	{
		return GetInput<T>(inputstype[typeid(T)]);
	}

	void Update();
};
