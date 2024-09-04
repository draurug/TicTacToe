//v3
#include "Settings.h"

Settings::Settings()
    : m_qSettings("MyCompanyTicTac", "MyAppTicTac")  // Инициализация QSettings с указанием компании и приложения
{
    load();  // Загрузка настроек при создании объекта
}

bool Settings::load()
{
    if ( ! m_qSettings.contains("address") )
    {
        return false;
    }
    m_address = m_qSettings.value("address", "localhost").toString();
    m_port = m_qSettings.value("port", 5555).toInt();
    m_username = m_qSettings.value("username", "user").toString();
    return true;
}

void Settings::save()
{
    m_qSettings.setValue("address", m_address);
    m_qSettings.setValue("port", m_port);
    m_qSettings.setValue("username", m_username);
}

QString Settings::getAddress() const
{
    return m_address;
}

void Settings::setAddress(const QString &address)
{
    m_address = address;
}

int Settings::getPort() const
{
    return m_port;
}

void Settings::setPort(int port)
{
    m_port = port;
}

QString Settings::getUsername() const
{
    return m_username;
}

void Settings::setUsername(const QString &username)
{
    m_username = username;
}

//v1
// #include "Settings.h"

// Settings::Settings() : m_settings() // что должно быть в аргументе?
// {
//     load(); // Загрузка настроек при создании объекта
// }

// void Settings::load()
// {
//     m_address = m_settings.value("address", "localhost").toString();
//     m_port = m_settings.value("port", 5555).toInt();
//     m_username = m_settings.value("username").toString();
// }

// void Settings::save()
// {
//     m_settings.setValue("address", m_address);
//     m_settings.setValue("port", m_port);
//     m_settings.setValue("username", m_username);
// }

// QString Settings::getAddress() const
// {
//     return m_address;
// }

// void Settings::setAddress(const QString &address)
// {
//     m_address = address;
// }

// int Settings::getPort() const
// {
//     return m_port;
// }

// void Settings::setPort(int port)
// {
//     m_port = port;
// }

// QString Settings::getUsername() const
// {
//     return m_username;
// }

// void Settings::setUsername(const QString &username)
// {
//     m_username = username;
// }
