#pragma once
#include <string>
#include <vector>

namespace rack::plugin
{

struct Model;
struct json_t;

struct Plugin {
	Plugin()
		: slug{""} {
	}

	Plugin(std::string slug)
		: slug{slug} {
	}

	std::vector<Model *> models;

	std::string slug; //brand slug

	void addModel(Model *model);
	~Plugin();

	Model *getModel(const std::string &slug);
	std::string getBrand();

	void fromJson(json_t *rootJ);
	void modulesFromJson(json_t *rootJ);

	std::string path;
	void *handle = nullptr;
	std::string version;
	std::string license;
	std::string name;
	std::string brand;
	std::string description;
	std::string author;
	std::string authorEmail;
	std::string authorUrl;
	std::string pluginUrl;
	std::string manualUrl;
	std::string sourceUrl;
	std::string donateUrl;
	std::string changelogUrl;
	double modifiedTimestamp{};
};

} // namespace rack::plugin
