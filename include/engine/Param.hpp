#pragma once

namespace rack::engine
{

struct Param {
	float value = 0.f;

	float getValue() const {
		return value;
	}

	void setValue(float value) {
		this->value = value;
	}
};

} // namespace rack::engine
