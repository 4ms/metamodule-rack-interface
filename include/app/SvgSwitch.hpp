#pragma once
#include <app/CircularShadow.hpp>
#include <app/Switch.hpp>
#include <app/common.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>

namespace rack::app
{

struct SvgSwitch : Switch {
	widget::FramebufferWidget *fb;
	CircularShadow *shadow;
	widget::SvgWidget *sw;

	std::vector<std::shared_ptr<window::Svg>> frames;

	// Use frames 0 and 1 when the mouse is pressed and released, instead of using the param value as the frame index.
	bool latch = false;

	SvgSwitch();
	~SvgSwitch() override;
	void addFrame(std::shared_ptr<window::Svg> svg);
};

using SVGSwitch = SvgSwitch;

} // namespace rack::app
