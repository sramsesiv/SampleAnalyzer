#ifndef SERVO_ANALYZER_RESULTS
#define SERVO_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class ServoAnalyzer;
class ServoAnalyzerSettings;

class ServoAnalyzerResults : public AnalyzerResults
{
public:
  ServoAnalyzerResults( ServoAnalyzer* analyzer, ServoAnalyzerSettings* settings );
  virtual ~ServoAnalyzerResults();

  virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
  virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

  virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
  virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
  virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
  ServoAnalyzerSettings* mSettings;
  ServoAnalyzer* mAnalyzer;
};

#endif //SERVO_ANALYZER_RESULTS
