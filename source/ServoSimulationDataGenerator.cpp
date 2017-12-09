#include "ServoSimulationDataGenerator.h"
#include "ServoAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

ServoSimulationDataGenerator::ServoSimulationDataGenerator()
:	mServoText( "My first analyzer, woo hoo!" ),
	mStringIndex( 0 )
{
}

ServoSimulationDataGenerator::~ServoSimulationDataGenerator()
{
}

void ServoSimulationDataGenerator::Initialize( U32 simulation_sample_rate, ServoAnalyzerSettings* settings )
{
	mSimulationSampleRateHz = simulation_sample_rate;
	mSettings = settings;

	mSerialSimulationData.SetChannel( mSettings->mInputChannel );
	mSerialSimulationData.SetSampleRate( simulation_sample_rate );
	mSerialSimulationData.SetInitialBitState( BIT_LOW );
}

U32 ServoSimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

	while( mSerialSimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		CreateServoPulse();
	}

	*simulation_channel = &mSerialSimulationData;
	return 1;
}

void ServoSimulationDataGenerator::CreateServoPulse()
{
	U8 byte = mServoText[ mStringIndex ];
  U32 pulsesamples =  ((double)(70 + byte) / 100.0) * ((double)mSimulationSampleRateHz / 1000.0);
  U32 periodsamples =  4.0 * ((double)mSimulationSampleRateHz / 1000.0); // Hard-code period to 4ms
	mStringIndex++;
	if( mStringIndex == mServoText.size() )
		mStringIndex = 0;

  mSerialSimulationData.TransitionIfNeeded( BIT_HIGH ); //high-going edge for start of pulse

	mSerialSimulationData.Advance( pulsesamples );

  mSerialSimulationData.TransitionIfNeeded( BIT_LOW ); //low-going edge for end of pulse
	mSerialSimulationData.Advance( periodsamples-pulsesamples ); // end of period
}
