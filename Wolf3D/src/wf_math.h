#ifndef WF_MATH_H
#define WF_MATH_H
#include "wf_pch.h"

namespace Wolf 
{
	#define PI 3.14159265359
	#define RADTODEG 57.295779513
	#define DEGTORAD 0.0174532925
	#define EPSILON 0.00001

	namespace Math 
	{
		inline void swap(f32& a, f32& b) { f32 aux = a; a = b; b = aux; } 
		inline f32 min(f32 a, f32 b) { return a < b ? a : b; } 
		inline f32 max(f32 a, f32 b) { return a < b ? b : a; } 
		inline f32 clamp(f32 value, f32 mi, f32 ma) { return min(max(value, mi), ma); } 
		inline f32 clamp01(f32 value) { clamp(value, 0.0f, 1.0f); }
		inline f32 lerp(f32 a, f32 b, f32 t) { return a + (clamp01(t) * (b - a)); }
		inline f32 lerp_unclamped(f32 a, f32 b, f32 t) { return a + (t * (b - a)); }
		inline f32 invlerp(f32 a, f32 b, f32 t) { return clamp01((t - a) / (b - a)); }
		inline f32 invlerp_unclamped(f32 a, f32 b, f32 t) { return (t - a) / (b - a); }
		inline f32 map(f32 value, f32 amin, f32 amax, f32 bmin, f32 bmax) { return lerp(bmin, bmax, invlerp(amin, amax, value)); }
		inline f32 sign(f32 value) { value >= 0.0f ? 1.0f : -1.0f; }
		inline f32 abs(f32 value) { value >= 0.0f ? value : -value; }

		inline void swap(f64& a, f64& b) { f64 aux = a; a = b; b = aux; } 
		inline f64 min(f64 a, f64 b) { return a < b ? a : b; } 
		inline f64 max(f64 a, f64 b) { return a < b ? b : a; } 
		inline f64 clamp(f64 value, f64 mi, f64 ma) { return min(max(value, mi), ma); } 
		inline f64 clamp01(f64 value) { clamp(value, 0.0, 1.0); }
		inline f64 lerp(f64 a, f64 b, f64 t) { return a + (clamp01(t) * (b - a)); }
		inline f64 lerp_unclamped(f64 a, f64 b, f64 t) { return a + (t * (b - a)); }
		inline f64 invlerp(f64 a, f64 b, f64 t) { return clamp01((t - a) / (b - a)); }
		inline f64 invlerp_unclamped(f64 a, f64 b, f64 t) { return (t - a) / (b - a); }
		inline f64 map(f64 value, f64 amin, f64 amax, f64 bmin, f64 bmax) { return lerp(bmin, bmax, invlerp(amin, amax, value)); }
		inline f64 sign(f64 value) { value >= 0.0 ? 1.0 : -1.0; }
		inline f64 abs(f64 value) { value >= 0.0 ? value : -value; }

		inline s32 min(s32 a, s32 b) { return a < b ? a : b; } 
		inline s32 max(s32 a, s32 b) { return a < b ? b : a; } 
		inline s32 clamp(s32 value, s32 mi, s32 ma) { return min(max(value, mi), ma); } 
		inline s32 clamp01(s32 value) { clamp(value, 0, 1); }
		inline s32 sign(s32 value) { value >= 0 ? 1 : -1; }
		inline s32 abs(s32 value) { value >= 0 ? value : -value; }
	}

	struct Vec2 
	{
		f32 x, y;

		Vec2() : x(0), y(0) {};
		Vec2(f32 a_x, f32 a_y) : x(a_x), y(a_y) {};

		f32 mod() const
		{ 
			return sqrtf(x * x + y * y); 
		}

		f32 sqrmod() const
		{
			return x * x + y * y;
		}

		Vec2 normalized() const
		{
			f32 a_mod = mod();
			assert(a_mod != 0.0f, "normalizing mod 0 vec2");
			return Vec2(x / a_mod, y / a_mod);
		}

		void normalize()
		{
			f32 a_mod = mod();
			assert(a_mod != 0.0f, "normalizing mod 0 vec2");
			x /= a_mod;
			y /= a_mod;
		}

		void set(f32 a_x, f32 a_y)
		{
			x = a_x; 
			y = a_y;
		}

		Vec2 perpendicularCW() const 
		{ 
			return Vec2(y, -x);
		}

		Vec2 perpendicularCCW() const 
		{ 
			return Vec2(-y, x); 
		}

		static f32 distance(const Vec2& v1, const Vec2& v2)  
		{
			return (v2 - v1).mod(); 
		}

		static Vec2 clamp(const Vec2& value, f32 mi, f32 ma)
		{
			return Vec2(Math::clamp(value.x, mi, ma), Math::clamp(value.y, mi, ma));
		}

		static Vec2 clamp01(Vec2 value)
		{
			return clamp(value, 0.0f, 1.0f);
		}

		static Vec2 lerp(Vec2 a, Vec2 b, f32 t)
		{
			return a + ((b - a) * Math::clamp01(t));
		}

		static Vec2 lerp_unclamped(Vec2 a, Vec2 b, f32 t)
		{
			return a + ((b - a) * t);
		}

		static Vec2 sign(Vec2 value)
		{
			return Vec2(Math::sign(value.x), Math::sign(value.y));
		}

		static Vec2 max(const Vec2& a, const Vec2& b)
		{
			return Vec2(Math::max(a.x, b.x), Math::max(a.y, b.y));
		}

		static Vec2 min(const Vec2& a, const Vec2& b)
		{
			return Vec2(Math::min(a.x, b.x), Math::min(a.y, b.y));
		}

		static Vec2 reflect(const Vec2& vector, const Vec2& normal)
		{
			const f32 dot = vector.x * normal.x + vector.y * normal.y;
			return Vec2(vector.x - 2.0f * dot * normal.x, vector.y - 2.0f * dot * normal.y);
		}

		static f32 angle(const Vec2& from, const Vec2& to)
		{
			Vec2 fromTo = to - from;
			return (f32)atan2(fromTo.y, fromTo.x);
		}

		static bool equals_offset(const Vec2& one, const Vec2& other, f32 offset)
		{
			f32 a_x = abs(one.x - other.x);
			f32 a_y = abs(one.y - other.y);

			return (a_x < offset && a_y < offset);
		}

