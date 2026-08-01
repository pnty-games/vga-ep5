#ifndef __ENGINE_H
#define __ENGINE_H

#include "engine\defs.h"

#include "engine\gamestat.h"

class VGInput;
class VGUI;
class Mode13h;

class Engine {
	VGInput* _Input;
  Mode13h* _Video;
  VGUI* _UI;

  GameState* _GameState;

public:
	Engine() : _GameState(null) { ; }

  VGInput* Input() const { return _Input; }
  Mode13h* Video() const { return _Video; }
  VGUI* UI() const { return _UI; }

	void Init();
  bool Run();
  void Shutdown();

  void SetGameState(GameState* _newState);

};

#endif
