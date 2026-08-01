#ifndef __GAMESTAT_H
#define __GAMESTAT_H

class Engine;

class GameState {
protected:
	Engine* _Engine;

public:
	virtual ~GameState() {;}

  virtual void Enter(Engine* _engine) { _Engine = _engine; }
  virtual void Exit() { ; }

  virtual void Tick() { ; }
  virtual void Render() { ; }
};

#endif