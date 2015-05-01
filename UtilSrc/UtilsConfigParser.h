#ifndef ___CONFIG_PARSER_H
#define ___CONFIG_PARSER_H
#include <string>
#include <map>
#include <vector>
#include "R3Graphics/R3Graphics.h"
// a static class
class ConfigParser
{
public:
    enum {SUM, MIN} SpatialOperation;
public:
	ConfigParser(void);
	void Import(const char* filename, bool create_new = false);
    void ImportFrequentlyUsedParameters(void);
    // Check
    bool HasSection(const std::string& sec) const;
	bool HasOption(const std::string& sec,
						const std::string& opt) const;
	bool IsLoaded(void) const;
    // Set
    void Set(const std::string& sec, const std::string& opt,
			 const std::string& val, bool create_new = false);
    // Get
	double GetScalar(const std::string& sec, const std::string& opt) const;
	int GetInt(const std::string& sec, const std::string& opt) const;
	const std::string Get(const std::string& sec,
						  const std::string& opt) const;
	const char* GetCharArray(const std::string& sec,
							 const std::string& opt) const;
	const std::vector<double> GetScalarArray(const std::string& sec,
										 const std::string& opt) const;
    bool IsEnabled(const std::string& sec,
						const std::string& opt) const;
public:
    // frequently used parameters
    double meaningless_node_const;
    double weight_rule_frequency;
    double weight_feature_prior;
    double weight_label_occurrence;
    double weight_spatial_energy;
    double weight_spatial_energy_object2parts;
    double object2part_threshold;
    double missing_spatial_relation_default_energy;
    double low_frequency_penalty;
    bool include_rule_frequency;
    bool include_label_occurrence_prior;
    bool include_pairwise_spatial_prior;
    bool include_internal_geometry_prior;
    int jittering_samples;
    double jittering_relative_size;
    std::string unary_descriptor_class;
    std::string binary_descriptor_class;
    double d2_max_distance;
    double d2_weight;
    double zmin_weight;
    double xyz_weight;
    double connected_max_distance;
    std::string binary_classifier_type;
    std::string unary_classifier_type;
    bool is_multiclass_normalized;
    double min_overlapped_ration_as_identical;
    bool constant_meaningless_penalty;
    int k_nearest_neighbor;
    bool ignore_meaningless_nodes_in_testing;
    bool ignore_meaningless_nodes_in_training;
    std::string label_edge_type;
    int min_num_instances_per_label_edge;
    double kde_min_bandwidth;
    double kde_bandwidth_estimate_ratio;
    bool kde_constant_z_bandwidth_flag;
    double kde_constant_z_bandwidth;
    int dual_direction_spatial_operation;
    std::vector<double> spatial_dim_weights;
    bool spatial_multiply_minus_1;
    int num_preserved_best_half_instances;
    bool unary_training_meaningless_include_all_meaningless_instances;
    bool unary_training_meaningless_include_corr_full_instances;
    double binary_merge_bound_margin;
    double maximum_feature_prior_difference_in_consideration;
    bool can_occurrency_over_limit;
    double highest_cardinality_penalty;
    double training_fraction;
    bool unary_labeling_including_meaningless;
protected:
	// Data
    std::map<std::string, std::map<std::string,std::string> > values;
	bool isLoaded;
};

extern ConfigParser MyConfigParser;
#endif
