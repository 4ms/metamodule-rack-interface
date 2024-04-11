#pragma once
#include <app/CircularShadow.hpp>
#include <app/PortWidget.hpp>
#include <app/common.hpp>
#include <settings.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>

namespace rack::app
{

struct SvgPort : PortWidget {
	widget::FramebufferWidget *fb = &_fb;
	CircularShadow *shadow = &_shadow;
	widget::SvgWidget *sw = &_sw;

	std::string svg_filename; //TODO: instead use sw->svg->filename;

	SvgPort();

	void setSvg(std::shared_ptr<window::Svg> svg);
	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}

private:
	widget::FramebufferWidget _fb;
	CircularShadow _shadow;
	widget::SvgWidget _sw;
};

struct ThemedSvgPort : SvgPort {
	std::shared_ptr<window::Svg> lightSvg;
	std::shared_ptr<window::Svg> darkSvg;

	void setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg);
};

} // namespace rack::app
