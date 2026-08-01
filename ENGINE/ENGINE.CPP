#include "engine\engine.h"

#include "engine\input\vginput.h"
#include "engine\video\mode13h.h"
#include "engine\ui\vgui.h"

#define CGS if (_GameState == null) { return false; } _GameState

void Engine::Init() {
	_Input = new VGInput();
  _Video = new Mode13h();
  _UI = new VGUI;
}

bool Engine::Run() {
	if (_GameState == null) {
  	return false;
  }

  _Input->Poll();


  CGS->Tick();
  _UI->PostTick();

  _Video->Clear(0);
  CGS->Render();
  _UI->Render(_Video->Pixels());
  _Video->Present();

	return _GameState != null; // return 1 on "continue"
}

void Engine::Shutdown() {
  delete _UI;
	delete _Video;
	delete _Input;
}

void Engine::SetGameState(GameState* _newState) {
	if (_GameState != null) {
  	_GameState->Exit();
    _GameState = null;
  }

  _GameState = _newState;
  if (_newState != null) {
  	_newState->Enter(this);
	}
}