#include "Model.h"
#include "Logic.h"
#include "Settings.h"
Model& model()
{
    static Model model;
    return model;
}

Model::Model()
{
    m_logic = new Logic;
    m_settings = new Settings;
}
