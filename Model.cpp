#include "Model.h"
#include "Logic.h"
#include "Settings.h"

Model& modelInstance()
{
    static Model model;
    return model;
}

Model::Model()
{
    m_settings = new Settings;
}

void   Model::initLogic()
{
    assert( m_logic==nullptr );
    m_logic = new Logic( m_settings->getUsername().toStdString() );
}
