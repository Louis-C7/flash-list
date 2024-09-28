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

#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "CellNode.h"

namespace rnoh {
class CellContainerComponentInstance : public CppComponentInstance<facebook::react::CellContainerShadowNode> {
private:
    CellNode m_cellNode;
    int m_index{-1};

public:
    using Shared = std::shared_ptr<CellContainerComponentInstance>;
    CellContainerComponentInstance(Context context);
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
    CellNode &getLocalRootArkUINode() override;
    void onPropsChanged(SharedConcreteProps const &props) override;

    void setIndex(int const &);
    int getIndex();

    void setLeft(facebook::react::Float const &);
    facebook::react::Float getLeft();
    void setTop(facebook::react::Float const &);
    facebook::react::Float getTop();
    void setRight(facebook::react::Float const &);
    facebook::react::Float getRight();
    void setBottom(facebook::react::Float const &);
    facebook::react::Float getBottom();
    void setHeight(facebook::react::Float const &);
    facebook::react::Float getHeight();
    void setWidth(facebook::react::Float const &);
    facebook::react::Float getWidth();
};
} // namespace rnoh