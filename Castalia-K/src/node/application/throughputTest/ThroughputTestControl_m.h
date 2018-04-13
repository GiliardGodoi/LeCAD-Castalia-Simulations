//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/throughputTest/ThroughputTestControl.msg.
//

#ifndef _THROUGHPUTTESTCONTROL_M_H_
#define _THROUGHPUTTESTCONTROL_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>src/node/application/throughputTest/ThroughputTestControl.msg:1</tt> by nedtool.
 * <pre>
 * enum ThroughputTestCommandDef
 * {
 * 
 *     SET_RATE = 1;
 *     SET_PRIORITY = 2;
 * }
 * </pre>
 */
enum ThroughputTestCommandDef {
    SET_RATE = 1,
    SET_PRIORITY = 2
};

/**
 * Class generated from <tt>src/node/application/throughputTest/ThroughputTestControl.msg:6</tt> by nedtool.
 * <pre>
 * message ThroughputTestControlCommand
 * {
 *     int throughputTestCommandKind @enum(ThroughputTestCommandDef);
 *     double parameter = 0;
 * }
 * </pre>
 */
class ThroughputTestControlCommand : public ::cMessage
{
  protected:
    int throughputTestCommandKind_var;
    double parameter_var;

  private:
    void copy(const ThroughputTestControlCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ThroughputTestControlCommand&);

  public:
    ThroughputTestControlCommand(const char *name=NULL, int kind=0);
    ThroughputTestControlCommand(const ThroughputTestControlCommand& other);
    virtual ~ThroughputTestControlCommand();
    ThroughputTestControlCommand& operator=(const ThroughputTestControlCommand& other);
    virtual ThroughputTestControlCommand *dup() const {return new ThroughputTestControlCommand(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getThroughputTestCommandKind() const;
    virtual void setThroughputTestCommandKind(int throughputTestCommandKind);
    virtual double getParameter() const;
    virtual void setParameter(double parameter);
};

inline void doPacking(cCommBuffer *b, ThroughputTestControlCommand& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ThroughputTestControlCommand& obj) {obj.parsimUnpack(b);}


#endif // ifndef _THROUGHPUTTESTCONTROL_M_H_
