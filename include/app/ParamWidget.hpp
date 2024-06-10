#pragma once
#include <app/common.hpp>
#include <engine/ParamQuantity.hpp>
#include <ui/Menu.hpp>
#include <ui/Tooltip.hpp>
#include <widget/OpaqueWidget.hpp>
#include <widget/SvgWidget.hpp>

namespace rack::app
{

struct ParamWidget : widget::OpaqueWidget {
	engine::Module *module = nullptr;
	int paramId = -1;

	virtual void initParamQuantity() {
	}

	engine::ParamQuantity *getParamQuantity();

	void createTooltip() {
	}
	void destroyTooltip() {
	}
	void createContextMenu() {
	}
	virtual void appendContextMenu(ui::Menu *menu) {
	}
	void resetAction() {
	}
};

} // namespace rack::app
