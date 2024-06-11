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
	auto *o = new TWidget;
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
	auto *panel = new TPanel;
	panel->setBackground(window::Svg::load(svgPath));
	return panel;
}

/** Creates a ThemedSvgPanel and loads the light/dark SVGs from the given paths. */
template<class TPanel = app::ThemedSvgPanel>
TPanel *createPanel(std::string lightSvgPath, std::string darkSvgPath) {
	auto *panel = new TPanel;
	panel->setBackground(window::Svg::load(lightSvgPath), window::Svg::load(darkSvgPath));
	return panel;
}

template<class TParamWidget>
TParamWidget *createParam(math::Vec pos, engine::Module *module, int paramId) {
	auto *o = new TParamWidget;
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
	auto *o = new TPortWidget;
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
	auto *o = new TPortWidget;
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
	auto *o = new TModuleLightWidget;
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