		Vec2 operator + (const Vec2& op) const 
		{
			return Vec2(x + op.x, y + op.y);
		}

		Vec2 operator - (const Vec2& op) const
		{
			return Vec2(x - op.x, y - op.y);
		}

		Vec2 operator * (f32 op) const
		{
			return Vec2(x * op, y * op);
		}

		Vec2 operator / (f32 op) const
		{
			return Vec2(x / op, y / op);
		}

		void operator += (Vec2 op)
		{
			x = x + op.x;
			y = y + op.y;
		}

		void operator -= (Vec2 op)
		{
			x = x - op.x;
			y = y - op.y;
		}

		void operator *= (f32 op)
		{
			x = x * op;
			y = y * op;
		}

		void operator /= (f32 op)
		{
			x = x / op;
			y = y / op;
		}

		Vec2 operator-() 
		{ 
			return (*this) * -1.0f; 
		}

		const static Vec2 zero;
		const static Vec2 one;
		const static Vec2 up;
		const static Vec2 right;
		const static Vec2 left;
		const static Vec2 down;
	};

	Vec2 operator * (f32 f, const Vec2& op)
	{
		return op * f;
	}

	bool operator == (const Vec2& a, Vec2& b) 
	{
		return a.x == b.x && a.y == b.y;
	}

	bool operator != (const Vec2& a, Vec2& b)
	{
		return a.x != b.x || a.y != b.y;
	}

	const Vec2 Vec2::zero = Vec2(0.0f, 0.0f);
	const Vec2 Vec2::one = Vec2(1.0f, 1.0f);
	const Vec2 Vec2::up = Vec2(0.0f, 1.0f);
	const Vec2 Vec2::down = Vec2(0.0f, -1.0f);
	const Vec2 Vec2::right = Vec2(1.0f, 0.0f);
	const Vec2 Vec2::left = Vec2(-1.0f, 0.0f);


	struct Vec3
	{
		union {
			struct { f32 x, y, z; };
			f32 values[3];
		};

		Vec3() : x(0), y(0), z(0) {};
		Vec3(f32 a_x, f32 a_y, f32 a_z) : x(a_x), y(a_y), z(a_z) {};
		Vec3(f32 v[3]) : x(v[0]), y(v[1]), z(v[2]) {};


		f32 mod() const
		{
			return sqrtf((x * x) + (y * y) + (z * z));
		}

		f32 sqrmod() const
		{
			return (x * x) + (y * y) + (z * z);
		}

		void set(f32 a_x, f32 a_y, f32 a_z) { x = a_x; y = a_y; z = a_z; };

		void normalize()
		{
			f32 mod = this->mod();
			assert(mod != 0.0f, "normalizing mod 0 vec3");
			x = x / mod; 
			y = y / mod; 
			z = z / mod;
		}

		Vec3 normalized() const
		{
			f32 mod = this->mod();
			assert(mod != 0.0f, "normalizing mod 0 vec3");
			return Vec3(x / mod, y / mod, z / mod);
		}

		static f32 dot(const Vec3& one, const Vec3& other)
		{
			return (other.x * one.x) + (other.y * one.y) + (other.z * one.z);
		}

		static Vec3 cross(const Vec3& one, const Vec3& other)
		{
			return Vec3(one.y * other.z - one.z * other.y, one.z * other.x - one.x * other.z, one.x * other.y - one.y * other.x);
		}

		static Vec3 clamp(const Vec3& value, f32 mi, f32 ma)
		{
			return Vec3(Math::clamp(value.x, mi, ma), Math::clamp(value.y, mi, ma), Math::clamp(value.z, mi, ma));
		}

		static Vec3 clamp01(Vec3 value)
		{
			return clamp(value, 0.0f, 1.0f);
		}

		static Vec3 lerp(Vec3 a, Vec3 b, f32 t)
		{
			return a + ((b - a) * Math::clamp01(t));
		}

		static Vec3 lerp_unclamped(Vec3 a, Vec3 b, f32 t)
		{
			return a + ((b - a) * t);
		}

		static Vec3 sign(Vec3 value)
		{
			return Vec3(Math::sign(value.x), Math::sign(value.y), Math::sign(value.z));
		}

		static Vec3 max(const Vec3& a, const Vec3& b)
		{
			return Vec3(Math::max(a.x, b.x), Math::max(a.y, b.y), Math::max(a.z, b.z));
		}

		static Vec3 min(const Vec3& a, const Vec3& b)
		{
			return Vec3(Math::min(a.x, b.x), Math::min(a.y, b.y), Math::min(a.z, b.z));
		}

		static Vec3 reflect(const Vec3& vector, const Vec3& normal)
		{
			return vector - 2.f * Vec3::dot(vector, normal) * normal;
		}

		static Vec3 slerp(const Vec3& start, const Vec3& end, f32 percent)
		{
			f32 dot = Vec3::dot(start, end);
			dot = fminf(1.0f, fmaxf(dot, -1.0f));
			f32 theta = acosf(dot) * percent;
			Vec3 RelativeVec = end - (start * dot);
			RelativeVec.normalize();
			return ((start * cosf(theta)) + (RelativeVec * sinf(theta)));
		}

		static f32 Vec3::distance(const Vec3& a, const Vec3& b)
		{
			Vec3 aToB = b - a;
			return aToB.mod();
		}

		Vec3 operator + (const Vec3& op) const
		{
			return Vec3(x + op.x, y + op.y, z + op.z);
		}

		Vec3 operator - (const Vec3& op) const
		{
			return Vec3(x - op.x, y - op.y, z - op.z);
		}

		Vec3 operator * (f32 a) const
		{
			return Vec3(a * x, a * y, a * z);
		}

		Vec3 operator / (f32 op) const
		{
			return Vec3(x / op, y / op, z / op);
		}

		Vec3 operator-()
		{
			return (*this) * -1.0f;
		}

		void operator += (const Vec3 b) 
		{
			x += b.x;
			y += b.y;
			z += b.z;
		}

		void operator -= (const Vec3 b)
		{
			x -= b.x;
			y -= b.y;
			z -= b.z;
		}

		void operator *= (f32 op)
		{
			x = x * op;
			y = y * op;
			z = z * op;
		}

