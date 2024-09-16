#pragma once
#include <app/ModuleLightWidget.hpp>
#include "util/colors_rgb565.hh"

namespace rack::widget
{

struct MetaModuleDisplay : rack::app::ModuleLightWidget {

	std::string text = "";
	std::string font = "";
	RGB565 color = Colors565::Grey;
};

} // namespace rack::widget
