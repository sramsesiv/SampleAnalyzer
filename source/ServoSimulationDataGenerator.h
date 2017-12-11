#ifndef SERVO_SIMULATION_DATA_GENERATOR
#define SERVO_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class ServoAnalyzerSettings;

class ServoSimulationDataGenerator
{
public:
  ServoSimulationDataGenerator();
  ~ServoSimulationDataGenerator();

  void Initialize( U32 simulation_sample_rate, ServoAnalyzerSettings* settings );
  U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
  ServoAnalyzerSettings* mSettings;
  U32 mSimulationSampleRateHz;

protected:
  void CreateServoPulse();
  std::string mServoText;
  U32 mStringIndex;

  SimulationChannelDescriptor mSerialSimulationData;

};
#endif //SERVO_SIMULATION_DATA_GENERATOR
