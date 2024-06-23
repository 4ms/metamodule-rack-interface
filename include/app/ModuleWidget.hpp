#pragma once
#include <app/Knob.hpp>
#include <app/ModuleLightWidget.hpp>
#include <app/ParamWidget.hpp>
#include <app/PortWidget.hpp>
#include <app/SvgButton.hpp>
#include <app/SvgKnob.hpp>
#include <app/SvgPanel.hpp>
#include <app/SvgSlider.hpp>
#include <app/common.hpp>
#include <componentlibrary.hpp>
#include <engine/Module.hpp>
#include <history.hpp>
#include <plugin/Model.hpp>
#include <ui/Menu.hpp>
#include <widget/OpaqueWidget.hpp>

namespace MetaModule
{
struct ModuleWidgetAdaptor;
}

namespace rack::app
{

struct ModuleWidget : widget::Widget {

	std::unique_ptr<rack::app::SvgPanel> panel;
	std::unique_ptr<MetaModule::ModuleWidgetAdaptor> adaptor;

	ModuleWidget();
	~ModuleWidget() override;

	plugin::Model *model = nullptr;

	engine::Module *module = nullptr;

	std::string svg_filename;

	void setModule(engine::Module *m) {
		module = m;
	}

	void setModel(plugin::Model *m) {
		model = m;
	}

	engine::Module *getModule() {
		return module;
	}

	template <class TModule>
	TModule* getModule() {
		return dynamic_cast<TModule*>(getModule());
	}

	plugin::Model *getModel() {
		return model;
	}

	void setPanel(app::SvgPanel *newpanel);

	void setPanel(std::shared_ptr<window::Svg> svg);

	widget::Widget *getPanel();

	// Catch-all:
	void addChild(Widget *w);

	// Rendered as images:
	void addChild(widget::SvgWidget *w);
	void addChild(app::SvgButton *w);
	void addChild(app::SvgScrew *widget);

	// Panels:
	void addChild(SvgPanel *child);
	void addChildBottom(SvgPanel *child);

	// Params:
	void addParam(ParamWidget *param);
	void addParam(Knob *param);
	void addParam(rack::componentlibrary::Rogan *widget);
	void addParam(app::SvgKnob *param);
	void addParam(app::SvgSlider *param);
	void addParam(app::SvgSwitch *param);
	void addParam(app::SliderKnob *param);

	// Button + Light:
	template<typename TLightBase>
	void addParam(componentlibrary::VCVLightBezel<TLightBase> *widget) {
		addLightSwitch(widget, widget->getLight());
	}
	void addLightSwitch(app::SvgSwitch *widget, app::ModuleLightWidget *light);

	// Slider + Light:
	template<typename TBase, typename TLightBase>
	void addParam(componentlibrary::LightSlider<TBase, TLightBase> *widget) {
		addLightSlider(widget, widget->getLight());
	}
	void addLightSlider(app::SvgSlider *slider, app::ModuleLightWidget *light);

	// Lights:
	void addChild(app::ModuleLightWidget *lightWidget);

	template<typename LightBaseT>
	void addChild(componentlibrary::TSvgLight<LightBaseT> *widget) {
		if (widget->sw && widget->sw->svg)
			addSvgLight(widget->sw->svg->filename, widget);
		else
			addChild(widget);
	}
	void addSvgLight(std::string_view image, app::ModuleLightWidget *widget);

	// Ports:
	void addInput(PortWidget *input);
	void addInput(SvgPort *input);
	void addOutput(PortWidget *output);
	void addOutput(SvgPort *output);

	ParamWidget *getParam(int paramId);
	PortWidget *getInput(int portId);
	PortWidget *getOutput(int portId);
	std::vector<ParamWidget *> getParams();
	std::vector<PortWidget *> getPorts();
	std::vector<PortWidget *> getInputs();
	std::vector<PortWidget *> getOutputs();

	// clang-format off
	// These are all no-op:
	void draw(const DrawArgs &args) override { }
	void drawLayer(const DrawArgs &args, int layer) override { }
	virtual void appendContextMenu(ui::Menu *menu) {}
	void onHover(const HoverEvent &e) override { }
	void onHoverKey(const HoverKeyEvent &e) override { }
	void onButton(const ButtonEvent &e) override { }
	void onDragStart(const DragStartEvent &e) override { }
	void onDragEnd(const DragEndEvent &e) override { }
	void onDragMove(const DragMoveEvent &e) override { }
	void onDragHover(const DragHoverEvent &e) override { }
	json_t *toJson(){ return {}; }
	void fromJson(json_t *rootJ){}
	bool pasteJsonAction(json_t *rootJ) { return false; }
	void copyClipboard(){}
	bool pasteClipboardAction(){ return {}; }
	void load(std::string filename){}
	void loadAction(std::string filename){}
	void loadTemplate(){}
	void loadDialog(){}
	void save(std::string filename){}
	void saveTemplate(){}
	void saveTemplateDialog(){}
	bool hasTemplate(){ return {}; }
	void clearTemplate(){}
	void clearTemplateDialog(){}
	void saveDialog(){}
	void disconnect(){}
	void resetAction(){}
	void randomizeAction(){}
	void appendDisconnectActions(history::ComplexAction *complexAction){}
	void disconnectAction(){}
	void cloneAction(bool cloneCables = true){}
	void bypassAction(bool bypassed){}
	void removeAction(){}
	void createContextMenu(){}
	math::Vec getGridPosition(){ return {}; }
	void setGridPosition(math::Vec pos){}
	math::Vec getGridSize(){ return {}; }
	math::Rect getGridBox(){ return {}; }
	// clang-format on
};

} // namespace rack::app
