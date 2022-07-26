#pragma once

#include<Windows.h>
#include<map>
#include<vector>
#include<string>
#include"IRefCount.h"
#include"VectorData.h"

class InputManager
{
private:
	InputManager();
	~InputManager();
public: // Singletone Function.
#pragma region InnerClass
private: // inner class.
	class InputData : public IRefCount
	{
	public: // 생성자.
		InputData(size_t _size) : isUp(false), isUnPressed(true), isDown(false), isPressed(false)
		{
			m_key.reserve(_size);
		}
		~InputData() {}
	private: // friend
		friend InputManager;
	private: // private data.
		std::vector<int> m_key;
		float PressedTime;
		bool isUp;
		bool isUnPressed;
		bool isDown;
		bool isPressed;

	public: // public function.
		void Update();

	private: // private function.
		bool AllKeyCheck();

	public: // public Template Function.
		template<class ... Rest>
		void PushKeyData(const int _value, Rest... _arg)
		{
			m_key.push_back(_value);
			PushKeyData(_arg...);
		}
	private:
		// 템플릿 가변인자를 사용한 재귀함수 종료를 위한 함수.
		void PushKeyData() {}
	};
#pragma endregion

private:
	static std::map<std::wstring, SPTR<InputData>>::iterator Start;
	static std::map<std::wstring, SPTR<InputData>>::iterator End;
	static std::map<std::wstring, SPTR<InputData>> m_InputData;

	static Vector2i m_MousePos;
	static float m_zDelta;

public:
	static InputData* FindNode(const wchar_t* _keyName)
	{
		std::map<std::wstring, SPTR<InputData>>::iterator FindIter = m_InputData.find(_keyName);

		if (FindIter == m_InputData.end())
		{
			return nullptr;
		}
		return FindIter->second.Get();
	}
	static bool IsUp(const wchar_t* _keyName);
	static bool IsDown(const wchar_t* _keyName);
	static bool IsUnPressed(const wchar_t* _keyName);
	static bool IsPressed(const wchar_t* _keyName);
	static float GetMouseWHeel();

	static void MouseUpdate();
	static Vector2i GetMousePos();
	static void SetMouseWHeel(float _zdelta);


private:
	friend class MainWindow;
	static void Update();
	static void Clear();

public: // public template Function.
	template<class ... Rest>
	static bool CreateKey(const wchar_t* _keyName, Rest... _arg)
	{
		InputData* pNewKey = FindNode(_keyName);

		if (pNewKey)
		{
			return false;
		}
		pNewKey = new InputData(sizeof...(Rest));
		pNewKey->PushKeyData(_arg...);
		m_InputData.insert(std::map<std::wstring, InputData*>::value_type(_keyName, pNewKey));
		return true;
	}
};

