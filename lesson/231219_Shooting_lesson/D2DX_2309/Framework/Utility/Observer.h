#pragma once

class Observer : public Singleton<Observer>
{
private:
    friend class Singleton;

    Observer() = default;
    ~Observer() = default;

public:
    void AddIntEvent(string key, IntEvent event) { intEvents[key] = event; }
    void ExcuteIntEvent(string key, int param) { intEvents[key](param); }

private:
    map<string, IntEvent> intEvents;
};
