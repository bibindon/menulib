#include "MenuLib.h"
#include <sstream>

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
    ISprite* sprPanel,
    ISprite* sprPanelLeft)
{
    m_font = font;
    m_SE = SE;
    m_sprCursor = sprCursor;
    m_sprBackground = sprBackground;
    m_sprPanel = sprPanel;
    m_sprPanelLeft = sprPanelLeft;

    m_TopBarName.push_back("アイテム");
    m_TopBarName.push_back("武器・防具");
    m_TopBarName.push_back("タスク");
    m_TopBarName.push_back("マップ");
    m_TopBarName.push_back("人物情報");
    m_TopBarName.push_back("敵情報");
    m_TopBarName.push_back("技・魔法");
    m_TopBarName.push_back("ステータス");
    m_TopBarName.push_back("タイトル");
    m_TopBarName.push_back("最初から");
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

void MenuLib::SetTask(const std::vector<TaskInfo>& items)
{
    m_taskInfoList = items;
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
    else if (m_eFocus == eFocus::TASK)
    {
        if (m_taskSelect >= 1)
        {
            m_taskSelect--;
            if (m_taskCursor >= 1)
            {
                m_taskCursor--;
            }
            else if (m_taskCursor == 0)
            {
                m_taskBegin--;
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
    else if (m_eFocus == eFocus::TASK)
    {
        // スクロール可能なためカーソルの位置と選択アイテムは異なる
        if (m_taskSelect <= (int)m_taskInfoList.size() - 2)
        {
            m_taskSelect++;
            // 10行まで表示可能なので現在行が8ならカーソルを下に移動可能
            if (m_taskCursor <= LEFT_PANEL_ROW_MAX-2)
            {
                m_taskCursor++;
            }
            else if (m_taskCursor == LEFT_PANEL_ROW_MAX-1)
            {
                m_taskBegin++;
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
        else if (m_topBarIndex == TOPBAR_TASK)
        {
            m_eFocus = eFocus::TASK;
            m_taskCursor = 0;
            m_taskBegin = 0;
            m_taskSelect = 0;
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
        else if (m_topBarIndex == TOPBAR_TITLE)
        {
            result = m_TopBarName.at(m_topBarIndex);
            m_topBarIndex = 0;
        }
        else if (m_topBarIndex == TOPBAR_OPENING)
        {
            result = m_TopBarName.at(m_topBarIndex);
            m_topBarIndex = 0;
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        m_eFocus = eFocus::ITEM_SUB;
        m_itemSubCursor = 0;
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        result = m_TopBarName.at(m_topBarIndex);
        result += ":" + m_itemInfoList.at(m_itemSelect).GetName();
        if (m_itemSubCursor == 0)
        {
            result += ":使う";
        }
        else
        {
            result += ":捨てる";
        }
    }
    return result;
}

std::string MenuLib::Back()
{
    std::string result;
    if (m_eFocus == eFocus::ITEM)
    {
        m_eFocus = eFocus::TOP_BAR;
        m_SE->PlayBack();
        result = m_TopBarName.at(m_topBarIndex);
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        m_eFocus = eFocus::ITEM;
        m_SE->PlayBack();
        result = m_TopBarName.at(m_topBarIndex);
        result += ":" + m_itemInfoList.at(m_itemSelect).GetName();
    }
    // TOP_BARにフォーカスがあるときに戻ろうとした。
    // つまりメニュー画面を閉じようとした。
    else if (m_eFocus == eFocus::TOP_BAR)
    {
        result = "EXIT";
    }
    else
    {
        m_eFocus = eFocus::TOP_BAR;
        m_SE->PlayBack();
        result = m_TopBarName.at(m_topBarIndex);
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

void MenuLib::Click(const int x, const int y)
{
    m_SE->PlayClick();
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
            m_eFocus = eFocus::TASK;
            m_topBarIndex = TOPBAR_TASK;
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
            m_eFocus = eFocus::TITLE;
            m_topBarIndex = TOPBAR_TITLE;
        }
        else if (TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 2 < x && x <= TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * 3)
        {
            m_eFocus = eFocus::OPENING;
            m_topBarIndex = TOPBAR_OPENING;
        }
    }
    else
    {
        if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
        {
            if (LEFT_PANEL_STARTY < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 1)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 0;
                    m_itemSelect = m_itemBegin;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 0;
                    m_weaponSelect = m_weaponBegin;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 1 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 2)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 1;
                    m_itemSelect = m_itemBegin + 1;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 1;
                    m_weaponSelect = m_weaponBegin + 1;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 2 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 3)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 2;
                    m_itemSelect = m_itemBegin + 2;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 2;
                    m_weaponSelect = m_weaponBegin + 2;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 3 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 4)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 3;
                    m_itemSelect = m_itemBegin + 3;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 3;
                    m_weaponSelect = m_weaponBegin + 3;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 4 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 5)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 4;
                    m_itemSelect = m_itemBegin + 4;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 4;
                    m_weaponSelect = m_weaponBegin + 4;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 5 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 6)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 5;
                    m_itemSelect = m_itemBegin + 5;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 5;
                    m_weaponSelect = m_weaponBegin + 5;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 6 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 7)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 6;
                    m_itemSelect = m_itemBegin + 6;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 6;
                    m_weaponSelect = m_weaponBegin + 6;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 7 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 8)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 7;
                    m_itemSelect = m_itemBegin + 7;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 7;
                    m_weaponSelect = m_weaponBegin + 7;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 8 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 9)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 8;
                    m_itemSelect = m_itemBegin + 8;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 8;
                    m_weaponSelect = m_weaponBegin + 8;
                }
            }
            else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 9 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 10)
            {
                if (m_topBarIndex == TOPBAR_ITEM)
                {
                    m_eFocus = eFocus::ITEM;
                    m_itemCursor = 9;
                    m_itemSelect = m_itemBegin + 9;
                }
                else if (m_topBarIndex == TOPBAR_WEAPON)
                {
                    m_eFocus = eFocus::WEAPON;
                    m_weaponCursor = 9;
                    m_weaponSelect = m_weaponBegin + 9;
                }
            }
        }
    }
}

