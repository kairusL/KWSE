#pragma once

namespace KWSE::Math
{
	struct Matrix4;

	struct Quaternion
	{
		float w, x, y, z;

		constexpr Quaternion() noexcept : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
		constexpr Quaternion(float w, float x, float y, float z) noexcept : w(w), x(x), y(y), z(z) {}

		const static Quaternion Zero;
		const static Quaternion Identity;


		static Quaternion RotationAxis(const Vector3& axis, float rad);
		static Quaternion RotationMatrix(const Matrix4& m);
		static Quaternion RotationLook(const Vector3& direction, const Vector3& up = Vector3::YAxis);
		static Quaternion RotationFromTo(const Vector3& from, const Vector3& to);

		constexpr Quaternion operator-() const { return { Quaternion(-w ,-x,-y,-z) }; }
		constexpr Quaternion operator+(const Quaternion& q) const {
			return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
		}
		constexpr Quaternion operator-(const Quaternion& q) const { return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z); }
		constexpr Quaternion operator*(const Quaternion& q) const
		{
			return
				Quaternion
				// x y z w
				// 0 1 2 3 
				((q.w * w) + (-q.x * x) + (-q.y * y) + (-q.z * z),     //00-11-22-33
				 (q.w * x) + (q.x * w) + (-q.y * z) + (q.z * y),    //01+10+23-32
				 (q.w * y) + (q.x * z) + (q.y * w) + (-q.z * x),     //02-13+20+31
				 (q.w * z) + (-q.x * y) + (q.y * x) + (q.z * w));      //03+12-21+30 		
		}
		constexpr Quaternion operator*(float s) const { return Quaternion(w * s, x * s, y * s, z * s); }
		Quaternion operator/(float s) const { return Quaternion(w / s, x / s, y / s, z / s); }


	};

	// Add to Matrix4.h:
	// static Matrix4 RotationQuaternion(const Quaternion& q);

	// Add to EngineMath.h:
	// inline float Magnitude(const Quaternion& q);
	// inline Quaternion Normalize(const Quaternion& q);
	// constexpr Quaternion Lerp(Quaternion q0, Quaternion q1, float t);
	// Quaternion Slerp(Quaternion q0, Quaternion q1, float t);
}