#ifndef SPEED_ANALYZER_H
#define SPEED_ANALYZER_H

#include <Analyzer.h>
#include "SpeedAnalyzerResults.h"
#include "SpeedSimulationDataGenerator.h"

class SpeedAnalyzerSettings;
class ANALYZER_EXPORT SpeedAnalyzer : public Analyzer2
{
public:
  SpeedAnalyzer();
  virtual ~SpeedAnalyzer();

  virtual void SetupResults();
  virtual void WorkerThread();

  virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
  virtual U32 GetMinimumSampleRateHz();

  virtual const char* GetAnalyzerName() const;
  virtual bool NeedsRerun();

protected: //vars
  std::auto_ptr< SpeedAnalyzerSettings > mSettings;
  std::auto_ptr< SpeedAnalyzerResults > mResults;
  AnalyzerChannelData* mSpeed;

  SpeedSimulationDataGenerator mSimulationDataGenerator;
  bool mSimulationInitilized;

  // Speed analysis vars:
  U32 mSampleRateHz;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //SPEED_ANALYZER_H
