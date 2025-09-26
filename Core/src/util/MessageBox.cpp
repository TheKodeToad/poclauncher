/* Copyright 2013-2021 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "util/MessageBox.h"

QMessageBox* selectableMessageBox(QWidget* parent,
                                  const QString& title,
                                  const QString& text,
                                  QMessageBox::Icon icon,
                                  QMessageBox::StandardButtons buttons,
                                  QMessageBox::StandardButton defaultButton,
                                  QCheckBox* checkBox)
{
    QMessageBox* result = new QMessageBox(parent);
    result->setWindowTitle(title);
    result->setText(text);
    result->setStandardButtons(buttons);
    result->setDefaultButton(defaultButton);
    result->setTextInteractionFlags(Qt::TextSelectableByMouse);
    result->setIcon(icon);
    result->setTextInteractionFlags(Qt::TextBrowserInteraction);

    if (checkBox)
        result->setCheckBox(checkBox);

    return result;
}  // namespace CustomMessageBox
