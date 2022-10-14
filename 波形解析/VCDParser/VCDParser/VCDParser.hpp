#pragma once
#include<string>
#include<iostream>
#include<regex>
using namespace std;
//定义一些用于表征解析得到的内容的种类的常量
#define COMMENT  1
#define DATE  2
#define ENDDEFINITIONS  3
#define SCOPE  4
#define TIMESCALE  5
#define UPSCOPE  6
#define VAR  7
#define VERSION  8
#define DUMPALL  9
#define DUMPOFF  10
#define DUMPON  11
#define DUMPVARS  12
#define END  13
#define CHANGE_TIME  14
#define CHANGE_SCALAR  15
#define CHANGE_VECTOR  16
#define CHANGE_REAL  17
#define CHANGE_STRING  18

class TokenKind {
private:
	int token_type;//用于表示解析得到的类别。
public:
	TokenKind(int _token_type) :token_type(_token_type) {}//默认构造函数
};

/* 
class VarDecl {
     VCD variable declaration.

    Examples::

    $var wire 4 !@# foobar[3:1] $end
    $var real 1 aaa foobar $end
    $var integer 32 > foobar[8] $end

    
private:
    type_: VarType  # : Type of variable
    size : int  # : Size, in bits, of variable
    id_code : str
    """Identifer code of variable.

    This code is used in subsequent value change descriptors
    to map - back to this variable declaration."""

    reference : str
    """Reference name of variable.

    This human - readable name typically corresponds to the name of a
    variable in the model that output the VCD."""

    bit_index : Union[None, int, Tuple[int, int]]
    """Optional range of bits to select from the variable.

    May select a single bit index, e.g. ``ref[3]``. Or a range of
    bits, e.g.from ``ref[7:3]`` (MSB index then LSB index)."""

    @property
    def ref_str(self)->str:
if self.bit_index is None :
return self.reference
elif isinstance(self.bit_index, int) :
    return f'{self.reference}[{self.bit_index}]'
else :
    return f'{self.reference}[{self.bit_index[0]}:{self.bit_index[1]}]'

};
    class ScopeDecl(NamedTuple) :
    """VCD scope declaration.

    Examples::

    $scope module Foo $end
    $scope
    fork alpha_beta
    $end

    """

    type_: ScopeType  # : Type of scope
    ident : str  # : Scope name


    class VectorChange(NamedTuple) :
    """Vector value change descriptor.

    A vector value consists of multiple 4 - state values, where the four
    states are 0, 1, X, and Z.When a vector value consists entirely
    of 0 and 1 states, : attr : `value` will be an int.Otherwise
    :attr:`value` will be a str.

    """

    id_code: str  # : Identifier code of associated variable.
    value : Union[int, str]  # : New value of associated vector variable.


    class RealChange(NamedTuple) :
    """Real value (floating point) change descriptor."""

    id_code : str  # : Identifier code of associated variable.
    value : float  # : New value of associated real variable.


    class ScalarChange(NamedTuple) :
    """Scalar value change descriptor.

    A scalar is a single 4 - state value.The value is one of '0', '1',
    'X', or 'Z'.

    """

    id_code: str  # : Identifier code of associated variable.
    value : str  # : New value of associated scalar variable.


    class StringChange(NamedTuple) :
    """String value change descriptor.

    Strings are VCD extension supported by GTKWave.

    """

    id_code : str  # : Identifier code of associated variable.
    value : str  # : New value of associated string variable.


    class Location(NamedTuple) :
    """Describe location within VCD stream/file."""

    line : int  # : Line number
    column : int  # : Column number


    class Span(NamedTuple) :
    """Describe location span within VCD stream/file."""

    start : Location  # : Start of span
    end : Location  # : End of span

        */


class VCDParser
{
private:
	string vcd_content; //用于解析的vcd内容

public:
	VCDParser();//构造函数
	VCDParser(string _vcd_content);//构造函数
	~VCDParser();//析构函数
	const string  get_vcd_content();//返回需要解析的内容
    void trim(string& s);//去除字符串开头和结尾的空格
    void trim_head(string& s);//去除字符串开头的空格
    void trim_tail(string& s);//去除字符串结束的空格
    string parse_date(string s); //用于解析日期
    string parse_timescale(string s); //用于解析时间
    string parse_comment(string s); //用于解析注释
};

VCDParser::VCDParser() {}//构造函数
VCDParser::VCDParser(string _vcd_content):vcd_content(_vcd_content) {}//构造函数
VCDParser::~VCDParser() {}//析构函数
const string   VCDParser::get_vcd_content() { return vcd_content; }//返回需要解析的内容
void VCDParser::trim(string& s)
{
    if (!s.empty())
    {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(0, s.find_first_not_of("\t"));
        s.erase(s.find_last_not_of(" ") + 1);
        s.erase(s.find_last_not_of("\t") + 1);
    }


}
void VCDParser::trim_head(string& s)
{
    if (!s.empty())
             {
                 s.erase(0, s.find_first_not_of(" "));
                 s.erase(0, s.find_first_not_of("\t"));
                 //s.erase(s.find_last_not_of(" ") + 1);
             }


}
void VCDParser::trim_tail(string& s)
{
    if (!s.empty())
    {
        s.erase(s.find_last_not_of(" ") + 1);
        s.erase(s.find_last_not_of("\t") + 1);
    }


}

    /*
    * 解析类似如下的内容
    * 
    * 
$date
    Tue Aug 23 16:03:49 2022 o
$end
    */
string VCDParser::parse_date(string s)
{

    smatch results;
    regex reg("(\\$date\n)(.*)(\n\\$end)");
    regex_search(s, results, reg); //这里必须使用search 而不是match
    // results 中存贮的内容 第0个，整个匹配得到的值
    //  第1 个$date 
    //  第2 个日期
    //  第3 个$end 

    string content = string(results[2]);
    trim(content);
    if (results.size() >= 2)
        return  content; //如果找到了则返回
    else
        return string("NO");//如果未找到，则返回NO

}

string VCDParser::parse_timescale(string s)
{

    smatch results;
    regex reg("(\\$timescale\n)(.*)(\n\\$end)");
    regex_search(s, results, reg); //这里必须使用search 而不是match
    // results 中存贮的内容 第0个，整个匹配得到的值
    //  第1 个$timescale
    //  第2 个时间单位
    //  第3 个$end 

    string content = string(results[2]);
    trim(content);
    if (results.size() >= 2)
        return  content; //如果找到了则返回
    else
        return string("NO");//如果未找到，则返回NO

}

string VCDParser::parse_comment(string s)
{

    smatch results;
    regex reg("(\\$comment)(.*)(\\$end)");
    regex_search(s, results, reg); //这里必须使用search 而不是match
    // results 中存贮的内容 第0个，整个匹配得到的值
    //  第1 个$comment
    //  第2 个注释
    //  第3 个$end 
    string content = string(results[2]);
    trim(content);
    if (results.size() >= 2)
        return  content; //如果找到了则返回
    else
        return string("NO");//如果未找到，则返回NO

}