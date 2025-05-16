﻿#include "MenuLib.h"
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace NSMenulib;

static std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

void MenuLib::Init(
    const std::string& csvfilepath, /* TODO remove */
    IFont* font,
    ISoundEffect* SE,
    ISprite* sprCursor,
    ISprite* sprBackground,
    const bool bEnglish)
{
    m_font = font;
    m_SE = SE;
    m_sprCursor = sprCursor;
    m_sprBackground = sprBackground;
    m_bEnglish = bEnglish;

    m_font->Init(m_bEnglish);
    m_SE->Init();

    if (!bEnglish)
    {
        m_TopBarName.push_back("アイテム");
        m_TopBarName.push_back("武器");
        m_TopBarName.push_back("ガイド");
        m_TopBarName.push_back("マップ");
        m_TopBarName.push_back("人物情報");
        m_TopBarName.push_back("敵情報");
        m_TopBarName.push_back("技・魔法");
        m_TopBarName.push_back("ステータス");
        m_TopBarName.push_back("セーブして終了");
        m_TopBarName.push_back("タイトルに戻る");
    }
    else
    {
        m_TopBarName.push_back("Item");
        m_TopBarName.push_back("Weapon");
        m_TopBarName.push_back("Guide");
        m_TopBarName.push_back("Map");
        m_TopBarName.push_back("Human Info");
        m_TopBarName.push_back("Enemy Info");
        m_TopBarName.push_back("Magic");
        m_TopBarName.push_back("Status");
        m_TopBarName.push_back("Save and Exit");
        m_TopBarName.push_back("Title");
    }

    m_TopBarNameKey.push_back("Item");
    m_TopBarNameKey.push_back("Weapon");
    m_TopBarNameKey.push_back("Guide");
    m_TopBarNameKey.push_back("Map");
    m_TopBarNameKey.push_back("Human Info");
    m_TopBarNameKey.push_back("Enemy Info");
    m_TopBarNameKey.push_back("Magic");
    m_TopBarNameKey.push_back("Status");
    m_TopBarNameKey.push_back("Save and Exit");
    m_TopBarNameKey.push_back("Title");
}

void NSMenulib::MenuLib::Finalize()
{
    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        delete it->GetSprite();
    }

    for (auto it = m_humanInfoList.begin(); it != m_humanInfoList.end(); ++it)
    {
        delete it->GetSprite();
    }

    for (auto it = m_enemyInfoList.begin(); it != m_enemyInfoList.end(); ++it)
    {
        delete it->GetSprite();
    }

    for (auto it = m_mapInfoList.begin(); it != m_mapInfoList.end(); ++it)
    {
        delete it->GetSprite();
    }

    for (auto it = m_skillInfoList.begin(); it != m_skillInfoList.end(); ++it)
    {
        delete it->GetSprite();
    }

    for (auto it = m_statusInfoList.begin(); it != m_statusInfoList.end(); ++it)
    {
        delete it->GetSprite();
    }

    for (auto it = m_weaponInfoList.begin(); it != m_weaponInfoList.end(); ++it)
    {
        delete it->GetSprite();
    }

    delete m_sprCursor;
    delete m_sprBackground;
    delete m_font;
    delete m_SE;
}

void MenuLib::SetItem(const std::vector<ItemInfo>& items)
{
    m_itemInfoList = items;
}

void MenuLib::SetHuman(const std::vector<HumanInfo>& items)
{
    m_humanInfoList = items;
}

void MenuLib::SetEnemy(const std::vector<EnemyInfo>& items)
{
    m_enemyInfoList = items;
}

void MenuLib::SetMap(const std::vector<MapInfo>& items)
{
    m_mapInfoList = items;
}

void MenuLib::SetSkill(const std::vector<SkillInfo>& items)
{
    m_skillInfoList = items;
}

void MenuLib::SetStatus(const std::vector<StatusInfo>& items)
{
    m_statusInfoList = items;
}

void MenuLib::SetGuide(const std::vector<GuideInfo>& items)
{
    m_guideInfoList = items;

    std::vector<std::string> vs;
    for (std::size_t i = 0; i < m_guideInfoList.size(); ++i)
    {
        std::string work_str = m_guideInfoList.at(i).GetCategory();
        if (std::find(vs.begin(), vs.end(), work_str) == vs.end())
        {
            vs.push_back(work_str);
        }
    }
    m_guideCategory = vs;

    m_guideSubCategory.clear();

    for (std::size_t i = 0; i < m_guideInfoList.size(); ++i)
    {
        std::string category = m_guideInfoList.at(i).GetCategory();
        std::string subCategory = m_guideInfoList.at(i).GetSubCategory();
        m_guideSubCategory[category].push_back(subCategory);
    }
}

void MenuLib::SetWeapon(const std::vector<WeaponInfo>& items)
{
    m_weaponInfoList = items;
}

