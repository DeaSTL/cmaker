#include "../Generators/Generators.hpp"
#include "Command.hpp"
#include <algorithm>
#include <cxxopts.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "../Utils/General.hpp"
#include <cmath>

namespace Command {
  using nlohmann::json;
  bool add(std::shared_ptr<Context> ctx, cxxopts::ParseResult &args) {
    if (!(args.count("subcommand") > 0)) {
      std::cout << "Usage add:" << ENDL
        "\tdep: adds a dependency" << ENDL
        "\tflag: adds a flag" << ENDL
        "\tlib:  adds a library" << std::endl;
      return false;
    }
      std::string subcommand = args["subcommand"].as<std::string>();
      if (subcommand == "dep") {
        addDependency(ctx, args);
      }
      if (subcommand == "flag") {
        addFlag(ctx, args);
      }

    return true;
  }

  bool addFlag(std::shared_ptr<Context> ctx, cxxopts::ParseResult &args) {
    if (args.count("subcommand") == 0) {
      for (auto flag : args["subcommand"].as<std::vector<std::string>>()) {
        ctx->flags.push_back(flag);
      }
    }
    return true;
  }

  bool addAuthors(std::shared_ptr<Context> ctx, cxxopts::ParseResult &args){
    if (args.count("args") == 0) {
      for (auto author : args["args"].as<std::vector<std::string>>()) {
        ctx->authors.push_back(author);
      }
    }
    return true;
  }

  bool checkForOverlappingDependencies(std::shared_ptr<Context> ctx, std::string name){
    if(ctx->dependencies.size() == 0){
      return false;
    }
    for(dependency dep: ctx->dependencies){
      if(dep.name == name){
        return true;
      }
    }
    return false;
  }

  bool searchVersions(){
    std::cout << "Getting versions" << std::endl;
    return true;
  }

  bool addDependency(std::shared_ptr<Context> ctx, cxxopts::ParseResult &args) {
    if (args.count("args") == 0) {
      std::cout << 
        "Usage add dep:" << ENDL
        "\t[args]: the dependencies to project" << ENDL
        "\tcmake add dep [args] " << std::endl;
      return false;
    }

    std::vector<packageResult> searchResults = searchPackage(args["args"].as<std::vector<std::string>>()[0]);
    if(searchResults.size() == 0){
      std::cout << "No results found" << std::endl;
      return false;
    }
    std::cout << "Select a package to install: ";
    std::string input;
    std::cin >> input;
    int index = std::stoi(input);

    std::cout << "Installing " << searchResults[index].name << std::endl;

    //json versionJson = Utils::fetchJson("https://raw.githubusercontent.com/cmaker-dev/index/main/index/" + searchResults[index].name + "/info.json"); 
  
    std::vector<std::string> versions = searchResults[index].versions;
    std::string version = ""; 

    for(size_t i = 0; i < versions.size(); i++){
      std::cout << "[" << i << "]" << versions[i] << std::endl;
      if (versions[i] ==  "master" || versions[i] == "main"  ||  versions[i] == "stable"){
        version = versions[i];
      }
    }

    
    std::cout << "Select a version to install [" + version + "] : ";
    std::string versionInput;
    std::cin >> versionInput;

    int versionIndex = std::stoi(versionInput);
    version = versions[versionIndex];
  
    if(checkForOverlappingDependencies(ctx, searchResults[index].name)){
      std::cout << "Package already installed" << std::endl;
      return false;
    }

    std::cout << "Adding dependency to config.toml" << std::endl;
    ctx->dependencies.push_back({

      .name = searchResults[index].name,
      .url = searchResults[index].url,
      .version = searchResults[index].versions[versionIndex],
      //TODO: Change target link to be the actual link
      .target_link = searchResults[index].target_link == "" 
        ? searchResults[index].name
        : searchResults[index].target_link

    });
    std::cout << "Writing config.toml" << std::endl;
    Generators::ConfigToml::writeConfig(ctx);
    Generators::CMakeList::create(ctx);

    return true;
  }
} // namespace Command
