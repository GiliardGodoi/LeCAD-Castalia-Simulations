//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/sensoringTest/Sensoring.msg.
//

#ifndef _SENSORING_M_H_
#define _SENSORING_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "ApplicationPacket_m.h"
#include <string>
using namespace std;
// }}

/**
 * Struct generated from src/node/application/sensoringTest/Sensoring.msg:21 by nedtool.
 */
struct Info
{
    Info();
    unsigned short nodeID;
    double locX;
    double locY;
    opp_string payload;
    double sensData;
};

void doPacking(cCommBuffer *b, Info& a);
void doUnpacking(cCommBuffer *b, Info& a);

/**
 * Class generated from <tt>src/node/application/sensoringTest/Sensoring.msg:29</tt> by nedtool.
 * <pre>
 * packet Sensoring extends ApplicationPacket
 * {
 *     Info extraData;
 * }
 * </pre>
 */
class Sensoring : public ::ApplicationPacket
{
  protected:
    Info extraData_var;

  private:
    void copy(const Sensoring& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Sensoring&);

  public:
    Sensoring(const char *name=NULL, int kind=0);
    Sensoring(const Sensoring& other);
    virtual ~Sensoring();
    Sensoring& operator=(const Sensoring& other);
    virtual Sensoring *dup() const {return new Sensoring(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Info& getExtraData();
    virtual const Info& getExtraData() const {return const_cast<Sensoring*>(this)->getExtraData();}
    virtual void setExtraData(const Info& extraData);
};

inline void doPacking(cCommBuffer *b, Sensoring& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Sensoring& obj) {obj.parsimUnpack(b);}


#endif // ifndef _SENSORING_M_H_

