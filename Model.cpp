#include "Model.h"
#include "Logic.h"
#include "Settings.h"

Model::Model()
{
    m_logic = new Logic;
    m_settings = new Settings;
}

Model& model()
{
    static Model model;
    return model;
}
