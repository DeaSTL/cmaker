#include "Frate/Utils/General.hpp"
#include <Frate/Command/Actions/FTP.hpp>
namespace Frate::Command::FTP {
  using namespace std::filesystem;
  using Utils::CLI::Prompt;
  using namespace Utils::CLI::Ansi;
  bool run(std::shared_ptr<Interface> inter) {

    Prompt prompt(
        "Are you sure you would like to delete the entire project?"
        );

    prompt.setColor(RED).isBool().run();
    auto [valid, value] = prompt.get<bool>();
    if (!valid || !value) {
      Utils::error << "Aborting..." << std::endl;
      return false;
    }

    path tmp_path = Utils::copyToTmpPath(inter->pro->path,"nuke-delete-frate-project-");

    Utils::info << "Deleting project" << ENDL;

    for (const directory_entry &p : 
        directory_iterator(inter->pro->path) | std::views::filter(
            [](const directory_entry &p) { return p.path().filename() != "frate"; })
        ){
      std::filesystem::path path = p.path();
      try{
        if(std::filesystem::is_directory(path)){
          std::filesystem::remove_all(path);
          if(verbose_mode) Utils::info << "Deleting: " << path << std::endl;
        }else{
          std::filesystem::remove(path);
          if(verbose_mode) Utils::info << "Deleting: " << path << std::endl;
        }
      }catch(std::exception &e){
        Utils::error << "Failed to delete: " << path << std::endl;
        Utils::debug(e.what());
        return false;
      }
    }
    return true;
  }
}
