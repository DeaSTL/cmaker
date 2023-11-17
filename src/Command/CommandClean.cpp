#include "Command.hpp"
#include <filesystem>

namespace Command {
using namespace std::filesystem;

bool cleanCache(std::shared_ptr<Project> pro) {
  const std::vector<path> files_to_delete = {
      pro->project_path / "CMakeCache.txt",
      pro->project_path / "install_manifest.txt",
      pro->project_path / "cmake_install.cmake",
      pro->project_path / "Makefile"};
  const std::vector<std::filesystem::path> dirs_to_delete = {
      pro->project_path / "CMakeFiles/", pro->project_path / "_deps/"};

  for (auto &file : files_to_delete) {
    if (exists(file)) {
      try {
        std::cout << "Deleting: " << file << std::endl;
        std::filesystem::remove(file);
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
      }
    }
  }
  for (auto &dir : dirs_to_delete) {
    if (exists(dir)) {
      try {
        std::cout << "Deleting: " << dir << std::endl;
        remove_all(dir);
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
      }
    }
  }

  return true;
  }


  bool Interface::clean(){
    bool clean_cache = false;
    if(args->operator[]("cache").as<bool>()){
      clean_cache = true;
    }
  
    if(clean_cache){
      if(!cleanCache(pro)){
        //WE HAD A FUCKING PROBLEM BRUH
        return false;
      }
    }


    //TODO: delete cache files and deps
    std::cout << "Cleaning: " << std::endl;
    if(exists(pro->project_path / "build")){
      for (directory_entry p : directory_iterator(pro->project_path / "build")) {
        std::cout << "Deleting" << p.path() << std::endl;
        if(p.is_directory()){
          remove_all(p.path());
        } else {
          std::filesystem::remove(p.path());
        }
      }
    }else{
      std::cout << "Could not find ./build" << std::endl;
    }

    return true;
  }
  } // namespace Command
