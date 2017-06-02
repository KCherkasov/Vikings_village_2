#ifndef VIKINGS_LOAD_GAME_COMMAND_H
#define VIKINGS_LOAD_GAME_COMMAND_H

class LoadGameCommand: public FrontendCommand {
  public:
    LoadGameCommand(const std::string& fname): FrontendCommand(), _fname(fname) {}
    virtual ~LoadGameCommand() {}

    virtual ssize_t execute(World* world);

  private:
    std::string _fname;
};

#endif
