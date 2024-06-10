#pragma once
#include <app/CircularShadow.hpp>
#include <app/common.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/OpaqueWidget.hpp>
#include <widget/SvgWidget.hpp>

namespace rack::app
{

struct SvgButton : widget::OpaqueWidget {
	widget::FramebufferWidget *fb;
	CircularShadow *shadow;
	widget::SvgWidget *sw;

	std::vector<std::shared_ptr<window::Svg>> frames;

	SvgButton();
	~SvgButton() override;
	void addFrame(std::shared_ptr<window::Svg> svg);
};

} // namespace rack::app
