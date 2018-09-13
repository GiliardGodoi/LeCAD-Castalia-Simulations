//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/throughputPriority/ThroughputPriorityMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ThroughputPriorityMsg_m.h"

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
    cEnum *e = cEnum::find("ThroughputPriorityCommandDef");
    if (!e) enums.getInstance()->add(e = new cEnum("ThroughputPriorityCommandDef"));
    e->insert(TAXAMAC_INFO, "TAXAMAC_INFO");
    e->insert(BUFFER_INFO, "BUFFER_INFO");
);

Register_Class(ThroghputPriorityMsg);

ThroghputPriorityMsg::ThroghputPriorityMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->type_var = 0;
    this->taxaMAC_var = 0;
    this->bufferState_var = 0;
}

ThroghputPriorityMsg::ThroghputPriorityMsg(const ThroghputPriorityMsg& other) : ::cMessage(other)
{
    copy(other);
}

ThroghputPriorityMsg::~ThroghputPriorityMsg()
{
}

ThroghputPriorityMsg& ThroghputPriorityMsg::operator=(const ThroghputPriorityMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ThroghputPriorityMsg::copy(const ThroghputPriorityMsg& other)
{
    this->type_var = other.type_var;
    this->taxaMAC_var = other.taxaMAC_var;
    this->bufferState_var = other.bufferState_var;
}

void ThroghputPriorityMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->type_var);
    doPacking(b,this->taxaMAC_var);
    doPacking(b,this->bufferState_var);
}

void ThroghputPriorityMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->taxaMAC_var);
    doUnpacking(b,this->bufferState_var);
}

int ThroghputPriorityMsg::getType() const
{
    return type_var;
}

void ThroghputPriorityMsg::setType(int type)
{
    this->type_var = type;
}

double ThroghputPriorityMsg::getTaxaMAC() const
{
    return taxaMAC_var;
}

void ThroghputPriorityMsg::setTaxaMAC(double taxaMAC)
{
    this->taxaMAC_var = taxaMAC;
}

double ThroghputPriorityMsg::getBufferState() const
{
    return bufferState_var;
}

void ThroghputPriorityMsg::setBufferState(double bufferState)
{
    this->bufferState_var = bufferState;
}

class ThroghputPriorityMsgDescriptor : public cClassDescriptor
{
  public:
    ThroghputPriorityMsgDescriptor();
    virtual ~ThroghputPriorityMsgDescriptor();

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

Register_ClassDescriptor(ThroghputPriorityMsgDescriptor);

ThroghputPriorityMsgDescriptor::ThroghputPriorityMsgDescriptor() : cClassDescriptor("ThroghputPriorityMsg", "cMessage")
{
}

ThroghputPriorityMsgDescriptor::~ThroghputPriorityMsgDescriptor()
{
}

bool ThroghputPriorityMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ThroghputPriorityMsg *>(obj)!=NULL;
}

const char *ThroghputPriorityMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ThroghputPriorityMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int ThroghputPriorityMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ThroghputPriorityMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
        "taxaMAC",
        "bufferState",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int ThroghputPriorityMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "taxaMAC")==0) return base+1;
    if (fieldName[0]=='b' && strcmp(fieldName, "bufferState")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ThroghputPriorityMsgDescriptor::getFieldTypeString(void *object, int field) const
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
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *ThroghputPriorityMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "ThroughputPriorityCommandDef";
            return NULL;
        default: return NULL;
    }
}

int ThroghputPriorityMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ThroghputPriorityMsg *pp = (ThroghputPriorityMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ThroghputPriorityMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ThroghputPriorityMsg *pp = (ThroghputPriorityMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        case 1: return double2string(pp->getTaxaMAC());
        case 2: return double2string(pp->getBufferState());
        default: return "";
    }
}

bool ThroghputPriorityMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ThroghputPriorityMsg *pp = (ThroghputPriorityMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        case 1: pp->setTaxaMAC(string2double(value)); return true;
        case 2: pp->setBufferState(string2double(value)); return true;
        default: return false;
    }
}

const char *ThroghputPriorityMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *ThroghputPriorityMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ThroghputPriorityMsg *pp = (ThroghputPriorityMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


