
#ifndef GATEWAY_HH
#define GATEWAY_HH

#include "ExtInterface.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include <iostream>
#include <unistd.h>
#include "Config.h"
#include "SharedMem.h"
#include <map>
#include "DebugCommand.h"
using  namespace  Comms;
using  namespace ConfigUtil;

class Capsule_GateWay : public UMLRTCapsule
{
public:
    Capsule_GateWay( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PortId
    {
        port_commandTimer,
        port_configTimer,
        port_extComm
    };
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        commWithSharedMem,
        configLoad,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[3];
    State currentState;
    void entryaction_____commWithSharedMem( const UMLRTMessage * msg );
    void entryaction_____configLoad( const UMLRTMessage * msg );
    void transitionaction_____extCommand( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____processAndForwardEvent( const UMLRTMessage * msg );
    void transitionaction_____registerCapsule( const UMLRTMessage * msg );
    void transitionaction_____replySelfExec( const UMLRTMessage * msg );
    void transitionaction_____setupSharedMem( const UMLRTMessage * msg );
    void actionchain_____extCommand( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____processAndForwardEvent( const UMLRTMessage * msg );
    void actionchain_____reconfigSHM( const UMLRTMessage * msg );
    void actionchain_____registerCapsule( const UMLRTMessage * msg );
    void actionchain_____replySelfExec( const UMLRTMessage * msg );
    void actionchain_____setupSharedMem( const UMLRTMessage * msg );
    State state_____commWithSharedMem( const UMLRTMessage * msg );
    State state_____configLoad( const UMLRTMessage * msg );
protected:
    UMLRTTimerProtocol_baserole commandTimer;
public:
    enum BorderPortId
    {
        borderport_commandTimer,
        borderport_configTimer,
        borderport_extComm
    };
protected:
    UMLRTTimerProtocol_baserole configTimer;
    ExtInterface::Base extComm;
public:
    enum PartId
    {
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    ConfigUtil::Config config;
    SharedMem eventSharedMemory;
    std::map<std::string,int> registeredCapsules;
    SharedMem commandSharedMemory;
};
extern const UMLRTCapsuleClass GateWay;

#endif

