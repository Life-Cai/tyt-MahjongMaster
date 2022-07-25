#ifndef TYT_JSONParse
#define TYT_JSONParse

#include"JSONBasic.hpp"

JSON ParseJSON (const char *Str);

namespace
{
	JSONInt    ParseInt    (const char *&Str);
	JSONBool   ParseBool   (const char *&Str);
	JSONString ParseString (const char *&Str);
	JSONArray  ParseArray  (const char *&Str);
	JSONObject ParseObject (const char *&Str);

	JSONInt ParseInt(const char *&Str)
	{
		assert(('0'<=*Str&&*Str<='9')||*Str=='-');
		int Symbol=1,Num=0;
		if(*Str=='-')
			Symbol=-1,Str++;
		for(;'0'<=*Str&&*Str<='9';Str++)
			Num=Num*10+(*Str-'0');
		Str--;
		return Symbol*Num;
	}
	
	JSONBool ParseBool(const char *&Str)
	{
		assert(*Str=='t'||*Str=='f');
		JSONBool Res;
		if(*Str=='t')
			Res=true,Str+=3;
		else
			Res=false,Str+=4;
		return Res;
	}
	
	JSONString ParseString(const char *&Str)
	{
		assert(*Str=='\"');Str++;
		JSONString Res;
		for(;*Str!='\"';Str++)
		{
			char ch=*Str;
			if(*Str=='\\')
			{
				Str++;
				if(*Str=='\\')ch='\\';
				if(*Str=='"')ch='"';
				if(*Str=='/')ch='/';
				if(*Str=='b')ch='\b';
				if(*Str=='f')ch='\f';
				if(*Str=='n')ch='\n';
				if(*Str=='r')ch='\r';
				if(*Str=='t')ch='\t';
			}
			Res+=ch;
		}
		return Res;
	}
	
	JSONArray ParseArray(const char *&Str)
	{
		assert(*Str=='[');Str++;
		JSONArray Res;
		for(;*Str!=']';Str++)
		{
			JSON Tmp;
			if(('0'<=*Str&&*Str<='9')||*Str=='-')
				Tmp=ParseInt(Str);
			if(*Str=='t'||*Str=='f')
				Tmp=ParseBool(Str);
			if(*Str=='"')
				Tmp=ParseString(Str);
			if(*Str=='[')
				Tmp=ParseArray(Str);
			if(*Str=='{')
				Tmp=ParseObject(Str);
			if(!Tmp.isNull())
				Res.push_back(Tmp);
		}
		return Res;
	}
	
	JSONObject ParseObject(const char *&Str)
	{
		assert(*Str=='{');Str++;
		JSONObject Res;
		JSONString Label;
		for(;*Str!='}';Str++)
		{
			if(Label.size())
			{
				JSON Tmp;
				if(('0'<=*Str&&*Str<='9')||*Str=='-')
					Tmp=ParseInt(Str);
				if(*Str=='t'||*Str=='f')
					Tmp=ParseBool(Str);
				if(*Str=='"')
					Tmp=ParseString(Str);
				if(*Str=='[')
					Tmp=ParseArray(Str);
				if(*Str=='{')
					Tmp=ParseObject(Str);
				if(!Tmp.isNull())
				{
					Res[Label]=Tmp;
					Label="";
				}
			}
			else
			{
				if(*Str=='"')
					Label=ParseString(Str);
			}
		}
		return Res;
	}
}

JSON ParseJSON(const char *Str)
{
	JSON Tmp;
	for(;*Str!='\0';Str++)
	{
		if(('0'<=*Str&&*Str<='9')||*Str=='-')
			Tmp=ParseInt(Str);
		if(*Str=='t'||*Str=='f')
			Tmp=ParseBool(Str);
		if(*Str=='"')
			Tmp=ParseString(Str);
		if(*Str=='[')
			Tmp=ParseArray(Str);
		if(*Str=='{')
			Tmp=ParseObject(Str);
		if(!Tmp.isNull())
			break;
	}
	return Tmp;
}

#endif