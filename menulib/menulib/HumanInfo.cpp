#include "MenuLib.h"

using namespace NSMenulib;

std::wstring HumanInfo::GetId()
{
    return m_id;
}

void HumanInfo::SetId(const std::wstring& arg)
{
    m_id = arg;
}

std::wstring HumanInfo::GetName()
{
    return m_name;
}

void HumanInfo::SetName(const std::wstring& arg)
{
    m_name = arg;
}

ISprite* HumanInfo::GetSprite()
{
    return m_sprite;
}

void HumanInfo::SetSprite(ISprite* const arg)
{
    m_sprite = arg;
}

std::wstring HumanInfo::GetDetail()
{
    return m_detail;
}

void HumanInfo::SetDetail(const std::wstring& arg)
{
    m_detail = arg;
}

