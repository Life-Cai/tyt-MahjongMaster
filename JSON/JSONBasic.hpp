#ifndef TYT_JSONBasic
#define TYT_JSONBasic

#include<map>
#include<vector>
#include<string>
#include<cctype>
#include<cassert>

enum JSONNodeType{Null,Int,Bool,String,Array,Object};
class JSON;
typedef int                       JSONInt;
typedef bool                      JSONBool;
typedef std::string               JSONString;
typedef std::vector<JSON>         JSONArray;
typedef std::map<JSONString,JSON> JSONObject;
class JSON
{
private:
	union
	{
		void*       Ptr;
		JSONInt*    IntPtr;
		JSONBool*   BoolPtr;
		JSONString* StringPtr;
		JSONArray*  ArrayPtr;
		JSONObject* ObjectPtr;
	};
	JSONNodeType Type;
public:
	JSON();
	JSON(const JSONInt x);
	JSON(const JSONBool x);
	JSON(const JSONString x);
	JSON(const JSONArray x);
	JSON(const JSONObject x);
	JSON(const JSON& x);
	~JSON();
	JSONInt    operator = (const JSONInt x);
	JSONBool   operator = (const JSONBool x);
	JSONString operator = (const JSONString x);
	JSONArray  operator = (const JSONArray x);
	JSONObject operator = (const JSONObject x);
	JSON   operator = (const JSON x);
	void* getPtr() const;
	JSONNodeType getType() const;
	bool isNull()   const;
	bool isInt()    const;
	bool isBool()   const;
	bool isString() const;
	bool isArray()  const;
	bool isObject() const;
	JSONInt    &asInt();
	JSONBool   &asBool();
	JSONString &asString();
	JSONArray  &asArray();
	JSONObject &asObject();
	JSONInt    &viewInt()    const;
	JSONBool   &viewBool()   const;
	JSONString &viewString() const;
	JSONArray  &viewArray()  const;
	JSONObject &viewObject() const;
	JSON &operator [] (const JSONInt x);
	JSON &operator [] (const JSONString x);
};

JSON::JSON(){Ptr=nullptr;Type=Null;}
JSON::JSON(const JSONInt x)    {(*this)=x;}
JSON::JSON(const JSONBool x)   {(*this)=x;}
JSON::JSON(const JSONString x) {(*this)=x;}
JSON::JSON(const JSONArray x)  {(*this)=x;}
JSON::JSON(const JSONObject x) {(*this)=x;}
JSON::JSON(const JSON& x)
{
	this->~JSON();
	if(x.Type==Int)    *this=*x.IntPtr;
	if(x.Type==Bool)   *this=*x.BoolPtr;
	if(x.Type==String) *this=*x.StringPtr;
	if(x.Type==Array)  *this=*x.ArrayPtr;
	if(x.Type==Object) *this=*x.ObjectPtr;
}
JSON::~JSON()
{
	if(Type==Int)delete IntPtr;
	if(Type==Bool)delete BoolPtr;
	if(Type==String)delete StringPtr;
	if(Type==Array)
	{
		for(JSON &it:*ArrayPtr)
			it.~JSON();
		delete ArrayPtr;
	}
	if(Type==Object)
	{
		for(auto &it:*ObjectPtr)
			it.second.~JSON();
		delete ObjectPtr;
	}
	Ptr=nullptr;Type=Null;
}
JSONInt JSON::operator = (const JSONInt x)
{
	Ptr=new JSONInt(x);
	Type=Int;
	return x;
}
JSONBool JSON::operator = (const JSONBool x)
{
	Ptr=new JSONBool(x);
	Type=Bool;
	return x;
}
JSONString JSON::operator = (const JSONString x)
{
	Ptr=new JSONString(x);
	Type=String;
	return x;
}
JSONArray JSON::operator = (const JSONArray x)
{
	Type=Array;
	Ptr=new JSONArray;
	JSONArray &Val=*ArrayPtr;
	for(const JSON &i:x)
	{
		if(i.Type==Int)Val.push_back(*i.IntPtr);
		if(i.Type==Bool)Val.push_back(*i.BoolPtr);
		if(i.Type==String)Val.push_back(*i.StringPtr);
		if(i.Type==Array)Val.push_back(*i.ArrayPtr);
		if(i.Type==Object)Val.push_back(*i.ObjectPtr);
	}
	return x;
}
JSONObject JSON::operator = (const JSONObject x)
{
	Type=Object;
	Ptr=new JSONObject;
	JSONObject &Val=*ObjectPtr;
	for(const auto &[i,j]:x)
	{
		if(j.Type==Int)Val[i]=*j.IntPtr;
		if(j.Type==Bool)Val[i]=*j.BoolPtr;
		if(j.Type==String)Val[i]=*j.StringPtr;
		if(j.Type==Array)Val[i]=*j.ArrayPtr;
		if(j.Type==Object)Val[i]=*j.ObjectPtr;
	}
	return x;
}
JSON JSON::operator = (const JSON x)
{
	this->~JSON();
	if(x.Type==Int)    *this=*x.IntPtr;
	if(x.Type==Bool)   *this=*x.BoolPtr;
	if(x.Type==String) *this=*x.StringPtr;
	if(x.Type==Array)  *this=*x.ArrayPtr;
	if(x.Type==Object) *this=*x.ObjectPtr;
	return x;
}
void* JSON::getPtr() const
{
	return Ptr;
}
JSONNodeType JSON::getType() const
{
	return Type;
}
bool JSON::isNull() const
{
	return Type==Null;
}
bool JSON::isInt() const
{
	return Type==Int;
}
bool JSON::isBool() const
{
	return Type==Bool;
}
bool JSON::isString() const
{
	return Type==String;
}
bool JSON::isArray() const
{
	return Type==Array;
}
bool JSON::isObject() const
{
	return Type==Object;
}
JSONInt &JSON::asInt()
{
	assert(isInt());
	return *IntPtr;
}
JSONBool &JSON::asBool()
{
	assert(isBool());
	return *BoolPtr;
}
JSONString &JSON::asString()
{
	assert(isString());
	return *StringPtr;
}
JSONArray &JSON::asArray()
{
	assert(isArray());
	return *ArrayPtr;
}
JSONObject &JSON::asObject()
{
	assert(isObject());
	return *ObjectPtr;
}
JSONInt &JSON::viewInt() const
{
	assert(isInt());
	return *IntPtr;
}
JSONBool &JSON::viewBool() const
{
	assert(isBool());
	return *BoolPtr;
}
JSONString &JSON::viewString() const
{
	assert(isString());
	return *StringPtr;
}
JSONArray &JSON::viewArray() const
{
	assert(isArray());
	return *ArrayPtr;
}
JSONObject &JSON::viewObject() const
{
	assert(isObject());
	return *ObjectPtr;
}
JSON &JSON::operator[] (const JSONInt x)
{
	assert(isArray());
	assert(x>=0&&x<(int)((*ArrayPtr).size()));
	return (*ArrayPtr)[x];
}
JSON &JSON::operator[] (const JSONString x)
{
	assert(isObject());
	assert(x.size()!=0);
	return (*ObjectPtr)[x];
}

#endif