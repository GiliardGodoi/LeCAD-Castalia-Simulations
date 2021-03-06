//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/mac/mac802154/Basic802154Control.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Basic802154Control_m.h"

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
    cEnum *e = cEnum::find("Basic802154CommandDef");
    if (!e) enums.getInstance()->add(e = new cEnum("Basic802154CommandDef"));
    e->insert(SET_INTERVAL, "SET_INTERVAL");
    e->insert(SET_OTHER, "SET_OTHER");
);

Register_Class(Basic802154ControlCommand);

Basic802154ControlCommand::Basic802154ControlCommand(const char *name, int kind) : ::cMessage(name,kind)
{
    this->basic802154CommandKind_var = 0;
    this->parameter_var = 0;
}

Basic802154ControlCommand::Basic802154ControlCommand(const Basic802154ControlCommand& other) : ::cMessage(other)
{
    copy(other);
}

Basic802154ControlCommand::~Basic802154ControlCommand()
{
}

Basic802154ControlCommand& Basic802154ControlCommand::operator=(const Basic802154ControlCommand& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Basic802154ControlCommand::copy(const Basic802154ControlCommand& other)
{
    this->basic802154CommandKind_var = other.basic802154CommandKind_var;
    this->parameter_var = other.parameter_var;
}

void Basic802154ControlCommand::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->basic802154CommandKind_var);
    doPacking(b,this->parameter_var);
}

void Basic802154ControlCommand::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->basic802154CommandKind_var);
    doUnpacking(b,this->parameter_var);
}

int Basic802154ControlCommand::getBasic802154CommandKind() const
{
    return basic802154CommandKind_var;
}

void Basic802154ControlCommand::setBasic802154CommandKind(int basic802154CommandKind)
{
    this->basic802154CommandKind_var = basic802154CommandKind;
}

double Basic802154ControlCommand::getParameter() const
{
    return parameter_var;
}

void Basic802154ControlCommand::setParameter(double parameter)
{
    this->parameter_var = parameter;
}

class Basic802154ControlCommandDescriptor : public cClassDescriptor
{
  public:
    Basic802154ControlCommandDescriptor();
    virtual ~Basic802154ControlCommandDescriptor();

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

Register_ClassDescriptor(Basic802154ControlCommandDescriptor);

Basic802154ControlCommandDescriptor::Basic802154ControlCommandDescriptor() : cClassDescriptor("Basic802154ControlCommand", "cMessage")
{
}

Basic802154ControlCommandDescriptor::~Basic802154ControlCommandDescriptor()
{
}

bool Basic802154ControlCommandDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Basic802154ControlCommand *>(obj)!=NULL;
}

const char *Basic802154ControlCommandDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Basic802154ControlCommandDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int Basic802154ControlCommandDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *Basic802154ControlCommandDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "basic802154CommandKind",
        "parameter",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int Basic802154ControlCommandDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "basic802154CommandKind")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "parameter")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Basic802154ControlCommandDescriptor::getFieldTypeString(void *object, int field) const
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

const char *Basic802154ControlCommandDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "Basic802154CommandDef";
            return NULL;
        default: return NULL;
    }
}

int Basic802154ControlCommandDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Basic802154ControlCommand *pp = (Basic802154ControlCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Basic802154ControlCommandDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Basic802154ControlCommand *pp = (Basic802154ControlCommand *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getBasic802154CommandKind());
        case 1: return double2string(pp->getParameter());
        default: return "";
    }
}

bool Basic802154ControlCommandDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Basic802154ControlCommand *pp = (Basic802154ControlCommand *)object; (void)pp;
    switch (field) {
        case 0: pp->setBasic802154CommandKind(string2long(value)); return true;
        case 1: pp->setParameter(string2double(value)); return true;
        default: return false;
    }
}

const char *Basic802154ControlCommandDescriptor::getFieldStructName(void *object, int field) const
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

void *Basic802154ControlCommandDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Basic802154ControlCommand *pp = (Basic802154ControlCommand *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