		void operator /= (f32 op)
		{
			x = x / op;
			y = y / op;
			z = z / op;
		}


		const static Vec3 zero;
		const static Vec3 one;
		const static Vec3 forward;
		const static Vec3 back;
		const static Vec3 up;
		const static Vec3 down;
		const static Vec3 right;
		const static Vec3 left;
	};

	const Vec3 Vec3::zero = Vec3(0,0,0);
	const Vec3 Vec3::one = Vec3(1,1,1);
	const Vec3 Vec3::forward = Vec3(0,0,1);
	const Vec3 Vec3::back = Vec3(0,0,-1);
	const Vec3 Vec3::up = Vec3(0,1,0);
	const Vec3 Vec3::down = Vec3(0,-1,0);
	const Vec3 Vec3::right = Vec3(1,0,0);
	const Vec3 Vec3::left = Vec3(-1,0,0);

	bool operator == (const Vec3& a, const Vec3& b)
	{
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
	}

	bool operator != (const Vec3& a, const Vec3& b) 
	{
		return (a.x != b.x) || (a.y != b.y) || (a.z != b.z);
	}

	Vec3 operator * (const f32 a, const Vec3& b)
	{
		return Vec3(a * b.x, a * b.y, a * b.z);
	}

	struct Vec4
	{
		f32 x, y, z, w;

		Vec4()
			:x(0.0f), y(0.0f), z(0.0f), w(0.0f)
		{}

		Vec4(f32 a_x, f32 a_y, f32 a_z, f32 a_w)
			:x(a_x), y(a_y), z(a_z), w(a_w)
		{}
	};

	struct Vec4s
	{
		s32 i, j, k, w;
		Vec4s()
			:i(0), j(0), k(0), w(0) 
		{}

		Vec4s(s32 a_i, s32 a_j, s32 a_k, s32 a_w)
			:i(a_i), j(a_j), k(a_k), w(a_w) 
		{}
	};

	//row major 4x4 matrix
	struct Mat44f
	{
		union
		{
			f32 m[4][4];
			f32 values[16];
		};

		Mat44f() { setIdentity(); }


		Mat44f(const Mat44f& other)
		{
			memcpy((void*)&values, (void*)&other.values, sizeof(f32) * 16);
		};

		inline void setIdentity()
		{
			m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = 0.0;
			m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = 0.0;
			m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = 0.0;
			m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
		}

		void setTranslation(const Vec3& translation)
		{
			setTranslation(translation.x, translation.y, translation.z);
		}

		void setTranslation(f32 tx, f32 ty, f32 tz)
		{
			setIdentity();
			m[3][0] = tx;
			m[3][1] = ty;
			m[3][2] = tz;
		}

		Vec3 getPosition() const
		{
			return Vec3(m[3][0], m[3][1], m[3][2]);
		}

		void setPosition(const Vec3& pos)
		{
			m[3][0] = pos.x;
			m[3][1] = pos.y;
			m[3][2] = pos.z;
		}

		Vec3 getScale() const
		{
			Vec3 aux;
			aux.x = m[0][0];
			aux.y = m[0][1];
			aux.z = m[0][2];
			f32 scaleX = aux.mod();

			aux.x = m[1][0];
			aux.y = m[1][1];
			aux.z = m[1][2];
			f32 scaleY = aux.mod();

			aux.x = m[2][0];
			aux.y = m[2][1];
			aux.z = m[2][2];
			f32 scaleZ = aux.mod();

			return Vec3(scaleX, scaleY, scaleZ);
		}

		void setRotation(f32 angleX, f32 angleY, f32 angleZ)
		{
			setIdentity();

			Mat44f rx, ry, rz;
			//TODO: remove this 3 matrix concats?
			rx.setRotation(angleX, Vec3(1.0, 0.0, 0.0));
			ry.setRotation(angleY, Vec3(0.0, 1.0, 0.0));
			rz.setRotation(angleZ, Vec3(0.0, 0.0, 1.0));

			(*this) = (*this) * rx * ry * rz;
		}

		void setRotation(f32 angle, const Vec3& axis)
		{
			setIdentity();
			Vec3 axis_n = axis;
			axis_n.normalize();

			f32 c = (f32)cos(DEGTORAD * angle);
			f32 s = (f32)sin(DEGTORAD * angle);
			f32 t = (f32)1 - c;

			m[0][0] = t * axis_n.x * axis_n.x + c;
			m[0][1] = t * axis_n.x * axis_n.y - s * axis_n.z;
			m[0][2] = t * axis_n.x * axis_n.z + s * axis_n.y;

			m[1][0] = t * axis_n.x * axis_n.y + s * axis_n.z;
			m[1][1] = t * axis_n.y * axis_n.y + c;
			m[1][2] = t * axis_n.y * axis_n.z - s * axis_n.x;

			m[2][0] = t * axis_n.x * axis_n.z - s * axis_n.y;
			m[2][1] = t * axis_n.y * axis_n.z + s * axis_n.x;
			m[2][2] = t * axis_n.z * axis_n.z + c;

			m[3][3] = 1.0f;
		}

		void setScale(const Vec3& scale)
		{
			setIdentity();
			m[0][0] = scale.x;
			m[1][1] = scale.y;
			m[2][2] = scale.z;
		}

		void transpose()
		{
			Math::swap(m[0][1], m[1][0]);
			Math::swap(m[0][2], m[2][0]);
			Math::swap(m[0][3], m[3][0]);

			Math::swap(m[1][2], m[2][1]);
			Math::swap(m[1][3], m[3][1]);

			Math::swap(m[2][3], m[3][2]);
		}

