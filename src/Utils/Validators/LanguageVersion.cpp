#include "Frate/Utils/Validation.hpp"
#include <iostream>
#include <string>
#include <regex>
#include <memory>
#include <Frate/Command.hpp> 
#include <Frate/Generators.hpp> 



namespace Generators::ConfigJson{
  /*
   * Validates the language version
   * @param prefix: the prefix of the message
   * @param ctx: the context of the command
   * @param config_json: the config json context
   * @return: true if the language version is valid
   */
  [[deprecated("Use the new project wizard")]]
  bool validateLanguageVersion(std::string prefix, std::shared_ptr<Command::Project> pro, std::shared_ptr<Config> config_json) {
    std::cout << prefix;
#ifndef TEST
      std::getline(std::cin, config_json->lang_version);
#endif
    std::vector<std::string> valid_c_versions = {"89", "90", "94", "99", "11", "18"};
    std::vector<std::string> valid_cpp_versions = {"98", "03", "11", "14", "17", "20","23"};

    //If the version is empty we're gonna set it
    if(config_json->lang_version == "") {
      goto end;
    }
    for(std::string version : valid_c_versions) {
      if(config_json->lang_version == version) {
        goto end;
        break;
      }
    }
    for(std::string version : valid_cpp_versions) {
      if(config_json->lang_version == version) {
        goto end;
        break;
      }
    }
    return false;
    end:
      pro->lang_version = config_json->lang_version == "" ? pro->lang_version : config_json->lang_version;
    
    return true;
  }
}

namespace Utils::Validation {
  bool CppLanguageVersion(std::string lang_ver){
    std::vector<std::string> valid_cpp_versions = {"98", "03", "1x", "11", "14", "17", "20","2x","23"};
    for(std::string version : valid_cpp_versions) {
      if(lang_ver == version) {
        return true;
      }
    }
    return false;
  }
  bool CLanguageVersion(std::string lang_ver){
    std::vector<std::string> valid_c_versions = {"89", "90", "94", "99", "11","1x", "18","20", "2x"};
    for(std::string version : valid_c_versions) {
      if(lang_ver == version) {
        return true;
      }
    }
    return false;
  }
}
