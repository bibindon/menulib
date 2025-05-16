#include "MenuLib.h"

using namespace NSMenulib;

std::wstring StatusInfo::GetName()
{
    return m_name;
}

void StatusInfo::SetName(const std::wstring& arg)
{
    m_name = arg;
}

ISprite* StatusInfo::GetSprite()
{
    return m_sprite;
}

void StatusInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::wstring StatusInfo::GetDetail()
{
    return m_detail;
}

void StatusInfo::SetDetail(const std::wstring& arg)
{
    m_detail = arg;
}

