#include "game\st_game.h"
#include "engine\engine.h"

#include "engine\input\inaction.h"
#include "engine\input\inlayer.h"
#include "engine\input\vginput.h"
#include "engine\input\keyboard.h"
#include "engine\input\keycodes.h"
#include "engine\render\biostext.h"
#include "engine\render\vgsprite.h"
#include "engine\render\pxlbuff.h"
#include "engine\render\vgpcx.h"
#include "engine\types\vgrect.h"
#include "engine\ui\vgui.h"
#include "engine\ui\vgpanel.h"

#include "engine\video\mode13h.h"

#include <stdlib.h>

static VGBIOSText* Font;

static uint16_t EnterKey = (uint16_t(VK::Enter << 8)) | InputFlag::Pressed;
static uint16_t TabKey = (uint16_t(VK::Tab << 8)) | InputFlag::Pressed;

class InKey : public VGInputAction {
	VGPanel* _Title;
  VGPanel* _Content;
  StateGame* _StateGame;
  int _Next;

public:
	InKey(VGPanel* _title, VGPanel* _content, StateGame* _sg, int _n) :
   _Title(_title), _Content(_content), _StateGame(_sg), _Next(_n) { ; }

	virtual bool React() {
  	if (Action() == EnterKey) {
    	_Content->SetLabelColor(7);
      return true;
    }

    if (Action() == TabKey) {
      _Title->SetLabelColor(22);
      _Content->SetLabelColor(22);
      _StateGame->Select(_Next);
			return true;
    }

    return false;
  }
};

StateGame::PanelLayer CreatePanel(
 const VGString& _name, int _x, int _y,
 const VGString& _title, const VGString& _content,
 StateGame* _state, byte_t _nextIndex) {
	VGPanel* outline = new VGPanel();
  VGPanel* panel = new VGPanel();
  VGPanel* title = new VGPanel();
  VGPanel* content = new VGPanel();

  outline->AddChild(panel);
  panel->AddChild(title);
  panel->AddChild(content);

  outline->SetFill(17);
  panel->SetFill(19);

	panel->SetName(_name);
  title->SetName(_name + " Label");
  content->SetName(_name + " Content");

  int titleWidth = _title.Length() * 8;
  int contentWidth = _content.Length() * 8;

  int textWidth = vmax(titleWidth, contentWidth);

  int width = 16 + textWidth; // padding both sides with 8px
  int height = 42; // 16 px pad + 8px text + 16px pad + 2px title

	title->SetLabel(_title.c_str());
  title->SetLabelColor(22);
  title->SetText(Font);
  title->SetRect(VGRect((width - titleWidth) / 2, -6, titleWidth, 8));

  content->SetLabel(_content.c_str());
  content->SetLabelColor(22);
  content->SetText(Font);
  content->SetRect(VGRect((width - contentWidth) / 2, 16, contentWidth, 8));

  panel->SetRect(VGRect(2, 2, width, height));
  outline->SetRect(VGRect(_x, _y, width + 4, height + 4));

  VGInputAction* enterAction = new InKey(title, content, _state, _nextIndex);
  VGInputAction* tabAction = new InKey(title, content, _state, _nextIndex);

  VGInputLayer* layer = new VGInputLayer(true);
  layer->Bind(EnterKey, VGOwnPtr<VGInputAction>(enterAction));
  layer->Bind(TabKey, VGOwnPtr<VGInputAction>(tabAction));

  StateGame::PanelLayer pl;
  pl.Panel = outline;
  pl.Title = title;
  pl.Content = content;
  pl.Layer = layer;

  return pl;
}

void StateGame::Enter(Engine* _engine) {
	GameState::Enter(_engine);

  VGUI* UI = _Engine->UI();

  Font = new VGBIOSText();

  _PanelLayers[0] = CreatePanel("Left", 60,  5, "1", "Accept", this, 1);
  _PanelLayers[1] = CreatePanel("Middle", 140, 5, "2", "Enter", this, 2);
  _PanelLayers[2] = CreatePanel("Right", 210, 5, "3", "OK", this, 0);

  UI->AddRoot(_PanelLayers[0].Panel);
  UI->AddRoot(_PanelLayers[1].Panel);
  UI->AddRoot(_PanelLayers[2].Panel);
  UI->Regenerate();

  Select(0);
}

void StateGame::Select(byte_t _index) {
	VGInput* input = _Engine->Input();
  PanelLayer& pl = _PanelLayers[_index];
  pl.Title->SetLabelColor(15);
	input->PushLayer(pl.Layer);
}

void StateGame::Exit() {
	for (int i = 0; i < 3; ++i) {
   	PanelLayer& pl = _PanelLayers[i];

    // UI deletes Panels
    // Input deletes InputActions
    // BUT
    // we delete layers
    if (pl.Layer != null) {
	    delete pl.Layer;
    }
  }

  Font = new VGBIOSText();
}

void StateGame::Tick() {
	if (_Engine->Input()->GetKeyboard()->GetState(0x01)) {
  	_Engine->SetGameState(0);
  }
}

void StateGame::Render() {

}
