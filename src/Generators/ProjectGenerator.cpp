
#include "Frate/Command.hpp"
#include "Frate/LuaAPI.hpp"
#include "Frate/Utils/CLI.hpp"
#include "inja.hpp"
#include "nlohmann/json_fwd.hpp"
#include <Frate/Generators.hpp>
#include <Frate/Constants.hpp>
#include <filesystem>
#include <git2/types.h>
#include <git2/clone.h>

namespace Frate::Generators::Project {
using inja::Environment;
using nlohmann::json;
using std::filesystem::path;
using Utils::CLI::Prompt;
json getTemplateIndex() {
  std::cout << "Getting Template Index" << std::endl;
std::string index_url = static_cast<std::string>(Constants::FRATE_TEMPLATES);

  json index = json::parse(Utils::fetchText(index_url));
  return index;
  } 







  void from_json(const json& j, Template& t){
    t.name = j.at("name").get<std::string>();
    t.git = j.at("git").get<std::string>();
    t.description = j.at("description").get<std::string>();
  }

  std::pair<bool, Template> promptForTemplateName(json index){
    Prompt template_name_prompt("Project type: ");
    for(Template templ: index){
      template_name_prompt.AddOption(templ.name);
    }

    template_name_prompt.PrintValidOptions();

    template_name_prompt.Run();

    auto [success,template_id] = template_name_prompt.Get<std::string>();

    if(!success){
      error << "Error while getting template name" << std::endl;
      return {false, Template()};
    }

    Template templ;
    for(Template t: index){
      if(t.name == template_id){
        templ = t;
        break;
      }
    }

    if(templ.name.empty()){
      error << "Template not found" << std::endl;
      return {false, Template()};
    }
    return {true, templ};
  }

  bool downloadTemplate(std::string git_url, path project_path) {
    //Delete old template before downloading new one
    if(std::filesystem::exists(project_path / "template")){
      Frate::info << "Deleting old template" << std::endl;
      std::filesystem::remove_all(project_path / "template");
    }

    std::filesystem::create_directories(project_path / "template");


    info << "Downloading template" << std::endl;
    git_repository* template_repo = NULL; 
    git_repository* callbacks_repo = NULL;
    Frate::info << "Cloning " << git_url << " into " 
      << (project_path / "template").c_str() << std::endl;


    int template_clone_status = git_clone(&template_repo,
        git_url.c_str(), (project_path / "template").c_str(), NULL);


    if(template_clone_status != 0){
      Frate::error << "Error while cloning repository" << std::endl;
      return false;
    }


    git_repository_free(template_repo);

    const std::string callbacks_url = "https://github.com/frate-templates/frate-callbacks.git";

    Frate::info << "Cloning " << callbacks_url << " into " 
      << (project_path / "template/frate-callbacks").c_str() << std::endl;


    int callbacks_clone_status= git_clone(&callbacks_repo,
        callbacks_url.c_str(),
        (project_path / "template/frate-callbacks").c_str(), NULL);


    if(callbacks_clone_status != 0){
      Frate::error << "Error while cloning repository" << std::endl;
      return false;
    }


    git_repository_free(callbacks_repo);

    std::filesystem::rename(project_path / "template/frate-callbacks/scripts",
        project_path / "template/scripts");

    std::filesystem::remove_all(project_path / "template/frate-callbacks");

    try{
      std::filesystem::remove(project_path / "template/.git");
    }catch(...){
      Frate::error << "could not find .git folder in template/" << std::endl;
    }

    return true;
  }

  bool runTemplatePrompts(std::shared_ptr<Command::Project> pro){
    for(auto [key, tmpl_prompt] : pro->prompts){
      Prompt prompt(tmpl_prompt.text, tmpl_prompt.default_value);
      if(tmpl_prompt.type == "bool"){
        prompt.IsBool();
      }

      for(std::string option: tmpl_prompt.options){
        prompt.AddOption(option);
      }

      prompt.PrintValidOptions();

      prompt.Run();
      auto [valid, value] = prompt.Get<std::string>();  
      if(!valid){
        error << "Error while getting prompt: " << key << std::endl;
        return false;
      }
      pro->prompts[key].value = value;
    }
    return true;
  }

