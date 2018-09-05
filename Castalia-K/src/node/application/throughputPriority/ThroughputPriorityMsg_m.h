//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/throughputPriority/ThroughputPriorityMsg.msg.
//

#ifndef _THROUGHPUTPRIORITYMSG_M_H_
#define _THROUGHPUTPRIORITYMSG_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>src/node/application/throughputPriority/ThroughputPriorityMsg.msg:1</tt> by nedtool.
 * <pre>
 * message ThroughputPriorityMsg
 * {
 *     double taxaMAC = 0;
 *     int bufferMeasure = 0;
 * }
 * </pre>
 */
class ThroughputPriorityMsg : public ::cMessage
{
  protected:
    double taxaMAC_var;
    int bufferMeasure_var;

  private:
    void copy(const ThroughputPriorityMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ThroughputPriorityMsg&);

  public:
    ThroughputPriorityMsg(const char *name=NULL, int kind=0);
    ThroughputPriorityMsg(const ThroughputPriorityMsg& other);
    virtual ~ThroughputPriorityMsg();
    ThroughputPriorityMsg& operator=(const ThroughputPriorityMsg& other);
    virtual ThroughputPriorityMsg *dup() const {return new ThroughputPriorityMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual double getTaxaMAC() const;
    virtual void setTaxaMAC(double taxaMAC);
    virtual int getBufferMeasure() const;
    virtual void setBufferMeasure(int bufferMeasure);
};

inline void doPacking(cCommBuffer *b, ThroughputPriorityMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ThroughputPriorityMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef _THROUGHPUTPRIORITYMSG_M_H_

