#pragma once

#include <string>
#include <vector>
#include <map>

class Params; // Forward declaration of Params

class DisplayAPI
{
public:
	DisplayAPI(const char* address, int port);
	~DisplayAPI();
    void sendParams(Params params);
//    void setPosition(std::string auvname, double x, double y, double theta);
private:
	int sock;
};

/*!
 * A class to hold any type supported by vibes properties system, an to provide JSON serialization
 * It looks like a container of decimal or string or param.
 */
class Value {
    enum value_type_enum{vt_none, vt_integer, vt_string, vt_decimal, vt_array, vt_object} _type;

    union {int _integer; double _decimal; const Params *_object;};
    std::string _string;
    std::vector<Value> _array;

public:
    Value() : _type(vt_none) {}
    Value(int i) : _integer(i), _type(vt_integer) {}
    Value(const double &d) : _decimal(d), _type(vt_decimal) {}
    Value(const std::string &s) : _string(s), _type(vt_string) {}
    Value(const char *s) : _string(s), _type(vt_string) {}
    Value(const std::vector<Value> &a) : _array(a), _type(vt_array) {}
    template <typename T> Value(const std::vector<T> &v) : _array(v.begin(),v.end()), _type(vt_array) {}
    /*explicit */Value(const Params &p) : _object(&p), _type(vt_object) {}
    bool empty() {return (_type == vt_none);}
    std::string toJSONString() const;
};

/**
 * It look like a python list. It contains values.
 */
class Params
{
public:
	Params() {}
    template<typename T> Params(const std::string & name, const T &p) {_values[name] = p;}
    Value & operator[](const std::string &key) {return _values[key];}
    /**
     * Remove first element from queue
     * @param key
     * @param value_not_found
     * @return
     */
    Value pop(const std::string &key, const Value &value_not_found = Value());
    Params& operator& (const Params &p) { for(KeyValueMap::const_iterator it = p._values.begin(); it != p._values.end(); ++it) _values[it->first] = it->second; return *this;}
    std::size_t size() const { return _values.size(); }
    std::string toJSON() const;
private:
	typedef std::map<std::string, Value> KeyValueMap; //! Typedef pour la table de hachage
    KeyValueMap _values;//! Table de hachage
};
