#include "SpeedAnalyzer.h"
#include "SpeedAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

SpeedAnalyzer::SpeedAnalyzer()
:	Analyzer2(),  
	mSettings( new SpeedAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

SpeedAnalyzer::~SpeedAnalyzer()
{
	KillThread();
}

void SpeedAnalyzer::SetupResults()
{
	mResults.reset( new SpeedAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void SpeedAnalyzer::WorkerThread()
{
	mSampleRateHz = GetSampleRate();

	mSpeed = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSpeed->GetBitState() == BIT_LOW )
  {
		mSpeed->AdvanceToNextEdge();
  }

	for( ; ; )
	{
    Frame frame;
    frame.mStartingSampleInclusive = mSpeed->GetSampleNumber();
		mSpeed->AdvanceToNextEdge(); // falling edge -- end of the sensor pulse
    mSpeed->AdvanceToNextEdge(); // rising edge -- end of the cycle pulse
    frame.mEndingSampleInclusive = mSpeed->GetSampleNumber();

    S64 speed_samples = frame.mEndingSampleInclusive - frame.mStartingSampleInclusive;
    double speedRPM = 60.0 * mSampleRateHz / (double)speed_samples;
    frame.mData1 = speedRPM;
    frame.mFlags = 0;

		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
	}
}

bool SpeedAnalyzer::NeedsRerun()
{
	return false;
}

U32 SpeedAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 SpeedAnalyzer::GetMinimumSampleRateHz()
{
	return 500;
}

const char* SpeedAnalyzer::GetAnalyzerName() const
{
	return "Speed Pulse";
}

const char* GetAnalyzerName()
{
	return "Speed Pulse";
}

Analyzer* CreateAnalyzer()
{
	return new SpeedAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
