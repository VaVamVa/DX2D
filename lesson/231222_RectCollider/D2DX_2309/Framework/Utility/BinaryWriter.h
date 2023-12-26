#pragma once

/*
이진수를 이용하여 data를 저장.
보안성, 속도면에서 장점이 있다.
하지만 중간에서 읽기 어려우며, 무조건 모두 load 해야한다.
동적인 vlaue는 저장할 수 없다.
*/
class BinaryWriter
{
public:
    BinaryWriter(string filePath);
    BinaryWriter(wstring filePath);
    ~BinaryWriter();

    void Int(int data);
    void UInt(UINT data);
    void Float(float data);
    void String(string data);
    void WString(wstring data);

    void Byte(void* data, UINT dataSize);

private:
    HANDLE file;
    DWORD size = 0;
};