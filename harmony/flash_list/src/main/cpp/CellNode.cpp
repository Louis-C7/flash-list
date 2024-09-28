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

#include "CellNode.h"
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {
CellNode::CellNode() : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_CUSTOM)) {
    userCallback_ = new CellNodeCallback();
    userCallback_->callback = [this](ArkUI_NodeCustomEvent *event) {
        auto type = OH_ArkUI_NodeCustomEvent_GetEventType(event);
        switch (type) {
        case ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE:
            onMeasure();
            break;
        case ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT:
            onLayout();
        default:
            break;
        }
    };
    eventReceiver = [](ArkUI_NodeCustomEvent *event) {
        auto *userData = reinterpret_cast<CellNodeCallback *>(OH_ArkUI_NodeCustomEvent_GetUserData(event));
        int32_t tagId = OH_ArkUI_NodeCustomEvent_GetEventTargetId(event);
        if (userData && (tagId == 44 || tagId == 45)) {
            userData->callback(event);
        }
    };
    maybeThrow(NativeNodeApi::getInstance()->addNodeCustomEventReceiver(m_nodeHandle, eventReceiver));
    maybeThrow(NativeNodeApi::getInstance()->registerNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE,
                                                                     44, userCallback_));
    maybeThrow(NativeNodeApi::getInstance()->registerNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT,
                                                                     45, userCallback_));
}

void CellNode::onMeasure() {
    int32_t width = getSavedWidth();
    int32_t height = getSavedHeight();
    maybeThrow(NativeNodeApi::getInstance()->setMeasuredSize(m_nodeHandle, width, height));
}

void CellNode::onLayout() {
    int32_t x = getSavedX();
    int32_t y = getSavedY();
    maybeThrow(NativeNodeApi::getInstance()->setLayoutPosition(m_nodeHandle, x, y));
}

void CellNode::insertChild(ArkUINode &child, std::size_t index) {
    maybeThrow(NativeNodeApi::getInstance()->insertChildAt(m_nodeHandle, child.getArkUINodeHandle(),
                                                           static_cast<int32_t>(index)));
}

void CellNode::addChild(ArkUINode &child) {
    maybeThrow(NativeNodeApi::getInstance()->addChild(m_nodeHandle, child.getArkUINodeHandle()));
}

void CellNode::removeChild(ArkUINode &child) {
    maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
}

CellNode::~CellNode() {
    NativeNodeApi::getInstance()->unregisterNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
    NativeNodeApi::getInstance()->unregisterNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT);
    NativeNodeApi::getInstance()->removeNodeCustomEventReceiver(m_nodeHandle, eventReceiver);
    delete userCallback_;
}

void CellNode::savePosition(int32_t x, int32_t y) {
    m_x = x;
    m_y = y;
}

ArkUINode &CellNode::setLayoutRect(facebook::react::Point const &position, facebook::react::Size const &size,
                                   facebook::react::Float pointScaleFactor) {
    ArkUI_NumberValue value[] = {{.i32 = static_cast<int32_t>(position.x * pointScaleFactor + 0.5)},
                                 {.i32 = static_cast<int32_t>(position.y * pointScaleFactor + 0.5)},
                                 {.i32 = static_cast<int32_t>(size.width * pointScaleFactor + 0.5)},
                                 {.i32 = static_cast<int32_t>(size.height * pointScaleFactor + 0.5)}};
    savePosition(value[0].i32, value[1].i32);
    saveSize(value[2].i32, value[3].i32);
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_LAYOUT_RECT, &item));
    return *this;
}

void CellNode::saveLayoutRect(facebook::react::Point const &position, facebook::react::Size const &size,
                              facebook::react::Float pointScaleFactor) {
    ArkUI_NumberValue value[] = {{.i32 = static_cast<int32_t>(position.x * pointScaleFactor + 0.5)},
                                 {.i32 = static_cast<int32_t>(position.y * pointScaleFactor + 0.5)},
                                 {.i32 = static_cast<int32_t>(size.width * pointScaleFactor + 0.5)},
                                 {.i32 = static_cast<int32_t>(size.height * pointScaleFactor + 0.5)}};
    savePosition(value[0].i32, value[1].i32);
    saveSize(value[2].i32, value[3].i32);
}

} // namespace rnoh
