#pragma once

#include <cstdint>

class SmoothColorCode {
private:
	uint8_t code_ = 0;
	mutable bool increasing_ = true;

public:
	inline SmoothColorCode &operator++()
	{
		if (increasing_) {
			++code_;
		} else {
			--code_;
		}
		if (code_ == UINT8_MAX) {
			increasing_ = false;
		}
		if (code_ == 0) {
			increasing_ = true;
		}
		return *this;
	}
	inline SmoothColorCode operator++(int)
	{
		SmoothColorCode temp = *this;
		++*this;
		return temp;
	}

	inline operator uint8_t() const
	{
		return code_;
	}
};
