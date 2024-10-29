#pragma once
#include <context.hpp>
#include <ui/Menu.hpp>
#include <ui/MenuEntry.hpp>
#include <ui/common.hpp>

namespace rack::ui
{

struct MenuItem : MenuEntry {
	std::string text;
	std::string rightText;
	bool disabled = false;

	void draw(const DrawArgs &args) override;
	void drawOffset(NVGcontext *vg, float offset = 0);
	void step() override;
	void onEnter(const EnterEvent &e) override;
	void onDragDrop(const DragDropEvent &e) override;
	void doAction(bool consume = true);

	virtual Menu *createChildMenu() {
		return nullptr;
	}

	void onAction(const ActionEvent &e) override;
};

struct ColorDotMenuItem : MenuItem {
	NVGcolor color = color::BLACK_TRANSPARENT;

	void draw(const DrawArgs &args) override;
	void step() override;
};

} // namespace rack::ui
