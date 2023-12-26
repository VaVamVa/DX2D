#pragma once

// writer로 쓴 순서 잘 지켜야 함.
// Transform::Load() 참고.
class BinaryReader
{
public:
	BinaryReader(string filePath);
	BinaryReader(wstring filePath);
	~BinaryReader();

    int Int();
    UINT UInt();
    float Float();
    string String();
    wstring WString();
    void Byte(void** data, UINT dataSize);

    bool IsFailed() { return file == INVALID_HANDLE_VALUE; }

private:
    HANDLE file;
    DWORD size = 0;
};