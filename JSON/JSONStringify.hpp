#ifndef TYT_JSONStringify
#define TYT_JSONStringify

#include"JSONBasic.hpp"

std::string StringifyJSON (const JSON x,const bool PrettyPrint);

namespace
{
	class Stringify
	{
	public:
		bool PrettyPrint;
		int IndentLayer;
		std::string StringifyInt    (const JSONInt &x);
		std::string StringifyBool   (const JSONBool &x);
		std::string StringifyString (const JSONString &x);
		std::string StringifyArray  (const JSONArray &x);
		std::string StringifyObject (const JSONObject &x);
		std::string StringifyJSON   (const JSON &x);
	};

	std::string Stringify::StringifyInt (const JSONInt &x)
	{
		return std::to_string(x);
	}

	std::string Stringify::StringifyBool (const JSONBool &x)
	{
		if(x)
			return "true";
		else
			return "false";
	}

	std::string Stringify::StringifyString (const JSONString &x)
	{
		std::string Res;
		Res+='"';
		for(const char ch:x)
			switch(ch)
			{
				case '\\':Res+="\\\\";break;
				case '"':Res+="\\\"";break;
				// case '/':Res+="\\/";break;
				case '\b':Res+="\\b";break;
				case '\f':Res+="\\f";break;
				case '\n':Res+="\\n";break;
				case '\r':Res+="\\r";break;
				case '\t':Res+="\\t";break;
				default:Res+=ch;break;
			}
		Res+='"';
		return Res;
	}

	std::string Stringify::StringifyArray (const JSONArray &x)
	{
		std::string Res;
		if(PrettyPrint)
			for(int i=1;i<=IndentLayer;i++)
				Res+='\t';
		Res+='[';
		if(PrettyPrint)
			Res+='\n';

		IndentLayer++;
		for(auto it=x.begin();it!=x.end();it++)
		{
			if(PrettyPrint)
			{
				if(it->isArray()||it->isObject())
					Res+=StringifyJSON(*it);
				else
				{
					for(int i=1;i<=IndentLayer;i++)
						Res+='\t';
					Res+=StringifyJSON(*it);
				}
			}
			else
				Res+=StringifyJSON(*it);
			if(it!=prev(x.end()))
				Res+=',';
			if(PrettyPrint)
				Res+='\n';
		}
		IndentLayer--;

		if(PrettyPrint)
			for(int i=1;i<=IndentLayer;i++)
				Res+='\t';
		Res+=']';
		// if(PrettyPrint)
		// 	Res+='\n';
		return Res;
	}

	std::string Stringify::StringifyObject (const JSONObject &x)
	{
		std::string Res;
		if(PrettyPrint)
			for(int i=1;i<=IndentLayer;i++)
				Res+='\t';
		Res+='{';
		if(PrettyPrint)
			Res+='\n';

		IndentLayer++;
		for(auto it=x.begin();it!=x.end();it++)
		{
			if(PrettyPrint)
			{
				for(int i=1;i<=IndentLayer;i++)
						Res+='\t';
				Res+='"'+it->first+'"'+':';
				if(it->second.isArray()||it->second.isObject())
					Res+='\n';
				Res+=StringifyJSON(it->second);
			}
			else
				Res+='"'+it->first+'"'+':'+StringifyJSON(it->second);
			if(it!=prev(x.end()))
				Res+=',';
			if(PrettyPrint)
				Res+='\n';
		}
		IndentLayer--;
		
		if(PrettyPrint)
			for(int i=1;i<=IndentLayer;i++)
				Res+='\t';
		Res+='}';
		// if(PrettyPrint)
		// 	Res+='\n';
		return Res;
	}

	std::string Stringify::StringifyJSON (const JSON &x)
	{
		std::string Res;
		if(x.getType()==Int)
			Res=StringifyInt(x.viewInt());
		if(x.getType()==Bool)
			Res=StringifyBool(x.viewBool());
		if(x.getType()==String)
			Res=StringifyString(x.viewString());
		if(x.getType()==Array)
			Res=StringifyArray(x.viewArray());
		if(x.getType()==Object)
			Res=StringifyObject(x.viewObject());
		return Res;
	}
}

std::string StringifyJSON (const JSON x,const bool PrettyPrint)
{
	Stringify Tmp;
	Tmp.PrettyPrint=PrettyPrint;
	Tmp.IndentLayer=0;
	return Tmp.StringifyJSON(x);
}

#endif