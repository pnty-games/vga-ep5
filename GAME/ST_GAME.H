#ifndef __ST_GAME_H
#define __ST_GAME_H

#include "engine\defs.h"
#include "engine\gamestat.h"

#include <mem.h>

class Engine;
class VGInputLayer;
class VGPanel;
class VGSprite;

class StateGame : public GameState {
public:
	struct PanelLayer {
    VGPanel* Panel;
  	VGPanel* Title;
  	VGPanel* Content;
  	VGInputLayer* Layer;
  };

  PanelLayer _PanelLayers[3];

	StateGame() {
		memset(_PanelLayers, 0, sizeof(PanelLayer) * 3);
	}

  void Select(byte_t _index);

	virtual void Enter(Engine* _engine);
  virtual void Exit();

  virtual void Tick();
  virtual void Render();
};

#endif
