#ifndef _SCENE_TP3_H_
#define _SCENE_TP3_H_
#include "NuanceurReg.h"
#include "NuanceurCalc.h"

class ArbreRenduINF2705;
class PlanDeCoupe;

class SceneTP3 {
public:
	SceneTP3(NuanceurReg* progReg, NuanceurCalc* progCalc);
	~SceneTP3();
	void initialiser();
	void animer();
	void dessiner(GLsizei w, GLsizei h);

	Nuanceur* progDraw_;
	Nuanceur* progCalc_;
};

#endif // _SCENE_TP3_H_

