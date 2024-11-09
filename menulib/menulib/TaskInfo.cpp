#include "MenuLib.h"

using namespace NSMenulib;

std::string TaskInfo::GetName()
{
    return m_name;
}

void TaskInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

ISprite* TaskInfo::GetSprite()
{
    return m_sprite;
}

void TaskInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::string TaskInfo::GetDetail()
{
    return m_detail;
}

void TaskInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

