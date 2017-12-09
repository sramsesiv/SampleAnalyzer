#ifndef SERVO_ANALYZER_H
#define SERVO_ANALYZER_H

#include <Analyzer.h>
#include "ServoAnalyzerResults.h"
#include "ServoSimulationDataGenerator.h"

class ServoAnalyzerSettings;
class ANALYZER_EXPORT ServoAnalyzer : public Analyzer2
{
public:
	ServoAnalyzer();
	virtual ~ServoAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< ServoAnalyzerSettings > mSettings;
	std::auto_ptr< ServoAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	ServoSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //SERVO_ANALYZER_H
