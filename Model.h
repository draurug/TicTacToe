#pragma once

#include <cassert>

class Settings;
class Logic;
class Model;

Model& modelInstance();

class Model
{
    Settings*   m_settings;
    Logic*      m_logic = nullptr;

public:
    Model();

    void initLogic();

    Settings& settings() { return *m_settings; }

    Logic&    logic()
    {
        assert( m_logic!=nullptr );
        return *m_logic;
    }
};