std::string MenuLib::Up()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex >= TOPBAR_COL_MAX)
        {
            m_topBarIndex -= TOPBAR_COL_MAX;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        if (m_itemSelect >= 1)
        {
            m_itemSelect--;
            if (m_itemCursor >= 1)
            {
                m_itemCursor--;
            }
            else if (m_itemCursor == 0)
            {
                m_itemBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::WEAPON)
    {
        if (m_weaponSelect >= 1)
        {
            m_weaponSelect--;
            if (m_weaponCursor >= 1)
            {
                m_weaponCursor--;
            }
            else if (m_weaponCursor == 0)
            {
                m_weaponBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::GUIDE)
    {
        if (m_guideSelect >= 1)
        {
            m_guideSelect--;
            if (m_guideCursor >= 1)
            {
                m_guideCursor--;
            }
            else if (m_guideCursor == 0)
            {
                m_guideBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::GUIDE_SUB)
    {
        if (m_guideSubSelect >= 1)
        {
            m_guideSubSelect--;
            if (m_guideSubCursor >= 1)
            {
                m_guideSubCursor--;
            }
            else if (m_guideSubCursor == 0)
            {
                m_guideSubBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::MAP)
    {
        if (m_mapSelect >= 1)
        {
            m_mapSelect--;
            if (m_mapCursor >= 1)
            {
                m_mapCursor--;
            }
            else if (m_mapCursor == 0)
            {
                m_mapBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::HUMAN)
    {
        if (m_humanSelect >= 1)
        {
            m_humanSelect--;
            if (m_humanCursor >= 1)
            {
                m_humanCursor--;
            }
            else if (m_humanCursor == 0)
            {
                m_humanBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ENEMY)
    {
        if (m_enemySelect >= 1)
        {
            m_enemySelect--;
            if (m_enemyCursor >= 1)
            {
                m_enemyCursor--;
            }
            else if (m_enemyCursor == 0)
            {
                m_enemyBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::SKILL)
    {
        if (m_skillSelect >= 1)
        {
            m_skillSelect--;
            if (m_skillCursor >= 1)
            {
                m_skillCursor--;
            }
            else if (m_skillCursor == 0)
            {
                m_skillBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::STATUS)
    {
        if (m_statusSelect >= 1)
        {
            m_statusSelect--;
            if (m_statusCursor >= 1)
            {
                m_statusCursor--;
            }
            else if (m_statusCursor == 0)
            {
                m_statusBegin--;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::QUIT)
    {
        if (m_quitCursor == 1)
        {
            m_quitCursor = 0;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::OPENING)
    {
        if (m_openingCursor == 1)
        {
            m_openingCursor = 0;
            m_SE->PlayMove();
        }
    }
     
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Down()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex <= 2)
        {
            m_topBarIndex += TOPBAR_COL_MAX;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_itemSelect <= (int)m_itemInfoList.size() - 2)
        {
            m_itemSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_itemCursor <= LEFT_PANEL_ROW_MAX - 2)
            {
                m_itemCursor++;
            }
            else if (m_itemCursor == LEFT_PANEL_ROW_MAX - 1)
            {
                m_itemBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::WEAPON)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_weaponSelect <= (int)m_weaponInfoList.size() - 2)
        {
            m_weaponSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_weaponCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_weaponCursor++;
            }
            else if (m_weaponCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_weaponBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::GUIDE)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_guideSelect <= (int)m_guideCategory.size() - 2)
        {
            m_guideSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_guideCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_guideCursor++;
            }
            else if (m_guideCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_guideBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::GUIDE_SUB)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        std::vector<std::string> vs = m_guideSubCategory.at(m_guideCategory.at(m_guideSelect));
        if (m_guideSubSelect <= (int)vs.size() - 2)
        {
            m_guideSubSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_guideSubCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_guideSubCursor++;
            }
            else if (m_guideSubCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_guideSubBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::MAP)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_mapSelect <= (int)m_mapInfoList.size() - 2)
        {
            m_mapSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_mapCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_mapCursor++;
            }
            else if (m_mapCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_mapBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::HUMAN)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_humanSelect <= (int)m_humanInfoList.size() - 2)
        {
            m_humanSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_humanCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_humanCursor++;
            }
            else if (m_humanCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_humanBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ENEMY)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_enemySelect <= (int)m_enemyInfoList.size() - 2)
        {
            m_enemySelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_enemyCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_enemyCursor++;
            }
            else if (m_enemyCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_enemyBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::SKILL)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_skillSelect <= (int)m_skillInfoList.size() - 2)
        {
            m_skillSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_skillCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_skillCursor++;
            }
            else if (m_skillCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_skillBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::STATUS)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_statusSelect <= (int)m_statusInfoList.size() - 2)
        {
            m_statusSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_statusCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_statusCursor++;
            }
            else if (m_statusCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_statusBegin++;
            }
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::QUIT)
    {
        if (m_quitCursor == 0)
        {
            m_quitCursor = 1;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::OPENING)
    {
        if (m_openingCursor == 0)
        {
            m_openingCursor = 1;
            m_SE->PlayMove();
        }
    }

    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Right()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex <= LEFT_PANEL_ROW_MAX - 2)
        {
            m_topBarIndex++;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        if (m_itemSubCursor == 0)
        {
            m_itemSubCursor++;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::WEAPON_SUB)
    {
        if (m_weaponSubCursor == 0)
        {
            m_weaponSubCursor++;
            m_SE->PlayMove();
        }
    }
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Left()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (1 <= m_topBarIndex)
        {
            m_topBarIndex--;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        if (m_itemSubCursor == 1)
        {
            m_itemSubCursor--;
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::WEAPON_SUB)
    {
        if (m_weaponSubCursor == 1)
        {
            m_weaponSubCursor--;
            m_SE->PlayMove();
        }
    }
    return m_TopBarName.at(m_topBarIndex);
}

std::string MenuLib::Into()
{
    std::string result;
    m_SE->PlayClick();
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex == TOPBAR_ITEM)
        {
            m_eFocus = eFocus::ITEM;
            m_itemCursor = 0;
            m_itemBegin = 0;
            m_itemSelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_WEAPON)
        {
            m_eFocus = eFocus::WEAPON;
            m_weaponCursor = 0;
            m_weaponBegin = 0;
            m_weaponSelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_GUIDE)
        {
            m_eFocus = eFocus::GUIDE;
            m_guideCursor = 0;
            m_guideBegin = 0;
            m_guideSelect = 0;

            m_guideSubCursor = 0;
            m_guideSubBegin = 0;
            m_guideSubSelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_MAP)
        {
            m_eFocus = eFocus::MAP;
            m_mapCursor = 0;
            m_mapBegin = 0;
            m_mapSelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_HUMAN)
        {
            m_eFocus = eFocus::HUMAN;
            m_humanCursor = 0;
            m_humanBegin = 0;
            m_humanSelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_ENEMY)
        {
            m_eFocus = eFocus::ENEMY;
            m_enemyCursor = 0;
            m_enemyBegin = 0;
            m_enemySelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_SKILL)
        {
            m_eFocus = eFocus::SKILL;
            m_skillCursor = 0;
            m_skillBegin = 0;
            m_skillSelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_STATUS)
        {
            m_eFocus = eFocus::STATUS;
            m_statusCursor = 0;
            m_statusBegin = 0;
            m_statusSelect = 0;
        }
        else if (m_topBarIndex == TOPBAR_QUIT)
        {
            m_eFocus = eFocus::QUIT;
            m_quitCursor = 0;
        }
        else if (m_topBarIndex == TOPBAR_OPENING)
        {
            m_eFocus = eFocus::OPENING;
            m_openingCursor = 0;
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        if (!m_itemInfoList.empty())
        {
            m_eFocus = eFocus::ITEM_SUB;
            m_itemSubCursor = 0;
        }
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        result = m_TopBarNameKey.at(m_topBarIndex);
        result += ":" + m_itemInfoList.at(m_itemSelect).GetName();
        result += ":" + std::to_string(m_itemInfoList.at(m_itemSelect).GetId());
        result += ":" + std::to_string(m_itemInfoList.at(m_itemSelect).GetSubId());

        if (!m_itemInfoList.at(m_itemSelect).GetEquipEnable())
        {
            if (m_itemSubCursor == 0)
            {
                result += ":Use";
            }
            else
            {
                result += ":Discard";
            }
        }
        else
        {
            if (!m_itemInfoList.at(m_itemSelect).GetEquip())
            {
                if (m_itemSubCursor == 0)
                {
                    result += ":Equip";
                }
                else
                {
                    result += ":Discard";
                }
            }
            else
            {
                if (m_itemSubCursor == 0)
                {
                    result += ":Unequip";
                }
                else
                {
                    result += ":Discard";
                }
            }
        }

        m_eFocus = eFocus::ITEM;
        m_itemSubCursor = 0;
    }
    else if (m_eFocus == eFocus::WEAPON)
    {
        if (!m_weaponInfoList.empty())
        {
            m_eFocus = eFocus::WEAPON_SUB;
            m_weaponSubCursor = 0;
        }
    }
    else if (m_eFocus == eFocus::WEAPON_SUB)
    {
        result = m_TopBarNameKey.at(m_topBarIndex);
        result += ":" + m_weaponInfoList.at(m_weaponSelect).GetName();
        result += ":" + std::to_string(m_weaponInfoList.at(m_weaponSelect).GetId());
        result += ":" + std::to_string(m_weaponInfoList.at(m_weaponSelect).GetSubId());
        if (m_weaponSubCursor == 0)
        {
            result += ":Equip";
        }
        else
        {
            result += ":Cancel";
        }
        m_eFocus = eFocus::WEAPON;
        m_weaponSubCursor = 0;
    }
    else if (m_eFocus == eFocus::GUIDE)
    {
        m_eFocus = eFocus::GUIDE_SUB;
        m_guideSubCursor = 0;
    }
    else if (m_eFocus == eFocus::QUIT)
    {
        if (m_quitCursor == 0)
        {
            result = m_TopBarNameKey.at(m_topBarIndex);
        }
        else
        {
            m_eFocus = eFocus::TOP_BAR;
            m_quitCursor = 0;
        }
    }
    else if (m_eFocus == eFocus::OPENING)
    {
        if (m_openingCursor == 0)
        {
            result = m_TopBarNameKey.at(m_topBarIndex);
        }
        else
        {
            m_eFocus = eFocus::TOP_BAR;
            m_openingCursor = 0;
        }
    }

    return result;
}

std::string MenuLib::Back()
{
    std::string result;
    if (m_eFocus == eFocus::ITEM ||
        m_eFocus == eFocus::WEAPON ||
        m_eFocus == eFocus::GUIDE ||
        m_eFocus == eFocus::MAP ||
        m_eFocus == eFocus::HUMAN ||
        m_eFocus == eFocus::ENEMY ||
        m_eFocus == eFocus::SKILL ||
        m_eFocus == eFocus::STATUS ||
        m_eFocus == eFocus::QUIT ||
        m_eFocus == eFocus::OPENING)
    {
        m_eFocus = eFocus::TOP_BAR;
        m_SE->PlayBack();
        result = m_TopBarNameKey.at(m_topBarIndex);
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        m_eFocus = eFocus::ITEM;
        m_SE->PlayBack();
        result = m_TopBarNameKey.at(m_topBarIndex);
        result += ":" + m_itemInfoList.at(m_itemSelect).GetName();
    }
    else if (m_eFocus == eFocus::WEAPON_SUB)
    {
        m_eFocus = eFocus::WEAPON;
        m_SE->PlayBack();
        result = m_TopBarNameKey.at(m_topBarIndex);
        result += ":" + m_weaponInfoList.at(m_weaponSelect).GetName();
    }
    else if (m_eFocus == eFocus::GUIDE_SUB)
    {
        m_eFocus = eFocus::GUIDE;
        m_SE->PlayBack();
        m_guideSubSelect = 0;
        m_guideSubBegin = 0;
    }
    // TOP_BARにフォーカスがあるときに戻ろうとした。
    // つまりメニュー画面を閉じようとした。
    else if (m_eFocus == eFocus::TOP_BAR)
    {
        m_SE->PlayBack();
        result = "EXIT";
    }
    else
    {
        m_eFocus = eFocus::TOP_BAR;
        m_SE->PlayBack();
        result = m_TopBarNameKey.at(m_topBarIndex);
    }
    return result;
}

std::string MenuLib::Next()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        Right();
    }
    else
    {
        Down();
    }
    return std::string();
}

std::string MenuLib::Previous()
{
    if (m_eFocus == eFocus::TOP_BAR)
    {
        Left();
    }
    else
    {
        Up();
    }
    return std::string();
}

void NSMenulib::MenuLib::CursorOn(const int x, const int y)
{
    int previousIndex = 0;
    if (m_eFocus == eFocus::TOP_BAR)
    {
        previousIndex = m_topBarIndex;
        if (TOPBAR_STARTY < y && y <= TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT * 1)
        {
            if (TOPBAR_STARTX < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1)
            {
                m_topBarIndex = TOPBAR_ITEM;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2)
            {
                m_topBarIndex = TOPBAR_WEAPON;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 3)
            {
                m_topBarIndex = TOPBAR_GUIDE;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 3 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 4)
            {
                m_topBarIndex = TOPBAR_MAP;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 4 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 5)
            {
                m_topBarIndex = TOPBAR_HUMAN;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 5 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 6)
            {
                m_topBarIndex = TOPBAR_ENEMY;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 6 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 7)
            {
                m_topBarIndex = TOPBAR_SKILL;
            }
        }
        else if (TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT * 1 < y && y <= TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT * 2)
        {
            if (TOPBAR_STARTX < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1)
            {
                m_topBarIndex = TOPBAR_STATUS;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2)
            {
                m_topBarIndex = TOPBAR_QUIT;
            }
            else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 3)
            {
                m_topBarIndex = TOPBAR_OPENING;
            }
        }

        if (previousIndex != m_topBarIndex)
        {
            m_SE->PlayMove();
        }
    }
    else if (m_eFocus == eFocus::ITEM ||
             m_eFocus == eFocus::WEAPON ||
             m_eFocus == eFocus::GUIDE ||
             m_eFocus == eFocus::MAP ||
             m_eFocus == eFocus::HUMAN||
             m_eFocus == eFocus::ENEMY ||
             m_eFocus == eFocus::SKILL ||
             m_eFocus == eFocus::STATUS ||
             m_eFocus == eFocus::QUIT ||
             m_eFocus == eFocus::OPENING)
    {
        if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
        {
            int nCursor = 0;
            int nSelect = -1;
            int nBegin = 0;
            size_t nSize = 10;
            if (m_eFocus == eFocus::ITEM)
            {
                previousIndex = m_itemSelect;
                nBegin = m_itemBegin;
                if (m_itemInfoList.size() <= 9)
                {
                    nSize = m_itemInfoList.size();
                }
            }
            else if (m_eFocus == eFocus::WEAPON)
            {
                previousIndex = m_weaponSelect;
                nBegin = m_weaponBegin;
                if (m_weaponInfoList.size() <= 9)
                {
                    nSize = m_weaponInfoList.size();
                }
            }
            else if (m_eFocus == eFocus::GUIDE)
            {
                previousIndex = m_guideSelect;
                nBegin = m_guideBegin;
                if (m_guideCategory.size() <= 9)
                {
                    nSize = m_guideCategory.size();
                }
            }
            else if (m_eFocus == eFocus::MAP)
            {
                previousIndex = m_mapSelect;
                nBegin = m_mapBegin;
                if (m_mapInfoList.size() <= 9)
                {
                    nSize = m_mapInfoList.size();
                }
            }
            else if (m_eFocus == eFocus::HUMAN)
            {
                previousIndex = m_humanSelect;
                nBegin = m_humanBegin;
                if (m_humanInfoList.size() <= 9)
                {
                    nSize = m_humanInfoList.size();
                }
            }
            else if (m_eFocus == eFocus::ENEMY)
            {
                previousIndex = m_enemySelect;
                nBegin = m_enemyBegin;
                if (m_enemyInfoList.size() <= 9)
                {
                    nSize = m_enemyInfoList.size();
                }
            }
            else if (m_eFocus == eFocus::SKILL)
            {
                previousIndex = m_skillSelect;
                nBegin = m_skillBegin;
                if (m_skillInfoList.size() <= 9)
                {
                    nSize = m_skillInfoList.size();
                }
            }
            else if (m_eFocus == eFocus::STATUS)
            {
                previousIndex = m_statusSelect;
                nBegin = m_statusBegin;
                if (m_statusInfoList.size() <= 9)
                {
                    nSize = m_statusInfoList.size();
                }
            }
            else if (m_eFocus == eFocus::QUIT)
            {
                previousIndex = m_quitCursor;
                nBegin = 0;
                nSize = 2;
            }
            else if (m_eFocus == eFocus::OPENING)
            {
                previousIndex = m_openingCursor;
                nBegin = 0;
                nSize = 2;
            }

            bool hit = false;

            for (int i = 0; i < (int)nSize; ++i)
            {
                if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                    y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                {
                    nCursor = i;
                    nSelect = nBegin + i;
                    hit = true;
                    break;
                }
            }

            if (nSelect != -1)
            {
                if (previousIndex != nSelect)
                {
                    m_SE->PlayMove();
                }
            }

            if (hit)
            {
                if (m_eFocus == eFocus::ITEM)
                {
                    m_itemCursor = nCursor;
                    m_itemSelect = nSelect;
                }
                else if (m_eFocus == eFocus::WEAPON)
                {
                    m_weaponCursor = nCursor;
                    m_weaponSelect = nSelect;
                }
                else if (m_eFocus == eFocus::GUIDE)
                {
                    m_guideCursor = nCursor;
                    m_guideSelect = nSelect;
                }
                else if (m_eFocus == eFocus::MAP)
                {
                    m_mapCursor = nCursor;
                    m_mapSelect = nSelect;
                }
                else if (m_eFocus == eFocus::HUMAN)
                {
                    m_humanCursor = nCursor;
                    m_humanSelect = nSelect;
                }
                else if (m_eFocus == eFocus::ENEMY)
                {
                    m_enemyCursor = nCursor;
                    m_enemySelect = nSelect;
                }
                else if (m_eFocus == eFocus::SKILL)
                {
                    m_skillCursor = nCursor;
                    m_skillSelect = nSelect;
                }
                else if (m_eFocus == eFocus::STATUS)
                {
                    m_statusCursor = nCursor;
                    m_statusSelect = nSelect;
                }
                else if (m_eFocus == eFocus::QUIT)
                {
                    m_quitCursor = nCursor;
                }
                else if (m_eFocus == eFocus::OPENING)
                {
                    m_openingCursor = nCursor;
                }
            }
        }
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * m_itemCursor - 10 < y &&
            y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (m_itemCursor + 1) - 10)
        {
            previousIndex = m_itemSubCursor;

            if (MIDDLE_PANEL_STARTX < x && x <= MIDDLE_PANEL_STARTX + 80)
            {
                m_itemSubCursor = 0;
            }
            else if (MIDDLE_PANEL_STARTX + 100 < x && x <= MIDDLE_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                m_itemSubCursor = 1;
            }
            else
            {
                m_itemSubCursor = -1;
            }

            if (previousIndex != m_itemSubCursor)
            {
                m_SE->PlayMove();
            }
        }
        else
        {
			m_itemSubCursor = -1;
        }
    }
    else if (m_eFocus == eFocus::WEAPON_SUB)
    {
        if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * m_weaponCursor -10 < y &&
            y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (m_weaponCursor + 1) -10)
        {
            previousIndex = m_weaponSubCursor;

            if (MIDDLE_PANEL_STARTX < x && x <= MIDDLE_PANEL_STARTX + 100)
            {
                m_weaponSubCursor = 0;
            }
            else if (MIDDLE_PANEL_STARTX + 100 < x && x <= MIDDLE_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                m_weaponSubCursor = 1;
            }
            else
            {
                m_weaponSubCursor = -1;
            }

            if (previousIndex != m_weaponSubCursor)
            {
                m_SE->PlayMove();
            }
        }
        else
        {
			m_weaponSubCursor = -1;
        }
    }
    else if (m_eFocus == eFocus::GUIDE_SUB)
    {
        if (MIDDLE_PANEL_STARTX - 250 < x && x <= MIDDLE_PANEL_STARTX -250 + LEFT_PANEL_WIDTH)
        {
            previousIndex = m_guideSubCursor;

            std::string category = m_guideCategory.at(m_guideSelect);
            size_t nSize = m_guideSubCategory.at(category).size();
            if (nSize >= 10)
            {
                nSize = 10;
            }

            for (int i = 0; i < (int)nSize; ++i)
            {
                if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                    y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                {
                    m_guideSubCursor = i;
                    m_guideSubSelect = m_guideSubBegin + i;
                    break;
                }
            }

            if (previousIndex != m_guideSubCursor)
            {
                m_SE->PlayMove();
            }
        }
    }
}

std::string MenuLib::Click(const int x, const int y)
{
    std::string result;
    m_SE->PlayClick();

    if (y < TOPBAR_STARTY)
    {
        return result;
    }

    // どこにフォーカスがあってもTOP Barをクリックしたら、その操作は有効にする。
    if (TOPBAR_STARTY < y && y <= TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT * 1)
    {
        if (TOPBAR_STARTX < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1)
        {
            m_eFocus = eFocus::ITEM;
            m_topBarIndex = TOPBAR_ITEM;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2)
        {
            m_eFocus = eFocus::WEAPON;
            m_topBarIndex = TOPBAR_WEAPON;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 3)
        {
            m_eFocus = eFocus::GUIDE;
            m_topBarIndex = TOPBAR_GUIDE;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 3 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 4)
        {
            m_eFocus = eFocus::MAP;
            m_topBarIndex = TOPBAR_MAP;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 4 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 5)
        {
            m_eFocus = eFocus::HUMAN;
            m_topBarIndex = TOPBAR_HUMAN;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 5 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 6)
        {
            m_eFocus = eFocus::ENEMY;
            m_topBarIndex = TOPBAR_ENEMY;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 6 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 7)
        {
            m_eFocus = eFocus::SKILL;
            m_topBarIndex = TOPBAR_SKILL;
        }
    }
    else if (TOPBAR_STARTY < y + TOPBAR_PANEL_HEIGHT * 1 && y <= TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT * 2)
    {
        if (TOPBAR_STARTX < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1)
        {
            m_eFocus = eFocus::STATUS;
            m_topBarIndex = TOPBAR_STATUS;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 1 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2)
        {
            m_eFocus = eFocus::QUIT;
            m_topBarIndex = TOPBAR_QUIT;
            m_quitCursor = 0;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 3)
        {
            m_eFocus = eFocus::OPENING;
            m_topBarIndex = TOPBAR_OPENING;
            m_openingCursor = 0;
        }
    }
    else
    {
        int nBegin = 0;
        size_t nSize = 10;

        // 同じ処理が延々と続くが、共通化してはいけない。
        // メニューごとにクリック範囲が変わる可能性があるため。
        // 例えば、「ガイド」ではサブカテゴリが左に250ピクセル寄っているのでクリックを検知する範囲が異なる。
        if (m_eFocus == eFocus::ITEM)
        {
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nBegin = m_itemBegin;
                if (m_itemInfoList.size() <= 9)
                {
                    nSize = m_itemInfoList.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_itemCursor = i;
                        m_itemSelect = nBegin + i;
                        m_itemSubCursor = 0;
                        m_eFocus = eFocus::ITEM_SUB;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::ITEM_SUB)
        {
            if (MIDDLE_PANEL_STARTX < x && x <= MIDDLE_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * m_itemCursor - 10 < y &&
                    y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (m_itemCursor + 1) - 10)
                {
                    if (MIDDLE_PANEL_STARTX < x && x <= MIDDLE_PANEL_STARTX + 80)
                    {
                        m_itemSubCursor = 0;
                    }
                    else if (MIDDLE_PANEL_STARTX + 100 < x &&
                             x <= MIDDLE_PANEL_STARTX + LEFT_PANEL_WIDTH)
                    {
                        m_itemSubCursor = 1;
                    }

                    result = m_TopBarNameKey.at(m_topBarIndex);
                    result += ":" + m_itemInfoList.at(m_itemSelect).GetName();
                    result += ":" + std::to_string(m_itemInfoList.at(m_itemSelect).GetId());
                    result += ":" + std::to_string(m_itemInfoList.at(m_itemSelect).GetSubId());

                    if (!m_itemInfoList.at(m_itemSelect).GetEquipEnable())
                    {
                        if (m_itemSubCursor == 0)
                        {
                            result += ":Use";
                        }
                        else
                        {
                            result += ":Discard";
                        }
                    }
                    else
                    {
                        if (!m_itemInfoList.at(m_itemSelect).GetEquip())
                        {
                            if (m_itemSubCursor == 0)
                            {
                                result += ":Equip";
                            }
                            else
                            {
                                result += ":Discard";
                            }
                        }
                        else
                        {
                            if (m_itemSubCursor == 0)
                            {
                                result += ":Unequip";
                            }
                            else
                            {
                                result += ":Discard";
                            }
                        }
                    }
                }
            }

            // 「使う」「捨てる」の部分をクリックした場合も、それ以外の場所をクリックした場合も
            // ITEM_SUBから抜ける。
            m_eFocus = eFocus::ITEM;
            m_itemSubCursor = 0;
        }
        else if (m_eFocus == eFocus::WEAPON)
        {
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nBegin = m_weaponBegin;
                if (m_weaponInfoList.size() <= 9)
                {
                    nSize = m_weaponInfoList.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_weaponCursor = i;
                        m_weaponSelect = nBegin + i;
                        m_weaponSubCursor = 0;
                        m_eFocus = eFocus::WEAPON_SUB;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::WEAPON_SUB)
        {
            if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * m_weaponCursor -10 < y &&
                y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (m_weaponCursor + 1) -10)
            {
                if (MIDDLE_PANEL_STARTX < x && x <= MIDDLE_PANEL_STARTX + 100)
                {
                    m_weaponSubCursor = 0;
                }
                else if (MIDDLE_PANEL_STARTX + 100 < x &&
                         x <= MIDDLE_PANEL_STARTX + LEFT_PANEL_WIDTH)
                {
                    m_weaponSubCursor = 1;
                }

                result = m_TopBarNameKey.at(m_topBarIndex);
                result += ":" + m_weaponInfoList.at(m_weaponSelect).GetName();
                result += ":" + std::to_string(m_weaponInfoList.at(m_weaponSelect).GetId());
                result += ":" + std::to_string(m_weaponInfoList.at(m_weaponSelect).GetSubId());
                if (m_weaponSubCursor == 0)
                {
                    result += ":Equip";
                }
                else
                {
                    result += ":Cancel";
                }
            }

            // 「装備」「キャンセル」の部分をクリックした場合も、それ以外の場所をクリックした場合も
            // WEAPON_SUBから抜ける。
            m_eFocus = eFocus::WEAPON;
            m_weaponSubCursor = 0;
        }
        else if (m_eFocus == eFocus::GUIDE)
        {
            // ガイドはサブカテゴリが左に寄っている
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH - 250)
            {
                nBegin = m_guideBegin;
                if (m_guideCategory.size() <= 9)
                {
                    nSize = m_guideCategory.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_guideCursor = i;
                        m_guideSelect = nBegin + i;
                        m_guideSubCursor = 0;
                        m_eFocus = eFocus::GUIDE_SUB;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::GUIDE_SUB)
        {
            // ガイドはサブカテゴリが左に寄っている
            if (MIDDLE_PANEL_STARTX - 250 < x && x <= MIDDLE_PANEL_STARTX - 250 + LEFT_PANEL_WIDTH)
            {
                nBegin = m_guideBegin;

                auto category = m_guideCategory.at(m_guideSelect);
                if (m_guideSubCategory.at(category).size() <= 9)
                {
                    nSize = m_guideSubCategory.at(category).size();
                }

                bool hit = false;
                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_guideSubCursor = i;
                        m_guideSubSelect = nBegin + i;

                        hit = true;

                        break;
                    }
                }
                
                if (!hit)
                {
                    m_eFocus = eFocus::GUIDE;
                    m_guideSubCursor = 0;
                    m_guideSubSelect = 0;
                }
            }
            else
            {
                m_eFocus = eFocus::GUIDE;
                m_guideSubCursor = 0;
                m_guideSubSelect = 0;
            }
        }
        else if (m_eFocus == eFocus::MAP)
        {
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nBegin = m_mapBegin;
                if (m_mapInfoList.size() <= 9)
                {
                    nSize = m_mapInfoList.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_mapCursor = i;
                        m_mapSelect = nBegin + i;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::HUMAN)
        {
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nBegin = m_humanBegin;
                if (m_humanInfoList.size() <= 9)
                {
                    nSize = m_humanInfoList.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_humanCursor = i;
                        m_humanSelect = nBegin + i;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::ENEMY)
        {
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nBegin = m_enemyBegin;
                if (m_enemyInfoList.size() <= 9)
                {
                    nSize = m_enemyInfoList.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_enemyCursor = i;
                        m_enemySelect = nBegin + i;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::SKILL)
        {
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nBegin = m_skillBegin;
                if (m_skillInfoList.size() <= 9)
                {
                    nSize = m_skillInfoList.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_skillCursor = i;
                        m_skillSelect = nBegin + i;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::STATUS)
        {
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nBegin = m_statusBegin;
                if (m_statusInfoList.size() <= 9)
                {
                    nSize = m_statusInfoList.size();
                }

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_statusCursor = i;
                        m_statusSelect = nBegin + i;
                        break;
                    }
                }
            }
        }
        else if (m_eFocus == eFocus::QUIT)
        {
            m_quitCursor = -1;
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nSize = 2;

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_quitCursor = i;
                        break;
                    }
                }
            }

            if (m_quitCursor == 0)
            {
                result = m_TopBarNameKey.at(m_topBarIndex);
            }
            else
            {
                m_eFocus = eFocus::TOP_BAR;
            }
        }
        else if (m_eFocus == eFocus::OPENING)
        {
            m_openingCursor = -1;
            if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
            {
                nSize = 2;

                for (int i = 0; i < (int)nSize; ++i)
                {
                    if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * i < y &&
                        y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * (i + 1))
                    {
                        m_openingCursor = i;
                        break;
                    }
                }
            }

            if (m_openingCursor == 0)
            {
                result = m_TopBarNameKey.at(m_topBarIndex);
            }
            else
            {
                m_eFocus = eFocus::TOP_BAR;
            }
        }
    }

    return result;
}

void NSMenulib::MenuLib::RightClick()
{
    Back();
}

void MenuLib::Draw()
{
    m_sprBackground->DrawImage(0, 0);

    if (m_eFocus == eFocus::TOP_BAR)
    {
        m_font->DrawText_(m_TopBarName.at(0), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 0) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(1), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 1) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(2), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 2) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(3), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 3) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(4), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 4) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(5), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 5) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(6), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 6) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(7), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 0) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(8), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 1) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY, true);
        m_font->DrawText_(m_TopBarName.at(9), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 2) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY, true);
    }
    else
    {
        const int transparency = 32;

        m_font->DrawText_(m_TopBarName.at(0), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 0) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(1), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 1) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(2), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 2) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(3), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 3) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(4), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 4) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(5), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 5) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(6), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 6) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(7), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 0) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(8), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 1) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY, true, transparency);
        m_font->DrawText_(m_TopBarName.at(9), TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 2) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY, true, transparency);

        if (m_topBarIndex < 7)
        {
            m_font->DrawText_(m_TopBarName.at(m_topBarIndex),
                              TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * m_topBarIndex) + TOPBAR_PADDINGX,
                              TOPBAR_STARTY + TOPBAR_PADDINGY,
                              true,
                              255);
        }
        else
        {
            m_font->DrawText_(m_TopBarName.at(m_topBarIndex),
                              TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * (m_topBarIndex - 7)) + TOPBAR_PADDINGX,
                              TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY,
                              true,
                              255);
        }
    }

    if (m_eFocus == eFocus::ITEM || m_eFocus == eFocus::ITEM_SUB)
    {
        if (!m_bEnglish)
        {
            m_font->DrawText_("強化", LEFT_PANEL_STARTX + 320, LEFT_PANEL_STARTY - 35, true, 64);
            m_font->DrawText_("耐久", LEFT_PANEL_STARTX + 380, LEFT_PANEL_STARTY - 35, true, 64);
        }
        else
        {
            m_font->DrawText_("Level", LEFT_PANEL_STARTX + 320, LEFT_PANEL_STARTY - 35, true, 64);
            m_font->DrawText_("Drblty", LEFT_PANEL_STARTX + 380, LEFT_PANEL_STARTY - 35, true, 64);
        }

        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_itemInfoList.size() <= m_itemBegin + i)
            {
                break;
            }

            int trans = 255;
            if (m_eFocus == eFocus::ITEM_SUB)
            {
                trans = 32;
                if (i == m_itemCursor)
                {
                    trans = 255;
                }
            }

            std::string work = m_itemInfoList.at((size_t)m_itemBegin + i).GetName();
            if (m_itemInfoList.at((size_t)m_itemBegin + i).GetEquip())
            {
                if (!m_bEnglish)
                {
                    work += "（装備中）";
                }
                else
                {
                    work += " (Equipped)";
                }
            }

            m_font->DrawText_(work,
                              LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                              LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i * LEFT_PANEL_HEIGHT),
                              false,
                              trans);

            if (m_itemInfoList.at((size_t)m_itemBegin + i).GetLevel() != -1)
            {
                m_font->DrawText_(
                    std::to_string(m_itemInfoList.at((size_t)m_itemBegin+i).GetLevel()),
                    350 + LEFT_PANEL_PADDINGX,
                    LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT),
                    true,
                    trans);
            }

            if (m_itemInfoList.at((size_t)m_itemBegin + i).GetDurability() != -1)
            {
                m_font->DrawText_(
                    std::to_string(m_itemInfoList.at((size_t)m_itemBegin + i).GetDurability()),
                    410 + LEFT_PANEL_PADDINGX,
                    LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i * LEFT_PANEL_HEIGHT),
                    true,
                    trans);
            }
        }
    }
    else if (m_eFocus == eFocus::WEAPON || m_eFocus == eFocus::WEAPON_SUB)
    {
        if (!m_bEnglish)
        {
            m_font->DrawText_("強化", LEFT_PANEL_STARTX + 320, LEFT_PANEL_STARTY - 35, true, 64);
            m_font->DrawText_("耐久", LEFT_PANEL_STARTX + 380, LEFT_PANEL_STARTY - 35, true, 64);
        }
        else
        {
            m_font->DrawText_("Level", LEFT_PANEL_STARTX + 320, LEFT_PANEL_STARTY - 35, true, 64);
            m_font->DrawText_("Drblty", LEFT_PANEL_STARTX + 380, LEFT_PANEL_STARTY - 35, true, 64);
        }

        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_weaponInfoList.size() <= m_weaponBegin + i)
            {
                break;
            }

            int trans = 255;
            if (m_eFocus == eFocus::WEAPON_SUB)
            {
                trans = 32;
                if (i == m_weaponSelect)
                {
                    trans = 255;
                }
            }

            m_font->DrawText_(
                m_weaponInfoList.at((size_t)m_weaponBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT),
                false,
                trans);

            if (m_weaponInfoList.at((size_t)m_weaponBegin + i).GetLevel() != -1)
            {
                m_font->DrawText_(
                    std::to_string(m_weaponInfoList.at((size_t)m_weaponBegin + i).GetLevel()),
                    350 + LEFT_PANEL_PADDINGX,
                    LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i * LEFT_PANEL_HEIGHT),
                    true,
                    trans);
            }

            if (m_weaponInfoList.at((size_t)m_weaponBegin + i).GetDurability() != -1)
            {
                m_font->DrawText_(
                    std::to_string(m_weaponInfoList.at((size_t)m_weaponBegin+i).GetDurability()),
                    410 + LEFT_PANEL_PADDINGX,
                    LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT),
                    true,
                    trans);
            }
        }
    }
    else if (m_eFocus == eFocus::GUIDE || m_eFocus == eFocus::GUIDE_SUB)
    {
        // 大カテゴリの数だけ表示
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_guideCategory.size() <= m_guideBegin + i)
            {
                break;
            }

            int trans = 255;
            if (m_eFocus == eFocus::GUIDE_SUB)
            {
                trans = 32;
                if (i == m_guideCursor)
                {
                    trans = 255;
                }
            }
            m_font->DrawText_(m_guideCategory.at((size_t)m_guideBegin+i),
                              LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                              LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT),
                              false,
                              trans);
        }
    }
    else if (m_eFocus == eFocus::MAP)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_mapInfoList.size() <= m_mapBegin + i)
            {
                break;
            }
            m_font->DrawText_(
                m_mapInfoList.at((size_t)m_mapBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_eFocus == eFocus::HUMAN)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_humanInfoList.size() <= m_humanBegin + i)
            {
                break;
            }
            m_font->DrawText_(
                m_humanInfoList.at((size_t)m_humanBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_eFocus == eFocus::ENEMY)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_enemyInfoList.size() <= m_enemyBegin + i)
            {
                break;
            }
            m_font->DrawText_(
                m_enemyInfoList.at((size_t)m_enemyBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_eFocus == eFocus::SKILL)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_skillInfoList.size() <= m_skillBegin + i)
            {
                break;
            }
            m_font->DrawText_(
                m_skillInfoList.at((size_t)m_skillBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_eFocus == eFocus::STATUS)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_statusInfoList.size() <= m_statusBegin + i)
            {
                break;
            }
            m_font->DrawText_(
                m_statusInfoList.at((size_t)m_statusBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_eFocus == eFocus::QUIT)
    {
        if (!m_bEnglish)
        {
            m_font->DrawText_(
                "はい",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*0));

            m_font->DrawText_(
                "いいえ",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*1));
        }
        else
        {
            m_font->DrawText_(
                "Yes",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*0));

            m_font->DrawText_(
                "No",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*1));
        }
    }
    else if (m_eFocus == eFocus::OPENING)
    {
        if (!m_bEnglish)
        {
            m_font->DrawText_(
                "はい",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*0));

            m_font->DrawText_(
                "いいえ",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*1));
        }
        else
        {
            m_font->DrawText_(
                "Yes",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*0));

            m_font->DrawText_(
                "No",
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (LEFT_PANEL_HEIGHT*1));
        }
    }

    // Show item detail
    if (m_eFocus == eFocus::ITEM || m_eFocus == eFocus::ITEM_SUB)
    {
        if (!m_itemInfoList.empty())
        {
            int trans = 255;
            if (m_eFocus == eFocus::ITEM_SUB)
            {
                trans = 64;
            }
            m_itemInfoList.at(m_itemSelect).GetSprite()->DrawImage(550, 300, trans);

            std::string detail = m_itemInfoList.at(m_itemSelect).GetDetail();
            std::vector<std::string> details = split(detail, '\n');

            std::string weight_volume;

            if (!m_bEnglish)
            {
                weight_volume += "重量(kg) ";
            }
            else
            {
                weight_volume += "Weight (kg) ";
            }

            weight_volume += ToStringWithPrecision(m_itemInfoList.at(m_itemSelect).GetWeight(), 2);
            weight_volume += "  ";

            if (!m_bEnglish)
            {
                weight_volume += "体積(mL) ";
            }
            else
            {
                weight_volume += "Volume (mL) ";
            }

            weight_volume += std::to_string(m_itemInfoList.at(m_itemSelect).GetVolume());

            details.insert(details.begin(), weight_volume);

            for (std::size_t i = 0; i < details.size(); ++i)
            {
                m_font->DrawText_(
                    details.at(i),
                    1100,
                    250 + (int)i*40
                    );
            }
        }

        // 総重量、積載量、最大積載量を表示
        {
            std::string weightAll_Vol_VolMax;

            if (!m_bEnglish)
            {
                weightAll_Vol_VolMax += "総重量(kg) ";
            }
            else
            {
                weightAll_Vol_VolMax += "Total Weight (kg) ";
            }

            weightAll_Vol_VolMax += ToStringWithPrecision(m_weightAll, 2);
            weightAll_Vol_VolMax += "  ";

            if (!m_bEnglish)
            {
                weightAll_Vol_VolMax += "積載量(mL)/最大積載量(mL) ";
            }
            else
            {
                weightAll_Vol_VolMax += "Volume (mL) / Total volume (mL) ";
            }

            weightAll_Vol_VolMax += std::to_string(m_volumeAll);
            weightAll_Vol_VolMax += "/";
            weightAll_Vol_VolMax += std::to_string(m_volumeMax);
            weightAll_Vol_VolMax += "  ";

            m_font->DrawText_(weightAll_Vol_VolMax, 1000, 850);
        }
    }

    // Show item sub
    if (m_eFocus == eFocus::ITEM_SUB)
    {
        // 装備が可能なアイテムなら「装備する」を表示するようにする
        if (!m_itemInfoList.at(m_itemSelect).GetEquipEnable())
        {
            if (!m_bEnglish)
            {
                m_font->DrawText_("使う　　　　　　捨てる",
                                  MIDDLE_PANEL_STARTX,
                                  LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_itemCursor * LEFT_PANEL_HEIGHT));
            }
            else
            {
                m_font->DrawText_("Use             Discard",
                                  MIDDLE_PANEL_STARTX,
                                  LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_itemCursor * LEFT_PANEL_HEIGHT));
            }
        }
        else
        {
            if (!m_itemInfoList.at(m_itemSelect).GetEquip())
            {
                if (!m_bEnglish)
                {
                    m_font->DrawText_("装備する　　　　捨てる",
                                      MIDDLE_PANEL_STARTX,
                                      LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_itemCursor * LEFT_PANEL_HEIGHT));
                }
                else
                {
                    m_font->DrawText_("Equip           Discard",
                                      MIDDLE_PANEL_STARTX,
                                      LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_itemCursor * LEFT_PANEL_HEIGHT));
                }
            }
            else
            {
                if (!m_bEnglish)
                {
                    m_font->DrawText_("装備を外す　　　捨てる",
                                      MIDDLE_PANEL_STARTX,
                                      LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_itemCursor * LEFT_PANEL_HEIGHT));
                }
                else
                {
                    m_font->DrawText_("Unequip         Discard",
                                      MIDDLE_PANEL_STARTX,
                                      LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_itemCursor * LEFT_PANEL_HEIGHT));
                }
            }
        }
    }

    // Show weapon sub
    if (m_eFocus == eFocus::WEAPON_SUB)
    {
        if (!m_bEnglish)
        {
            m_font->DrawText_("装備する　　　　キャンセル",
                              MIDDLE_PANEL_STARTX,
                              LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_weaponCursor * LEFT_PANEL_HEIGHT));
        }
        else
        {
            m_font->DrawText_("Equip           Cancel",
                              MIDDLE_PANEL_STARTX,
                              LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (m_weaponCursor * LEFT_PANEL_HEIGHT));
        }
    }

    // Show guide sub category
    if (m_eFocus == eFocus::GUIDE || m_eFocus == eFocus::GUIDE_SUB)
    {
        std::string category = m_guideCategory.at(m_guideSelect);
        std::vector<std::string> vs = m_guideSubCategory.at(category);

        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)vs.size() <= m_guideSubBegin + i)
            {
                break;
            }

            int trans = 255;
            if (m_eFocus == eFocus::GUIDE)
            {
                trans = 32;
            }

            m_font->DrawText_(vs.at((size_t)m_guideSubBegin+i),
                              MIDDLE_PANEL_STARTX - 250,
                              LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT),
                              false,
                              trans);
        }
    }

    if (m_eFocus == eFocus::WEAPON || m_eFocus == eFocus::WEAPON_SUB)
    {
        if (!m_weaponInfoList.empty())
        {
            int trans = 255;
            if (m_eFocus == eFocus::WEAPON_SUB)
            {
                trans = 64;
            }

            m_weaponInfoList.at(m_weaponSelect).GetSprite()->DrawImage(550, 300, trans);

            std::string detail = m_weaponInfoList.at(m_weaponSelect).GetDetail();
            std::vector<std::string> details = split(detail, '\n');

            for (std::size_t i = 0; i < details.size(); ++i)
            {
                m_font->DrawText_(
                    details.at(i),
                    1100,
                    250 + (int)i*40
                    );
            }
        }
    }

    if (m_eFocus == eFocus::GUIDE_SUB)
    {
        std::string category = m_guideCategory.at(m_guideSelect);
        std::string subCategory = m_guideSubCategory.at(category).at(m_guideSubSelect);
        std::string detail;
        for (std::size_t i = 0; i < m_guideInfoList.size(); ++i)
        {
            if (m_guideInfoList.at(i).GetCategory() == category &&
                m_guideInfoList.at(i).GetSubCategory() == subCategory)
            {
                detail = m_guideInfoList.at(i).GetDetail();
                break;
            }
        }
        std::vector<std::string> details = split(detail, '\n');

        for (std::size_t i = 0; i < details.size(); ++i)
        {
            m_font->DrawText_(details.at(i),
                              700,
                              250 + (int)i*40);
        }
    }

    if (m_eFocus == eFocus::MAP)
    {
        m_mapInfoList.at(m_mapSelect).GetSprite()->DrawImage(550, 300);

        std::string detail = m_mapInfoList.at(m_mapSelect).GetDetail();
        std::vector<std::string> details = split(detail, '\n');

        for (std::size_t i = 0; i < details.size(); ++i)
        {
            m_font->DrawText_(
                details.at(i),
                1100,
                250 + (int)i*40
                );
        }
    }

    if (m_eFocus == eFocus::HUMAN)
    {
        m_humanInfoList.at(m_humanSelect).GetSprite()->DrawImage(550, 300);

        std::string detail = m_humanInfoList.at(m_humanSelect).GetDetail();
        std::vector<std::string> details = split(detail, '\n');

        for (std::size_t i = 0; i < details.size(); ++i)
        {
            m_font->DrawText_(
                details.at(i),
                1100,
                250 + (int)i*40
                );
        }
    }

    if (m_eFocus == eFocus::ENEMY)
    {
        m_enemyInfoList.at(m_enemySelect).GetSprite()->DrawImage(550, 300);

        std::string detail = m_enemyInfoList.at(m_enemySelect).GetDetail();
        std::vector<std::string> details = split(detail, '\n');

        for (std::size_t i = 0; i < details.size(); ++i)
        {
            m_font->DrawText_(
                details.at(i),
                1100,
                250 + (int)i*40
                );
        }
    }

    if (m_eFocus == eFocus::SKILL)
    {
        m_skillInfoList.at(m_skillSelect).GetSprite()->DrawImage(550, 300);

        std::string detail = m_skillInfoList.at(m_skillSelect).GetDetail();
        std::vector<std::string> details = split(detail, '\n');

        for (std::size_t i = 0; i < details.size(); ++i)
        {
            m_font->DrawText_(
                details.at(i),
                1100,
                250 + (int)i*40
                );
        }
    }

    if (m_eFocus == eFocus::STATUS)
    {
        m_statusInfoList.at(m_statusSelect).GetSprite()->DrawImage(900, 200, 64);

        std::string detail = m_statusInfoList.at(m_statusSelect).GetDetail();
        std::vector<std::string> details = split(detail, '\n');

        for (std::size_t i = 0; i < details.size(); ++i)
        {
            m_font->DrawText_(
                details.at(i),
                500,
                250 + (int)i*40
                );
        }
    }

    // Show cursor
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex <= 6)
        {
            m_sprCursor->DrawImage(95 + TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * m_topBarIndex, TOPBAR_STARTY - 13);
        }
        else
        {
            m_sprCursor->DrawImage(95 + TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * (m_topBarIndex - 7), TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT - 13);
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        if (!m_itemInfoList.empty())
        {
            m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_itemCursor * 60));
        }
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        if (m_itemSubCursor != -1)
        {
			m_sprCursor->DrawImage(MIDDLE_PANEL_CURSORX + (m_itemSubCursor * 160),
                                   MIDDLE_PANEL_CURSORY + (m_itemCursor * 60));
        }
    }
    else if (m_eFocus == eFocus::WEAPON)
    {
        if (!m_weaponInfoList.empty())
        {
            m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_weaponCursor * 60));
        }
    }
    else if (m_eFocus == eFocus::WEAPON_SUB)
    {
        if (m_weaponSubCursor != -1)
        {
			m_sprCursor->DrawImage(MIDDLE_PANEL_CURSORX + (m_weaponSubCursor * 160),
                                   MIDDLE_PANEL_CURSORY + (m_weaponCursor * 60));
        }
    }
    else if (m_eFocus == eFocus::GUIDE)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_guideCursor * 60));
    }
    else if (m_eFocus == eFocus::GUIDE_SUB)
    {
        m_sprCursor->DrawImage(MIDDLE_PANEL_CURSORX - 250, MIDDLE_PANEL_CURSORY + (m_guideSubCursor * 60));
    }
    else if (m_eFocus == eFocus::MAP)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_mapCursor * 60));
    }
    else if (m_eFocus == eFocus::HUMAN)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_humanCursor * 60));
    }
    else if (m_eFocus == eFocus::ENEMY)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_enemyCursor * 60));
    }
    else if (m_eFocus == eFocus::SKILL)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_skillCursor * 60));
    }
    else if (m_eFocus == eFocus::STATUS)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_statusCursor * 60));
    }
    else if (m_eFocus == eFocus::QUIT)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_quitCursor * 60));
    }
    else if (m_eFocus == eFocus::OPENING)
    {
        m_sprCursor->DrawImage(LEFT_PANEL_CURSORX, LEFT_PANEL_CURSORY + (m_openingCursor * 60));
    }
}