		bool inverse()
		{
			u32 i, j, k, u_swap;
			f32 t;
			Mat44f temp, final;
			final.setIdentity();

			temp = (*this);

			u32 m, n;
			m = n = 4;

			for (i = 0; i < m; i++)
			{
				// Look for largest element in column

				u_swap = i;
				for (j = i + 1; j < m; j++)// m or n
				{
					if (fabs(temp.m[j][i]) > fabs(temp.m[u_swap][i]))
						u_swap = j;
				}

				if (u_swap != i)
				{
					// Swap rows.
					for (k = 0; k < n; k++)
					{
						Math::swap(temp.m[i][k], temp.m[u_swap][k]);
						Math::swap(final.m[i][k], final.m[u_swap][k]);
					}
				}

				// No non-zero pivot.  The CMatrix is singular, which shouldn't
				// happen.  This means the user gave us a bad CMatrix.


	#define MATRIX_SINGULAR_THRESHOLD 0.00001 //change this if you experience problems with matrices

				if (fabsf(temp.m[i][i]) <= MATRIX_SINGULAR_THRESHOLD)
				{
					final.setIdentity();
					return false;
				}
	#undef MATRIX_SINGULAR_THRESHOLD

				t = 1.0f / temp.m[i][i];

				for (k = 0; k < n; k++)//m or n
				{
					temp.m[i][k] *= t;
					final.m[i][k] *= t;
				}

				for (j = 0; j < m; j++) // m or n
				{
					if (j != i)
					{
						t = temp.m[j][i];
						for (k = 0; k < n; k++)//m or n
						{
							temp.m[j][k] -= (temp.m[i][k] * t);
							final.m[j][k] -= (final.m[i][k] * t);
						}
					}
				}
			}

			*this = final;

			return true;
		}

		void translate(const Vec3& translation)
		{
			Mat44f T;
			T.setTranslation(translation);
			*this = (*this) * T;
		}

		void translate(f32 tx, f32 ty, f32 tz)
		{
			Mat44f T;
			T.setTranslation(tx, ty, tz);
			*this = (*this) * T;
		}

		void translateLocal(const Vec3& translation)
		{
			Mat44f T;
			T.setTranslation(translation);
			*this = T * (*this);
		}

		void translateLocal(f32 tx, f32 ty, f32 tz)
		{
			Mat44f T;
			T.setTranslation(tx, ty, tz);
			*this = T * (*this);
		}

		void rotateLocal(f32 rotX, f32 rotY, f32 rotZ)
		{
			Mat44f rotation;
			rotation.setRotation(rotX, rotY, rotZ);
			*this = rotation * *this;
		}

		void rotate(f32 rotX, f32 rotY, f32 rotZ)
		{
			Mat44f rotation;
			rotation.setRotation(rotX, rotY, rotZ);

			(*this) = (*this) * rotation;
		}

		void scale(const Vec3& scale)
		{
			m[0][0] *= scale.x;
			m[1][1] *= scale.y;
			m[2][2] *= scale.z;
		}

		void replaceScale(const Vec3& scale)
		{
			m[0][0] = scale.x;
			m[1][1] = scale.y;
			m[2][2] = scale.z;
		}

		void setLookAt(const Vec3& position, const Vec3& targetPos32, const Vec3& up)
		{
			Vec3 front = (targetPos32 - position);
			front.normalize();
			Vec3 right = Vec3::cross(front, up);
			right.normalize();
			Vec3 top = Vec3::cross(right, front);
			top.normalize();

			setIdentity();

			m[0][0] = right.x; m[0][1] = top.x; m[0][2] = -front.x;
			m[1][0] = right.y; m[1][1] = top.y; m[1][2] = -front.y;
			m[2][0] = right.z; m[2][1] = top.z; m[2][2] = -front.z;

			translateLocal(-position.x, -position.y, -position.z);
		}

		void setPerspective(f32 fov, f32 aspect, f32 _near, f32 _far)
		{
			setIdentity();

			f32 f = 1.0f / tanf((f32)DEGTORAD * fov * 0.5f);

			m[0][0] = f / aspect;
			m[1][1] = f;
			m[2][2] = (_far + _near) / (_near - _far);
			m[2][3] = -1.0f;
			m[3][2] = 2.0f * (_far * _near) / (_near - _far);
			m[3][3] = 0.0f;
		}

		void makeRotationDir(const Vec3& forward, const Vec3& up)
		{
			Vec3 forwardNormalized = forward.normalized();
			Vec3 upNormalized = up.normalized();
			Vec3 xaxis = Vec3::cross(forwardNormalized, upNormalized);
			xaxis.normalize();

			Vec3 yaxis = Vec3::cross(xaxis, forwardNormalized);
			yaxis.normalize();

			setIdentity();

			m[0][0] = -xaxis.x;
			m[1][0] = xaxis.y;
			m[2][0] = xaxis.z;

			m[0][1] = -yaxis.x;
			m[1][1] = yaxis.y;
			m[2][1] = yaxis.z;

			m[0][2] = -forwardNormalized.x;
			m[1][2] = forwardNormalized.y;
			m[2][2] = forwardNormalized.z;
		}

		void setOrthographic(f32 left, f32 right, f32 bottom, f32 top, f32 _near, f32 _far)
		{
			m[0][0] = 2.0f / (right - left);
			m[0][1] = 0.0f;
			m[0][2] = 0.0f;
			m[0][3] = 0.0f;

			m[1][0] = 0.0f;
			m[1][1] = 2.0f / (top - bottom);
			m[1][2] = 0.0f;
			m[1][3] = 0.0f;

			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = -2.0f / (_far - _near);
			m[2][3] = 0.0f;

			m[3][0] = -(right + left) / (right - left);
			m[3][1] = -(top + bottom) / (top - bottom);
			m[3][2] = -(_far + _near) / (_far - _near);
			m[3][3] = 1.0f;
		}

		Mat44f getRotationOnly()
		{
			Vec3 scale = getScale();
			Mat44f rot;
			rot = *this;

			rot.m[3][0] = 0.0f;
			rot.m[3][1] = 0.0f;
			rot.m[3][2] = 0.0f;

			rot.m[0][3] = 0.0f;
			rot.m[1][3] = 0.0f;
			rot.m[2][3] = 0.0f;

			rot.m[3][3] = 1.0f;

			rot.m[0][0] = rot.m[0][0] / scale.x;
			rot.m[0][1] = rot.m[0][1] / scale.x;
			rot.m[0][2] = rot.m[0][2] / scale.x;

			rot.m[1][0] = rot.m[1][0] / scale.y;
			rot.m[1][1] = rot.m[1][1] / scale.y;
			rot.m[1][2] = rot.m[1][2] / scale.y;

			rot.m[2][0] = rot.m[2][0] / scale.z;
			rot.m[2][1] = rot.m[2][1] / scale.z;
			rot.m[2][2] = rot.m[2][2] / scale.z;

			return rot;
		}

