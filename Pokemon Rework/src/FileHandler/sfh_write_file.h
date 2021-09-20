#pragma once
#include "sfh_file.h"
#include <fstream>
#include <vector>
#include <thread>

namespace SimpleFileHandler
{
    class WriteFile : public File
    {
    private:
        std::ofstream outFile;

    public:
        WriteFile();

        // Used to open a file
        WriteFile(const char* filename);

    public:
        // Used to write buffer
        void WriteBuffer(char* buffer, int size);

    public:
        // Used to write primitive datatype like ints, floats ect...
        template<typename T>
        void WritePrimitive(T primitive)
        {
            outFile.write(reinterpret_cast<char const*>(&primitive), sizeof(T));
        }

        // Used to write an array of a primitive datatype like ints, floats ect...
        template<typename T>
        void WritePrimitives(T* primitives, int size)
        {
            for (int i = 0; i < size; i++)
                WritePrimitive<T>(primitives[i]);
        }


    public:
        // Used to write a user defined datatype
        // Be aware of pointers in your class
        template<class T>
        void WriteClass(T* type)
        {
            outFile.write((char*)type, sizeof(T));
        }

        // Used to write a user defined datatype
        // Be aware of pointers in your class
        template<class T>
        void WriteClass(T& type)
        {
            WriteClass(&type);
        }

    public:
        // Used to write a std::vector containing user defined datatype
        // Be aware of pointers in your class
        template<class T>
        void WriteCollection(std::vector<T*> types)
        {
            WritePrimitive<long long>(types.size());
            for (int i = 0; i < types.size(); i++)
                WriteClass<T>(*types[i]);
        }

        // Used to write a std::vector containing any datatype
        // Be aware of pointers in your class
        template<class T>
        void WriteCollection(std::vector<T> types)
        {
            WritePrimitive<long long>(types.size());
            for (int i = 0; i < types.size(); i++)
                WriteClass<T>(types[i]);
        }

    private:
        virtual void Open() override;

    public:
        // Used to close file
        virtual void Close() override;

    public:
        // Used to get std::ofstream&
        std::ofstream& GetOutFileStream();
    };
}