#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void usage(int argc, char **argv)
{
    if(argc != 3)
    {
        cout << "用法： %s "<< argv[0] << "<原文件> <目标文件>\n" << endl;
        exit(0);
    }
}

int main(int argc, char **argv)
{
    usage(argc, argv);

    ifstream ifile;
    ofstream ofile;

    ifile.open(argv[1]);
    ofile.open(argv[2]);

    if(!ifile.is_open() || !ofile.is_open())
    {
        cerr << "打开文件失败！" << endl;
        exit(0);
    }

    char *buf = new char[1024];
    long total_bytes = 0;

    while(1)
    {
        if(ifile.eof())
            break;

        ifile.read(buf, 1024);
        ofile.write(buf, ifile.gcount());

        total_bytes += ifile.gcount();
    }

    delete [] buf;
    cout << "总共复制了" << total_bytes << "个字节。" << endl;

    ifile.close();
    ofile.close();

    return 0;
}