		Vec3 rotateVector(const Vec3& v)
		{
			return (*this) * v;
		}

		Mat44f operator * (f32 val)
		{
			Mat44f result;
			for (size_t i = 0; i < 16; i++)
				result.values[i] = values[i] * val;

			return result;
		}

		Mat44f operator * (const Mat44f& other)
		{
			Mat44f result;
			u16 aux_row;
			u16 aux_col;

			for (u16 i = 0; i < 16; i++)
			{
				aux_row = u16(i * 0.25f);
				aux_col = i % 4;
				result.values[i] =
					m[aux_row][0] * other.m[0][aux_col] +
					m[aux_row][1] * other.m[1][aux_col] +
					m[aux_row][2] * other.m[2][aux_col] +
					m[aux_row][3] * other.m[3][aux_col];
			}

			return result;
		}

		Vec3 operator * (const Vec3& other) const
		{
			Vec3 result;
			for (u16 i = 0; i < 3; i++)
			{
				result.values[i] =
					m[0][i] * other.x +
					m[1][i] * other.y +
					m[2][i] * other.z +
					m[3][i] * 0;
			}
	
			return result;
		}

		Vec3 front() { return (this->getRotationOnly() * Vec3(0.0f, 0.0f, 1.0f)).normalized(); }
		Vec3 up() { return (this->getRotationOnly() * Vec3(0.0f, 1.0f, 0.0f)).normalized(); }
		Vec3 right() { return (this->getRotationOnly() * Vec3(1.0f, 0.0f, 0.0f)).normalized(); }

		const static Mat44f identity;
	};

	const Mat44f Mat44f::identity = Mat44f();

	//This quaternions are taken from Javi Agenjo's code
	//https://www.dtic.upf.edu/~jagenjo/?page_id=11
	struct Quaternion
	{
	public:

		union
		{
			struct { f32 x; f32 y; f32 z; f32 w; };
			f32 q[4];
		};

	public:
		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
		Quaternion(const f32 X, const f32 Y, const f32 Z, const f32 W) : x(X), y(Y), z(Z), w(W) {}

		Quaternion invert() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		Quaternion conjugate() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		Vec3 right()
		{
			return Vec3(1 - 2 * (y * y + z * z),
				2 * (x * y + w * z),
				2 * (x * z - w * y));
		}

		Vec3 up()
		{
			return Vec3(2 * (x * y - w * z),
				1 - 2 * (x * x + z * z),
				2 * (y * z + w * x));
		}

		Vec3 forward()
		{
			return Vec3(2 * (x * z + w * y),
				2 * (y * z - w * x),
				1 - 2 * (x * x + y * y));
		}

		void set(const f32 X, const f32 Y, const f32 Z, const f32 W)
		{
			x = X;  y = Y; z = Z; w = W;
		}

		Quaternion(const f32* q)
		{
			x = q[0];
			y = q[1];
			z = q[2];
			w = q[3];
		}

		void identity()
		{
			x = y = z = 0.0f; w = 1.0f;
		}

		void slerp(const Quaternion& b, f32 t)
		{
			//quaternion a(*this);
			*this = Qslerp(*this, b, t);
		}

		void slerp(const Quaternion& q2, f32 t, Quaternion& q3) const
		{
			q3 = Qslerp(*this, q2, t);
		}

		void lerp(const Quaternion& b, f32 t)
		{
			*this = Qlerp(*this, b, t);
		}

		void lerp(const Quaternion& q2, f32 t, Quaternion& q3) const
		{
			q3 = Qlerp(*this, q2, t);
		}

		void setAxisAngle(const Vec3& axis, const f32 angle)
		{
			f32 s;
			s = sinf(angle * 0.5f);

			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
			w = cosf(angle * 0.5f);
		}

		Quaternion(const Vec3& axis, f32 angle)
		{
			setAxisAngle(axis, angle);
		}

		void operator *= (const Quaternion& q)
		{
			Quaternion quaternion = *this * q;
			*this = quaternion;
		}

		void operator*=(const Vec3& v)
		{
			*this = *this * v;
		}

		void operator += (const Quaternion& q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
		}

		/*
		//http://www.cs.yorku.ca/~arlene/aquasim/mymath.c
		quaternion operator * (const quaternion& p, const quaternion& q)
		{
		return quaternion(
		p.w*q.x + p.x*q.w + p.y*q.z - p.z*q.y,
		p.w*q.y + p.y*q.w + p.z*q.x - p.x*q.z,
		p.w*q.z + p.z*q.w + p.x*q.y - p.y*q.x,
		p.w*q.w - p.x*q.x - p.y*q.y - p.z*q.z);
		}
		*/

		void operator *= (f32 f)
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;
		}

		void normalize()
		{
			f32 len = length();
			len = 1.0f / len;

			x *= len;
			y *= len;
			z *= len;
			w *= len;
		}

		void lookRotation(const Vec3& forward, const Vec3& up)
		{
			Vec3 vector = forward.normalized();
			Vec3 vector2 = Vec3::cross(up.normalized(), vector).normalized();
			Vec3 vector3 = Vec3::cross(vector, vector2);
			f32 m00 = vector2.x;
			f32 m01 = vector2.y;
			f32 m02 = vector2.z;
			f32 m10 = vector3.x;
			f32 m11 = vector3.y;
			f32 m12 = vector3.z;
			f32 m20 = vector.x;
			f32 m21 = vector.y;
			f32 m22 = vector.z;


			f32 num8 = (m00 + m11) + m22;
			if (num8 > 0.0f)
			{
				f32 num = (f32)sqrtf(num8 + 1.0f);
				w = num * 0.5f;
				num = 0.5f / num;
				x = (m12 - m21) * num;
				y = (m20 - m02) * num;
				z = (m01 - m10) * num;
			}
			if ((m00 >= m11) && (m00 >= m22))
			{
				f32 num7 = (f32)sqrtf(((1.0f + m00) - m11) - m22);
				f32 num4 = 0.5f / num7;
				x = 0.5f * num7;
				y = (m01 + m10) * num4;
				z = (m02 + m20) * num4;
				w = (m12 - m21) * num4;
			}
			if (m11 > m22)
			{
				f32 num6 = (f32)sqrtf(((1.0f + m11) - m00) - m22);
				f32 num3 = 0.5f / num6;
				x = (m10 + m01) * num3;
				y = 0.5f * num6;
				z = (m21 + m12) * num3;
				w = (m20 - m02) * num3;
			}
			f32 num5 = (f32)sqrtf(((1.0f + m22) - m00) - m11);
			f32 num2 = 0.5f / num5;
			x = (m20 + m02) * num2;
			y = (m21 + m12) * num2;
			z = 0.5f * num5;
			w = (m01 - m10) * num2;
		}

