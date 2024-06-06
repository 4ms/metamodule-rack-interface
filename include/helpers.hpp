#pragma once
#include "metamodule/create_model.hh"

#include <app/SvgPanel.hpp>
#include <engine/Module.hpp>
#include <functional>
#include <math.hpp>
#include <plugin/Model.hpp>
#include <span>
#include <string_view>
#include <ui/Menu.hpp>
#include <ui/MenuItem.hpp>
#include <ui/MenuLabel.hpp>

namespace rack
{

/** Creates a Widget subclass with its top-left at a position. */
template<class TWidget>
TWidget *createWidget(math::Vec pos) {
	TWidget *o = new TWidget;
	o->box.pos = pos;
	return o;
}

/** Creates a Widget subclass with its center at a position. */
template<class TWidget>
TWidget *createWidgetCentered(math::Vec pos) {
	TWidget *o = createWidget<TWidget>(pos);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}

/** Creates an SvgPanel and loads the SVG from the given path. */
template<class TPanel = app::SvgPanel>
TPanel *createPanel(std::string svgPath) {
	TPanel *panel = new TPanel;
	panel->setBackground(window::Svg::load(svgPath));
	return panel;
}

/** Creates a ThemedSvgPanel and loads the light/dark SVGs from the given paths. */
template<class TPanel = app::ThemedSvgPanel>
TPanel *createPanel(std::string lightSvgPath, std::string darkSvgPath) {
	TPanel *panel = new TPanel;
	panel->setBackground(window::Svg::load(lightSvgPath), window::Svg::load(darkSvgPath));
	return panel;
}

template<class TParamWidget>
TParamWidget *createParam(math::Vec pos, engine::Module *module, int paramId) {
	TParamWidget *o = new TParamWidget;
	o->box.pos = pos;
	o->app::ParamWidget::module = module;
	o->app::ParamWidget::paramId = paramId;
	o->initParamQuantity();
	return o;
}

template<class TParamWidget>
TParamWidget *createParamCentered(math::Vec pos, engine::Module *module, int paramId) {
	TParamWidget *o = createParam<TParamWidget>(pos, module, paramId);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}

template<class TPortWidget>
TPortWidget *createInput(math::Vec pos, engine::Module *module, int inputId) {
	TPortWidget *o = new TPortWidget;
	o->box.pos = pos;
	o->app::PortWidget::module = module;
	o->app::PortWidget::type = engine::Port::INPUT;
	o->app::PortWidget::portId = inputId;
	return o;
}

template<class TPortWidget>
TPortWidget *createInputCentered(math::Vec pos, engine::Module *module, int inputId) {
	TPortWidget *o = createInput<TPortWidget>(pos, module, inputId);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}

template<class TPortWidget>
TPortWidget *createOutput(math::Vec pos, engine::Module *module, int outputId) {
	TPortWidget *o = new TPortWidget;
	o->box.pos = pos;
	o->app::PortWidget::module = module;
	o->app::PortWidget::type = engine::Port::OUTPUT;
	o->app::PortWidget::portId = outputId;
	return o;
}

template<class TPortWidget>
TPortWidget *createOutputCentered(math::Vec pos, engine::Module *module, int outputId) {
	TPortWidget *o = createOutput<TPortWidget>(pos, module, outputId);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLight(math::Vec pos, engine::Module *module, int firstLightId) {
	TModuleLightWidget *o = new TModuleLightWidget;
	o->box.pos = pos;
	o->app::ModuleLightWidget::module = module;
	o->app::ModuleLightWidget::firstLightId = firstLightId;
	return o;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLightCentered(math::Vec pos, engine::Module *module, int firstLightId) {
	TModuleLightWidget *o = createLight<TModuleLightWidget>(pos, module, firstLightId);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}

/** Creates a param with a light and calls setFirstLightId() on it.
Requires ParamWidget to have a `light` member.
*/
template<class TParamWidget>
TParamWidget *createLightParam(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	TParamWidget *o = createParam<TParamWidget>(pos, module, paramId);
	o->getLight()->module = module;
	o->getLight()->firstLightId = firstLightId;
	return o;
}

template<class TParamWidget>
TParamWidget *createLightParamCentered(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	TParamWidget *o = createLightParam<TParamWidget>(pos, module, paramId, firstLightId);
	o->box.pos = o->box.pos.minus(o->box.size.div(2));
	return o;
}

//template<typename T>
//T *createElementWidget(math::Vec pos, MetaModule::Coords coord_ref, std::string_view name) {
//	auto *widget = new T;
//	widget->element = MetaModule::make_element(widget, {pos.x, pos.y, coord_ref, name, name});
//	return widget;
//}

//// Creates a Widget and makes the right Element in the Widget
//template<typename T>
//T *createElementParamWidget(
//	math::Vec pos, MetaModule::Coords coord_ref, std::string_view name, engine::Module *module, int paramId) {
//	auto *widget = new T;
//	widget->module = module;
//	widget->paramId = paramId;
//	widget->element = MetaModule::make_element(widget, {pos.x, pos.y, coord_ref, name, name});
//	widget->box.pos = coord_ref == MetaModule::Coords::TopLeft ? pos : pos.minus(widget->box.size.div(2));
//	return widget;
//}

//// Special case for slide widgets because
//// 1) They sometimes offset their position manually in VCV Rack class constructors. Apply those manual adjustments here.
//// 2) If it's a slider with snapEnabled == true, then the element should be a switch, not a slider
//template<typename T>
//T *createElementParamWidget(
//	math::Vec pos, MetaModule::Coords coord_ref, std::string_view name, engine::Module *module, int paramId)
//	requires(std::derived_from<T, app::SvgSlider>)
//{
//	auto *widget = new T;
//	widget->module = module;
//	widget->paramId = paramId;
//	engine::ParamQuantity *pq = widget->getParamQuantity();

//	// Slide switch is SvgSlider type in VCV, so we need to disambiguiate
//	if (pq && pq->snapEnabled)
//		widget->element = MetaModule::make_element_slideswitch(widget, {pos.x, pos.y, coord_ref, name, name});
//	else
//		widget->element = MetaModule::make_element(widget, {pos.x, pos.y, coord_ref, name, name});

//	if (coord_ref == MetaModule::Coords::TopLeft) {
//		widget->box.pos = pos + widget->background->box.pos;
//	} else {
//		widget->box.pos = pos.minus(widget->background->box.size.div(2));
//	}

//	return widget;
//}

//template<class TWidget>
//TWidget *createWidget(math::Vec pos) {
//	return createElementWidget<TWidget>(pos, MetaModule::Coords::TopLeft, "Unknown");
//}

//template<class TWidget>
//TWidget *createWidgetCentered(math::Vec pos) {
//	return createElementWidget<TWidget>(pos, MetaModule::Coords::Center, "Unknown");
//}

//template<class TPanel = app::SvgPanel>
//TPanel *createPanel(std::string svgPath) {
//	auto *panel = new TPanel;
//	panel->setBackground(window::Svg::load(svgPath));
//	return panel;
//}

//template<class TPanel = app::ThemedSvgPanel>
//TPanel *createPanel(std::string lightSvgPath, std::string darkSvgPath) {
//	auto *panel = new TPanel;
//	panel->setBackground(window::Svg::load(lightSvgPath), window::Svg::load(darkSvgPath));
//	return panel;
//}

//template<class TParamWidget>
//requires(std::derived_from<TParamWidget, app::ParamWidget>)
//TParamWidget *createParamImpl(MetaModule::Coords coords, math::Vec pos, engine::Module *module, int paramId) {
//	using namespace MetaModule;

//	auto name = getParamName(module, paramId);
//	auto widget = createElementParamWidget<TParamWidget>(pos, coords, name, module, paramId);

//	if (auto pq = widget->getParamQuantity()) {
//		pq->name = name;
//		set_labels(pq, widget->element);
//	}
//	return widget;
//}

//template<class TParamWidget>
//TParamWidget *createParam(math::Vec pos, engine::Module *module, int paramId) {
//	auto widget = createParamImpl<TParamWidget>(MetaModule::Coords::TopLeft, pos, module, paramId);
//	return widget;
//}

//template<class TParamWidget>
//TParamWidget *createParamCentered(math::Vec pos, engine::Module *module, int paramId) {
//	auto widget = createParamImpl<TParamWidget>(MetaModule::Coords::Center, pos, module, paramId);
//	return widget;
//}

//template<class TPortWidget>
//TPortWidget *createInput(math::Vec pos, engine::Module *module, int inputId) {
//	auto name = getInputName(module, inputId);
//	auto *widget = new TPortWidget;
//	widget->box.pos = pos;
//	widget->portId = inputId;
//	if (widget->getPortInfo())
//		widget->getPortInfo()->name = name;
//	widget->element = MetaModule::make_element_input(widget, {pos.x, pos.y, MetaModule::Coords::TopLeft, name, name});
//	return widget;
//}

//template<class TPortWidget>
//TPortWidget *createInputCentered(math::Vec pos, engine::Module *module, int inputId) {
//	auto name = getInputName(module, inputId);
//	auto *widget = new TPortWidget;
//	widget->box.pos = pos.minus(widget->box.size.div(2));
//	widget->portId = inputId;
//	if (widget->getPortInfo())
//		widget->getPortInfo()->name = name;
//	widget->element = MetaModule::make_element_input(widget, {pos.x, pos.y, MetaModule::Coords::Center, name, name});
//	return widget;
//}

//template<class TPortWidget>
//TPortWidget *createOutput(math::Vec pos, engine::Module *module, int outputId) {
//	auto name = getOutputName(module, outputId);
//	auto *widget = new TPortWidget;
//	widget->box.pos = pos;
//	widget->portId = outputId;
//	if (widget->getPortInfo())
//		widget->getPortInfo()->name = name;
//	widget->element = MetaModule::make_element_output(widget, {pos.x, pos.y, MetaModule::Coords::TopLeft, name, name});
//	return widget;
//}

//template<class TPortWidget>
//TPortWidget *createOutputCentered(math::Vec pos, engine::Module *module, int outputId) {
//	auto name = getOutputName(module, outputId);
//	auto *widget = new TPortWidget;
//	widget->box.pos = pos.minus(widget->box.size.div(2));
//	widget->portId = outputId;
//	if (widget->getPortInfo())
//		widget->getPortInfo()->name = name;
//	widget->element = MetaModule::make_element_output(widget, {pos.x, pos.y, MetaModule::Coords::Center, name, name});
//	return widget;
//}

//template<class TModuleLightWidget>
//TModuleLightWidget *createLight(math::Vec pos, engine::Module *module, int firstLightId) {
//	auto name = getLightName(module, firstLightId);
//	auto widget = createElementWidget<TModuleLightWidget>(pos, MetaModule::Coords::TopLeft, name);
//	widget->box.pos = pos;
//	widget->firstLightId = firstLightId;
//	return widget;
//}

//template<class TModuleLightWidget>
//TModuleLightWidget *createLightCentered(math::Vec pos, engine::Module *module, int firstLightId) {
//	auto name = getLightName(module, firstLightId);
//	auto widget = createElementWidget<TModuleLightWidget>(pos, MetaModule::Coords::Center, name);
//	widget->box.pos = pos.minus(widget->box.size.div(2));
//	widget->firstLightId = firstLightId;
//	return widget;
//}

////
//// Light + Params
////
//template<class TParamWidget>
//TParamWidget *
//createLightParamImpl(math::Vec pos, engine::Module *module, MetaModule::Coords coord_ref, int paramId, int firstLightId)
//	requires(std::derived_from<TParamWidget, app::SvgSlider>)
//{
//	auto name = getParamName(module, paramId);

//	auto *widget = new TParamWidget;
//	widget->element = MetaModule::make_element_lightslider(widget, {pos.x, pos.y, coord_ref, name, name});

//	if (coord_ref == MetaModule::Coords::TopLeft) {
//		widget->box.pos = pos + widget->background->box.pos;
//	} else {
//		widget->box.pos = pos.minus(widget->background->box.size.div(2));
//	}

//	widget->module = module;
//	widget->paramId = paramId;
//	widget->getLight()->module = module;
//	widget->getLight()->firstLightId = firstLightId;

//	return widget;
//}

//template<class TParamWidget>
//TParamWidget *createLightParamImpl(
//	math::Vec pos, engine::Module *module, MetaModule::Coords coords_ref, int paramId, int firstLightId)
////requires(std::derived_from<TParamWidget, app::SvgSwitch>)
//{
//	auto name = getParamName(module, paramId);
//	auto widget = createElementWidget<TParamWidget>(pos, coords_ref, name);
//	widget->box.pos = pos.minus(widget->box.size.div(2));
//	widget->paramId = paramId;
//	return widget;
//}

//template<class TParamWidget>
//TParamWidget *createLightParam(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
//	return createLightParamImpl<TParamWidget>(pos, module, MetaModule::Coords::TopLeft, paramId, firstLightId);
//}

//template<class TParamWidget>
//TParamWidget *createLightParamCentered(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
//	return createLightParamImpl<TParamWidget>(pos, module, MetaModule::Coords::Center, paramId, firstLightId);
//}

//
// Menus
//
template<class TMenu = ui::Menu>
TMenu *createMenu() {
	return nullptr;
}

template<class TMenuLabel = ui::MenuLabel>
TMenuLabel *createMenuLabel(std::string_view text) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
TMenuItem *createMenuItem(std::string_view text, std::string_view rightText = "") {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
TMenuItem *createMenuItem(std::string_view text,
						  std::string_view rightText,
						  std::function<void()> action,
						  bool disabled = false,
						  bool alwaysConsume = false) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createCheckMenuItem(std::string_view text,
								  std::string_view rightText,
								  std::function<bool()> checked,
								  std::function<void()> action,
								  bool disabled = false,
								  bool alwaysConsume = false) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createBoolMenuItem(std::string_view text,
								 std::string_view rightText,
								 std::function<bool()> getter,
								 std::function<void(bool state)> setter,
								 bool disabled = false,
								 bool alwaysConsume = false) {
	return nullptr;
}

template<typename T>
ui::MenuItem *createBoolPtrMenuItem(std::string_view text, std::string_view rightText, T *ptr) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createSubmenuItem(std::string_view text,
								std::string_view rightText,
								std::function<void(ui::Menu *menu)> createMenu,
								bool disabled = false) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createIndexSubmenuItem(std::string_view text,
									 std::vector<std::string> labels,
									 std::function<size_t()> getter,
									 std::function<void(size_t val)> setter,
									 bool disabled = false,
									 bool alwaysConsume = false) {
	return nullptr;
}

template<typename T>
ui::MenuItem *createIndexPtrSubmenuItem(std::string_view text, std::vector<std::string_view> labels, T *ptr) {
	return nullptr;
}

} // namespace rack
