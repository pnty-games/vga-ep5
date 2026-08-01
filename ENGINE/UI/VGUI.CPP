#include "engine\ui\vgui.h"
#include "engine\ui\vgpanel.h"

#include <dos.h>

void VGUI::Init() {
	_Regenerate = true;
}

void VGUI::Render(PixelBuffer* _dest) {
  for (int rootIndex = 0, numRoots = _Roots.Num(); rootIndex < numRoots; ++rootIndex) {
		VGPanel* root = _Roots[rootIndex];
		root->Draw(_dest);
  }
}

void VGUI::PostTick() {
	Regenerate();
}

void VGUI::Regenerate() {
	if (!_Regenerate) {
  	return;
  }

  _Regenerate = false;

  _Panels.Clear();
  VGVector<VGPanel*> queue;
  for (int rootIndex = 0, numRoots = _Roots.Num(); rootIndex < numRoots; ++rootIndex) {
  	queue.PushBack(_Roots[rootIndex]);
  }

  while (!queue.Empty()) {
		VGPanel* panel = queue.PopFront();
    _Panels.PushBack(panel);
    panel->Unsettle();

		const VGVector<VGPanel*>& children = panel->Children();
    for (int ci = 0, numc = children.Num(); ci < numc; ++ci) {
     	VGPanel* child = children[ci];
      queue.PushBack(child);
		}
  }

  for (int panelIndex = 0, nump = _Panels.Num(); panelIndex < nump; ++panelIndex) {
		VGPanel* panel = _Panels[panelIndex];
    panel->Settle();
  }
}

void VGUI::AddRoot(VGPanel* _root) {
	_Roots.PushBack(_root);
	_Regenerate = true;
}

// TODO: Add a remove you sloppy guy