		void computeMinimumRotation(const Vec3& rotateFrom, const Vec3& rotateTo)
		{
			// Check if the vectors are valid.
			//rotateFrom.GetLength()==0.0f
			//rotateTo.GetLength()==0.0f

			Vec3 from(rotateFrom);
			from.normalize();
			Vec3 to(rotateTo);
			to.normalize();

			const f32 _dot = Vec3::dot(from, to);
			Vec3 crossvec = Vec3::cross(from, to);
			const f32 crosslen = (f32)crossvec.mod();

			if (crosslen == 0.0f)
			{
				// Parallel vectors
				// Check if they are pos32ing in the same direction.
				if (_dot > 0.0f)
				{
					x = y = z = 0.0f;
					w = 1.0f;
				}
				// Ok, so they are parallel and pos32ing in the opposite direction
				// of each other.
				else
				{
					// Try crossing with x axis.
					Vec3 t = Vec3::cross(from, Vec3(1.0f, 0.0f, 0.0f));
					// If not ok, cross with y axis.
					if (t.mod() == 0.0f)
						Vec3::cross(from, Vec3(0.0f, 1.0f, 0.0f));

					t.normalize();
					x = t.x;
					y = t.y;
					z = t.z;
					w = 0.0f;
				}
			}
			else
			{ // Vectors are not parallel
				crossvec.normalize();
				// The fabs() wrapping is to avoid problems when `dot' "overflows"
				// a tiny wee bit, which can lead to sqrt() returning NaN.
				crossvec *= (f32)sqrtf(0.5f * fabsf(1.0f - _dot));
				// The fabs() wrapping is to avoid problems when `dot' "underflows"
				// a tiny wee bit, which can lead to sqrt() returning NaN.
				x = crossvec.x;
				y = crossvec.y;
				z = crossvec.z,
					w = (f32)sqrtf(0.5f * fabsf(1.0f + _dot));
			}
		}

		Quaternion SimpleRotation(const Vec3& a, const Vec3& b)
		{
			Vec3 axis = Vec3::cross(a, b);
			f32 _dot = Vec3::dot(a, b);
			if (_dot < -1.0f + /*DOT_EPSILON*/0.001f) return Quaternion(0, 1, 0, 0);

			Quaternion result(axis.x * 0.5f, axis.y * 0.5f, axis.z * 0.5f, (_dot + 1.0f) * 0.5f);
			result.normalize();

			return result;
		}


		f32 length() const
		{
			return sqrtf(w * w + x * x + y * y + z * z);
		}

		f32 squaredLength() const
		{
			return w * w + x * x + y * y + z * z;
		}

