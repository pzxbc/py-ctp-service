#pragma once

#include <map>
#include <boost/variant.hpp>

#include "boost_variant_bind.h"

using namespace std;

typedef map<string, boost::variant<int, double, string>> CTP_STRUCT;
