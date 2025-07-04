﻿#pragma comment( lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib")
#else
#pragma comment( lib, "d3dx9.lib")
#endif

#pragma comment (lib, "winmm.lib")

#pragma comment( lib, "menulib.lib")

#include "..\menulib\MenuLib.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <sstream>
#include <tchar.h>

using namespace NSMenulib;

#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = NULL; } }

static std::vector<std::wstring> split(const std::wstring& s, wchar_t delim)
{
    std::vector<std::wstring> result;
    std::wstringstream ss(s);
    std::wstring item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}


class Sprite : public ISprite
{
public:

    Sprite(LPDIRECT3DDEVICE9 dev)
        : m_pD3DDevice(dev)
    {
    }

    void DrawImage(const int x, const int y, const int transparency) override
    {
        D3DXVECTOR3 pos {(float)x, (float)y, 0.f};
        m_D3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
        RECT rect = {
            0,
            0,
            static_cast<LONG>(m_width),
            static_cast<LONG>(m_height) };
        D3DXVECTOR3 center { 0, 0, 0 };
        m_D3DSprite->Draw(
            m_pD3DTexture,
            &rect,
            &center,
            &pos,
            D3DCOLOR_ARGB(transparency, 255, 255, 255));
        m_D3DSprite->End();

    }

    void Load(const std::wstring& filepath) override
    {
        LPD3DXSPRITE tempSprite { nullptr };
        if (FAILED(D3DXCreateSprite(m_pD3DDevice, &m_D3DSprite)))
        {
            throw std::exception("Failed to create a sprite.");
        }

        if (FAILED(D3DXCreateTextureFromFile(
            m_pD3DDevice,
            filepath.c_str(),
            &m_pD3DTexture)))
        {
            throw std::exception("Failed to create a texture.");
        }

        D3DSURFACE_DESC desc { };
        if (FAILED(m_pD3DTexture->GetLevelDesc(0, &desc)))
        {
            throw std::exception("Failed to create a texture.");
        }
        m_width = desc.Width;
        m_height = desc.Height;
    }

    ~Sprite()
    {
        m_D3DSprite->Release();
        m_pD3DTexture->Release();
    }

private:

    LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;
    LPD3DXSPRITE m_D3DSprite = NULL;
    LPDIRECT3DTEXTURE9 m_pD3DTexture = NULL;
    UINT m_width { 0 };
    UINT m_height { 0 };
};

class Font : public IFont
{
public:

    Font(LPDIRECT3DDEVICE9 pD3DDevice)
        : m_pD3DDevice(pD3DDevice)
    {
    }

    void Init(const bool bEnglish)
    {
        if (!bEnglish)
        {
            HRESULT hr = D3DXCreateFont(m_pD3DDevice,
                                        20,
                                        0,
                                        FW_NORMAL,
                                        1,
                                        false,
                                        SHIFTJIS_CHARSET,
                                        OUT_TT_ONLY_PRECIS,
                                        ANTIALIASED_QUALITY,
                                        FF_DONTCARE,
                                        _T("ＭＳ 明朝"),
                                        &m_pFont);
        }
        else
        {
            HRESULT hr = D3DXCreateFont(m_pD3DDevice,
                                        20,
                                        0,
                                        FW_NORMAL,
                                        1,
                                        false,
                                        DEFAULT_CHARSET,
                                        OUT_TT_ONLY_PRECIS,
                                        CLEARTYPE_NATURAL_QUALITY,
                                        FF_DONTCARE,
                                        _T("Courier New"),
                                        &m_pFont);
        }
    }

    virtual void DrawText_(const std::wstring& msg, const int x, const int y, const bool hcenter, const int transparency)
    {
        if (hcenter)
        {
            RECT rect = { x, y, x + 100, y + 20 };
            m_pFont->DrawText(NULL, msg.c_str(),
                              -1,
                              &rect,
                              DT_VCENTER | DT_CENTER | DT_NOCLIP,
                              D3DCOLOR_ARGB(transparency, 255, 255, 255));
        }
        else
        {
            RECT rect = { x, y, x + 200, y + 20 };
            m_pFont->DrawText(NULL, msg.c_str(),
                              -1,
                              &rect,
                              DT_VCENTER | DT_NOCLIP,
                              D3DCOLOR_ARGB(transparency, 255, 255, 255));
        }
    }

