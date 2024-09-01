//v3
#pragma once

#include <QSettings>
#include <QString>

class Settings
{
public:
    Settings();
    void load();
    void save();

    QString getAddress() const;
    void setAddress(const QString &address);

    int getPort() const;
    void setPort(int port);

    QString getUsername() const;
    void setUsername(const QString &username);

private:
    QString m_address;
    int m_port;
    QString m_username;
    QSettings m_settings;
};

//v1
// #pragma once

// class Settings
// {

// public:

// private:

// };
