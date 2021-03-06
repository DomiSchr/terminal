/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- renderData.hpp

Abstract:
- This method provides an interface for rendering the final display based on the current console state

Author(s):
- Michael Niksa (miniksa) Nov 2015
--*/

#pragma once

#include "..\renderer\inc\IRenderData.hpp"

class RenderData final : public Microsoft::Console::Render::IRenderData
{
public:
    Microsoft::Console::Types::Viewport GetViewport() noexcept override;
    const TextBuffer& GetTextBuffer() noexcept override;
    const FontInfo& GetFontInfo() noexcept override;
    const TextAttribute GetDefaultBrushColors() noexcept override;

    const COLORREF GetForegroundColor(const TextAttribute& attr) const noexcept override;
    const COLORREF GetBackgroundColor(const TextAttribute& attr) const noexcept override;

    COORD GetCursorPosition() const noexcept override;
    bool IsCursorVisible() const noexcept override;
    bool IsCursorOn() const noexcept override;
    ULONG GetCursorHeight() const noexcept override;
    CursorType GetCursorStyle() const noexcept override;
    ULONG GetCursorPixelWidth() const noexcept override;
    COLORREF GetCursorColor() const noexcept override;
    bool IsCursorDoubleWidth() const noexcept override;

    const std::vector<Microsoft::Console::Render::RenderOverlay> GetOverlays() const noexcept override;

    const bool IsGridLineDrawingAllowed() noexcept override;

    std::vector<Microsoft::Console::Types::Viewport> GetSelectionRects() noexcept override;
    bool IsAreaSelected() const override;
    void ClearSelection() override;
    void SelectNewRegion(const COORD coordStart, const COORD coordEnd) override;

    // TODO GitHub #605: Search functionality
    // For now, just adding it here to make UiaTextRange easier to create (Accessibility)
    // We should actually abstract this out better once Windows Terminal has Search
    HRESULT SearchForText(_In_ BSTR text,
                          _In_ BOOL searchBackward,
                          _In_ BOOL ignoreCase,
                          _Outptr_result_maybenull_ ITextRangeProvider** ppRetVal,
                          unsigned int _start,
                          unsigned int _end,
                          std::function<unsigned int(IRenderData*, const COORD)> _coordToEndpoint,
                          std::function<COORD(IRenderData*, const unsigned int)> _endpointToCoord,
                          std::function<IFACEMETHODIMP(ITextRangeProvider**)> Clone);

    const std::wstring GetConsoleTitle() const noexcept override;

    void LockConsole() noexcept override;
    void UnlockConsole() noexcept override;
};
