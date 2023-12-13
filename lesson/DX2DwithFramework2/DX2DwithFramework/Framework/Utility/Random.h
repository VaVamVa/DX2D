#pragma once

class Random : public Singleton<Random>
{
private:
    friend class Singleton;

    const int MAX_NUMBER = INT_MAX;

    Random();
    ~Random();

public:
    int Range(const int& min, const int& max);
    float Range(const float& min, const float& max);

private:
    random_device randomDevice;
    mt19937_64 generator;

    uniform_int_distribution<int> disInt;
    uniform_real_distribution<float> disFloat;
};
