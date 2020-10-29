#include <Varcmd.hpp>

std::string vc_board::main(Context *ctx, std::vector<std::string> args) {

    Board board;
    std::string key;

    if (args.size() == 1) {
        board = ctx->getBoard();
        key = args[0];
    } else {
        board = Board::findByName(args[0]);
       if (board == noBoard) {
             return "OBJECT_NOT_FOUND";
        }
        key = args[1];
    }

    if (args[0] == "root") {
        return board.getFolder().getAbsolutePath();
    }
    return board.getProperties().getPlatformSpecific(key);
}

std::string vc_board::usage() {
    return "${board:key}";
}
