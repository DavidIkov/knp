/**
 * @file network_description.cpp
 * @brief Network description.
 * @kaspersky_support D. Postnikov
 * @date 20.03.2026
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

#include <knp/framework/network_description.h>


/**
 * @brief Framework namespace.
 */
namespace knp::framework
{
void NetworkDescription::specify_wta_border(
    const knp::core::UID& population_uid, const knp::core::UID& projection_uid, const std::vector<size_t>& borders)
{
    wta_data_.emplace_back(WTAData{population_uid, projection_uid, borders});
}

/*
#define INSTANCE_POPULATION_FUNCTIONS(n, _, neuron_type)                                                          \
    template <>                                                                                                   \
    NetworkDescription::PopulationDescriptor NetworkDescription::add_population<knp::neuron_traits::neuron_type>( \
        std::string_view, const knp::neuron_traits::neuron_parameters<knp::neuron_traits::neuron_type>&, size_t,  \
        PopulationDescription::FlagsType);

#define INSTANCE_PROJECTION_FUNCTIONS(n, _, synapse_type)                                                           \
    template <>                                                                                                     \
    NetworkDescription::ProjectionDescriptor NetworkDescription::add_projection<knp::synapse_traits::synapse_type>( \
        std::string_view, knp::core::UID, knp::core::UID,                                                           \
        const knp::synapse_traits::synapse_parameters<knp::synapse_traits::synapse_type>&,                          \
        const ProjectionDescription::CreatorType<knp::synapse_traits::synapse_type>&,                               \
        PopulationDescription::FlagsType);

// cppcheck-suppress unknownMacro
BOOST_PP_SEQ_FOR_EACH(INSTANCE_POPULATION_FUNCTIONS, "", BOOST_PP_VARIADIC_TO_SEQ(ALL_NEURONS))
// cppcheck-suppress unknownMacro
BOOST_PP_SEQ_FOR_EACH(INSTANCE_PROJECTION_FUNCTIONS, "", BOOST_PP_VARIADIC_TO_SEQ(ALL_SYNAPSES))
*/

}  // namespace knp::framework
