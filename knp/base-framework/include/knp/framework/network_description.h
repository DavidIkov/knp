/**
 * @file network_description.h
 * @brief Network description.
 * @kaspersky_support D. Postnikov
 * @date 19.03.2026
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

#include <knp/framework/network.h>

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <boost/graph/adjacency_list.hpp>


/**
 * @brief Framework namespace.
 */
namespace knp::framework
{
class KNP_DECLSPEC NetworkDescription
{
    /**
     * @brief Get output populations
     * @return Output populations
     */
    [[nodiscard]] inline const auto& get_output_populations() const { return output_populations_; }


    /**
     * @brief Get projections from inputs.
     * @return Projections from inputs.
     */
    [[nodiscard]] inline const auto& get_projections_from_inputs() const { return projections_from_inputs_; }


    /**
     * @brief Get inference populations.
     * @return Inference populations.
     */
    [[nodiscard]] inline const auto& get_inference_populations() const { return inference_populations_; }


    /**
     * @brief Get inference projections.
     * @return Inference projections.
     */
    [[nodiscard]] inline const auto& get_inference_projections() const { return inference_projections_; }


    /**
     * @brief Get populations names.
     * @return Populations names.
     */
    [[nodiscard]] inline const auto& get_populations_names() const { return populations_names_; }


    /**
     * @brief Get wta data.
     * @return Wta data.
     */
    [[nodiscard]] inline const auto& get_wta_data() const { return wta_data_; }

public:
    struct PopulationDescription
    {
        static constexpr uint32_t INPUT = 1U << 0U;
        static constexpr uint32_t OUTPUT = 1U << 1U;
        static constexpr uint32_t CHANNELED = 1U << 2U;
        static constexpr uint32_t INFERENCE = 1U << 3U;
        static constexpr uint32_t WTA = 1U << 4U;

        using AnyParameter = boost::mp11::mp_apply<
            std::variant,
            boost::mp11::mp_transform<knp::neuron_traits::neuron_parameters, knp::neuron_traits::AllNeurons>>;
        using FlagsType = uint32_t;

        knp::core::UID uid_;
        std::string name_;
        AnyParameter parameters_;
        size_t neurons_amount_;
        FlagsType flags_;
    };

    template <typename NeuronType>
    [[nodiscard]] knp::core::UID add_population(
        std::string_view name, const knp::neuron_traits::neuron_parameters<NeuronType>& parameter,
        size_t neurons_amount, PopulationDescription::FlagsType flags = 0);

    struct ProjectionDescription
    {
        static constexpr uint32_t INPUT = 1U << 0U;
        static constexpr uint32_t OUTPUT = 1U << 1U;
        static constexpr uint32_t CHANNELED = 1U << 2U;
        static constexpr uint32_t INFERENCE = 1U << 3U;
        static constexpr uint32_t WTA = 1U << 4U;

        template <typename SynapseType>
        using CreatorType = std::function<knp::core::Projection<SynapseType>(
            const knp::core::UID&, const knp::core::UID&, size_t, size_t)>;

        template <typename SynapseType>
        struct TypeDependentInfo
        {
            knp::synapse_traits::synapse_parameters<SynapseType> params_;
            CreatorType<SynapseType> creator_;
        };

        using AnyParameter = boost::mp11::mp_apply<
            std::variant, boost::mp11::mp_transform<TypeDependentInfo, knp::synapse_traits::AllSynapses>>;
        using FlagsType = uint32_t;

        knp::core::UID uid_;
        std::string name_;


        AnyParameter type_dependent_info_;

        uint32_t flags_;
    };

    template <typename SynapseType>
    [[nodiscard]] knp::core::UID add_projection(
        std::string_view name, knp::core::UID presynaptic_population, knp::core::UID postsynaptic_population,
        const knp::synapse_traits::synapse_parameters<SynapseType>& parameter,
        const ProjectionDescription::CreatorType<SynapseType>& creator, PopulationDescription::FlagsType flags = 0);

    void specify_wta_border(
        const knp::core::UID& population_uid, const knp::core::UID& projection_uid, std::vector<size_t> borders);

private:
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, PopulationDescription, ProjectionDescription>
        network_graph_;

    struct KNP_DECLSPEC WTAData
    {
        knp::core::UID population_;
        knp::core::UID projection_;
        std::vector<size_t> borders_;
    };

    /**
     * @brief Data about WTA connections.
     */
    std::vector<WTAData> wta_data_;
};
}  // namespace knp::framework
