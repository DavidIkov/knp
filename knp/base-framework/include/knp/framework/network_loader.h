/**
 * @file network_loader.h
 * @brief Network loader for model executor.
 * @kaspersky_support D. Postnikov
 * @date 23.03.2026
 * @license Apache 2.0
 * @copyright © 2026 AO Kaspersky Lab
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

#pragma once

#include <knp/framework/model_executor.h>
#include <knp/framework/network_description.h>
#include <knp/framework/network.h>


/**
 * @brief Framework namespace.
 */
namespace knp::framework
{
class KNP_DECLSPEC NetworkLoader
{
public:
    NetworkLoader(ModelExecutor& model_executor, const NetworkDescription& network_description);
    NetworkLoader(const NetworkLoader&) = delete;
    NetworkLoader& operator=(const NetworkLoader&) = delete;
    NetworkLoader(NetworkLoader&&) = delete;
    NetworkLoader& operator=(NetworkLoader&&) = delete;

    void run_checks();
    Network generate_network();
    void load_other_stuff();

private:
    ModelExecutor& model_executor_;
    const NetworkDescription& network_description_;
};
}  //namespace knp::framework
