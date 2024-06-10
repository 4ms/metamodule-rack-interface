#pragma once
#include <app/SliderKnob.hpp>
#include <app/common.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>

namespace rack::app
{

/** Behaves like a knob but linearly moves an widget::SvgWidget between two points.
Can be used for horizontal or vertical linear faders.
*/
struct SvgSlider : app::SliderKnob {
	widget::FramebufferWidget *fb;
	widget::SvgWidget *background;
	widget::SvgWidget *handle;
	math::Vec minHandlePos, maxHandlePos;

	SvgSlider();
	~SvgSlider() override;
	void setBackgroundSvg(std::shared_ptr<window::Svg> svg);
	void setHandleSvg(std::shared_ptr<window::Svg> svg);
	void setHandlePos(math::Vec minHandlePos, math::Vec maxHandlePos);
	void setHandlePosCentered(math::Vec minHandlePosCentered, math::Vec maxHandlePosCentered);
};

} // namespace rack::app
