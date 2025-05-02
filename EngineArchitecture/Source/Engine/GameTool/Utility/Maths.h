#pragma once

#include <limits>
#include <cmath>

/*
 Namespace providing mathematical constants and utility functions.
 */
namespace Maths
{
    const float PI = 3.1415926535f; // Pi constant (approx. 3.14159).
    const float TWO_PI = PI * 2.0f; // 2 * Pi.
    const float PI_HALVED = PI / 2.0f; // Pi / 2.
    const float INFINITY_POS = std::numeric_limits<float>::infinity(); // Positive infinity.
    const float INFINITY_NEG = -INFINITY_POS; // Negative infinity.

    /*
     * Converts degrees to radians.
     * @param degrees Angle in degrees.
     * @return Angle in radians.
     */
    inline float ToRad(float degrees) { return degrees * PI / 180.0f; }
    /*
     * Converts radians to degrees.
     * @param radians Angle in radians.
     * @return Angle in degrees.
     */
    inline float ToDeg(float radians) { return radians * 180.0f / PI; }

    /*
     * Checks if a float value is near zero within a small epsilon range.
     * @param val The value to check.
     * @param epsilon Threshold to consider zero (default: 0.001f).
     * @return True if value is near zero, false otherwise.
     */
    inline bool NearZero(float val, float epsilon = 0.001f) { return fabs(val) <= epsilon; }

    /*
     * Returns the maximum of two values.
     * @tparam T Type of values to compare.
     * @param a First value.
     * @param b Second value.
     * @return The greater of a and b.
     */
    template<typename T>
    T Max(const T& a, const T& b) { return a < b ? b : a; }
    /*
     * Returns the minimum of two values.
     * @tparam T Type of values to compare.
     * @param a First value.
     * @param b Second value.
     * @return The lesser of a and b.
     */
    template<typename T>
    T Min(const T& a, const T& b) { return a < b ? a : b; }
    /*
     * Clamps a value between a lower and upper bound.
     * @tparam T Type of the value.
     * @param val The value to clamp.
     * @param lower Lower bound.
     * @param upper Upper bound.
     * @return Clamped value.
     */
    template<typename T>
    T Clamp(const T& val, const T& lower, const T& upper) { return Min(upper, Max(val, lower)); }

    /*
     * Returns the absolute value of a float.
     * @param val Value to process.
     * @return Absolute value.
     */
    inline float Abs(float val) { return fabs(val); }

    /*
     * Computes the cosine of an angle (in radians).
     * @param angle Angle in radians.
     * @return Cosine of the angle.
     */
    inline float Cos(float angle) { return cosf(angle); }
    /*
     * Computes the sine of an angle (in radians).
     * @param angle Angle in radians.
     * @return Sine of the angle.
     */
    inline float Sin(float angle) { return sinf(angle); }
    /*
     * Computes the tangent of an angle (in radians).
     * @param angle Angle in radians.
     * @return Tangent of the angle.
     */
    inline float Tan(float angle) { return tanf(angle); }

    /*
     * Computes the arccosine of a value.
     * @param angle Value in range [-1, 1].
     * @return Arccosine in radians.
     */
    inline float ACos(float angle) { return acosf(angle); }
    /*
     * Computes the arctangent of y/x using signs to determine the correct quadrant.
     * @param opposite Opposite side length (y).
     * @param adjacent Adjacent side length (x).
     * @return Arctangent in radians.
     */
    inline float ATan2(float opposite, float adjacent) { return atan2f(opposite, adjacent); }
    /*
     * Computes the cotangent of an angle (in radians).
     * @param angle Angle in radians.
     * @return Cotangent of the angle.
     */
    inline float Cot(float angle) { return 1.0f / Tan(angle); }

    /*
     * Performs linear interpolation between two values.
     * @param a Start value.
     * @param b End value.
     * @param t Interpolation factor (typically in range [0, 1]).
     * @return Interpolated value.
     */
    inline float Lerp(float a, float b, float t) { return a + t * (b - a); }

    /*
     * Computes the square root of a value.
     * @param val Input value.
     * @return Square root of the input.
     */
    inline float Sqrt(float val) { return sqrtf(val); }

    /*
     * Computes the floating-point remainder of division.
     * @param numer Numerator.
     * @param denom Denominator.
     * @return Remainder after division.
     */
    inline float Fmod(float numer, float denom) { return std::fmod(numer, denom); }

    /*
     * Rounds a float to the nearest integer.
     * @param val Float value to round.
     * @return Rounded integer.
     */
    inline int Round(float val) { return static_cast<int>(val); }
}

