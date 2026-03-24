/**
 * @file network_loader.cpp
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

#include <knp/framework/network_loader.h>

#include <spdlog/spdlog.h>


/**
 * @brief Framework namespace.
 */
namespace knp::framework
{
NetworkLoader::NetworkLoader(ModelExecutor& model_executor, const NetworkDescription& network_description)
    : model_executor_(model_executor), network_description_(network_description)
{
}

void NetworkLoader::run_checks()
{
    // TODO Add checks.
}
Network NetworkLoader::generate_network()
{
    Network network;

    const auto& graph = network_description_.get_network_graph();
    auto [vertices_iter, vertices_end] = boost::vertices(graph);
    for (; vertices_iter != vertices_end; ++vertices_iter)
    {
        const auto& population = graph[*vertices_iter];
        if (population.flags_ & NetworkDescription::PopulationDescription::CHANNELED)
        {
            continue;
        }
        std::visit(
            [&population, &network](const auto& params)
            {
                using NeuronType = typename knp::neuron_traits::neuron_type<std::decay_t<decltype(params)>>::t;
                network.add_population(knp::core::Population<NeuronType>(
                    population.uid_, [&params](size_t) { return params; }, population.neurons_amount_));
            },
            population.parameters_);
    }

    auto [edges_iter, edges_end] = boost::edges(graph);
    for (; edges_iter != edges_end; ++edges_iter)
    {
        const auto& projection = graph[*edges_iter];
        std::visit(
            [&projection, &network](const auto& info)
            {
                using SynapseType = typename knp::synapse_traits::synapse_type<std::decay_t<decltype(info.params_)>>::t;
                knp::core::Projection<SynapseType> created_projection = info.creator_(projection);
                if (projection.flags_ & NetworkDescription::ProjectionDescription::WTA &&
                    created_projection.get_presynaptic())
                {
                    SPDLOG_WARN("Non zero presynaptic UID in WTA projection \"{}\".", projection.name_);
                }
                if (projection.flags_ & NetworkDescription::ProjectionDescription::TRAINABLE)
                {
                    created_projection.unlock_weights();
                }
                network.add_projection(created_projection);
            },
            projection.type_dependent_info_);
    }

    return network;
}
void NetworkLoader::load_other_stuff()
{
    //TODO
}

}  //namespace knp::framework
