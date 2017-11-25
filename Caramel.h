#ifndef __CARAMEL__
#define __CARAMEL__

#include "IPlug_include_in_plug_hdr.h"

class Caramel : public IPlug
{
public:
  Caramel(IPlugInstanceInfo instanceInfo);
  ~Caramel();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain = 1.0;
};

#endif