  bool refreshTemplate(Environment &env, sol::state &lua, std::shared_ptr<Command::Project> pro) {
    info << "Refreshing template" << std::endl;
    std::vector<path> paths_to_refresh{
      pro->path / "template/CMakeLists.txt.inja",
    };

    LuaAPI::registerAPI(lua);

    if(!LuaAPI::registerProject(lua, pro)){
      error << "Error while registering project" << std::endl;
      return false;
    }

    if(!LuaAPI::registerProjectScripts(env, lua,pro->path / "template/scripts", pro)){
      error << "Error while registering project scripts" << std::endl;
      return false;
    }

    for(const path& current_p: paths_to_refresh){
      std::string rendered_file = env.render_file(current_p, pro->toJson());
      std::string new_file = current_p.string();
      new_file = new_file.replace(new_file.find(".inja"), 5, "");
      Utils::replaceKey(new_file, "template/", "");
      std::ofstream file;
      try{
        file.open(new_file);
      }catch(...){
        error << "Error while opening file: " << new_file << std::endl;
        return false;
      }
      file << rendered_file;
      file.close();
    }
    return true;
  }
  bool loadTemplateConfig(std::shared_ptr<Command::Project> pro){


    try{

      std::filesystem::copy(
          pro->path / "template/default.json",
          pro->path / "frate-project.json"
          );

    }catch(...){

      error << "Error while copying frate-project.json" << std::endl;
      return false;

    }
  

    std::ifstream file;


    try{

      file.open(pro->path / "frate-project.json");

    }catch(...){

      error << "Error while opening file: " << pro->path / "frate-project.json" << std::endl;
      return false;

    }

    json current_j = pro->toJson();
    json j = json::parse(file);

    j.merge_patch(current_j);

    pro->fromJson(j);


    return true;
  }

  bool initializeLua(Environment &env, sol::state &lua, std::shared_ptr<Command::Project> pro){
    LuaAPI::registerAPI(lua);
    if(!LuaAPI::registerProject(lua, pro)){
      error << "Error while registering project" << std::endl;
      return false;
    }
    if(!LuaAPI::registerProjectScripts(env,lua, pro->path / "template/scripts", pro)){
      error << "Error while registering project scripts" << std::endl;
      return false;
    }
    return true;
  }
      

