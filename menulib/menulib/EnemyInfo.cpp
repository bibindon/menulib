#include "MenuLib.h"

using namespace NSMenulib;

std::wstring EnemyInfo::GetId()
{
    return m_id;
}

void EnemyInfo::SetId(const std::wstring& arg)
{
    m_id = arg;
}

std::wstring EnemyInfo::GetName()
{
    return m_name;
}

void EnemyInfo::SetName(const std::wstring& arg)
{
    m_name = arg;
}

ISprite* EnemyInfo::GetSprite()
{
    return m_sprite;
}

void EnemyInfo::SetSprite(ISprite* const arg)
{
    if (m_sprite != nullptr)
    {
        delete m_sprite;
        m_sprite = nullptr;
    }

    m_sprite = arg;
}

std::wstring EnemyInfo::GetDetail()
{
    return m_detail;
}

void EnemyInfo::SetDetail(const std::wstring& arg)
{
    m_detail = arg;
}

