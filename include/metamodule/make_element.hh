#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{

Element make_element_output(rack::app::SvgPort const *widget, BaseElement b);
Element make_element_input(rack::app::SvgPort const *widget, BaseElement b);
Element make_element(rack::app::Knob const *widget, BaseElement b);
Element make_element(rack::app::SvgKnob *widget, BaseElement b);
Element make_element_slideswitch(rack::app::SvgSlider const *widget, BaseElement b);
Element make_element(rack::app::SvgSlider const *widget, BaseElement b);
Element make_element(rack::componentlibrary::Rogan const *widget, BaseElement b);
Element make_element(rack::app::SvgSwitch const *widget, BaseElement b);
Element make_element(rack::app::SvgScrew const *widget, BaseElement);
Element make_element(rack::app::ParamWidget const *widget, BaseElement el);
Element make_element(rack::widget::SvgWidget const *widget, BaseElement el);
Element make_element(rack::app::SliderKnob const *widget, BaseElement b);
Element make_element(rack::app::MultiLightWidget const *widget, BaseElement el);
Element make_element_lightslider(rack::app::SvgSlider const *widget, BaseElement el);

Element make_multi_led_element(std::string_view image, rack::app::MultiLightWidget const *, BaseElement const &);
Element make_momentary_rgb(std::string_view image, BaseElement const &el);
Element make_latching_rgb(std::string_view image, BaseElement const &el);
Element make_latching_mono(std::string_view image, NVGcolor c, BaseElement const &el);
Element make_momentary_mono(std::string_view image, NVGcolor c, BaseElement const &el);
Element make_button_light(rack::app::MultiLightWidget const *, rack::app::SvgSwitch const *, BaseElement const &);

//
// Button with lights
//

template<typename LightBaseT>
Element make_element(rack::componentlibrary::VCVLightBezel<LightBaseT> const *widget, BaseElement el) {
	return make_button_light(widget->light, widget, el);
}

//
// SVG Light
//

template<typename LightBaseT>
Element make_element(rack::componentlibrary::TSvgLight<LightBaseT> const *widget, BaseElement el) {
	return make_multi_led_element(widget->sw->svg->filename, widget, el);
}

} // namespace MetaModule