void MenuLib::RightClick(const int x, const int y)
{
    m_SE->PlayClick();
    if (LEFT_PANEL_STARTX < x && x <= LEFT_PANEL_STARTX + LEFT_PANEL_WIDTH)
    {
        if (LEFT_PANEL_STARTY < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 1)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 0;
                m_itemSelect = m_itemBegin;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 1 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 2)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 1;
                m_itemSelect = m_itemBegin + 1;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 2 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 3)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 2;
                m_itemSelect = m_itemBegin + 2;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 3 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 4)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 3;
                m_itemSelect = m_itemBegin + 3;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 4 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 5)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 4;
                m_itemSelect = m_itemBegin + 4;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 5 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 6)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 5;
                m_itemSelect = m_itemBegin + 5;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 6 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 7)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 6;
                m_itemSelect = m_itemBegin + 6;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 7 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 8)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 7;
                m_itemSelect = m_itemBegin + 7;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 8 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 9)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 8;
                m_itemSelect = m_itemBegin + 8;
            }
        }
        else if (LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 9 < y && y <= LEFT_PANEL_STARTY + LEFT_PANEL_HEIGHT * 10)
        {
            if (m_topBarIndex == TOPBAR_ITEM)
            {
                m_eFocus = eFocus::ITEM_SUB;
                m_itemCursor = 9;
                m_itemSelect = m_itemBegin + 9;
            }
        }
    }
}

