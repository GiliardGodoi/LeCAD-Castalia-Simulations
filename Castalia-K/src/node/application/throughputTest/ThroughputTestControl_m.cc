//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/throughputTest/ThroughputTestControl.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ThroughputTestControl_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("ThroughputTestCommandDef");
    if (!e) enums.getInstance()->add(e = new cEnum("ThroughputTestCommandDef"));
    e->insert(SET_RATE, "SET_RATE");
    e->insert(SET_PRIORITY, "SET_PRIORITY");
);

Register_Class(ThroughputTestControlCommand);

ThroughputTestControlCommand::ThroughputTestControlCommand(const char *name, int kind) : ::cMessage(name,kind)
{
    this->throughputTestCommandKind_var = 0;
    this->parameter_var = 0;
}

ThroughputTestControlCommand::ThroughputTestControlCommand(const ThroughputTestControlCommand& other) : ::cMessage(other)
{
    copy(other);
}

ThroughputTestControlCommand::~ThroughputTestControlCommand()
{
}

ThroughputTestControlCommand& ThroughputTestControlCommand::operator=(const ThroughputTestControlCommand& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ThroughputTestControlCommand::copy(const ThroughputTestControlCommand& other)
{
    this->throughputTestCommandKind_var = other.throughputTestCommandKind_var;
    this->parameter_var = other.parameter_var;
}

void ThroughputTestControlCommand::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->throughputTestCommandKind_var);
    doPacking(b,this->parameter_var);
}

void ThroughputTestControlCommand::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->throughputTestCommandKind_var);
    doUnpacking(b,this->parameter_var);
}

int ThroughputTestControlCommand::getThroughputTestCommandKind() const
{
    return throughputTestCommandKind_var;
}

void ThroughputTestControlCommand::setThroughputTestCommandKind(int throughputTestCommandKind)
{
    this->throughputTestCommandKind_var = throughputTestCommandKind;
}

double ThroughputTestControlCommand::getParameter() const
{
    return parameter_var;
}

void ThroughputTestControlCommand::setParameter(double parameter)
{
    this->parameter_var = parameter;
}

class ThroughputTestControlCommandDescriptor : public cClassDescriptor
{
  public:
    ThroughputTestControlCommandDescriptor();
    virtual ~ThroughputTestControlCommandDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ThroughputTestControlCommandDescriptor);

ThroughputTestControlCommandDescriptor::ThroughputTestControlCommandDescriptor() : cClassDescriptor("ThroughputTestControlCommand", "cMessage")
{
}

ThroughputTestControlCommandDescriptor::~ThroughputTestControlCommandDescriptor()
{
}

bool ThroughputTestControlCommandDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ThroughputTestControlCommand *>(obj)!=NULL;
}

const char *ThroughputTestControlCommandDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ThroughputTestControlCommandDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int ThroughputTestControlCommandDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *ThroughputTestControlCommandDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "throughputTestCommandKind",
        "parameter",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int ThroughputTestControlCommandDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "throughputTestCommandKind")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "parameter")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ThroughputTestControlCommandDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *ThroughputTestControlCommandDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "ThroughputTestCommandDef";
            return NULL;
        default: return NULL;
    }
}

int ThroughputTestControlCommandDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ThroughputTestControlCommand *pp = (ThroughputTestControlCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ThroughputTestControlCommandDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ThroughputTestControlCommand *pp = (ThroughputTestControlCommand *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getThroughputTestCommandKind());
        case 1: return double2string(pp->getParameter());
        default: return "";
    }
}

bool ThroughputTestControlCommandDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ThroughputTestControlCommand *pp = (ThroughputTestControlCommand *)object; (void)pp;
    switch (field) {
        case 0: pp->setThroughputTestCommandKind(string2long(value)); return true;
        case 1: pp->setParameter(string2double(value)); return true;
        default: return false;
    }
}

const char *ThroughputTestControlCommandDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *ThroughputTestControlCommandDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ThroughputTestControlCommand *pp = (ThroughputTestControlCommand *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


