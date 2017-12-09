#include "ServoAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


ServoAnalyzerSettings::ServoAnalyzerSettings()
:	mInputChannel( UNDEFINED_CHANNEL )
{
	mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mInputChannelInterface->SetTitleAndTooltip( "Servo", "Standard Servo Pulse" );
	mInputChannelInterface->SetChannel( mInputChannel );

	AddInterface( mInputChannelInterface.get() );

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mInputChannel, "Servo", false );
}

ServoAnalyzerSettings::~ServoAnalyzerSettings()
{
}

bool ServoAnalyzerSettings::SetSettingsFromInterfaces()
{
	mInputChannel = mInputChannelInterface->GetChannel();

	ClearChannels();
	AddChannel( mInputChannel, "Servo Pulse", true );

	return true;
}

void ServoAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
}

void ServoAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;

	ClearChannels();
	AddChannel( mInputChannel, "Servo Pulse", true );

	UpdateInterfacesFromSettings();
}

const char* ServoAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;

	return SetReturnString( text_archive.GetString() );
}
