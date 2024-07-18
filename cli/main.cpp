#include <iostream>
#include <cstring>

using namespace std;

int main(int argc,const char* argv[])
{
    if(argc == 2)  //./program filename
    {

    }
    else if(argc == 3) // ./program filename word_to_find
    {

    }
    else if(argc == 4) // ./program filename word_to_find -regex
    {
        const char* filename;
        const char* to_find;
        if(strcmp(argv[1],"-regex") == 0)
        {
            filename = argv[2];
            to_find = argv[3];
        }
        else if(strcmp(argv[2],"-regex") == 0)
        {
            filename = argv[1];
            to_find = argv[3];
        }
        else if(strcmp(argv[3],"-regex") == 0)
        {
            filename = argv[1];
            to_find = argv[2];
        }
        else
        {
            cerr << "invalid usage "<< endl;
            return 1;
        }
    }
    else
    {
        cerr << "invalid usage" << endl;
        return 1;
    }
}

