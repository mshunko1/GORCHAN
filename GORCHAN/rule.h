#pragma once

enum rule_type {rule_type_undefined, rule_type_temproray, rule_type_init, rule_type_friendly, rule_type_aquare_by_rule, rule_type_soul_matter};

class rule
{
public:
	rule();
	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);
private:
	gint m_weight;
	gvector<shape_index> m_path;
};

