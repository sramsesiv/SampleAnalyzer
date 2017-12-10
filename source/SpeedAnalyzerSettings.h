#ifndef SPEED_ANALYZER_SETTINGS
#define SPEED_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class SpeedAnalyzerSettings : public AnalyzerSettings
{
public:
	SpeedAnalyzerSettings();
	virtual ~SpeedAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
};

#endif //SPEED_ANALYZER_SETTINGS