    ~Font()
    {
        m_pFont->Release();
    }

private:

    LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;
    LPD3DXFONT m_pFont = NULL;
};


class SoundEffect : public ISoundEffect
{
    virtual void PlayMove() override
    {
        PlaySound(_T("cursor_move.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    virtual void PlayClick() override
    {
        PlaySound(_T("cursor_confirm.wav"), NULL, SND_FILENAME | SND_ASYNC);
//        PlaySound(_T("cursor_move.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    virtual void PlayBack() override
    {
        PlaySound(_T("cursor_cancel.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    virtual void Init() override
    {

    }
};

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LPD3DXFONT g_pFont = NULL;
LPD3DXMESH pMesh = NULL;
D3DMATERIAL9* pMaterials = NULL;
LPDIRECT3DTEXTURE9* pTextures = NULL;
DWORD dwNumMaterials = 0;
LPD3DXEFFECT pEffect = NULL;
D3DXMATERIAL* d3dxMaterials = NULL;
float f = 0.0f;
bool bShowMenu = true;

MenuLib menu;

void TextDraw(LPD3DXFONT pFont, wchar_t* text, int X, int Y)
{
    RECT rect = { X,Y,0,0 };
    pFont->DrawText(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
}

HRESULT InitD3D(HWND hWnd)
{
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
    {
        return E_FAIL;
    }

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.BackBufferCount = 1;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.Flags = 0;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
    {
        if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
        {
            return(E_FAIL);
        }
    }

    HRESULT hr = D3DXCreateFont(
        g_pd3dDevice,
        20,
        0,
        FW_HEAVY,
        1,
        false,
        SHIFTJIS_CHARSET,
        OUT_TT_ONLY_PRECIS,
        ANTIALIASED_QUALITY,
        FF_DONTCARE,
        _T("ＭＳ ゴシック"),
        &g_pFont);
    if FAILED(hr)
    {
        return(E_FAIL);
    }

    LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

    if (FAILED(D3DXLoadMeshFromX(_T("cube.x"),
                                 D3DXMESH_SYSTEMMEM,
                                 g_pd3dDevice,
                                 NULL,
                                 &pD3DXMtrlBuffer,
                                 NULL,
                                 &dwNumMaterials,
                                 &pMesh)))
    {
        MessageBox(NULL, _T("Xファイルの読み込みに失敗しました"), NULL, MB_OK);
        return E_FAIL;
    }
    d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    pMaterials = new D3DMATERIAL9[dwNumMaterials];
    pTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];

    for (DWORD i = 0; i < dwNumMaterials; i++)
    {
        pMaterials[i] = d3dxMaterials[i].MatD3D;
        pMaterials[i].Ambient = pMaterials[i].Diffuse;
        pTextures[i] = NULL;

        int len = MultiByteToWideChar(CP_ACP, 0, d3dxMaterials[i].pTextureFilename, -1, NULL, 0);
        std::wstring texFilename(len, 0);
        MultiByteToWideChar(CP_ACP, 0, d3dxMaterials[i].pTextureFilename, -1, &texFilename[0], len);

        if (!texFilename.empty())
        {
            if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice,
                                                 texFilename.c_str(),
                                                 &pTextures[i])))
            {
                MessageBox(NULL, _T("テクスチャの読み込みに失敗しました"), NULL, MB_OK);
            }
        }
    }
    pD3DXMtrlBuffer->Release();

    D3DXCreateEffectFromFile(
        g_pd3dDevice,
        _T("simple.fx"),
        NULL,
        NULL,
        D3DXSHADER_DEBUG,
        NULL,
        &pEffect,
        NULL
    );

    Sprite* sprCursor = new Sprite(g_pd3dDevice);
    sprCursor->Load(_T("cursor.png"));

    Sprite* sprBackground = new Sprite(g_pd3dDevice);
    sprBackground->Load(_T("background.png"));

    Sprite* sprPanel = new Sprite(g_pd3dDevice);
    sprPanel->Load(_T("panel.png"));

    Sprite* sprPanelLeft = new Sprite(g_pd3dDevice);
    sprPanelLeft->Load(_T("panelLeft.png"));

    IFont* pFont = new Font(g_pd3dDevice);

    ISoundEffect* pSE = new SoundEffect();

    const bool bEnglish = true;
    menu.Init(_T(""), pFont, pSE, sprCursor, sprBackground, bEnglish);
    std::vector<ItemInfo> itemInfoList;
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(1);
        itemInfo.SetLevel(3);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("袋"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetLevel(2);
        itemInfo.SetEquipEnable(true);
        itemInfo.SetEquip(false);
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(2);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("袋"));
        itemInfo.SetDurability(300);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetEquipEnable(true);
        itemInfo.SetEquip(true);
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(3);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetWeight(12.34f);
        itemInfo.SetVolume(5678);
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(4);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム２"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetWeight(2222.f);
        itemInfo.SetVolume(3333);
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(5);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム３"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(6);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(7);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム２"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(8);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム３"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(9);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(10);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム２"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(11);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム３"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(12);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(13);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム２"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(14);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム３"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(15);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(16);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム２"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(17);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム３"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(18);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(19);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム２"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(20);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム３"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(21);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テストアイテム１"));
        itemInfo.SetDurability(10);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item1.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"1");
        itemInfo.SetSubId(22);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テスト武器１"));
        itemInfo.SetDurability(20);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＡＡＡテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"weapon1");
        itemInfo.SetSubId(2);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テスト武器１"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item2.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"weapon1");
        itemInfo.SetSubId(3);
        itemInfoList.push_back(itemInfo);
    }
    {
        ItemInfo itemInfo;
        itemInfo.SetName(_T("テスト武器２"));
        itemInfo.SetDurability(30);
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("item3.png"));
        itemInfo.SetSprite(sprItem);
        itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
        itemInfo.SetId(L"weapon2");
        itemInfo.SetSubId(3);
        itemInfoList.push_back(itemInfo);
    }
    menu.SetItem(itemInfoList);
    menu.SetWeightAll(33.33f);
    menu.SetVolumeAll(1234);
    menu.SetVolumeMax(12345);
    std::vector<HumanInfo> humanInfoList;
    {
        HumanInfo humanInfo;
        humanInfo.SetName(_T("テスト人物１"));
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("human1.png"));
        humanInfo.SetSprite(sprItem);
        humanInfo.SetDetail(_T("テスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト"));
        humanInfoList.push_back(humanInfo);
    }
    {
        HumanInfo humanInfo;
        humanInfo.SetName(_T("テスト人物２"));
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("human2.png"));
        humanInfo.SetSprite(sprItem);
        humanInfo.SetDetail(_T("テスト人物２\n　\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト"));
        humanInfoList.push_back(humanInfo);
    }
    {
        HumanInfo humanInfo;
        humanInfo.SetName(_T("テスト人物３"));
        Sprite* sprItem = new Sprite(g_pd3dDevice);
        sprItem->Load(_T("human3.png"));
        humanInfo.SetSprite(sprItem);
        humanInfo.SetDetail(_T("テスト人物３\n　\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト"));
        humanInfoList.push_back(humanInfo);
    }
    menu.SetHuman(humanInfoList);

    {
        std::vector<WeaponInfo> infoList;
        {
            WeaponInfo info;
            info.SetId(L"weapon1");
            info.SetSubId(2);
            info.SetName(_T("テスト武器１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDurability(10);
            info.SetDetail(_T("テスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト"));
            infoList.push_back(info);
        }
        {
            WeaponInfo info;
            info.SetId(L"weapon1");
            info.SetSubId(3);
            info.SetName(_T("テスト武器１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDurability(20);
            info.SetDetail(_T("テスト人物２\n　\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト"));
            infoList.push_back(info);
        }
        {
            WeaponInfo info;
            info.SetId(L"weapon2");
            info.SetSubId(3);
            info.SetName(_T("テスト武器２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDurability(30);
            info.SetDetail(_T("テスト人物３\n　\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト\nテスト人物テキスト"));
            infoList.push_back(info);
        }
        menu.SetWeapon(infoList);
    }

    {
        std::vector<GuideInfo> infoList;
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１"));
            info.SetSubCategory(_T("小カテゴリ２"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１"));
            info.SetSubCategory(_T("小カテゴリ３"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ２"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ３"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ４"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ２"));
            info.SetSubCategory(_T("小カテゴリ５"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ３"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ４"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ５"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ６"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ７"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ８"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ９"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１０"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１１"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ１"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ2"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ3"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ4"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ5"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ6"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ7"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ8"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ9"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ10"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ11"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            GuideInfo info;
            info.SetCategory(_T("大カテゴリ１２"));
            info.SetSubCategory(_T("小カテゴリ12"));
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト"));
            infoList.push_back(info);
        }
        menu.SetGuide(infoList);
    }
    {
        std::vector<EnemyInfo> infoList;
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト３"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト３"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            EnemyInfo info;
            info.SetName(_T("サンプルテキスト３"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        menu.SetEnemy(infoList);
    }
    {
        std::vector<SkillInfo> infoList;
        {
            SkillInfo info;
            info.SetName(_T("サンプルテキスト１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            SkillInfo info;
            info.SetName(_T("サンプルテキスト２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            SkillInfo info;
            info.SetName(_T("サンプルテキスト３"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        menu.SetSkill(infoList);
    }
    {
        std::vector<StatusInfo> infoList;
        {
            StatusInfo info;
            info.SetName(_T("サンプルテキスト１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            StatusInfo info;
            info.SetName(_T("サンプルテキスト２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            StatusInfo info;
            info.SetName(_T("サンプルテキスト３"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        menu.SetStatus(infoList);
    }
    {
        std::vector<MapInfo> infoList;
        {
            MapInfo info;
            info.SetName(_T("サンプルテキスト１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            MapInfo info;
            info.SetName(_T("サンプルテキスト２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            MapInfo info;
            info.SetName(_T("サンプルテキスト３"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            MapInfo info;
            info.SetName(_T("サンプルテキスト１"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            MapInfo info;
            info.SetName(_T("サンプルテキスト２"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        {
            MapInfo info;
            info.SetName(_T("サンプルテキスト３"));
            Sprite* sprItem = new Sprite(g_pd3dDevice);
            sprItem->Load(_T("test.png"));
            info.SetSprite(sprItem);
            info.SetDetail(_T("サンプルテキスト\n\nサンプルテキスト\nサンプルテキスト\nサンプルテキスト"));
            infoList.push_back(info);
        }
        menu.SetMap(infoList);
    }

    return S_OK;
}

VOID Cleanup()
{
    SAFE_RELEASE(pEffect);

    for (int i = 0; i < (int)dwNumMaterials; ++i)
    {
        pTextures[i]->Release();;
    }
    delete[] pTextures;

    delete[] pMaterials;
    SAFE_RELEASE(pMesh);
    SAFE_RELEASE(g_pFont);
    SAFE_RELEASE(g_pd3dDevice);
    SAFE_RELEASE(g_pD3D);
    menu.Finalize();
}

VOID Render()
{
    if (NULL == g_pd3dDevice)
    {
        return;
    }
    f += 0.010f;

    D3DXMATRIX mat;
    D3DXMATRIX View, Proj;
    D3DXMatrixPerspectiveFovLH(&Proj, D3DXToRadian(45), 1600.0f / 900.0f, 1.0f, 10000.0f);
    D3DXVECTOR3 vec1(3 * sinf(f), 3, -3 * cosf(f));
    D3DXVECTOR3 vec2(0, 0, 0);
    D3DXVECTOR3 vec3(0, 1, 0);
    D3DXMatrixLookAtLH(&View, &vec1, &vec2, &vec3);
    D3DXMatrixIdentity(&mat);
    mat = mat * View * Proj;
    pEffect->SetMatrix("matWorldViewProj", &mat);

    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(80, 80, 80), 1.0f, 0);

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        wchar_t msg[128];
        wcscpy_s(msg, 128, _T("Mキーでメニューを表示・非表示"));
        TextDraw(g_pFont, msg, 0, 0);

        pEffect->SetTechnique("BasicTec");
        UINT numPass;
        pEffect->Begin(&numPass, 0);
        pEffect->BeginPass(0);
        for (DWORD i = 0; i < dwNumMaterials; i++)
        {
            pEffect->SetTexture("texture1", pTextures[i]);
            pMesh->DrawSubset(i);
        }
        if (bShowMenu)
        {
            menu.Draw();
        }
        pEffect->EndPass();
        pEffect->End();
        g_pd3dDevice->EndScene();
    }

    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        Cleanup();
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        Render();
        return 0;
    case WM_SIZE:
        InvalidateRect(hWnd, NULL, true);
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case 'M':
            if (bShowMenu)
            {
                bShowMenu = false;
            }
            else
            {
                bShowMenu = true;
            }
            break;
        // メニューを表示している最中にメニューに表示されている内容を変える
        case VK_F2:
        {
            std::vector<ItemInfo> itemInfoList;
            {
                ItemInfo itemInfo;
                itemInfo.SetName(_T("テストアイテム１"));
                itemInfo.SetDurability(10);
                Sprite* sprItem = new Sprite(g_pd3dDevice);
                sprItem->Load(_T("item1.png"));
                itemInfo.SetSprite(sprItem);
                itemInfo.SetDetail(_T("テストアイテムテキスト\nテストテキストテキスト\nテストテキストテキスト\nテストテキストテストテキスト")); // TODO
                itemInfoList.push_back(itemInfo);
            }
            {
                ItemInfo itemInfo;
                itemInfo.SetName(_T("テストアイテム３"));
                itemInfo.SetDurability(30);
                Sprite* sprItem = new Sprite(g_pd3dDevice);
                sprItem->Load(_T("item3.png"));
                itemInfo.SetSprite(sprItem);
                itemInfo.SetDetail(_T("ＢＢＢテストアイテムテキスト\nテストテキストテストテキスト")); // TODO
                itemInfoList.push_back(itemInfo);
            }
            menu.SetItem(itemInfoList);
        }
        case VK_UP:
            menu.Up();
            break;
        case VK_DOWN:
            menu.Down();
            break;
        case VK_LEFT:
            menu.Left();
            break;
        case VK_RIGHT:
            menu.Right();
            break;
        case VK_RETURN:
        {
            std::wstring result = menu.Into();
            if (result == _T("タイトル"))
            {
                bShowMenu = false;
            }
            else if (result == _T("最初から"))
            {
                bShowMenu = false;
            }

            std::vector<std::wstring> vs = split(result, ':');

            if (vs.size() == 5)
            {
                if (vs.at(0) == L"Item")
                {
                    std::wstring id = vs.at(2);
                    int subId =std::stoi(vs.at(3));
                    menu.DeleteItem(id, subId);
                }
            }
            break;
        }
        case VK_BACK:
        {
            std::wstring result;
            result = menu.Back();
            if (result == _T("EXIT"))
            {
                bShowMenu = false;
            }
            break;
        }
        case VK_ESCAPE:
            Cleanup();
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_LBUTTONDOWN:
    {
        POINTS mouse_p = MAKEPOINTS(lParam);
        menu.Click(mouse_p.x, mouse_p.y);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        POINTS mouse_p = MAKEPOINTS(lParam);
        menu.RightClick();
        break;
    }
    case WM_MOUSEMOVE:
    {
        POINTS mouse_p = MAKEPOINTS(lParam);
        menu.CursorOn(mouse_p.x, mouse_p.y);
        break;
    }
    case WM_MOUSEWHEEL:
    {
        int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (zDelta <= 0)
        {
            menu.Next();
        }
        else
        {
            menu.Previous();
        }
        break;
    }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI wWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ INT)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      _T("Window1"), NULL };
    RegisterClassEx(&wc);

    RECT rect;
    SetRect(&rect, 0, 0, 1600, 900);
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    rect.right = rect.right - rect.left;
    rect.bottom = rect.bottom - rect.top;
    rect.top = 0;
    rect.left = 0;

    HWND hWnd = CreateWindow(_T("Window1"),
                             _T("Hello DirectX9 World !!"),
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             rect.right,
                             rect.bottom,
                             NULL,
                             NULL,
                             wc.hInstance,
                             NULL);

    if (SUCCEEDED(InitD3D(hWnd)))
    {
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterClass(_T("Window1"), wc.hInstance);
    return 0;
}
