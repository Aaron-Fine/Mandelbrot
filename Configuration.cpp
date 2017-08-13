#include <exception>
#include "Configuration.h"
#include "Utils.h"

void Configuration::addParameter( std::string name, std::string parameter )
{
    name = trim(name);
    parameter = trim(parameter);
    // duplicate parameters are not allowed
    if ( !m_config.contains( name ))
    {
        m_config.add( name, parameter );
    }
}

std::string Configuration::getParamAsString( std::string name )
{
    name = trim(name);

    if ( m_config.contains( name ))
    {
        return m_config.getByKey(name).getData();
    }
    else {
        return "";
    }
}

void Configuration::addOrChangeParameter( std::string name, std::string parameter )
{
    name = trim(name);
    parameter = trim(parameter);

    if ( m_config.contains( name ))
    {
        m_config.getByKey(name).setData(parameter);
    }
    else {
        m_config.add( name, parameter );
    }
}

int Configuration::getParamAsInt( std::string name )
{
    name = trim(name);

    if (!m_config.contains(name))
    {
        std::string errorMessage;
        errorMessage += "Cannot find " + name + " in configuration";
        throw std::out_of_range(errorMessage);
    }

    bool converted;
    int result;

    result = convertStringToInt(m_config.getByKey(name).getData(), &converted);

    if (!converted)
    {
        std::string errorMessage;
        errorMessage += "Unable to convert " + m_config.getByKey(name).getData() + " to int";
        throw std::domain_error(errorMessage);
    }

    return result;
}

double Configuration::getParamAsDouble( std::string name )
{
    name = trim(name);

    if (!m_config.contains(name))
    {
        std::string errorMessage;
        errorMessage += "Cannot find " + name + " in configuration";
        throw std::out_of_range(errorMessage);
    }

    bool converted;
    double result;

    result = convertStringToDouble(m_config.getByKey(name).getData(), &converted);

    if (!converted)
    {
        std::string errorMessage;
        errorMessage += "Unable to convert " + m_config.getByKey(name).getData() + " to int";
        throw std::domain_error(errorMessage);
    }

    return result;
}
