#include <fstream>
#include <sstream>
#include "UtilsConfigParser.h"
#include "Utils/Utils.h"

using namespace std;
//ConfigParser MyConfigParser;

ConfigParser::
ConfigParser(void)
:isLoaded(FALSE)
{}

void ConfigParser::
Import(const char* filename, bool create_new)
{
    ifstream fin(filename);
	if (!fin)
	{
		fprintf(stderr, "Unable to open setting file %s\n", filename);
		return;
	}
    string buffer;
	string current_section = "";
	int line_counter = 0;
	bool fail_flag = FALSE;
    while (!fin.eof())
    {
        getline(fin, buffer);
		line_counter ++;
		// comments
        if (buffer[0] == '#') continue;
		// section name
		else if (buffer[0] == '[') {
			size_t last_pos = buffer.find_last_of("]");
			if (last_pos == string::npos) {
				fprintf(stderr, "ConfigParser::Import syntax error found at"
						" line %d\n", line_counter);
				fail_flag = true;
				break;
			}
			else {
				current_section = buffer.substr(1, last_pos-1);
			}
		}
		// option name
		else {
			// empty line
			if (buffer.length() == 0) continue;
			if (current_section.length() == 0) {
				fprintf(stderr, "ConfigParser::Import syntax error found at"
						" line %d\n", line_counter);
				fail_flag = true;
				break;
			}
			size_t equal_pos = buffer.find_last_of("=");
			if (equal_pos == string::npos) {
				fprintf(stderr, "ConfigParser::Import syntax error found at"
						" line %d\n", line_counter);
				fail_flag = true;
				break;
			}
			string opt_part = buffer.substr(0, equal_pos);
			string val_part = buffer.substr(equal_pos+1);
			Set(current_section, StringUtil::Trim(opt_part, " "),
				StringUtil::Trim(val_part, " "),
				create_new);
		}
    }
    fin.close();
	if (!fail_flag) {
		isLoaded = TRUE;
	}
	else
	{
		fprintf(stderr, "ConfigParser::Import fail to import %s\n",
				filename);
	}
    ImportFrequentlyUsedParameters();
}

void ConfigParser::
ImportFrequentlyUsedParameters(void)
{
    meaningless_node_const = GetScalar("Parameters", "meaningless_node_const");
    weight_rule_frequency = GetScalar("Parameters", "weight_rule_frequency");
    weight_feature_prior = GetScalar("Parameters", "weight_feature_prior");
    weight_label_occurrence = GetScalar("Parameters", "weight_label_occurrence");
    weight_spatial_energy = GetScalar("Parameters", "weight_spatial_energy");
    weight_spatial_energy_object2parts = GetScalar("Parameters", "weight_spatial_energy_object2parts");
    object2part_threshold = GetScalar("Parameters", "object2part_threshold");
    missing_spatial_relation_default_energy = GetScalar("Parameters", "missing_spatial_relation_default_energy");
    low_frequency_penalty = GetScalar("Parameters", "low_frequency_penalty");
    include_rule_frequency = IsEnabled("Energy", "include_rule_frequency");
    include_label_occurrence_prior = IsEnabled("Energy", "include_label_occurrence_prior");
    include_pairwise_spatial_prior = IsEnabled("Energy", "include_pairwise_spatial_prior");
    jittering_samples = GetInt("Parameters", "jittering_samples");
    jittering_relative_size = GetScalar("Parameters", "jittering_relative_size");
    unary_descriptor_class = Get("Descriptor", "unary_descriptor_class");
    binary_descriptor_class = Get("Descriptor", "binary_descriptor_class");
    d2_max_distance = GetScalar("Parameters", "d2_max_distance");
    d2_weight = GetScalar("Parameters", "d2_weight");
    zmin_weight = GetScalar("Parameters", "zmin_weight");
    xyz_weight = GetScalar("Parameters", "xyz_weight");
    connected_max_distance = GetScalar("Parameters", "connected_max_distance");
    
    // classifier
    binary_classifier_type = Get("Descriptor", "binary_classifier_type");
    unary_classifier_type = Get("Descriptor", "unary_classifier_type");
    is_multiclass_normalized = IsEnabled("Descriptor", "is_multiclass_normalized");
    // identicalness
    min_overlapped_ration_as_identical = GetScalar("Parameters", "min_overlapped_ration_as_identical");
    
    constant_meaningless_penalty = IsEnabled("Parameters", "constant_meaningless_penalty");
    
    include_internal_geometry_prior = IsEnabled("Energy", "include_internal_geometry_prior");
    
    k_nearest_neighbor = GetInt("Parameters", "k_nearest_neighbor");
    
    ignore_meaningless_nodes_in_testing = IsEnabled("Algorithm", "ignore_meaningless_nodes_in_testing");
    
    ignore_meaningless_nodes_in_training = IsEnabled("Algorithm", "ignore_meaningless_nodes_in_training");
    
    label_edge_type = Get("Descriptor", "label_edge_type");
    
    min_num_instances_per_label_edge = GetInt("Descriptor", "min_num_instances_per_label_edge");
    
    kde_min_bandwidth = GetScalar("Parameters", "kde_min_bandwidth");
    kde_bandwidth_estimate_ratio = GetScalar("Parameters", "kde_bandwidth_estimate_ratio");
    kde_constant_z_bandwidth_flag = IsEnabled("Parameters", "kde_constant_z_bandwidth_flag");
    kde_constant_z_bandwidth = GetScalar("Parameters", "kde_constant_z_bandwidth");
    if (Get("Descriptor", "dual_direction_spatial_operation") == "sum") {
        dual_direction_spatial_operation = ConfigParser::SUM;
    }
    else if (Get("Descriptor", "dual_direction_spatial_operation") == "min") {
        dual_direction_spatial_operation = ConfigParser::MIN;
    }
    spatial_dim_weights = TypeUtil::String2Array(Get("Parameters", "spatial_dim_weights"));
    
    spatial_multiply_minus_1 = IsEnabled("Parameters", "spatial_multiply_minus_1");
    
    num_preserved_best_half_instances = GetInt("Parameters", "num_preserved_best_half_instances");
    
    unary_training_meaningless_include_all_meaningless_instances = IsEnabled("Grammar", "unary_training_meaningless_include_all_meaningless_instances");
    
    unary_training_meaningless_include_corr_full_instances = IsEnabled("Grammar", "unary_training_meaningless_include_corr_full_instances");
    
    binary_merge_bound_margin = GetScalar("Parameters", "binary_merge_bound_margin");
    
    maximum_feature_prior_difference_in_consideration = GetScalar("Parameters", "maximum_feature_prior_difference_in_consideration");
    
    can_occurrency_over_limit = IsEnabled("Energy", "can_occurrency_over_limit");
    
    highest_cardinality_penalty = GetScalar("Parameters", "highest_cardinality_penalty");
    
    training_fraction = GetScalar("RemovingScenes", "training_fraction");
    
    unary_labeling_including_meaningless = IsEnabled("Algorithm", "unary_labeling_including_meaningless");
}

