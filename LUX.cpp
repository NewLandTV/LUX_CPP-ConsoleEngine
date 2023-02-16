#include <cstring>
#include <Windows.h>
#include "LUX.h"

namespace LUX
{
	// Console
	Console::Console(const char* title, unsigned short width, unsigned short height, bool cursorVisible) : width(width), height(height)
	{
		SetTitle(title);

		// Set console width, height
		unsigned int w = 0;
		unsigned int h = 0;

		for (w = 0; width; w++)
		{
			width /= 10;
		}

		for (h = 0; height; h++)
		{
			height /= 10;
		}

		char* modeConCommand = new char[w + h + 22];

		sprintf_s(modeConCommand, 22 + w + h, "mode con cols=%d lines=%d", this->width, this->height);
		system(modeConCommand);

		delete[] modeConCommand;

		// Set cursor vislble.
		SetCursorVisible(cursorVisible);
	}

	Console::~Console()
	{
		delete[] title;
	}

	void Console::SetCursorVisible(bool value)
	{
		CONSOLE_CURSOR_INFO consoleCursorInfo;

		consoleCursorInfo.bVisible = value;
		consoleCursorInfo.dwSize = 1;

		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	}

	void Console::Gotoxy(unsigned short x, unsigned short y)
	{
		COORD position = { x, y };

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	}

	void Console::SetTitle(const char* title)
	{
		int titleLength = strlen(title) + 1;

		if (this->title != nullptr)
		{
			delete[] this->title;
		}

		this->title = new char[titleLength];

		strcpy_s(this->title, titleLength, title);

		char* titleCommand = new char[titleLength + 6];

		sprintf_s(titleCommand, titleLength + 6, "title %s", this->title);
		system(titleCommand);

		delete[] titleCommand;
	}

	// Game
	void Game::Start()
	{

	}

	void Game::Update(float deltaTime)
	{

	}

	Game::Game(Console* console) : console(console)
	{

	}

	Game::~Game()
	{

	}

	void Game::Run()
	{
		Start();

		__int64 periodFrequency = 0;
		__int64 lastTime;
		__int64 currentTime;

		QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

		float deltaTime = 0.0f;
		float timeScale = 1.0f / (float)periodFrequency;

		while (true)
		{
			Update(deltaTime);
			Sleep(1);
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

			deltaTime = (float)(currentTime - lastTime) * timeScale;
			lastTime = currentTime;
		}
	}

	// GameObject
	GameObject::GameObject(const char* name, const char* tag, bool active) : name(name), tag(tag), active(active)
	{
		position = new Vector2(Vector2::zero);
		rotation = new Quaternion(Quaternion::identity);
		scale = new Vector2(Vector2::one);
	}

	GameObject::~GameObject()
	{
		delete position;
		delete rotation;
		delete scale;
	}

	void GameObject::SetName(const char* name)
	{
		this->name = name;
	}

	void GameObject::SetTag(const char* tag)
	{
		this->tag = tag;
	}

	void GameObject::SetActive(bool active)
	{
		this->active = active;
	}

	// String
	const String String::empty = "";

	String::String() : value(0), length(0)
	{

	}

	String::String(const char* value)
	{
		length = strlen(value) + 1;

		this->value = new char[length];

		strcpy_s(this->value, length, value);
	}

	String::String(const String& string)
	{
		length = string.length;

		value = new char[length];

		strcpy_s(value, length, string.value);
	}

	String::~String()
	{
		if (value != nullptr)
		{
			delete[] value;
		}
	}

	String& String::SetValue(const char* value)
	{
		length = strlen(value) + 1;

		if (this->value != nullptr)
		{
			delete[] this->value;
		}

		this->value = new char[length];

		strcpy_s(this->value, length, value);

		return *this;
	}

	String& String::SetValue(const String& string)
	{
		length = string.length;

		if (value != nullptr)
		{
			delete[] value;
		}

		value = new char[length];

		strcpy_s(value, length, string.value);

		return *this;
	}

	bool String::operator == (const char* value)
	{
		return strcmp(this->value, value) == 0;
	}

	bool String::operator == (const String& string)
	{
		return strcmp(value, string.value) == 0;
	}

	bool String::operator != (const char* value)
	{
		return strcmp(this->value, value) != 0;
	}

	bool String::operator != (const String& string)
	{
		return strcmp(value, string.value) != 0;
	}

	void String::operator = (const char* value)
	{
		length = strlen(value) + 1;

		if (this->value != nullptr)
		{
			delete[] this->value;
		}

		this->value = new char[length];

		strcpy_s(this->value, length, value);
	}

	void String::operator = (const String& string)
	{
		length = string.length;

		if (value != nullptr)
		{
			delete[] value;
		}

		value = new char[length];

		strcpy_s(value, length, string.value);
	}

	void String::operator += (const char* value)
	{
		length += strlen(value);

		String temp = this->value;

		if (this->value != nullptr)
		{
			delete[] this->value;
		}

		this->value = new char[length];

		strcpy_s(this->value, length, temp.value);
		strcat_s(this->value, length, value);
	}

	void String::operator += (const String& string)
	{
		length += string.length;

		String temp = value;

		if (value != nullptr)
		{
			delete[] value;
		}

		value = new char[length];

		strcpy_s(value, length, temp.value);
		strcat_s(value, length, string.value);
	}

	std::istream& operator >> (std::istream& is, String& string)
	{
		char buffer[512];

		is >> buffer;

		string.SetValue(buffer);

		return is;
	}

	std::ostream& operator << (std::ostream& os, const String& string)
	{
		os << string.GetValue();

		return os;
	}

