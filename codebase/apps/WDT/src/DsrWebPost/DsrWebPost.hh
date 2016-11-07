#ifndef DsrWebPost_H
#define DsrWebPost_H

#include <toolsa/umisc.h>
#include <tdrp/tdrp.h>
#include <rapformats/DsRadarMsg.hh>
#include <Fmq/DsRadarQueue.hh>
#include <cstdio>
#include <vector>

#include "Args.hh"
#include "Params.hh"
#include "Swap.h"
#include "rda_rpg_message_header.h"
#include "basedata.h"
#include "generic_basedata.h"
#include "metadata_block.h"

using namespace std;

class DsrWebPost {
  
public:

  // constructor

  DsrWebPost (int argc, char **argv);

  // destructor
  
  ~DsrWebPost();

  // run 

  int Run();

  // check constructor OK

  int isOK;

protected:
  
private:
  
  string _progName;
  char *_paramsPath;
  Args _args;
  Params _params;
  
  FILE *_out;
  time_t _startTime;
  time_t _endTime;

  int _scanType;
  int _scanMode;
  int _rayNumInVol;

  bool _snrCensorWarningPrinted;

  int _readMsg(DsRadarQueue &radarQueue,
           DsRadarMsg &radarMsg,
           int &contents,
           DsRadarFlags& radarFlags,
           bool &end_of_vol);

  int _startNewVolume( const time_t& filetime, const std::string &radarid );
  
  //
  // Volume date/time
  //
  std::string _volDateTimeStr;

  //
  // Build the http post
  //
  void _buildHttpHeader(stringstream& hdr, const string& application, const string& payload, const string& remoteServer);

  //
  // Socket open
  //
  int _openSocket(const string &host_name, const int port_number);
  
  //
  // Compress radials using bzip2
  //
  int _bz2CompressRadials( unsigned char **buffer );
  
  //
  // Compress volume header and metadata using bzip2
  //
  int _bz2CompressHeader( unsigned char **buffer, unsigned char *source, unsigned int sourceLen );

  //
  // Free radial memory
  //
  void _freeRadialMemory();

  //
  // Output file
  //
  std::string _outFilePath;

  //
  // Radial status
  //
  unsigned char _radial_status;

  //
  // azimuth number
  //
  uint16_t _aznum;

  //
  // azimuth spacing
  //
  unsigned char _azspacing;
    
  //
  // azimuth difference
  //
  float _azdiff;
  float _prevaz;

  //
  // sequence number
  //
  uint16_t _sequence_num;

  //
  // Message number within the volume
  //
  uint16_t _message_num;

  //
  // Output radials flag
  //
  bool _output_radials;

  //
  // Radial collection
  //
  void _addBeam( const DsRadarBeam& beam,
                 const vector<DsFieldParams*> &fieldParams,
                 const DsRadarParams& radarParams );
  //
  // Encoding base64
  //
  std::string _base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);

  typedef struct
  {

      uint16_t  byteWidth;

      float   offset;

      float   scale;

      uint16_t  dataMin;

      uint16_t  dataMax;
  } mom_conversion;

  std::map< std::string, mom_conversion > _momCharacteristics;

  typedef struct
  {

      RDA_RPG_message_header_t    msg_hdr;

      Generic_basedata_header_t   base;
      
      //
      // Storage for the data block pointers...see below
      //
      uint32_t data_block_pointers[9];

      /*
      uint32_t vol_data_const_pointer;
      
      uint32_t elev_data_const_pointer;
      
      uint32_t radial_data_const_pointer;
      
      uint32_t ref_data_pointer;
      
      uint32_t vel_data_pointer;
      
      uint32_t spw_data_pointer;
      
      uint32_t zdr_data_pointer;
      
      uint32_t phi_data_pointer;
      
      uint32_t rho_data_pointer;
      */

      /*   
       *   Storage pointer for the moment data...no allocation is done until we know the
       *   final size of the data...then we can memcpy the data in
       *
       */
      unsigned char datablocks[0];

  } Generic_basedata_w_t;

  typedef struct message_type31
  {
      NEXRAD_ctm_info ctm;
      Generic_basedata_w_t basedata;
  } Type31_Radar_message;
  
  std::vector< std::pair< Type31_Radar_message*,uint32_t > > _radials;

  //
  // Adjust radial status
  //
  void _adjustRadialStatus( const unsigned char& status );
  
  //
  // Post the radials
  //
  void _postRadials();

};

#endif
