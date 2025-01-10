#pragma once
#include <widget/Widget.hpp>

namespace rack::widget
{

/** Owns and draws a window::Svg */
struct SvgWidget : Widget {
	std::shared_ptr<window::Svg> svg;

	SvgWidget();

	void wrap();

	// FIXME: set box size from svg
	void setSvg(std::shared_ptr<window::Svg> svg);
	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}

	void draw(const DrawArgs &args) override;
};

} // namespace rack::widget
