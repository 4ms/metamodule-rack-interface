#pragma once
#include <app/CircularShadow.hpp>
#include <app/Knob.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>
#include <widget/TransformWidget.hpp>

namespace rack::app
{

/** A knob which rotates an SVG and caches it in a framebuffer */
struct SvgKnob : Knob {
	widget::FramebufferWidget *fb;
	CircularShadow *shadow;
	widget::SvgWidget *sw;
	widget::TransformWidget *tw;

	SvgKnob();
	void setSvg(std::shared_ptr<window::Svg> svg);
};

} // namespace rack::app