void MenuLib::Draw()
{
    m_sprBackground->DrawImage(0, 0);

    for (int i = 0; i < TOPBAR_COL_MAX; ++i)
    {
        m_sprPanel->DrawImage(TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * i), TOPBAR_STARTY);
    }
    for (int i = 0; i < TOPBAR_COL_MAX; ++i)
    {
        m_sprPanel->DrawImage(TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * i), TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT);
    }
 
    m_font->DrawText_("アイテム", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 0) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY);
    m_font->DrawText_("武器・防具", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 1) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY);
    m_font->DrawText_("タスク", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 2) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY);
    m_font->DrawText_("マップ", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 3) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY);
    m_font->DrawText_("人物情報", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 4) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY);
    m_font->DrawText_("敵情報", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 5) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY);
    m_font->DrawText_("技・魔法", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 6) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PADDINGY);
    m_font->DrawText_("ステータス", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 0) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY);
    m_font->DrawText_("タイトル", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 1) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY);
    m_font->DrawText_("最初から", TOPBAR_STARTX + (TOPBAR_PANEL_WIDTH * 2) + TOPBAR_PADDINGX, TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT + TOPBAR_PADDINGY);

    // Show left bar
    if (m_topBarIndex == TOPBAR_ITEM)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_itemInfoList.size() <= m_itemBegin + i)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(LEFT_PANEL_STARTX, LEFT_PANEL_STARTY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_itemInfoList.at(m_itemBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                std::to_string(m_itemInfoList.at(m_itemBegin+i).GetNum()),
                445 + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_topBarIndex == TOPBAR_WEAPON)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_weaponInfoList.size() <= m_weaponBegin + i)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(LEFT_PANEL_STARTX, LEFT_PANEL_STARTY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_weaponInfoList.at(m_weaponBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_topBarIndex == TOPBAR_TASK)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_taskInfoList.size() <= m_taskBegin + i)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(LEFT_PANEL_STARTX, LEFT_PANEL_STARTY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_taskInfoList.at(m_taskBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_topBarIndex == TOPBAR_MAP)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_mapInfoList.size() <= m_mapBegin + i)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(LEFT_PANEL_STARTX, LEFT_PANEL_STARTY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_mapInfoList.at(m_mapBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_topBarIndex == TOPBAR_HUMAN)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_humanInfoList.size() <= m_humanBegin + i)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(LEFT_PANEL_STARTX, LEFT_PANEL_STARTY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_humanInfoList.at(m_humanBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_topBarIndex == TOPBAR_ENEMY)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_enemyInfoList.size() <= m_enemyBegin + i)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(LEFT_PANEL_STARTX, LEFT_PANEL_STARTY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_enemyInfoList.at(m_enemyBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }
    else if (m_topBarIndex == TOPBAR_SKILL)
    {
        for (int i = 0; i < LEFT_PANEL_ROW_MAX; ++i)
        {
            if ((int)m_skillInfoList.size() <= m_skillBegin + i)
            {
                break;
            }
            m_sprPanelLeft->DrawImage(LEFT_PANEL_STARTX, LEFT_PANEL_STARTY + (i*LEFT_PANEL_HEIGHT));
            m_font->DrawText_(
                m_skillInfoList.at(m_skillBegin+i).GetName(),
                LEFT_PANEL_STARTX + LEFT_PANEL_PADDINGX,
                LEFT_PANEL_STARTY + LEFT_PANEL_PADDINGY + (i*LEFT_PANEL_HEIGHT));
        }
    }

    // Show item detail
    if (m_eFocus == eFocus::ITEM || m_eFocus == eFocus::ITEM_SUB)
    {
        m_itemInfoList.at(m_itemSelect).GetSprite()->DrawImage(550, 300);

        std::string detail = m_itemInfoList.at(m_itemSelect).GetDetail();
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
    // Show item sub
    if (m_eFocus == eFocus::ITEM_SUB)
    {
        m_sprPanelLeft->DrawImage(550, 200 + (m_itemCursor*LEFT_PANEL_HEIGHT));
        m_font->DrawText_(
            "使う　　　　　捨てる",
            650,
            200 + LEFT_PANEL_PADDINGY + (m_itemCursor * LEFT_PANEL_HEIGHT)
        );
    }
    if (m_eFocus == eFocus::WEAPON)
    {
        m_weaponInfoList.at(m_weaponSelect).GetSprite()->DrawImage(550, 300);

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
    if (m_eFocus == eFocus::TASK)
    {
        m_taskInfoList.at(m_taskSelect).GetSprite()->DrawImage(550, 300);

        std::string detail = m_taskInfoList.at(m_taskSelect).GetDetail();
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

    // Show cursor
    if (m_eFocus == eFocus::TOP_BAR)
    {
        if (m_topBarIndex <= 6)
        {
            m_sprCursor->DrawImage(-30 + TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * m_topBarIndex, TOPBAR_STARTY);
        }
        else
        {
            m_sprCursor->DrawImage(-30 + TOPBAR_STARTX + TOPBAR_PANEL_WIDTH * (m_topBarIndex - 7), TOPBAR_STARTY + TOPBAR_PANEL_HEIGHT);
        }
    }
    else if (m_eFocus == eFocus::ITEM)
    {
        m_sprCursor->DrawImage(80, 205 + (m_itemCursor * 60));
    }
    else if (m_eFocus == eFocus::ITEM_SUB)
    {
        m_sprCursor->DrawImage(570 + (m_itemSubCursor * 160), 205 + (m_itemCursor * 60));
    }
    else if (m_eFocus == eFocus::WEAPON)
    {
        m_sprCursor->DrawImage(80, 205 + (m_weaponCursor * 60));
    }
    else if (m_eFocus == eFocus::TASK)
    {
        m_sprCursor->DrawImage(80, 205 + (m_taskCursor * 60));
    }
    else if (m_eFocus == eFocus::MAP)
    {
        m_sprCursor->DrawImage(80, 205 + (m_mapCursor * 60));
    }
    else if (m_eFocus == eFocus::HUMAN)
    {
        m_sprCursor->DrawImage(80, 205 + (m_humanCursor * 60));
    }
    else if (m_eFocus == eFocus::ENEMY)
    {
        m_sprCursor->DrawImage(80, 205 + (m_enemyCursor * 60));
    }
    else if (m_eFocus == eFocus::SKILL)
    {
        m_sprCursor->DrawImage(80, 205 + (m_skillCursor * 60));
    }
}