bool ConfigParser::
HasSection(const string& sec) const
{
	return (values.find(sec) != values.end());
}

bool ConfigParser::
HasOption(const string& sec, const string& opt) const
{
	if (!HasSection(sec)) return FALSE;
	map<string, map<string, string> >::const_iterator sec_map =
	values.find(sec);
	return ((*sec_map).second.find(opt) != (*sec_map).second.end());
}

bool ConfigParser::
IsLoaded(void) const
{
	return isLoaded;
}

void ConfigParser::
Set(const std::string& sec, const std::string& opt,
	const std::string& val, bool create_new)
{
	if (!create_new && !HasOption(sec, opt)) {
		fprintf(stderr, "ConfigParser::Set Option %s::%s doesn't exist!\n", sec.c_str(), opt.c_str());
		return;
	}
	values[sec][opt] = val;
}

const string ConfigParser::
Get(const std::string& sec, const std::string& opt) const
{
	if (!HasOption(sec, opt)) {
		fprintf(stderr, "ConfigParser::Get Unable to find %s::%s\n",
				sec.c_str(), opt.c_str());
	}
	map<string, map<string, string> >::const_iterator sec_map = values.find(sec);
	map<string, string>::const_iterator opt_map = (*sec_map).second.find(opt);
	return (*opt_map).second;
}

double ConfigParser::
GetScalar(const std::string& sec, const std::string& opt) const
{
	return TypeUtil::String2Number(Get(sec, opt));
}

int ConfigParser::
GetInt(const std::string& sec, const std::string& opt) const
{
	return int(GetScalar(sec, opt));
}

const char* ConfigParser::
GetCharArray(const std::string& sec, const std::string& opt) const
{
	return Get(sec, opt).c_str();
}

const std::vector<double> ConfigParser::
GetScalarArray(const std::string& sec,
			   const std::string& opt) const
{
	std::string str = Get(sec, opt);
	std::vector<std::string> segments = StringUtil::Split(str, ',');
	std::vector<double> scalar_array;
	for (int i=0; i<int(segments.size()); i++) {
		scalar_array.push_back(TypeUtil::String2Number(segments[i]));
	}
	return scalar_array;
}

RNBoolean ConfigParser::
IsEnabled(const std::string& sec, const std::string& opt) const
{
	return Get(sec, opt) == "on";
}