void NSMenulib::MenuLib::AddItem(const ItemInfo& itemInfo)
{
    m_itemInfoList.push_back(itemInfo);
    std::sort(m_itemInfoList.begin(), m_itemInfoList.end(),
              [&](const ItemInfo& left, const ItemInfo& right)
              {
                  if (left.GetId() < right.GetId())
                  {
                      return true;
                  }
                  else if (left.GetId() > right.GetId())
                  {
                      return false;
                  }
                  else
                  {
                      if (left.GetSubId() < right.GetSubId())
                      {
                          return true;
                      }
                      else
                      {
                          return false;
                      }
                  }
              });
}

void NSMenulib::MenuLib::DeleteItem(const int id, const int subId)
{
    for (std::size_t i = 0; i < m_itemInfoList.size(); ++i)
    {
        if (m_itemInfoList.at(i).GetId() == id && m_itemInfoList.at(i).GetSubId() == subId)
        {
            m_itemInfoList.erase(m_itemInfoList.begin() + i);
            break;
        }
    }

    // 一番最後の要素を削除した場合、カーソルが何もない場所を選択してしまう。
    // 選択中を表すインデックスを一つ小さくする。
    if ((int)m_itemInfoList.size() <= m_itemSelect)
    {
        m_itemSelect = (int)m_itemInfoList.size() - 1;

        // アイテムの数が9個以下ならカーソルの位置は、一つ上に移動する。
        if (m_itemInfoList.size() <= 9)
        {
            --m_itemCursor;
        }
        // アイテムの数が10個以上ならカーソルの位置はそのまま、全体が下に移動する。
        else
        {
            --m_itemBegin;
        }
    }

    // 武器だったら武器リストからも削除
    for (auto it = m_weaponInfoList.begin(); it != m_weaponInfoList.end(); ++it)
    {
        if (it->GetId() == id && it->GetSubId() == subId)
        {
            m_weaponInfoList.erase(it);
            break;
        }
    }
}

void NSMenulib::MenuLib::UpdateItem(const ItemInfo& itemInfo)
{
    for (std::size_t i = 0; i < m_itemInfoList.size(); ++i)
    {
        if (m_itemInfoList.at(i).GetId() == itemInfo.GetId() &&
            m_itemInfoList.at(i).GetSubId() == itemInfo.GetSubId())
        {
            m_itemInfoList.at(i).SetDurability(itemInfo.GetDurability());
            m_itemInfoList.at(i).SetLevel(itemInfo.GetLevel());
            m_itemInfoList.at(i).SetEquip(itemInfo.GetEquip());
            break;
        }
    }
}

void NSMenulib::MenuLib::UpdateStatusText(const std::string& text)
{
    m_statusInfoList.at(0).SetDetail(text);
}

std::string NSMenulib::MenuLib::ToStringWithPrecision(const float value, const int precision)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

void NSMenulib::MenuLib::SetWeightAll(const float arg)
{
    m_weightAll = arg;
}

void NSMenulib::MenuLib::SetVolumeAll(const int arg)
{
    m_volumeAll = arg;
}

void NSMenulib::MenuLib::SetVolumeMax(const int arg)
{
    m_volumeMax = arg;
}

