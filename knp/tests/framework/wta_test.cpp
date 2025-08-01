/**
 * @file wta_test.cpp
 * @brief Test for winner takes all.
 * @kaspersky_support D. Postnikov
 * @date 23.07.2025
 * @license Apache 2.0
 * @copyright © 2024 AO Kaspersky Lab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <knp/framework/model_executor.h>
#include <knp/framework/projection/wta.h>

#include <tests_common.h>


TEST(WinnerTakesAllTest, HandlersPush)
{
    knp::framework::Model model({});
    knp::framework::BackendLoader backend_loader;
    knp::framework::ModelExecutor model_executor(model, backend_loader.load(knp::testing::get_backend_path()), {});

    knp::framework::projection::add_wta_handlers(model_executor, 1, {}, {{{}, {}}});

    auto const& handlers = model_executor.get_message_handlers();

    ASSERT_EQ(handlers.size(), 1);
}