  bool renderTemplate(
      Environment &env,
      sol::state &lua,
      std::shared_ptr<Command::Project> pro){


    info << "Rendering templates" << std::endl;

    std::string CPM;

    CPM = Utils::fetchText("https://raw.githubusercontent.com/cpm-cmake/CPM.cmake/v0.38.6/cmake/CPM.cmake");


    std::ofstream CPMFile;
    try{
      if(!std::filesystem::exists(pro->path / "cmake"))
        std::filesystem::create_directories(pro->path / "cmake");
      CPMFile.open(pro->path / "cmake/CPM.cmake");
    }catch(...){
      Utils::debug("Error while opening file: CPM.cmake");
      return false;
    }

    CPMFile << CPM;
  
    
    //Array to store all the paths to remove at the end of the function
    std::vector<path> paths_to_remove = {
      pro->path / "template/__init__",
      pro->path / "template/__post__",
    };

    //Array of all the file extensions that we're going to ignore when copying files
    std::vector<std::string> source_file_extensions_to_remove;
    
    //Map of all the source file extensions that are related to the project language
    std::unordered_map<std::string, std::vector<std::string>> related_source_exts = {};
      
    related_source_exts["cpp"] = {
      ".cpp",
      ".cxx",
      ".cc",
      ".C",
      ".c++",
      ".hpp",
      ".hxx",
      ".hh"
    };
    related_source_exts["c"] = {
      ".c",
      ".h"
    };
    //Removes all source files that are not related to the project language
    for(auto [key, source_files]: related_source_exts){
      if(pro->lang != key){
        for(std::string source_file: source_files){
          source_file_extensions_to_remove.push_back(source_file);
        }
      }
    }

    for(const path& current_p: std::filesystem::recursive_directory_iterator(pro->path)){
      if(current_p.string().find("template/") != std::string::npos){
        continue;
      }
      if(current_p.extension() == ".inja"){
        std::string rendered_file = env.render_file(current_p, pro->toJson());
        std::string new_file = current_p.string();
        //Removes the .inja extension from the file
        new_file = new_file.replace(new_file.find(".inja"), 5, "");
        std::ofstream file;
        try{
          file.open(new_file);
        }catch(...){
          error << "Error while opening file: " << new_file << std::endl;
          return false;
        }
        file << rendered_file;
        paths_to_remove.push_back(current_p);
      }
      //Removes the scripts from the project directory
      if(current_p.string().find("/scripts") != std::string::npos){
        paths_to_remove.push_back(current_p);
      }
    }

    //Removes all unrelated source files from the project directory
    //Frate does allow you to make both a c and cpp project on top of each other
    for(const path& current_p: std::filesystem::recursive_directory_iterator(pro->path / pro->src_dir)){
      for(std::string ext: source_file_extensions_to_remove){
        if(current_p.extension() == ext){
          paths_to_remove.push_back(current_p);
        }
      }
    }
    
    //Iterates through all projects we marked for removal and removes them
    for(const path& p: paths_to_remove){
      if(std::filesystem::is_directory(p)){
        std::filesystem::remove_all(p);
      }else{
        std::filesystem::remove(p);
      }
    }

    
    return true;
  }
  bool create(std::shared_ptr<Command::Project> pro){
    info << "Creating Project" << std::endl;
    

    json index = getTemplateIndex();
    bool has_template = false;

    Template current_template;

    for(Template templ: index){
      if(pro->type == templ.name){
        has_template = true;
        current_template = templ;
        break;
      }
    }

    if(!has_template){
      auto [success, templ] = promptForTemplateName(index);
      if(!success){
        error << "Error while prompting for project name" << std::endl;
        return false;
      }
      current_template = templ;
      info << "Creating project from template: " << templ.name << std::endl;
    }

    if(!downloadTemplate(current_template.git, pro->path)){
      error << "Error while downloading template" << std::endl;
      return false;
    }

    std::filesystem::copy(
        pro->path / "template",
        pro->path,
        std::filesystem::copy_options::recursive  | std::filesystem::copy_options::overwrite_existing
        );

    if(!loadTemplateConfig(pro)){
      error << "Error while loading template config" << std::endl;
      return false;
    }

    if(!runTemplatePrompts(pro)){
      error << "Error while running template prompts" << std::endl;
      return false;
    }

    Environment env;
    sol::state lua;

    if(!initializeLua(env, lua, pro)){
      error << "Error while initializing lua" << std::endl;
      return false;
    }

    if(!LuaAPI::initScripts(lua, pro)){
      error << "Error while running init scripts" << std::endl;
      return false;
    }

    if(!renderTemplate(env, lua,  pro)){
      error << "Error while rendering template to tmp" << std::endl;
      return false;
    }

    if(!LuaAPI::postScripts(lua, pro)){
      error << "Error while running post scripts" << std::endl;
      return false;
    }

    pro->save();

    return true;
  }

  bool refresh(std::shared_ptr<Command::Project> pro){
    Environment env;
    sol::state lua;

    LuaAPI::initScripts(lua, pro);

    if(!initializeLua(env, lua, pro)){
      error << "Error while initializing lua" << std::endl;
      return false;
    }

    if(!refreshTemplate(env, lua,  pro)){
      error << "Error while rendering template to tmp" << std::endl;
      return false;
    }

    LuaAPI::postScripts(lua, pro);


    return true;
  }
}
