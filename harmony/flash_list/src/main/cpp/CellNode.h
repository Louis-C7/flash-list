/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "RNOH/arkui/ArkUINode.h"

namespace rnoh {

struct CellNodeCallback {
    std::function<void(ArkUI_NodeCustomEvent *event)> callback;
};

class CellNode : public ArkUINode {
public:
    CellNode();
    ~CellNode() override;

    void insertChild(ArkUINode &child, std::size_t index);
    void addChild(ArkUINode &child);
    void removeChild(ArkUINode &child);
    void onMeasure();
    void onLayout();
    void savePosition(int32_t x, int32_t y);
    int32_t getSavedX() { return m_x; };
    int32_t getSavedY() { return m_y; };
    ArkUINode &setLayoutRect(facebook::react::Point const &position, facebook::react::Size const &size,
                             facebook::react::Float pointScaleFactor) override;
    void saveLayoutRect(facebook::react::Point const &position, facebook::react::Size const &size,
                        facebook::react::Float pointScaleFactor);
    CellNodeCallback *userCallback_ = nullptr;
    void (*eventReceiver)(ArkUI_NodeCustomEvent *event);

private:
    int32_t m_x = 0;
    int32_t m_y = 0;
};

} // namespace rnoh