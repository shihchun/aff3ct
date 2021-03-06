#include <utility>

#include "Tools/Exception/exception.hpp"
#include "Tools/Documentation/documentation.h"
#include "Tools/Display/Terminal/Standard/Terminal_std.hpp"
#include "Factory/Tools/Display/Terminal/Terminal.hpp"

using namespace aff3ct;
using namespace aff3ct::factory;

const std::string aff3ct::factory::Terminal_name   = "Terminal";
const std::string aff3ct::factory::Terminal_prefix = "ter";

Terminal::parameters
::parameters(const std::string &prefix)
: Factory::parameters(Terminal_name, Terminal_name, prefix)
{
}

Terminal::parameters
::parameters(const std::string &name, const std::string &prefix)
: Factory::parameters(name, Terminal_name, prefix)
{
}

Terminal::parameters* Terminal::parameters
::clone() const
{
	return new Terminal::parameters(*this);
}

void Terminal::parameters
::get_description(tools::Argument_map_info &args) const
{
	auto p = this->get_prefix();
	const std::string class_name = "factory::Terminal::parameters::";

	tools::add_arg(args, p, class_name+"p+type",
		tools::Text(tools::Including_set("STD")));

	tools::add_arg(args, p, class_name+"p+no",
		tools::None());

	tools::add_arg(args, p, class_name+"p+freq",
		tools::Integer(tools::Positive()));
}

void Terminal::parameters
::store(const tools::Argument_map_value &vals)
{
	auto p = this->get_prefix();

	if(vals.exist({p+"-type"})) this->type      = vals.at({p+"-type"});
	if(vals.exist({p+"-no"  })) this->disabled  = true;
	if(vals.exist({p+"-freq"})) this->frequency = std::chrono::milliseconds(vals.to_int({p+"-freq"}));
}

void Terminal::parameters
::get_headers(std::map<std::string,header_list>& headers, const bool full) const
{
	auto p = this->get_prefix();

	headers[p].push_back(std::make_pair("Enabled", this->disabled ? "no" : "yes"));
	headers[p].push_back(std::make_pair("Frequency (ms)", std::to_string(this->frequency.count())));
}


tools::Terminal* Terminal::parameters
::build(const std::vector<std::unique_ptr<tools::Reporter>> &reporters) const
{
	if (this->type == "STD") return new tools::Terminal_std(reporters);

	throw tools::cannot_allocate(__FILE__, __LINE__, __func__);
}

tools::Terminal* Terminal
::build(const parameters &params, const std::vector<std::unique_ptr<tools::Reporter>> &reporters)
{
	return params.build(reporters);
}