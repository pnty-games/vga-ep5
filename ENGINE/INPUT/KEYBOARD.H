#ifndef __VGKEYBOARD_H
#define __VGKEYBOARD_H

#define NUM_KEYS (128)

class VGInput;

class VGKeyboard {
private:
	VGInput* _Input;

	volatile unsigned char _KeyState[NUM_KEYS];
  unsigned char _PrevState[NUM_KEYS];

public:

	VGKeyboard(VGInput* _input);
  ~VGKeyboard();

  unsigned char GetState(unsigned char _keyCode) const { return _KeyState[_keyCode]; }
  unsigned char GetPrevState(unsigned char _keyCode) const { return _PrevState[_keyCode]; }

  void HandleInt9();
	void Poll();
};

#endif
