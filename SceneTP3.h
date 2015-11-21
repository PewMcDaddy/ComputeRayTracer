#ifndef _SCENE_TP3_H_
#define _SCENE_TP3_H_
#include "NuanceurReg.h"

class ArbreRenduINF2705;
class PlanDeCoupe;

class SceneTP3 {
public:
	SceneTP3(Nuanceur* prog);
	~SceneTP3();
	void initialiser();
	void animer();
	void dessiner();

	Nuanceur* progDraw_;
};

#endif // _SCENE_TP3_H_

