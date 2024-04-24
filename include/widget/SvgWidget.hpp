#pragma once
#include <widget/Widget.hpp>

namespace rack::widget
{

/** Owns and draws a window::Svg */
struct SvgWidget : Widget {
	std::shared_ptr<window::Svg> svg;

	NVGcolor bgColor{};

	void wrap() {
	}

	void setSvg(std::shared_ptr<window::Svg> svg);
	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}
};

} // namespace rack::widget
