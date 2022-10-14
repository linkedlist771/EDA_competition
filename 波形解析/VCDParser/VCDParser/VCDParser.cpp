/*
这个文件用于实现对于波形的解析
*/


#include"VCDParser.hpp"


int main()
{

    string vcd_content[] = { "$date\n\tTue Aug 23 16:03 : 49 2022\n$end",
                            "$timescale\n\t1ns\n$end",
                            "$comment Csum: 1 9ba2991b94438432 $end"
    };
    for (auto i : vcd_content) {
        VCDParser parser(i);
        cout << parser.get_vcd_content()<<endl;
        cout << "时间" << endl;
        cout<<parser.parse_date(parser.get_vcd_content())<<endl;
        cout << "时间单位" << endl;
        cout << parser.parse_timescale(parser.get_vcd_content()) << endl;
        cout << "注释" << endl;
        cout << parser.parse_comment(parser.get_vcd_content()) << endl;
        cout << "\n\n\n\n";
    }
    return 0; 
}