		void toMatrix(Mat44f& matrix) const
		{
			/*
			If q is guaranteed to be a unit quaternion, s will always
			be 2.  In that case, this calculation can be optimized out.
			*/
			//const f32	norm = x*x + y*y + z*z + w*w;
			//const f32 s = (norm > 0) ? 2/norm : 0;

			const f32 s = 2;

			/*
			Precalculate coordinate products
			*/
			const f32 xx = x * x * s;
			const f32 yy = y * y * s;
			const f32 zz = z * z * s;
			const f32 xy = x * y * s;
			const f32 xz = x * z * s;
			const f32 yz = y * z * s;
			const f32 wx = w * x * s;
			const f32 wy = w * y * s;
			const f32 wz = w * z * s;


			matrix.m[0][0] = 1.0f - (yy + zz);
			matrix.m[0][1] = xy + wz;
			matrix.m[0][2] = xz - wy;

			matrix.m[1][0] = xy - wz;

			matrix.m[1][1] = 1.0f - (xx + zz);

			matrix.m[1][2] = yz + wx;

			matrix.m[2][0] = xz + wy;
			matrix.m[2][1] = yz - wx;
			matrix.m[2][2] = 1.0f - (xx + yy);

			matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][2] = 0;
			matrix.m[0][3] = matrix.m[1][3] = matrix.m[2][3] = 0;
			matrix.m[3][3] = 1;
		}

		Mat44f toMatrix() const
		{
			Mat44f matrix;
			const f32 s = 2;

			const f32 xx = x * x * s;
			const f32 yy = y * y * s;
			const f32 zz = z * z * s;
			const f32 xy = x * y * s;
			const f32 xz = x * z * s;
			const f32 yz = y * z * s;
			const f32 wx = w * x * s;
			const f32 wy = w * y * s;
			const f32 wz = w * z * s;

			matrix.m[0][0] = 1.0f - (yy + zz);
			matrix.m[1][0] = xy + wz;
			matrix.m[2][0] = xz - wy;

			matrix.m[0][1] = xy - wz;
			matrix.m[1][1] = 1.0f - (xx + zz);
			matrix.m[2][1] = yz + wx;

			matrix.m[0][2] = xz + wy;
			matrix.m[1][2] = yz - wx;
			matrix.m[2][2] = 1.0f - (xx + yy);

			matrix.m[0][3] = matrix.m[1][3] = matrix.m[2][3] = 0;
			matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][2] = 0;
			matrix.m[3][3] = 1;

			return matrix;
		}

		void fromMatrix(const Mat44f& mat)
		{
			const f32 trace = 1.0f + mat.m[0][0] + mat.m[1][1] + mat.m[2][2];

			if (trace > 0.00001f)
			{
				const f32 s = sqrtf(trace) * 2;
				x = (mat.m[2][1] - mat.m[1][2]) / s;
				y = (mat.m[0][2] - mat.m[2][0]) / s;
				z = (mat.m[1][0] - mat.m[0][1]) / s;
				w = s / 4;
				return;
			}
			else if (mat.m[0][0] > mat.m[1][1] && mat.m[0][0] > mat.m[2][2])
			{
				const f32 s = sqrtf(1.0f + mat.m[0][0] - mat.m[1][1] - mat.m[2][2]) * 2;

				x = s / 4;
				y = (mat.m[1][0] + mat.m[0][1]) / s;
				z = (mat.m[0][2] + mat.m[2][0]) / s;
				w = (mat.m[2][1] - mat.m[1][2]) / s;
				return;
			}
			else if (mat.m[1][1] > mat.m[2][2])
			{
				const f32 s = sqrtf(1.0f + mat.m[1][1] - mat.m[0][0] - mat.m[2][2]) * 2;

				x = (mat.m[1][0] + mat.m[0][1]) / s;
				y = s / 4;
				z = (mat.m[2][1] + mat.m[1][2]) / s;
				w = (mat.m[0][2] - mat.m[2][0]) / s;
				return;
			}
			else
			{
				const f32 s = sqrtf(1.0f + mat.m[2][2] - mat.m[0][0] - mat.m[1][1]) * 2;

				x = (mat.m[0][2] + mat.m[2][0]) / s;
				y = (mat.m[2][1] + mat.m[1][2]) / s;
				z = s / 4;
				w = (mat.m[1][0] - mat.m[0][1]) / s;
				return;
			}
		}

		/*
		Logarithm of a quaternion, given as:
		Qlog(q) = v*a where q = [cos(a),v*sin(a)]
		*/
		Quaternion Qlog(const Quaternion& q)
		{
			f32 a = static_cast<f32>(acos(q.w));
			f32 sina = static_cast<f32>(sin(a));
			Quaternion ret;
			ret.w = 0;
			if (sina > 0)
			{
				ret.x = a * q.x / sina;
				ret.y = a * q.y / sina;
				ret.z = a * q.z / sina;
			}
			else
			{
				ret.x = ret.y = ret.z = 0;
			}
			return ret;
		}

		/*
		e^quaternion given as:
		Qexp(v*a) = [cos(a),vsin(a)]
		*/
		Quaternion Qexp(const Quaternion& q)
		{
			f32 a = static_cast<f32>(sqrtf(q.x * q.x + q.y * q.y + q.z * q.z));
			f32 sina = static_cast<f32>(sin(a));
			f32 cosa = static_cast<f32>(cos(a));
			Quaternion ret;

			ret.w = cosa;
			if (a > 0)
			{
				ret.x = sina * q.x / a;
				ret.y = sina * q.y / a;
				ret.z = sina * q.z / a;
			}
			else
			{
				ret.x = ret.y = ret.z = 0;
			}

			return ret;
		}


		/*
		Given 3 quaternions, qn-1,qn and qn+1, calculate a control pos32 to be used in spline s32erpolation
		*/

		Quaternion& operator -()
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;

			return *this;
		}

		void getAxisAngle(Vec3& v, f32& angle) const
		{
			angle = 2.0f * acosf(w);
			f32 factor = 1.0f / sqrtf(1 - w * w);
			v.x = x * factor;
			v.y = y * factor;
			v.z = z * factor;
		}

		Vec3 rotate(const Vec3& v) const
		{
			Vec3 ret;
			Quaternion temp(-x, -y, -z, w);
			temp *= v;
			temp *= (*this);

			ret.x = temp.x;
			ret.y = temp.y;
			ret.z = temp.z;

			return ret;
		}

		void toEulerAngles(Vec3& euler) const
		{
			/// Local Variables ///////////////////////////////////////////////////////////
			f32 matrix[3][3];
			f32 cx, sx;
			f32 cy, sy;
			f32 cz, sz;

			const f32 y2 = y * y;
			///////////////////////////////////////////////////////////////////////////////
			// CONVERT QUATERNION TO MATRIX - I DON'T REALLY NEED ALL OF IT
			matrix[0][0] = 1.0f - (2.0f * y2) - (2.0f * z * z);
			//	matrix[0][1] = (2.0f * quat->x * quat->y) - (2.0f * quat->w * quat->z);
			//	matrix[0][2] = (2.0f * quat->x * quat->z) + (2.0f * quat->w * quat->y);
			matrix[1][0] = (2.0f * x * y) + (2.0f * w * z);
			//	matrix[1][1] = 1.0f - (2.0f * quat->x * quat->x) - (2.0f * quat->z * quat->z);
			//	matrix[1][2] = (2.0f * quat->y * quat->z) - (2.0f * quat->w * quat->x);
			matrix[2][0] = (2.0f * x * z) - (2.0f * w * y);
			matrix[2][1] = (2.0f * y * z) + (2.0f * w * x);
			matrix[2][2] = 1.0f - (2.0f * x * x) - (2.0f * y2);

			sy = -matrix[2][0];
			cy = sqrtf(1 - (sy * sy));
			euler.y = atan2f(sy, cy);
			//euler->y = (yr * 180.0f) / (f32)M_PI;

			// AVOID DIVIDE BY ZERO ERROR ONLY WHERE Y= +-90 or +-270 
			// NOT CHECKING cy BECAUSE OF PRECISION ERRORS
			if (sy != 1.0f && sy != -1.0f)
			{
				cx = matrix[2][2] / cy;
				sx = matrix[2][1] / cy;
				//euler->x = ((f32)atan2(sx,cx) * 180.0f) / (f32)M_PI;	// RAD TO DEG
				euler.x = atan2f(sx, cx);

				cz = matrix[0][0] / cy;
				sz = matrix[1][0] / cy;
				//euler->z = ((f32)atan2(sz,cz) * 180.0f) / (f32)M_PI;	// RAD TO DEG
				euler.z = atan2f(sz, cz);
			}
			else
			{
				// SINCE Cos(Y) IS 0, I AM SCREWED.  ADOPT THE STANDARD Z = 0
				// I THINK THERE IS A WAY TO FIX THIS BUT I AM NOT SURE.  EULERS SUCK
				// NEED SOME MORE OF THE MATRIX TERMS NOW
				matrix[1][1] = 1.0f - (2.0f * x * x) - (2.0f * z * z);
				matrix[1][2] = (2.0f * y * z) - (2.0f * w * x);
				cx = matrix[1][1];
				sx = -matrix[1][2];
				//euler->x = ((f32)atan2(sx,cx) * 180.0f) / (f32)M_PI;	// RAD TO DEG
				euler.x = atan2f(sx, cx);

				cz = 1.0f;
				sz = 0.0f;
				//euler->z = ((f32)atan2(sz,cz) * 180.0f) / (f32)M_PI;	// RAD TO DEG
				euler.z = atan2f(sz, cz);
			}
		}

		Quaternion Euler(const Vec3& eulerAngles)
		{
			f32 yaw = eulerAngles.x;
			f32 pitch = eulerAngles.y;
			f32 roll = eulerAngles.z;
			f32 rollOver2 = roll * 0.5f;
			f32 sinRollOver2 = sinf(rollOver2);
			f32 cosRollOver2 = cosf(rollOver2);
			f32 pitchOver2 = pitch * 0.5f;
			f32 sinPitchOver2 = sinf(pitchOver2);
			f32 cosPitchOver2 = cosf(pitchOver2);
			f32 yawOver2 = yaw * 0.5f;
			f32 sinYawOver2 = sinf(yawOver2);
			f32 cosYawOver2 = cosf(yawOver2);
			Quaternion result;
			result.x = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
			result.y = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
			result.z = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
			result.w = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
			return result;
		}


		void setAxisAngle(f32 ax, f32 ay, f32 az, f32 angle)
		{
			const f32 halfAngle = angle * 0.5f;
			const f32 s = sinf(halfAngle);

			w = cosf(halfAngle);
			x = ax * s;
			y = ay * s;
			z = az * s;

		}
	};

	Quaternion operator + (const Quaternion& q1, const Quaternion& q2)
	{
		return Quaternion(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w);
	}

	bool operator == (const Quaternion& q1, const Quaternion& q2)
	{
		return ((q1.x == q2.x) && (q1.y == q2.y) &&
			(q1.z == q2.z) && (q1.w == q2.w));
	}

	bool operator != (const Quaternion& q1, const Quaternion& q2)
	{
		return ((q1.x != q2.x) || (q1.y != q2.y) ||
			(q1.z != q2.z) || (q1.w != q2.w));
	}

	Quaternion operator * (const Quaternion& q1, const Quaternion& q2)
	{
		Quaternion q;

		q.x = q1.y * q2.z - q1.z * q2.y + q1.w * q2.x + q1.x * q2.w;
		q.y = q1.z * q2.x - q1.x * q2.z + q1.w * q2.y + q1.y * q2.w;
		q.z = q1.x * q2.y - q1.y * q2.x + q1.w * q2.z + q1.z * q2.w;
		q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
		return q;
	}

	Quaternion operator * (const Quaternion& q, const Vec3& v)
	{
		return Quaternion
		(
			q.w * v.x + q.y * v.z - q.z * v.y,
			q.w * v.y + q.z * v.x - q.x * v.z,
			q.w * v.z + q.x * v.y - q.y * v.x,
			-(q.x * v.x + q.y * v.y + q.z * v.z)
		);
	}

	Quaternion operator * (const Quaternion& q, f32 f)
	{
		Quaternion q1;
		q1.x = q.x * f;
		q1.y = q.y * f;
		q1.z = q.z * f;
		q1.w = q.w * f;
		return q1;
	}

	Quaternion operator * (f32 f, const Quaternion& q)
	{
		Quaternion q1;
		q1.x = q.x * f;
		q1.y = q.y * f;
		q1.z = q.z * f;
		q1.w = q.w * f;
		return q1;
	}

	f32 DotProduct(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}

	Quaternion Qlerp(const Quaternion& q1, const Quaternion& q2, f32 t)
	{
		Quaternion ret;
		//ret = q1 + t*(q2-q1);

		Quaternion b;
		if (DotProduct(q1, q2) < 0.0f)
			b.set(-q2.x, -q2.y, -q2.z, -q2.w);
		else b = q2;

		ret = q1 * (1 - t) + b * t;

		ret.normalize();
		return ret;
	}

	Quaternion Qslerp(const Quaternion& q1, const Quaternion& q2, f32 t)
	{
		Quaternion q3;
		f32 dot = DotProduct(q1, q2);

		//dot = cos(theta)
		//if (dot < 0), q1 and q2 are more than 90 degrees apart,
		//so we can invert one to reduce spinning

		if (dot < 0)
		{
			dot = -dot;
			q3.set(-q2.x, -q2.y, -q2.z, -q2.w);
		}
		else
		{
			q3 = q2;
		}

		if (dot < 0.95f)
		{
			f32 angle = static_cast<f32>(acosf(dot));
			f32 sina, sinat, sinaomt;
			sina = sinf(angle);
			sinat = sinf(angle * t);
			sinaomt = sinf(angle * (1 - t));
			return (q1 * sinaomt + q3 * sinat) * (1.0f / sina);
		}

		//if the angle is small, use linear s32erpolation

		else
		{
			return Qlerp(q1, q3, t);
		}



		/*
		f32 fCos = DotProduct(q1,q2);
		if (fCos > 1)
		fCos = 1;
		if (fCos < -1)
		fCos = -1;
		f32 fAngle = acosf(fCos);
		if ( fabs(fAngle) < 0.0001 )
		{
		return q1;
		}
		f32 fSin = sinf(fAngle);
		f32 fInvSin = 1.0f/fSin;
		f32 fCoeff0 = sinf((1.0f-fT)*fAngle)*fInvSin;
		f32 fCoeff1 = sinf(fT*fAngle)*fInvSin;
		return fCoeff0*q1 + fCoeff1*q2;
		*/
	}

	//Quaternion Qsquad(const Quaternion &q1, const Quaternion &q2, const Quaternion &a, const Quaternion &b, f32 t);
	//Quaternion Qsquad(const Quaternion &q1, const Quaternion &q2, const Quaternion &a, f32 t);
	//Quaternion Qspline(const Quaternion &q1, const Quaternion &q2, const Quaternion &q3);
	//Quaternion QslerpNoInvert(const Quaternion &q1, const Quaternion &q2, f32 t);
	Quaternion Qexp(const Quaternion &q);
	Quaternion Qlog(const Quaternion &q);
	Quaternion SimpleRotation(const Vec3 &a, const Vec3 &b);

}

#endif //WF_MATH_H