	// Vector2
	const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
	const Vector2 Vector2::right = Vector2(1.0f, 0.0f);
	const Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
	const Vector2 Vector2::up = Vector2(0.0f, 1.0f);
	const Vector2 Vector2::down = Vector2(0.0f, -1.0f);
	const Vector2 Vector2::one = Vector2(1.0f, 1.0f);

	Vector2::Vector2(float x, float y) : x(x), y(y)
	{

	}

	Vector2& Vector2::Set(float x, float y)
	{
		this->x = x;
		this->y = y;

		return *this;
	}

	Vector2& Vector2::Set(Vector2& ref)
	{
		x = ref.x;
		y = ref.y;

		return *this;
	}

	Vector2& Vector2::SetX(float x)
	{
		this->x = x;

		return *this;
	}

	Vector2& Vector2::SetY(float y)
	{
		this->y = y;

		return *this;
	}

	Vector2 Vector2::Lerp(const Vector2& s, const Vector2& e, float t)
	{
		return Vector2(s.x * (1.0f - t) + e.x * t, s.y * (1.0f - t) + e.y * t);
	}

	bool Vector2::operator == (const Vector2& ref)
	{
		return ref.x == x && ref.y == y;
	}

	bool Vector2::operator != (const Vector2& ref)
	{
		return ref.x != x || ref.y != y;
	}

	void Vector2::operator = (const Vector2& ref)
	{
		x = ref.x;
		y = ref.y;
	}

	void Vector2::operator *= (const Vector2& ref)
	{
		x *= ref.x;
		y *= ref.y;
	}

	// Quaternion
	const Quaternion Quaternion::identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{

	}

	Quaternion& Quaternion::Set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		return *this;
	}

	Quaternion& Quaternion::Set(Quaternion& ref)
	{
		x = ref.x;
		y = ref.y;
		z = ref.z;
		w = ref.w;

		return *this;
	}

	Quaternion& Quaternion::SetX(float x)
	{
		this->x = x;

		return *this;
	}

	Quaternion& Quaternion::SetY(float y)
	{
		this->y = y;

		return *this;
	}

	Quaternion& Quaternion::SetZ(float z)
	{
		this->z = z;

		return *this;
	}

	Quaternion& Quaternion::SetW(float w)
	{
		this->w = w;

		return *this;
	}

	bool Quaternion::operator == (const Quaternion& ref)
	{
		return x == ref.x && y == ref.y && z == ref.z && w == ref.w;
	}

	bool Quaternion::operator != (const Quaternion& ref)
	{
		return x != ref.x || y != ref.y || z != ref.z || w != ref.w;
	}

	void Quaternion::operator = (const Quaternion& ref)
	{
		x = ref.x;
		y = ref.y;
		z = ref.z;
		w = ref.w;
	}

	void Quaternion::operator *= (const Quaternion& ref)
	{
		x *= ref.x;
		y *= ref.y;
		z *= ref.z;
		w *= ref.w;
	}

	// Input
	bool Input::GetKeyDown(KeyCode keyCode)
	{
		return GetAsyncKeyState((int)keyCode) & 0x8000;
	}

	bool Input::GetKeyUp(KeyCode keyCode)
	{
		return !(GetAsyncKeyState((int)keyCode) & 0x8000);
	}

	// Math
	const float Math::PI = 3.14159274f;

	int Math::Abs(int n)
	{
		return n > 0 ? n : -n;
	}

	float Math::Abs(float n)
	{
		return n > 0 ? n : -n;
	}

	double Math::Abs(double n)
	{
		return n > 0 ? n : -n;
	}

	long Math::Abs(long n)
	{
		return n > 0 ? n : -n;
	}

	long long Math::Abs(long long n)
	{
		return n > 0 ? n : -n;
	}

	float Math::Lerp(float s, float e, float t)
	{
		return s * (1.0f - t) + e * t;
	}

	double Math::Lerp(double s, double e, double t)
	{
		return s * (1.0f - t) + e * t;
	}

	int Math::Max(int a, int b)
	{
		return a > b ? a : b;
	}

	float Math::Max(float a, float b)
	{
		return a > b ? a : b;
	}

	double Math::Max(double a, double b)
	{
		return a > b ? a : b;
	}

	long Math::Max(long a, long b)
	{
		return a > b ? a : b;
	}

	long long Math::Max(long long a, long long b)
	{
		return a > b ? a : b;
	}

	unsigned int Math::Max(unsigned int a, unsigned int b)
	{
		return a > b ? a : b;
	}

	unsigned long Math::Max(unsigned long a, unsigned long b)
	{
		return a > b ? a : b;
	}

	unsigned long long Math::Max(unsigned long long a, unsigned long long b)
	{
		return a > b ? a : b;
	}

	int Math::Min(int a, int b)
	{
		return a < b ? a : b;
	}

	float Math::Min(float a, float b)
	{
		return a < b ? a : b;
	}

	double Math::Min(double a, double b)
	{
		return a < b ? a : b;
	}

	long Math::Min(long a, long b)
	{
		return a < b ? a : b;
	}

	long long Math::Min(long long a, long long b)
	{
		return a < b ? a : b;
	}

	unsigned int Math::Min(unsigned int a, unsigned int b)
	{
		return a < b ? a : b;
	}

	unsigned long Math::Min(unsigned long a, unsigned long b)
	{
		return a < b ? a : b;
	}

	unsigned long long Math::Min(unsigned long long a, unsigned long long b)
	{
		return a < b ? a : b;
	}
}