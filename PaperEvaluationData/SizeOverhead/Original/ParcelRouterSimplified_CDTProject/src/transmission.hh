
#ifndef TRANSMISSION_HH
#define TRANSMISSION_HH

#include "Parcel.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace transmission
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal transmit( const Parcel & p ) const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
    };
    enum SignalId
    {
        signal_transmit = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
};

#endif

