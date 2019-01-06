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

	// ����
	void Consume() const;

	// ������Ă��邩
	bool GetButton() const;

	// �����ꂽ��
	bool GetButtonDown() const;

	// �����ꂽ��
	bool GetButtonUp() const;
};

// <���̓f�o�C�X>
class Input : public std::enable_shared_from_this<Input>
{
public:
	Input();

	virtual ~Input();

	// �X�V
	virtual void Update() = 0;

	// ����
	virtual void Consume(int button) = 0;

	// �{�^���n���h��
	InputButton GetInputButton(int button);

	// ������Ă��邩
	virtual bool GetButton(int button) = 0;

	// �����ꂽ��
	virtual bool GetButtonDown(int button) = 0;

	// �����ꂽ��
	virtual bool GetButtonUp(int button) = 0;
};

// <�{�^�����̓f�o�C�X>
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

// <�W���C�p�b�h���̓f�o�C�X>
class JoypadInput final : public ButtonInput
{
private:
	// �W���C�p�b�h�̎��ʎq
	int pad_id;

public:
	JoypadInput(int pad_id = DX_INPUT_KEY_PAD1);

	~JoypadInput();

	void Update() override;
};

// <�}�E�X���̓f�o�C�X>
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

	// �}�E�X�����W���擾
	const Vector2& GetPosition();

	// �}�E�X�����W��ݒ�
	void SetPosition(const Vector2& pos);

	// �}�E�X�̉�]�ʂ��擾
	float GetWheel();

	// �}�E�X�̉�]�ʂ̍����擾
	float GetDeltaWheel();
};

// <�L�[���̓f�o�C�X>
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

// <���̓f�o�C�X�}�l�[�W��>
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
