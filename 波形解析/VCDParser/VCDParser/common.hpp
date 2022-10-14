#pragma once
#include<map>
#include<string>
using std::map;
using std::string;

/*
这里默认用一个字典来记录这个映射关系
*/
class ScopeType {
private:
    map<string, string> dict;
public:
    ScopeType() {
             //  Valid VCD scope types.
            dict["begin"] = "begin";
            dict["begin"] = "begin";
            dict["fork"] = "fork";
            dict["function"] = "function";
            dict["module"] = "module";
            dict["task"] = "task";
    }
    
};

    class VarType(Enum) :
    """Valid VCD variable types."""

    event = 'event'
    integer = 'integer'
    parameter = 'parameter'
    real = 'real'
    realtime = 'realtime'
    reg = 'reg'
    supply0 = 'supply0'
    supply1 = 'supply1'
    time = 'time'
    tri = 'tri'
    triand = 'triand'
    trior = 'trior'
    trireg = 'trireg'
    tri0 = 'tri0'
    tri1 = 'tri1'
    wand = 'wand'
    wire = 'wire'
    wor = 'wor'
    string = 'string'

    def __str__(self)->str:
return self.value


class TimescaleMagnitude(Enum) :
    """Valid timescale magnitudes."""

    one = 1
    ten = 10
    hundred = 100


    class TimescaleUnit(Enum) :
    """Valid timescale units."""

    second = 's'
    millisecond = 'ms'
    microsecond = 'us'
    nanosecond = 'ns'
    picosecond = 'ps'
    femtosecond = 'fs'


    class Timescale(NamedTuple) :
    """Timescale magnitude and unit."""

    magnitude : TimescaleMagnitude
    unit : TimescaleUnit

    @classmethod
    def from_str(cls, s: str) -> 'Timescale':
for unit in TimescaleUnit :
if s == unit.value :
    mag = TimescaleMagnitude(1)
    break
else :
    for mag in reversed(TimescaleMagnitude) :
        mag_str = str(mag.value)
        if s.startswith(mag_str) :
            unit_str = s[len(mag_str):].lstrip(' ')
            unit = TimescaleUnit(unit_str)
            break
        else:
raise ValueError(f'Invalid timescale magnitude {s!r}')
return Timescale(mag, unit)

def __str__(self)->str :
    return f'{self.magnitude.value} {self.unit.value}'
