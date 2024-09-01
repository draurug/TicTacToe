#pragma once

class Settings;
class Logic;
class Model;

Model& model();

class Model
{
    Settings* m_settings;
    Logic* m_logic;

public:
    Model();
    Settings* settings() {return m_settings;}
    Logic* logic() {return m_logic;}
};
