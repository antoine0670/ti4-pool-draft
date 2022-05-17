#include <iostream>
#include <fstream>
#include <map>
#include <experimental/filesystem>
#include "../libs/nlohmann/json.hpp"

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

json config;

// Implemented myself because nlohmann::json::contains() didn't work
bool 
contains(const json& obj, const std::string key)
{
	for (const auto& it: obj)
	{
		if (it == key)
		{
			return true;
		}
	}

	return false;
}


bool 
load_config(const std::string& input_file)
{
	if (!fs::exists(input_file))
	{
		return false;
	}

	try {
		std::ifstream in(input_file);
		in >> config;
	} catch (...) {
		return false;
	}

	return true;
}

std::map<int, std::string> 
load_factions()
{
	std::map<int, std::string> factions;
	int pair_idx{0};

	for (int i = 0 ; i < config["FactionsList"].size() ; ++i)
	{
		if(!contains(config["ExcludeList"], config["FactionsList"][i]))
		{
			factions.insert(
				std::pair<int, std::string>(pair_idx, config["FactionsList"][i]));
			pair_idx++;
		}
	}
	
	for (int i = 0 ; i < config["OtherFactionsList"].size() ; ++i)
	{
		if(!contains(config["ExcludeList"], config["OtherFactionsList"][i]))
		{
			factions.insert(
				std::pair<int, std::string>(pair_idx, config["OtherFactionsList"][i]));
			pair_idx++;
		}
	}

	if (config["PoK"])
	{
		for (int i = 0 ; i < config["PoKFactionsList"].size() ; ++i)
		{
			if(!contains(config["ExcludeList"], config["PoKFactionsList"][i]))
			{
				factions.insert(
					std::pair<int, std::string>(pair_idx, config["PoKFactionsList"][i]));
				pair_idx++;
			}
		}
	}

	return factions;
}

void 
print_setup(const int& faction_count, const int& pool_size)
{
	std::cout << "Number of players: " << config["Players"].size() << std::endl;
	std::cout << "Using PoK expansion: " << config["PoK"] << std::endl;
	std::cout << "Number of factions: " << faction_count << std::endl;
	std::cout << "Draft pool size: " << pool_size << std::endl;
	std::cout << std::endl;
}

int 
main(void)
{
	srand(time(NULL));

	load_config("setup.json");

	int faction_count = config["FactionsList"].size() + 
						config["OtherFactionsList"].size() - 
						config["ExcludeList"].size();
	if (config["PoK"])
	{
		faction_count += config["PoKFactionsList"].size();
	}

	//std::cout << faction_count << std::endl;
	int player_count = config["Players"].size();

	int pool_size = faction_count / player_count;
	if (!config["AutoPool"])
	{
		if (config["PoolSize"] < pool_size)
		{
			pool_size = config["PoolSize"];
		}
	}

	print_setup(faction_count, pool_size);

	std::map<int, std::string> factions{ load_factions() };

	for (int i = 0 ; i < player_count ; ++i)
	{
		std::cout << config["Players"][i] << ": " << std::endl;
		for (int j = 0 ; j < pool_size ; ++j)
		{
			auto key = factions.begin();
			std::advance(key, rand() % factions.size());
			//std::cout << "\t" << key->first;
			std::cout << "\t" << factions[key->first] << std::endl;

			factions.erase(key); // Should modify a copy instead
		}
	}
}