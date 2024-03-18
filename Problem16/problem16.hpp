#include <vector>
#include <string>

class TextEditor {
private:
    std::vector<std::string> file;
    std::vector<std::string> undo;
    std::vector<std::string> redo;
    std::string file_opened;
public:
    void open_file();
    void display_file();
    void write_text_at_position();
    void save_to_file();
    void undo_action();
    void redo_action();
    void delete_text_from_position();
};

