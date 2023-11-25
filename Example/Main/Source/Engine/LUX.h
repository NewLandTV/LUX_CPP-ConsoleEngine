#ifndef __LUX_H__
#define __LUX_H__

#include <iostream>

namespace LUX
{
	// [Enum]
	// KeyCode
	enum class KeyCode
	{
		// A ~ Z
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		// a ~ z
		a = 97,
		b = 98,
		c = 99,
		d = 100,
		e = 101,
		f = 102,
		g = 103,
		h = 104,
		i = 105,
		j = 106,
		k = 107,
		l = 108,
		m = 109,
		n = 110,
		o = 111,
		p = 112,
		q = 113,
		r = 114,
		s = 115,
		t = 116,
		u = 117,
		v = 118,
		w = 119,
		x = 120,
		y = 121,
		z = 122
	};

	// [Classes]
	class Console;
	class Game;
	class GameObject;
	class String;
	class Vector2;
	class Quaternion;
	static class Input;
	static class Math;

	// Basic console class.
	class Console
	{
	private:
		char* title;

		unsigned short width;
		unsigned short height;

	public:
		Console(const char* title, unsigned short width, unsigned short height, bool cursorVisible);
		~Console();

		void SetCursorVisible(bool value);
		void Gotoxy(unsigned short x, unsigned short y);

		const char* GetTitle() const { return title; }
		unsigned short GetWidth() const { return width; }
		unsigned short GetHeight() const { return height; }

		void SetTitle(const char* title);
	};

	// Basic game class.
	class Game
	{
	protected:
		Console* console;

		virtual void Start();
		virtual void Update(float deltaTime);

	public:
		Game(Console* console);
		virtual ~Game();

		void Run();
	};

	// Basic gameObject class
	class GameObject
	{
	private:
		std::string name;
		std::string tag;
		bool active = true;

		Vector2* position;
		Quaternion* rotation;
		Vector2* scale;

	public:
		GameObject(const char* name, const char* tag, bool active);
		~GameObject();

		const char* GetName() const { return name.c_str(); };
		const char* GetTag() const { return tag.c_str(); };
		bool GetActive() const { return active; }
		void SetName(const char* name);
		void SetTag(const char* tag);
		void SetActive(bool active);

		Vector2* GetPosition() { return position; };
		Quaternion* GetRotation() { return rotation; };
		Vector2* GetScale() { return scale; };
	};

	// Basic string class.
	class String
	{
	private:
		char* value;
		int length;

	public:
		static const String empty;

		String();
		String(const char* value);
		String(const String& string);
		~String();

		int GetLength() const { return length; }
		const char* GetValue() const { return value; }
		String& SetValue(const char* value);
		String& SetValue(const String& string);

		bool operator == (const char* value);
		bool operator == (const String& string);
		bool operator != (const char* value);
		bool operator != (const String& string);

		void operator = (const char* value);
		void operator = (const String& string);
		void operator += (const char* value);
		void operator += (const String& string);

		friend std::istream& operator >> (std::istream& is, String& string);
		friend std::ostream& operator << (std::ostream& os, const String& string);
	};

	// Basic vector2 class.
	class Vector2
	{
	private:
		float x;
		float y;

	public:
		static const Vector2 zero;
		static const Vector2 right;
		static const Vector2 left;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 one;

		Vector2(float x, float y);

		float GetX() const { return x; }
		float GetY() const { return y; }
		Vector2& Set(float x, float y);
		Vector2& Set(Vector2& ref);
		Vector2& SetX(float x);
		Vector2& SetY(float y);

		static Vector2 Lerp(const Vector2& s, const Vector2& e, float t);

		bool operator == (const Vector2& ref);
		bool operator != (const Vector2& ref);

		void operator = (const Vector2& ref);
		void operator *= (const Vector2& ref);
	};

	// Basic quaternion class.
	class Quaternion
	{
	private:
		float x;
		float y;
		float z;
		float w;

	public:
		static const Quaternion identity;

		Quaternion(float x, float y, float z, float w);

		float GetX() const { return x; }
		float GetY() const { return y; }
		float GetZ() const { return z; }
		float GetW() const { return w; }
		Quaternion& Set(float x, float y, float z, float w);
		Quaternion& Set(Quaternion& ref);
		Quaternion& SetX(float x);
		Quaternion& SetY(float y);
		Quaternion& SetZ(float z);
		Quaternion& SetW(float w);

		bool operator == (const Quaternion& ref);
		bool operator != (const Quaternion& ref);

		void operator = (const Quaternion& ref);
		void operator *= (const Quaternion& ref);
	};

	// Basic input class.
	static class Input
	{
	public:
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);
	};

	// Basic math class
	static class Math
	{
	public:
		// Constants
		static const float PI;

		// Abs
		static int Abs(int n);
		static float Abs(float n);
		static double Abs(double n);
		static long Abs(long n);
		static long long Abs(long long n);

		// Lerp
		static float Lerp(float s, float e, float t);
		static double Lerp(double s, double e, double t);

		// Max
		static int Max(int a, int b);
		static float Max(float a, float b);
		static double Max(double a, double b);
		static long Max(long a, long b);
		static long long Max(long long a, long long b);
		static unsigned int Max(unsigned int a, unsigned int b);
		static unsigned long Max(unsigned long a, unsigned long b);
		static unsigned long long Max(unsigned long long a, unsigned long long b);

		// Min
		static int Min(int a, int b);
		static float Min(float a, float b);
		static double Min(double a, double b);
		static long Min(long a, long b);
		static long long Min(long long a, long long b);
		static unsigned int Min(unsigned int a, unsigned int b);
		static unsigned long Min(unsigned long a, unsigned long b);
		static unsigned long long Min(unsigned long long a, unsigned long long b);
	};
}

#endif