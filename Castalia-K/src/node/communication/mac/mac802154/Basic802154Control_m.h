//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/mac/mac802154/Basic802154Control.msg.
//

#ifndef _BASIC802154CONTROL_M_H_
#define _BASIC802154CONTROL_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>src/node/communication/mac/mac802154/Basic802154Control.msg:1</tt> by nedtool.
 * <pre>
 * enum Basic802154CommandDef
 * {
 * 
 *     SET_INTERVAL = 1;
 *     SET_OTHER = 2;
 * }
 * </pre>
 */
enum Basic802154CommandDef {
    SET_INTERVAL = 1,
    SET_OTHER = 2
};

/**
 * Class generated from <tt>src/node/communication/mac/mac802154/Basic802154Control.msg:6</tt> by nedtool.
 * <pre>
 * message Basic802154ControlCommand
 * {
 *     int basic802154CommandKind @enum(Basic802154CommandDef);
 *     double parameter = 0;
 * }
 * </pre>
 */
class Basic802154ControlCommand : public ::cMessage
{
  protected:
    int basic802154CommandKind_var;
    double parameter_var;

  private:
    void copy(const Basic802154ControlCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Basic802154ControlCommand&);

  public:
    Basic802154ControlCommand(const char *name=NULL, int kind=0);
    Basic802154ControlCommand(const Basic802154ControlCommand& other);
    virtual ~Basic802154ControlCommand();
    Basic802154ControlCommand& operator=(const Basic802154ControlCommand& other);
    virtual Basic802154ControlCommand *dup() const {return new Basic802154ControlCommand(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getBasic802154CommandKind() const;
    virtual void setBasic802154CommandKind(int basic802154CommandKind);
    virtual double getParameter() const;
    virtual void setParameter(double parameter);
};

inline void doPacking(cCommBuffer *b, Basic802154ControlCommand& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Basic802154ControlCommand& obj) {obj.parsimUnpack(b);}


#endif // ifndef _BASIC802154CONTROL_M_H_

