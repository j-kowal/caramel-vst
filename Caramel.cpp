#include "Caramel.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"


enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kGainX = 125,
  kGainY = 125,
  kKnobFrames = 60
};

Caramel::Caramel(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumPublicParams, kNumPrivateParams, kNumPrograms, instanceInfo)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 50., 0., 100.0, 0.01, "%");
  GetParam(kGain)->SetShape(2.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);

  pGraphics->AttachPanelBackground(&COLOR_RED);
  
  IBitmap* knob = pGraphics->LoadPointerToBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
  pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, knob));
   
 
  IColor textColor = IColor(255, 0, 0, 0);
  IText textProps4(24, &textColor, "Arial", IText::kStyleNormal, IText::kAlignCenter, 0, IText::kQualityDefault);
  pGraphics->AttachControl(new ITextControl(this, DRAW_RECT(IRECT(80, 44, 220, 84)), &textProps4, "Caramel v1 :)"));
  
  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

Caramel::~Caramel() {}

void Caramel::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];

  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2)
  {
    *out1 = *in1 * mGain;
    *out2 = *in2 * mGain;
  }
}

void Caramel::Reset()
{
  TRACE;
  IMutexLock lock(this);
}

void Caramel::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kGain:
      mGain = GetParam(kGain)->Value() / 100.;
      break;

    default:
      break;
  }
}