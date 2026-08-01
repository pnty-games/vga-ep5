#include "engine\input\inlayer.h"

#include "engine\input\vginput.h"
#include "engine\input\inaction.h"

void VGInputLayer::Bind(uint16_t _packedKey, VGOwnPtr<VGInputAction> _action) {
 	VGVectorPtr<VGInputAction>** ptrActionList = _Actions.Get(_packedKey);
  if (ptrActionList == null) {
		VGVectorPtr<VGInputAction>* newList = new VGVectorPtr<VGInputAction>();
    _Actions.Set(_packedKey, newList);
    ptrActionList = _Actions.Get(_packedKey);
  }

  VGVectorPtr<VGInputAction>* actionList = *ptrActionList;
  actionList->PushBack(_action);
}

bool VGInputLayer::React(VGInput* _input, uint16_t _packedKey) const {
  VGVectorPtr<VGInputAction>** ptrActionList = _Actions.Get(_packedKey);
  if (ptrActionList == null) return false;

  bool handled = false;
  VGVectorPtr<VGInputAction>& actions = **ptrActionList;
  for (uint32_t i = 0, num = actions.Num(); i < num; ++i) {
  	VGInputAction* action = actions[i];
    action->Setup(_input, _packedKey);
    if (action->React()) handled = true;
  }

	return handled;
}