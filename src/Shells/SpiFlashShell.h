#pragma once

#include "Interfaces/ITerminalView.h"
#include "Interfaces/IInput.h"
#include "Managers/UserInputManager.h"
#include "Transformers/ArgTransformer.h"
#include "Services/SpiService.h"
#include "Managers/BinaryAnalyzeManager.h"
#include "Models/TerminalCommand.h"
#include "States/GlobalState.h"

class SpiFlashShell {
public:
    SpiFlashShell(
        SpiService& spiService,
        ITerminalView& view,
        IInput& input,
        ArgTransformer& argTransformer,
        UserInputManager& userInputManager,
        BinaryAnalyzeManager& binaryAnalyzeManager
    );

    void run();

private:
    const std::vector<std::string> actions = {
        " 🔍 Probe Flash",
        " 📊 Analyze Flash",
        " 🔎 Search string",
        " 📜 Extract strings",
        " 📖 Read bytes",
        " ✏️  Write bytes",
        " ✏️  Flash Firmware",
        " 🗃️  Dump ASCII",
        " 🗃️  Dump RAW",
        " 💣 Erase Flash",
        "🚪 Exit Shell"
    };

    SpiService& spiService;
    ITerminalView& terminalView;
    IInput& terminalInput;
    ArgTransformer& argTransformer;
    UserInputManager& userInputManager;
    BinaryAnalyzeManager& binaryAnalyzeManager;
    GlobalState& state = GlobalState::getInstance();

    void cmdProbe();
    void cmdAnalyze();
    void cmdSearch();
    void cmdStrings();
    void cmdRead();
    void cmdWrite();
    void cmdFlash();
    void cmdErase();
    void cmdDump(bool raw = false);
    void readFlashInChunks(uint32_t address, uint32_t length);
    void readFlashInChunksRaw(uint32_t address, uint32_t length);
    uint32_t readFlashCapacity();
    bool checkFlashPresent();
};
