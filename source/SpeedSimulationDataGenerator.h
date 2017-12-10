#ifndef SPEED_SIMULATION_DATA_GENERATOR
#define SPEED_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class SpeedAnalyzerSettings;

class SpeedSimulationDataGenerator
{
public:
	SpeedSimulationDataGenerator();
	~SpeedSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, SpeedAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	SpeedAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSpeedByte();
	std::string mSpeedText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSpeedSimulationData;

};
#endif //SPEED_SIMULATION_DATA_GENERATOR
