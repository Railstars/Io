#ifndef __MYCONFIGHANDLER_H__
#define __MYCONFIGHANDLER_H__

#include "MyEventHandler.h"
#include "OLCB_Virtual_Node.h"
#include "OLCB_Datagram_Handler.h"

//XML CDI data, taken from Io_8P_8C_default.xml
static PROGMEM char cdixml[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<cdi>\n<identification>\n<manufacturer>Railstars Limited</manufacturer>\n<model>Io</model>\n<hardwareVersion>1.0</hardwareVersion>\n<softwareVersion>1.0</softwareVersion>\n</identification>\n<segment origin=\"0\" space=\"0\">\n<group offset=\"0\" replication=\"8\">\n<name>Produced Events</name>\n<description>The EventIDs for the outputs</description>\n<eventid/>\n<eventid/>\n</group>\n<group replication=\"8\">\n<name>Consumed Events</name>\n<description>The EventIDs for the inputs</description>\n<eventid/>\n<eventid/>\n</group>\n</segment>\n</cdi>";

//defines from other library
#define MAC_PROTOCOL_ID 0x20

// define the operation codes, full byte

//notice that these conflict with the WIKI http://sourceforge.net/apps/trac/openlcb/wiki/BasicSpecDoc
#define MAC_CMD_WRITE                       0x00
#define MAC_CMD_READ                        0x40
#define MAC_CMD_OPERATION                   0x80
#define MAC_CMD_READ_REPLY                  0x50
#define MAC_CMD_GET_CONFIG_OPTIONS          0x80
#define MAC_CMD_GET_CONFIG_OPTIONS_REPLY    0x82
#define MAC_CMD_GET_ADD_SPACE_INFO          0x84
#define MAC_CMD_GET_ADD_SPACE_INFO_REPLY    0x86
#define MAC_CMD_LOCK                        0x88
#define MAC_CMD_LOCK_REPLY                  0x8A
#define MAC_CMD_GET_UNIQUEID                0x8C
#define MAC_CMD_GET_UNIQUEID_REPLY          0x8E

#define MAC_CMD_FREEZE                      0xA0
#define MAC_CMD_INDICATE                    0xA4
#define MAC_CMD_RESETS                      0xA8


#define MAC_CONFIG_OPTIONS_1_BYTE_WRITE      0x80
#define MAC_CONFIG_OPTIONS_2_BYTE_WRITE      0x40
#define MAC_CONFIG_OPTIONS_4_BYTE_WRITE      0x20
#define MAC_CONFIG_OPTIONS_64_BYTE_WRITE     0x10
#define MAC_CONFIG_OPTIONS_ARBITRARY_WRITE   0x02
#define MAC_CONFIG_OPTIONS_STREAM_WRITE      0x01

#define MAC_CONFIG_OPTIONS_WRITE_UNDER_MASK  0x80
#define MAC_CONFIG_OPTIONS_UNALIGNED_READS   0x40
#define MAC_CONFIG_OPTIONS_UNALIGNED_WRITES  0x20
#define MAC_CONFIG_OPTIONS_MFG_ACDI_FD_READ  0x08
#define MAC_CONFIG_OPTIONS_USR_ACDI_FC_READ  0x04
#define MAC_CONFIG_OPTIONS_USR_ACDI_FC_WRITE 0x02


/* Class to handle Memory Configuration protocol and CDI protocol */
class MyConfigHandler : 
public OLCB_Datagram_Handler
{
public:
  void create(OLCB_Link *link, OLCB_NodeID *nid, MyEventHandler *eventHandler);
//  void update(void);
  void datagramResult(bool accepted, uint16_t errorcode);
  void initialize(void);
  bool processDatagram(void);

  bool MACProcessRead(void);
  bool MACProcessWrite(void);
  bool MACProcessCommand(void);

private:
  MyEventHandler *_eventHandler; //for configuring PC-event memory space
  uint32_t getAddress(uint8_t* data);
  uint8_t decodeLength(uint8_t* data);
  uint8_t decodeSpace(uint8_t* data);
  uint8_t readCDI(uint16_t address, uint8_t length, uint8_t *data);
};


#endif

