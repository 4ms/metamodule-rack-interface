#pragma once
#include <common.hpp>
#include <settings.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>
#include <widget/Widget.hpp>

namespace rack::app
{

struct SvgScrew : widget::Widget {
	widget::FramebufferWidget *fb=&_fb;
	widget::SvgWidget *sw=&_sw;

	void setSvg(std::shared_ptr<window::Svg> svg) {
	}

	private:
	widget::FramebufferWidget _fb;
	widget::SvgWidget _sw;
};

struct ThemedSvgScrew : SvgScrew {
	std::shared_ptr<window::Svg> lightSvg;
	std::shared_ptr<window::Svg> darkSvg;

	void setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
		this->lightSvg = lightSvg;
		this->darkSvg = darkSvg;
		SvgScrew::setSvg(settings::preferDarkPanels ? darkSvg : lightSvg);
	}
};

} // namespace rack::app
